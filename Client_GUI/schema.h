#pragma once
using namespace System;
public ref class schema
{
public:
	schema(String^ opt, Object^ data) :operation(opt), data(data) {};
	String^ operation;
	Object^ data;
};

public ref class schemaWithSession {
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
	signUpSchema(String^ username, String^ password, bool isPlayer) :username(username), password(password), isPlayer(isPlayer) {};
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

public ref class wordSchema {
public:
	wordSchema(String^ word, int level) :word(word), level(level) {};
	String^ word;
	int level;
};

public ref class getQuestionListSchema {
public:
	getQuestionListSchema(int level) :level(level) {};
	int level;
};

public ref  class UserSchema {
public:
	UserSchema(String^ username, int id, bool isPlayer, int count, int level) :name(username), id(id), isPlayer(isPlayer), count(count), level(level) {};
	String^ name;
	bool isPlayer = true;
	int count;
	int level;
	int id;
};

public ref class PlayerSchema : public UserSchema
{
public:
	PlayerSchema(String^ username, int id, int count, int level, int exp) :UserSchema(username, id, true, count, level), exp(exp) {};
	int exp = 0;
};

public ref class CommitterSchema :
	public UserSchema
{
public:
	CommitterSchema(String^ username, int id, int count, int level) :UserSchema(username, id, false, count, level) {};
};

template <typename T>
public ref class querySchema{
public:
	querySchema(String^ role, String^ property, T value) :role(role), property(property), value(value) {};
	String^ role;
	String^ property;
	T value;
};

public ref class updateUserSchema {
public:
	updateUserSchema(int count, int exp, int level) :count(count), exp(exp), level(level) {};
	int count;
	int exp;
	int level;
};


ref class CompareUser :System::Collections::Generic::Comparer<UserSchema^> {
public:
	virtual int Compare(UserSchema^ a, UserSchema^ b) override {
		return a->count > b->count;//count larger come first
	}
};