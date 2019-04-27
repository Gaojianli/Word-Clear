#include "pch.h"
#include "sql.h"
using namespace daotk;
using namespace mysql;

std::vector<User>* sql::fetchUsersByCondition() {
	std::vector<User>* toReturn = nullptr;
	_instance->con.query("select id,name,isPlayer,count,exp,level from user").each([&toReturn](int id, string name, bool isPlayer, int count, int exp, int level) {
		if (toReturn == nullptr)
			toReturn = new std::vector<User>();
		toReturn->push_back(User(name, id, isPlayer, count, exp, level));
		return true;
		});
	return toReturn;
}

User sql::fetchUserByPropertiesExtremum(std::string properties, bool highest, bool isPlayer) {
	//example: select id,name,isPlayer,count,exp,level from user where isPlayer=true order by exp DESC limit 1
	string sqlCommand = "select id,name,count,exp,level from user where %s=";
	sqlCommand.append(isPlayer ? "true " : "false ");
	sqlCommand.append("order by %s ");
	sqlCommand.append(highest ? "DESC " : "ASC ");
	sqlCommand.append(" limit 1");
	int id;
	string name;
	int count;
	int exp;
	int level;
	auto result = _instance->con.query(sqlCommand.c_str(), "isPlayer", properties.c_str());
	if (result.fetch(id, name, count, exp, level)) {
		return User(name, id, isPlayer, count, exp, level);
	}
	else
		return User("", -1);
}

bool sql::addWord(const char* word, int difficulty, int committerID) {
	//check for duplicate
	int committer = 1;
	auto result=_instance->con.query("select committer from question where word like '%s'", word);
	if (result.fetch(committer) || committer != -1)
		return false;
	else {
		_instance->con.exec("INSERT INTO question(word, level, committer) VALUES('%s', %d, %d)", word, difficulty, committerID);
		return true;
	}
}

User* sql::addUser(const std::string& username, const std::string& password, bool isPlayer) {
	_instance->con.exec("insert into user(name,password,isPlayer) values('%s','%s',%s)", username.c_str(), password.c_str(), isPlayer ? "true" : "false");
	return fetchUserByName(username);
}

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

bool sql::checkDuplicateUser(const std::string& username) {
	prepared_stmt stmt(_instance->con, "select id from user where name like ?");
	int id = -1;//invaild id
	stmt.bind_param(username);
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
User sql::fetchUserBySession(const std::string& session) {
	int id;
	std::string name;
	bool isPlayer;
	int count;
	int exp;
	int level;
	auto result = _instance->con.query("select id,name,isPlayer,count,exp,level from user where session like '%s'", session.c_str());
	if (result.fetch(id, name, isPlayer, count, exp, level)) {
		return User(name, id, isPlayer, count, exp, level);
	}
	else
		return User("", -1);
}
std::vector<Word>* sql::fetchQestion(const int difficulty) {
	std::vector<Word>* toReturn = nullptr;
	auto pushFunc = [&toReturn](std::string word, int level, int committer) {
		if (toReturn == nullptr)
			toReturn = new std::vector<Word>();
		toReturn->push_back(Word(word.c_str(), level, committer));
		return true;
	};
	string sqlCommand;
	if (difficulty < 0)
		sqlCommand = "select word,level,committer from question";
	else
		sqlCommand = "select word,level,committer from question where level=%d";
	_instance->con.query(sqlCommand.c_str(), difficulty).each(pushFunc);
	return toReturn;
}

