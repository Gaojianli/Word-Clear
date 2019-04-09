#include "pch.h"
#include "sql.h"


sql::sql(string connections) {
	char* zErrMsg = 0;
	int rc;
	rc = sqlite3_open(connections.c_str(), &db);
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
		free(data);
		return toReturn;
	}
}

static int getUserByName_callback(void* data, int argc, char** argv, char** azColName) {
	if (argc == 7) {
		if (!*(User **)data)
			if (string(argv[3])._Equal("true"))
				*(User **)data = new Player(argv[1], atoi(argv[0]), atoi(argv[4]), atoi(argv[6]), atoi(argv[5]));
			else
				*(User **)data = new Committer(argv[1], atoi(argv[0]), atoi(argv[4]), atoi(argv[6]));
	}
	return 0;
}
User* sql::getUserByName(string userName) {
	char* zErrMsg;
	User* data = nullptr;
	string sqlCommand = "select * from User where name like \"";
	sqlCommand.append(userName);
	sqlCommand.append("\"");
	auto rc = sqlite3_exec(_instance->db, sqlCommand.c_str(), getUserByName_callback, (void*)& data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(-1);
	}
	else {
		return data;
	}
}

User* sql::AddUser(string name, string password, bool isPlayer) {
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
