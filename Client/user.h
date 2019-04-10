#pragma once
class User
{
public:
	User(std::string username, int id) :name(username), id(id),count(0),level(1) {};
	User(std::string username, int id, bool isPlayer, int count, int level) :name(username), id(id), isPlayer(isPlayer), count(count), level(level) {};
	~User() = default;
	std::string name;
	virtual void showStat()=0;
	bool isPlayer = true;
	int count;
	int level;
	int id;
};
