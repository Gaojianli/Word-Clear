#pragma once
#include "user.h"
class Committer :
	public User
{
public:
	Committer(std::string name,int id);
	Committer(std::string username, int id, int count, int level);
	void commit();
	void showStat() override;
	static void showRank();
	~Committer();
};

