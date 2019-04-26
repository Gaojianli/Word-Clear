#pragma once
#ifndef socket_H
#define socket_H
using namespace System;
public ref class socketMgnt
{
public:
	static socketMgnt^ getInstance();
private:
	static socketMgnt^ _instance;
	System::Net::Sockets::Socket^ connection;
	socketMgnt();
};

#endif // !socket_H
