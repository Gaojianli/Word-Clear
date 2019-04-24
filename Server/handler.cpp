#include "pch.h"
#include "utils.h"
#include "sql.h"
#include "handler.h"
std::string handler::login(Document& dc) {
	auto data = dc.FindMember("data");
	if (data == dc.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	auto usernameItem = data->value.FindMember("username");
	auto passwordItem = data->value.FindMember("password");
	if (usernameItem == data->value.MemberEnd() || passwordItem == data->value.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	std::string username = usernameItem->value.GetString();
	std::string password = passwordItem->value.GetString();
	if (sql::queryPassword(username, password)) {
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
		return s.GetString();
	}
	else
		return utils::throwInfo("Invaild credential", 403);
}

std::string handler::sessionOperationRouter(Document& dc, string& operation) {
	auto user = std::make_shared<User>(std::move(sql::fetchUserBySession(dc["session"].GetString())));
	if (user == nullptr)
		return utils::throwInfo("Session invaild, please login again.", 419);
	else {
		if (operation._Equal("getQuestionList"))
			return getQuesiontList(dc);
		else if (operation._Equal("getUsers"))
			return getUsers("isPlayer", user->isPlayer);
		else if (operation._Equal("getAllUsers"))
			return getUsers(NULL);
		else if (operation._Equal("commit"))
			return commit(user, dc);
		else {
			return utils::throwInfo("Operation can't be recognized", 404);
		}
	}
}

std::string handler::getQuesiontList(Document& dc) {
	int difficulty = -1;
	auto data = dc.FindMember("data");
	//set difficutly
	if (data == dc.MemberEnd())
		difficulty = -1;//not set difficulty, return all questions
	else {
		auto level = data->value.FindMember("level");
		if (level == data->value.MemberEnd())
			difficulty = -1;
		else {
			difficulty = level->value.GetInt();
			if (difficulty > 10 || difficulty < 0)//invaild difficutly
				difficulty = -1;
		}
	}
	auto questionList = sql::fetchQestion(difficulty);
	StringBuffer s;
	Writer<StringBuffer, Document::EncodingType, ASCII<>> response(s);
	if (questionList) {
		if (questionList->size() > 0) {
			response.StartObject();
			response.Key("code");
			response.Int(200);
			response.Key("data");
			//start data object
			response.StartObject();
			response.Key("Words");
			response.StartArray();
			std::for_each(questionList->begin(), questionList->end(), [&response](Word & item) {
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
		else {
			delete questionList;
			return utils::throwInfo("Not found", 404);
		}
	}
	else
		return utils::throwInfo("Not found", 404);
}

template<typename ...T>//we don't need overload function!
std::string handler::getUsers(const char* condition, T ...args) {
	std::vector<User>* result;
	if constexpr (sizeof...(args) == 0)
		result = sql::fetchUsersByCondition();
	else
		//expand the args pack
		int temp[] = { (result = sql::fetchUsersByCondition(condition, args), 0)... };
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
		if (result->size() > 0) {
			std::for_each(result->begin(), result->end(), [&response](User & item) {
				response.StartObject();
				response.Key("id");
				response.Int(item.id);
				response.Key("name");
				response.String(item.name.c_str());
				response.Key("isPlayer");
				response.Bool(item.isPlayer);
				response.Key("count");
				response.Int(item.count);
				if (item.isPlayer) {
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

template<typename user_ptr>
std::string handler::commit(user_ptr user, Document& dc) {
	if (user->isPlayer)
		return utils::throwInfo("Only committer can commit a word!", 403);
	auto data = dc.FindMember("data");
	if (data == dc.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	auto wordDC = data->value.FindMember("word");
	auto difficultyDC = data->value.FindMember("difficulty");
	if(wordDC==data->value.MemberEnd()||difficultyDC==data->value.MemberEnd())
		return utils::throwInfo("Not acceptable!", 406);
	auto word = wordDC->value.GetString();
	auto difficulty = difficultyDC->value.GetInt();
	sql::addWord(word, difficulty, user->id);
	return utils::throwInfo("Created", 201);
}
