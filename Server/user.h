#pragma once
class User
{
public:
	User(std::string username, int id) :name(username), id(id),count(0),level(1) {};
	User(std::string username, int id, bool isPlayer, int count, int exp, int level) :name(username), id(id), isPlayer(isPlayer), count(count), level(level), exp(exp) {};
	~User() = default;
	std::string name;
	bool isPlayer = true;
	int count;
	int level;
	int id;
	int exp = 0;
};

enum class property {
	id,
	name,
	count,
	level,
	exp
};