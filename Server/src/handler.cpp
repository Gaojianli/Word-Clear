#include "../include/pch.h"
#include "../include/utils.h"
#include "../include/sql.h"
#include "../include/handler.h"
std::string handler::login(Document &dc)
{
	auto data = dc.FindMember("data");
	if (data == dc.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	auto usernameItem = data->value.FindMember("username");
	auto passwordItem = data->value.FindMember("password");
	if (usernameItem == data->value.MemberEnd() || passwordItem == data->value.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	std::string username = usernameItem->value.GetString();
	std::string password = passwordItem->value.GetString();
	if (sql::queryPassword(username, password))
	{
		auto user = sql::fetchUserByName(username);
		auto session = MD5(username + password + std::to_string(time(nullptr))).toStr();
		StringBuffer s;
		Writer<StringBuffer, Document::EncodingType, ASCII<>> response(s);
		response.StartObject();
		response.Key("code");
		response.Int(200);
		response.Key("data");
		//start data object
		response.StartObject();
		response.Key("id");
		response.Int(user->id);
		response.Key("username");
		response.String(username.c_str());
		response.Key("session");
		response.String(session.c_str());
		response.Key("isPlayer");
		response.Bool(user->isPlayer);
		response.Key("count");
		response.Int(user->count);
		response.Key("exp");
		response.Int(user->exp);
		response.Key("level");
		response.Int(user->level);
		response.EndObject();
		response.EndObject();
		sql::updateSession(session, user->id);
		delete user;
#ifdef DEBUG
		cout << s.GetString() << endl;
#endif // DEBUG
		return s.GetString();
	}
	else
		return utils::throwInfo("Invaild credential", 403);
}

std::string handler::signUP(Document &dc)
{
	auto data = dc.FindMember("data");
	if (data == dc.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	auto usernameItem = data->value.FindMember("username");
	auto passwordItem = data->value.FindMember("password");
	auto isPlayerDC = data->value.FindMember("isPlayer");
	if (usernameItem == data->value.MemberEnd() || passwordItem == data->value.MemberEnd() || isPlayerDC == data->value.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	if (sql::checkDuplicateUser(usernameItem->value.GetString()))
		return utils::throwInfo("User existed!", 401);
	auto password = passwordItem->value.GetString();
	auto username = usernameItem->value.GetString();
	auto user = sql::addUser(username, password, isPlayerDC->value.GetBool());
	auto session = std::move(MD5(user->name + password + std::to_string(time(nullptr))).toStr());
	StringBuffer s;
	Writer<StringBuffer, Document::EncodingType, ASCII<>> response(s);
	response.StartObject();
	response.Key("code");
	response.Int(200);
	response.Key("data");
	//start data object
	response.StartObject();
	response.Key("id");
	response.Int(user->id);
	response.Key("username");
	response.String(username);
	response.Key("session");
	response.String(session.c_str());
	response.Key("isPlayer");
	response.Bool(user->isPlayer);
	response.Key("count");
	response.Int(user->count);
	response.Key("exp");
	response.Int(user->exp);
	response.Key("level");
	response.Int(user->level);
	response.EndObject();
	response.EndObject();
	sql::updateSession(session, user->id);
	delete user;
#ifdef DEBUG
	cout << s.GetString() << endl;
#endif // DEBUG
	return s.GetString();
}

std::string handler::mainHandler(const char *stream, uvw::TCPHandle &client)
{
	string response;
	Document dc;
	try
	{
		if (dc.Parse(stream).HasParseError() || !dc.IsObject())
			response = utils::throwInfo("Invaild JSON data", 406);
		else if (dc.HasMember("operation"))
		{
			string operation = dc["operation"].GetString();
			if (operation == "close")
			{ //close connection
				client.close();
				return "";
			}
			else if (operation == "login")
			{
				response = handler::login(dc);
			}
			else if (operation == "register")
			{
				response = handler::signUP(dc);
			}
			else if (dc.HasMember("session"))
			{
				response = handler::sessionOperationRouter(dc, operation);
			}
			else
			{
				response = utils::throwInfo("Forbidden", 403);
			}
		}
		else
			response = utils::throwInfo("Invaild operation", 406);
	}
	catch (std::string &msg)
	{
		response = utils::throwInfo(msg, 500);
	}
	catch (const char *msg)
	{
		response = utils::throwInfo(msg, 500);
	}
	catch (...)
	{
		response = utils::throwInfo("Unknown internal server error.", 500);
	}
	return response;
}

std::string handler::sessionOperationRouter(Document &dc, string &operation)
{
	auto user = std::make_shared<User>(std::move(sql::fetchUserBySession(dc["session"].GetString())));
	if (user == nullptr || user->id == -1)
		return utils::throwInfo("Session invaild, please login again.", 419);
	else
	{
		if (operation == "getQuestionList")
			return getQuestiontList(dc);
		else if (operation == "getSameUsers")
			return getUsers("isPlayer", user->isPlayer);
		else if (operation == "getDifferentUsers")
			return getUsers("isPlayer", !user->isPlayer);
		else if (operation == "getAllUsers")
			return getUsers(NULL);
		else if (operation == "commit")
			return commit(user, dc);
		else if (operation == "updateUser")
			return updateUser(user, dc);
		else if (operation == "fetchExtremum")
			return fetchExtremum(user, dc);
		else if (operation == "getUsersByCondition")
			return fetchUsersByCondition(user, dc);
		else if (operation == "getQuestionListWithCommitter")
			return getQuestionListWithCommitter(dc);
		else
		{
			return utils::throwInfo("Operation can't be recognized", 404);
		}
	}
}

std::string handler::getQuestiontList(Document &dc)
{
	int difficulty = -1;
	auto data = dc.FindMember("data");
	//set difficutly
	if (data == dc.MemberEnd())
		difficulty = -1; //not set difficulty, return all questions
	else
	{
		auto level = data->value.FindMember("level");
		if (level == data->value.MemberEnd())
			difficulty = -1;
		else
		{
			difficulty = level->value.GetInt();
			if (difficulty > 10 || difficulty < 0) //invaild difficutly
				difficulty = -1;
		}
	}
	auto questionList = sql::fetchQestion(difficulty);
	StringBuffer s;
	Writer<StringBuffer, Document::EncodingType, ASCII<>> response(s);
	if (questionList)
	{
		if (questionList->size() > 0)
		{
			response.StartObject();
			response.Key("code");
			response.Int(200);
			response.Key("data");
			//start data object
			response.StartObject();
			response.Key("Words");
			response.StartArray();
			std::for_each(questionList->begin(), questionList->end(), [&response](Word &item) {
				response.StartObject();
				response.Key("Word");
				response.String(item.str.c_str());
				response.Key("level");
				response.Int(item.level);
				response.EndObject();
			});
			response.EndArray();
			response.EndObject();
			response.EndObject();
			delete questionList;
			return s.GetString();
		}
		else
		{
			delete questionList;
			return utils::throwInfo("Not found", 404);
		}
	}
	else
		return utils::throwInfo("Not found", 404);
}
template <typename user_ptr>
std::string handler::fetchUsersByCondition(user_ptr user, Document &dc)
{
	auto data = dc.FindMember("data");
	if (data == dc.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	auto roleDC = data->value.FindMember("role");
	auto propertyDC = data->value.FindMember("property");
	auto valueDC = data->value.FindMember("value");
	if (propertyDC == data->value.MemberEnd() || valueDC == data->value.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	bool isPlayer_request; //role
	if (roleDC == data->value.MemberEnd())
		isPlayer_request = user->isPlayer;
	else
	{
		string role = roleDC->value.GetString();
		if (role == "player")
			isPlayer_request = true;
		else if (role == "committer")
			isPlayer_request = false;
		else
			isPlayer_request = user->isPlayer;
	}
	std::vector<User> *result = nullptr;
	string propertyToQuery = propertyDC->value.GetString();
	if (propertyToQuery == "name")
		result = sql::fetchUsersByCondition(propertyToQuery, valueDC->value.GetString());
	else if (propertyToQuery == "count" || propertyToQuery == "level" || propertyToQuery == "id")
		result = sql::fetchUsersByCondition(propertyToQuery, valueDC->value.GetInt());
	else if (propertyToQuery == "exp")
	{ //committer don't have exp
		if (isPlayer_request)
			result = sql::fetchUsersByCondition(propertyToQuery, valueDC->value.GetInt());
		else
			return utils::throwInfo("Invaild Property!", 406);
	}
	else
		return utils::throwInfo("Invaild Property!", 406);
	StringBuffer s;
	Writer<StringBuffer, Document::EncodingType, ASCII<>> response(s);
	response.StartObject();
	response.Key("code");
	response.Int(200);
	response.Key("data");
	response.StartObject();
	response.Key("Users");
	response.StartArray();
	if (result != nullptr)
		if (result->size() > 0)
		{
			std::for_each(result->begin(), result->end(), [&response, isPlayer_request](User &item) {
				if (item.isPlayer == isPlayer_request)
				{
					response.StartObject();
					response.Key("id");
					response.Int(item.id);
					response.Key("name");
					response.String(item.name.c_str());
					response.Key("isPlayer");
					response.Bool(item.isPlayer);
					response.Key("count");
					response.Int(item.count);
					if (item.isPlayer)
					{
						response.Key("exp");
						response.Int(item.exp);
					}
					response.Key("level");
					response.Int(item.level);
					response.EndObject();
				}
			});
		}
	response.EndArray();
	response.EndObject();
	response.EndObject();
	delete result;
	return s.GetString();
}

template <typename user_ptr>
std::string handler::fetchExtremum(user_ptr user, Document &dc)
{
	auto data = dc.FindMember("data");
	if (data == dc.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	auto roleDC = data->value.FindMember("role");
	auto propertiesDC = data->value.FindMember("property");
	auto typeDC = data->value.FindMember("type");
	if (typeDC == data->value.MemberEnd() || propertiesDC == data->value.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	string type = typeDC->value.GetString();
	bool highestFlag;
	if (type == "highest")
		highestFlag = true;
	else if (type == "lowest")
		highestFlag = false;
	else
		return utils::throwInfo("Unrecognizable type!", 406);
	bool isPlayer; //role
	if (roleDC == data->value.MemberEnd())
		isPlayer = user->isPlayer;
	else
	{
		string role = roleDC->value.GetString();
		if (role == "player")
			isPlayer = true;
		else if (role == "committer")
			isPlayer = false;
		else
			isPlayer = user->isPlayer;
	}
	auto &&fetchResult = sql::fetchUserByPropertiesExtremum(propertiesDC->value.GetString(), highestFlag, isPlayer);
	if (fetchResult.id == -1)
		return utils::throwInfo("Not found", 404);
	StringBuffer s;
	Writer<StringBuffer, Document::EncodingType, ASCII<>> response(s);
	response.StartObject();
	response.Key("code");
	response.Int(200);
	response.Key("data");
	response.StartObject();
	response.Key("id");
	response.Int(fetchResult.id);
	response.Key("name");
	response.String(fetchResult.name.c_str(), fetchResult.name.size(), false);
	response.Key("isPlayer");
	response.Bool(fetchResult.isPlayer);
	response.Key("count");
	response.Int(fetchResult.count);
	if (fetchResult.isPlayer)
	{
		response.Key("exp");
		response.Int(fetchResult.exp);
	}
	response.Key("level");
	response.Int(fetchResult.level);
	response.EndObject();
	response.EndObject();
	return s.GetString();
}

template <typename... T> //we don't need overload function!
std::string handler::getUsers(const char *condition, T... args)
{
	std::vector<User> *result;
	if constexpr (sizeof...(args) == 0)
		result = sql::fetchUsersByCondition();
	else
		//expand the args pack
		int temp[] = {(result = sql::fetchUsersByCondition(condition, args), 0)...};
	StringBuffer s;
	Writer<StringBuffer, Document::EncodingType, ASCII<>> response(s);
	response.StartObject();
	response.Key("code");
	response.Int(200);
	response.Key("data");
	response.StartObject();
	response.Key("Users");
	response.StartArray();
	if (result != nullptr)
		if (result->size() > 0)
		{
			std::for_each(result->begin(), result->end(), [&response](User &item) {
				response.StartObject();
				response.Key("id");
				response.Int(item.id);
				response.Key("name");
				response.String(item.name.c_str());
				response.Key("isPlayer");
				response.Bool(item.isPlayer);
				response.Key("count");
				response.Int(item.count);
				if (item.isPlayer)
				{
					response.Key("exp");
					response.Int(item.exp);
				}
				response.Key("level");
				response.Int(item.level);
				response.EndObject();
			});
		}
	response.EndArray();
	response.EndObject();
	response.EndObject();
	delete result;
	return s.GetString();
}

template <typename user_ptr>
std::string handler::commit(user_ptr user, Document &dc)
{
	if (user->isPlayer)
		return utils::throwInfo("Only committer can commit a word!", 403);
	auto data = dc.FindMember("data");
	if (data == dc.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	auto wordDC = data->value.FindMember("word");
	auto difficultyDC = data->value.FindMember("difficulty");
	if (wordDC == data->value.MemberEnd() || difficultyDC == data->value.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	const char *word;
	int difficulty;
	try
	{
		word = wordDC->value.GetString();
		difficulty = difficultyDC->value.GetInt();
	}
	catch (...)
	{
		return utils::throwInfo("Not acceptable!", 406);
	}
	if (sql::addWord(word, difficulty, user->id))
	{
		sql::updateUserOneCol("count", user->count + 1, user->id);
		if (++user->count / 10 > user->level)
			sql::updateUserOneCol("level", user->level + 1, user->id);
		return utils::throwInfo("Created", 201);
	}
	else
		return utils::throwInfo("Word existed!", 202);
}

//One can only update himself
template <typename user_ptr>
std::string handler::updateUser(user_ptr user, Document &dc)
{
	auto data = dc.FindMember("data");
	if (data == dc.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	//only these properties can be updated
	auto countDC = data->value.FindMember("count");
	if (countDC != data->value.MemberEnd())
		sql::updateUserOneCol("count", countDC->value.GetInt(), user->id);
	auto expDC = data->value.FindMember("exp");
	if (expDC != data->value.MemberEnd())
		sql::updateUserOneCol("exp", expDC->value.GetInt(), user->id);
	if (auto exp = expDC->value.GetInt(); exp >= (user->level - 1) * 100)
		sql::updateUserOneCol("level", exp / 100 + 1, user->id);
	return utils::throwInfo("Accepted", 202);
}

std::string handler::getQuestionListWithCommitter(Document &dc)
{
	auto questionList = sql::fetchQestionWithName();
	StringBuffer s;
	Writer<StringBuffer, Document::EncodingType, ASCII<>> response(s);
	if (questionList)
	{
		if (questionList->size() > 0)
		{
			response.StartObject();
			response.Key("code");
			response.Int(200);
			response.Key("data");
			//start data object
			response.StartObject();
			response.Key("Words");
			response.StartArray();
			std::for_each(questionList->begin(), questionList->end(), [&response](WordWithCommitter &item) {
				response.StartObject();
				response.Key("Word");
				response.String(item.str.c_str());
				response.Key("level");
				response.Int(item.level);
				response.Key("committer");
				response.String(item.committerUserName.c_str());
				response.EndObject();
			});
			response.EndArray();
			response.EndObject();
			response.EndObject();
			delete questionList;
			return s.GetString();
		}
		else
		{
			delete questionList;
			return utils::throwInfo("Not found", 404);
		}
	}
	else
		return utils::throwInfo("Not found", 404);
}