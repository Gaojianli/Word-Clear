#pragma once
#ifndef socket_H
#define socket_H
#include "Player.h"
#include "schema.h"
#include "Committer.h"
using namespace System;
using namespace System::Collections::Generic;
public ref class socketMgnt
{
public:
	static socketMgnt^ getInstance();
	User^ login(String^ username, String^ password);
	User^ signup(String^ username, String^ password, bool isPlayer);
	bool commit(String^ word, int difficulty, User^ committer);
	//get the users which have the same role
	List<UserSchema^>^ getSameUser(User^ user);
	List<UserSchema^>^ getDifferentUser(User^ user);
private:
	static socketMgnt^ _instance;
	String^ sendAndRec(String^ toSend);
	System::Net::Sockets::Socket^ connection;
	socketMgnt();
};

#endif // !socket_H
