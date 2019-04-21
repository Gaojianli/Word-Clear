#pragma once
using namespace daotk;
using namespace mysql;
class sql
{
public:
	~sql();
	static void init();
	static void close();
	static bool queryPassword(std::string username, std::string password);
private:
	sql();
	static sql* _instance;
	connection con;
};

