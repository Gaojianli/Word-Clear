#pragma once
#include "user.h"
class Player : public User
{
public:
	Player(std::string name,int id);
	Player(std::string username, int id, int count, int level,int exp);
	int exp;
	void startGame(std::vector<Word>* questionList);
	static void showRank();
	void showStat() override;
	~Player();
};

