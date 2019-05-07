#pragma once
#include "user.h"
public ref class Committer :
	public User
{
public:
	Committer(String^ username, int id, String^ session, int count, int level) :User(username, id, session, false, count, level) {};
};

