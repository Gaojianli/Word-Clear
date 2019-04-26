#pragma once
#include "user.h"
public ref class Committer :
	public User
{
public:
	Committer(String name,int id);
	Committer(String username, int id, int count, int level);
	~Committer();
};

