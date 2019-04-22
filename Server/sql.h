#pragma once

class sql
{
public:
	static void init();
	static void close();
	static User* fetchUserByName(const std::string name);
	static bool queryPassword(const std::string username,const std::string password);
	template<typename T>
	static void updateUserOneCol(const char* column,const T& toUpdate, int id);
	static void updateSession(std::string session, int id);
private:
	sql();
	~sql();
	static sql* _instance;
	daotk::mysql::connection con;
};
