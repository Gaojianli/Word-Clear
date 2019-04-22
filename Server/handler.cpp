#include "pch.h"
#include "schema.h"
#include "handler.h"
#include "sql.h"
std::string handler::login(Document& dc) {
	auto data = dc.FindMember("data");
	if (data == dc.MemberEnd())
		return schema::throwError("Bad request!", 400);
	auto usernameItem = data->value.FindMember("username");
	auto passwordItem = data->value.FindMember("password");
	if (usernameItem == data->value.MemberEnd() || passwordItem == data->value.MemberEnd())
		return schema::throwError("Bad request!", 400);
	std::string username = usernameItem->value.GetString();
	std::string password = passwordItem->value.GetString();
	if (sql::queryPassword(username, password)) {
		auto user = sql::fetchUserByName(username);
		auto session = username + password + std::to_string(time(nullptr));
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
		return schema::throwError("Invaild credential", 403);
}
