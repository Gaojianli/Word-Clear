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