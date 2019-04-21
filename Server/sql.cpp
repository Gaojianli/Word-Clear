#include "pch.h"
#include "sql.h"
#pragma comment(lib,"libmysql.lib")

sql::sql() {
	con.open({ "localhost","wordclear","lazybones+each","word_clear_game" });
	if (!con) {
		std::cout << "Connection failed" << std::endl;
		return;
	}
	std::cout << "Connect to database successfully!" << std::endl;
}

sql::~sql() {
	if (con.is_open())
		con.close();
	delete _instance;
}

sql* sql::_instance = nullptr;

void sql::init() {
	if (!_instance)
		_instance = new sql();
}

void sql::close() {
	_instance->con.close();
	delete _instance;
}

bool sql::queryPassword(std::string username, std::string password) {
	prepared_stmt stmt(_instance->con, "select id from user where name like ? and password like ?");
	int id = -1;//invaild id
	stmt.bind_param(username, password);
	stmt.bind_result(id);//if user existed, the id will be override
	stmt.execute();
	if (stmt.fetch() && id != -1)
		return true;
	else
		return false;
}