#pragma once
#include "user.h"
public ref class Player : public User
{
public:
	Player(String^ username, int id, String^ session, int count, int level, int exp) :User(username, id, session, true, count, level), exp(exp) {};
	int exp = 0;
	inline void addCount() {
		count++;
		exp += 10;
		if (exp / 100 > level)
			level++;
	}
};

