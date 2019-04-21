#include "pch.h"
#include "sql.h"
#pragma comment(lib, "sqlite3.lib")


sql::sql(string connections) {
	char* zErrMsg = 0;
	int rc;
	rc = sqlite3_open(connections.c_str(), &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(-1);
	}
	//create table user
	rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS user(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, name STRING UNIQUE NOT NULL, password STRING NOT NULL, isPlayer BOOLEAN NOT NULL DEFAULT true, count INTEGER DEFAULT (0), exp INTEGER DEFAULT (0), level INTEGER DEFAULT (1) NOT NULL)", nullptr, nullptr, &zErrMsg);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(-1);
	}
	//create table question
	rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS question (word STRING UNIQUE NOT NULL PRIMARY KEY, level INTEGER NOT NULL, committer INTEGER NOT NULL REFERENCES user (id) ON DELETE CASCADE)", nullptr, nullptr, &zErrMsg);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(-1);
	}
}
sql* sql::_instance = nullptr;
sql::~sql() {
	sqlite3_close(db);
	free(_instance);
}

void sql::init(string dbConnection) {
	if (!_instance)
		_instance = new sql(dbConnection);
}

//getQuestion
static int getQuestion_callback(void* data, int argc, char** argv, char** azColName) {
	if (argc == 3) {
		((vector<Word>*)data)->push_back(Word(argv[0], atoi(argv[1]), atoi(argv[2])));
		return 0;
	}
	else
		return 0;
}
vector<Word>* sql::getQuestions() {
	auto toReturn = new vector<Word>();
	char* zErrMsg;
	auto rc = sqlite3_exec(_instance->db, "select * from question", getQuestion_callback, (void*)toReturn, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}
	else {
		return toReturn;
	}
}

//queryPassword
static int queryPassword_callback(void* data, int argc, char** argv, char** azColName) {
	if (argc == 0)
		* ((bool*)data) = false;
	else
		*((bool*)data) = true;
	return 0;
}
bool sql::queryPassword(string username, string password) {
	char* zErrMsg;
	bool* data = new bool();
	string sqlCommand = "select * from User where name like \"";
	sqlCommand.append(username);
	sqlCommand.append("\" and password like \"");
	sqlCommand.append(password);
	sqlCommand.append("\"");
	auto rc = sqlite3_exec(_instance->db, sqlCommand.c_str(), queryPassword_callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}
	else {
		bool toReturn = *data;
		delete data;
		return toReturn;
	}
}

static int getSingleUser_callback(void* data, int argc, char** argv, char** azColName) {
	if (argc == 7) {
		if (!*(User * *)data)
			if (string(argv[3])._Equal("true"))
				* (User * *)data = new Player(argv[1], atoi(argv[0]), atoi(argv[4]), atoi(argv[6]), atoi(argv[5]));
			else
				*(User * *)data = new Committer(argv[1], atoi(argv[0]), atoi(argv[4]), atoi(argv[6]));
	}
	return 0;
}
User* sql::getUserByName(string userName) {
	char* zErrMsg;
	User* data = nullptr;
	string sqlCommand = "select * from User where name like \"";
	sqlCommand.append(userName);
	sqlCommand.append("\"");
	auto rc = sqlite3_exec(_instance->db, sqlCommand.c_str(), getSingleUser_callback, (void*)& data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}
	else {
		return data;
	}
}

User* sql::addUser(string name, string password, bool isPlayer) {
	char* zErrMsg;
	string sqlCommand = "insert into user (name,password,isPlayer) values(\"";
	sqlCommand.append(name);
	sqlCommand.append("\",\"");
	sqlCommand.append(password);
	sqlCommand.append("\",");
	sqlCommand.append(isPlayer ? "\"true\"" : "\"false\"");
	sqlCommand.append(");");
	auto rc = sqlite3_exec(_instance->db, sqlCommand.c_str(), nullptr, nullptr, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}
	else {
		return sql::getUserByName(name);
	}
}

static int getUsers_callback(void* data, int argc, char** argv, char** azColName) {
	if (argc == 7)
		if (string(argv[3])._Equal("true"))
			((vector<User*>*)data)->push_back(new Player(argv[1], atoi(argv[0]), atoi(argv[4]), atoi(argv[6]), atoi(argv[5])));
		else
			((vector<User*>*)data)->push_back(new Committer(argv[1], atoi(argv[0]), atoi(argv[4]), atoi(argv[6])));
	return 0;
}
vector<User*>* sql::getAllUsers() {
	auto toReturn = new vector<User*>();
	char* zErrMsg;
	auto rc = sqlite3_exec(_instance->db, "select * from user", getUsers_callback, (void*)toReturn, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}
	else {
		return toReturn;
	}
}

void sql::addWord(string word, int level, int committerID) {
	char* zErrMsg;
	string sqlCommand = "insert into question (word,level,committer) values(\"";
	sqlCommand.append(word);
	sqlCommand.append("\",");
	sqlCommand.append(to_string(level));
	sqlCommand.append(",");
	sqlCommand.append(to_string(committerID));
	sqlCommand.append(")");
	auto rc = sqlite3_exec(_instance->db, sqlCommand.c_str(), nullptr, nullptr, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}
}

void sql::updateUser(User * const toUpdate) {
	string sqlCommand = "update user set ";
	sqlCommand.append("count = ");
	sqlCommand.append(to_string(toUpdate->count));
	sqlCommand.append(", level= ");
	sqlCommand.append(to_string(toUpdate->level));
	if (toUpdate->isPlayer) {
		sqlCommand.append(",exp=");
		sqlCommand.append(to_string(static_cast<Player*>(toUpdate)->exp));
	}
	sqlCommand.append(" where id=");
	sqlCommand.append(to_string(toUpdate->id));
	char* zErrMsg;
	auto rc = sqlite3_exec(_instance->db, sqlCommand.c_str(), nullptr, nullptr, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}
}


vector<User*>* sql::fetchByCondition(property pro, string value, bool isPlayer) {
	auto toReturn = new vector<User*>();
	char* zErrMsg;
	string sqlCommand = "select * from user where isPlayer like \"";
	sqlCommand.append(isPlayer ? "true" : "false");
	sqlCommand.append("\" and ");
	string types[] = { "id","name","count","level","exp" };
	string proStr = types[static_cast<int>(pro)];
	sqlCommand.append(proStr);
	sqlCommand.append(" like \"");
	sqlCommand.append(value);
	sqlCommand.append("\"");
	auto rc = sqlite3_exec(_instance->db, sqlCommand.c_str(), getUsers_callback, (void*)toReturn, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}
	else {
		return toReturn;
	}
}

User* sql::getHighest(property pro, bool high, bool isPlayer) {
	User* data = nullptr;
	char* zErrMsg;
	string sqlCommand = "select * from User where isPlayer like \""; 
	sqlCommand.append(isPlayer ? "true" : "false");
	sqlCommand.append("\" order by ");
	string types[] = { "id","name","count","level","exp" };
	string proStr = types[static_cast<int>(pro)];
	sqlCommand.append(proStr);
	sqlCommand.append(high ? " DESC" : " ASC");
	sqlCommand.append(" limit 1");
	auto rc = sqlite3_exec(_instance->db, sqlCommand.c_str(), getSingleUser_callback, (void*)& data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}
	else {
		return data;
	}
}

