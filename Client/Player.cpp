#include "pch.h"
#include "Player.h"

Player::Player(std::string name, int id) :User(name, id) {
	isPlayer = true;
	exp = 0;
}


Player::~Player() {
}


Player::Player(std::string username, int id, int count, int level, int exp) :User(username, id, true, count, level), exp(exp) {
};