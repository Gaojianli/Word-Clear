#pragma once
using namespace System;
public ref  class User
{
public:
	User(String^ username, int id, String^ session, bool isPlayer, int count, int level) :name(username), id(id), isPlayer(isPlayer), count(count), level(level), session(session) {};
	String^ name;
	String^ session;
	bool isPlayer = true;
	int count;
	int level;
	int id;
};

