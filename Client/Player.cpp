#include "pch.h"
#include "Player.h"
#include "sql.h"
using namespace std;
Player::Player(std::string name, int id) :User(name, id) {
	isPlayer = true;
	exp = 0;
}


Player::~Player() {
}


Player::Player(std::string username, int id, int count, int level, int exp) :User(username, id, true, count, level), exp(exp) {
}
void Player::startGame() {

}
void Player::showRank() {
	auto playerList = sql::getAllUsers();
	sort(playerList->begin(), playerList->end(), [](User * a, User * b)->bool {
		return static_cast<Player*>(a)->exp > static_cast<Player*>(b)->exp;//sort by exp
	});
	cout << "Name\tLevel\tPassed Ranks\tExp" << endl;
	for_each(playerList->begin(), playerList->end(), [](User * item)->void {
		if (item->isPlayer)
			cout << item->name << "\t" << item->level << "\t" << item->count << "\t\t" << static_cast<Player*>(item)->exp << endl;
	});
	cout << endl;
}
void Player::showStat() {
	cout << "UID\tName\t\tLevel\tPassed Ranks\tExp" << endl;
	cout << id << "\t" << name << "\t\t" << level << "\t\t" << count << "\t" << exp << endl;
}
;