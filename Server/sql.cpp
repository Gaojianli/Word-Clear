#include "pch.h"
#include "sql.h"
using namespace daotk;
using namespace mysql;

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

bool sql::queryPassword(const std::string username, const std::string password) {
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

User* sql::fetchUserByName(const std::string name) {
	int id;
	bool isPlayer;
	int count;
	int exp;
	int level;
	auto result = _instance->con.query("select id,isPlayer,count,exp,level from user where name like '%s'", name.c_str());
	if (result.fetch(id, isPlayer, count, exp, level)) {
		return new User(name, id, isPlayer, count, exp, level);
	}
	else
		return nullptr;
}

void sql::updateSession(std::string session, int id) {
	updateUserOneCol("session", session, id);
}
template<typename T>
void sql::updateUserOneCol(const char* column, const T& toUpdate, int id) {
	std::string sqlCommand = "update user set %s = ";
	sqlCommand += toUpdate;
	sqlCommand.append(" where id=%d");
	std::cout << sqlCommand;
	//_instance->con.exec(sqlCommand.c_str(), column, id);
}
