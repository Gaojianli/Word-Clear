#pragma once
using namespace System;
public ref class schema
{
public:
	schema(String ^opt,Object^ data) :operation(opt), data(data) {};
	String^ operation;
	Object^ data;
};

public ref class schemaWithSession{
public:
	schemaWithSession(String^ opt, String^ session, Object^ data) :operation(opt), session(session), data(data) {};
	String^ operation;
	String^ session;
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
public ref class commitSchema {
public:
	commitSchema(String^ word, int difficulty) :word(word), difficulty(difficulty) {};
	String^ word;
	int difficulty;
};