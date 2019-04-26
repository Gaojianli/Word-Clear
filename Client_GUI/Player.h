#pragma once
#include "user.h"
public ref class Player : public User
{
public:
	Player(String^ name,int id);
	Player(String^username, int id, int count, int level,int exp);
	int exp;
	~Player();
};

