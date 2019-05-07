#pragma once
class User
{
public:
	User(std::string username, int id) :name(username), id(id),count(0),level(1),exp(0) {};
	User(std::string username, int id, bool isPlayer, int count, int exp, int level) :name(username), id(id), isPlayer(isPlayer), count(count), level(level), exp(exp) {};
	User(User&& m) :name(std::move(m.name)), id(m.id), isPlayer(m.isPlayer), count(m.count), level(m.level), exp(m.exp) {};
	~User() = default;
	std::string name;
	bool isPlayer = true;
	int count;
	int level;
	int id;
	int exp;
};

enum class property {
	id,
	name,
	count,
	level,
	exp
};
