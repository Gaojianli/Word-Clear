#pragma once
#ifndef socket_H
#define socket_H
#include "Player.h"
#include "Committer.h"
using namespace System;
public ref class socketMgnt
{
public:
	static socketMgnt^ getInstance();
	User^ login(String^ username, String^ password);
	User^ signup(String^ username, String^ password, bool isPlayer);
	bool commit(String^ word, int difficulty, User^ committer);
private:
	static socketMgnt^ _instance;
	String^ sendAndRec(String^ toSend);
	System::Net::Sockets::Socket^ connection;
	socketMgnt();
};

#endif // !socket_H
