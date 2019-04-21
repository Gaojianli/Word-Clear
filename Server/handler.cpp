#include "pch.h"
#include "handler.h"
#include "schema.h"
#include "sql.h"

std::string handler::login(Document& dc) {
	auto data = dc.FindMember("data");
	if (data == dc.MemberEnd())
		return schema::throwError("Bad request!", 400);
	auto usernameItem = data->value.FindMember("username");
	auto passwordItem = data->value.FindMember("password");
	if (usernameItem == data->value.MemberEnd() || passwordItem == data->value.MemberEnd())
		return schema::throwError("Bad request!", 400);
	auto username = usernameItem->value.GetString();
	auto password = passwordItem->value.GetString();
	if (sql::queryPassword(username, password)) {
		return "login success";
	}
	else
		return schema::throwError("Invaild credential", 403);
}
