#pragma once
using namespace System;
public ref class schema
{
public:
	schema(String ^opt,Object^ data) :operation(opt), data(data) {};
	String^ operation;
	Object^ data;
};

public ref class loginSchema {
public:
	loginSchema(String^ username, String^ password) :username(username), password(password) {};
	String^ username;
	String^ password;
};
public ref class signUpSchema {
public:
	signUpSchema(String^ username, String^ password, bool isPlayer) :username(username), password(password), isPlayer(isPlayer){};
	String^ username;
	String^ password;
	bool isPlayer;
 };