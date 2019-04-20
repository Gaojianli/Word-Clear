#include "pch.h"
#include "handler.h"
#include "schema.h"

std::string handler::login(Document& dc) {
	auto data = dc.FindMember("data");
	if (data == dc.MemberEnd())
		return schema::throwError("Bad request!", 400);
	auto usernameItem = data->value.FindMember("usernameItem");
	auto passwordItem = data->value.FindMember("passwordItem");
	if (usernameItem == data->value.MemberEnd() || passwordItem == data->value.MemberEnd())
		return schema::throwError("Bad request!", 400);
	auto username = usernameItem->value.GetString();
	auto password = usernameItem->value.GetString();
	std::cout << "Username:" << usernameItem->value.GetString() << std::endl << "password:" << passwordItem->value.GetString() << std::endl;

}
