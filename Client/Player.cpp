#include "pch.h"
#include "Player.h"
#include "sql.h"
using namespace std;
#pragma comment(lib, "pdcurses.lib")

Player::Player(std::string name, int id) :User(name, id) {
	isPlayer = true;
	exp = 0;
}

Player::~Player() {
}

Player::Player(std::string username, int id, int count, int level, int exp) :User(username, id, true, count, level), exp(exp) {
}
void Player::startGame(vector<Word>* questionList) {
	initscr();
	raw();
	noecho();
	int currentLevel = 1;
	bool finishFlag = false;//finsih all question flag
	//draw the border
	attrset(A_REVERSE);
	for (int i = 0; i < COLS; ++i)
		mvaddch(0, i, ' ');
	mvprintw(0, COLS / 2 - 16, "Level:%d   Exp:%d   Passed Ranks:%d", currentLevel, exp, count);
	attrset(A_NORMAL);
	curs_set(0);//disable cursor
	mvprintw(LINES / 2, COLS / 2 - 27, "Press ENTER to start, press any other key to quit.");
	refresh();
	string played;
	if (auto ch = getch(); ch == 13)
		while (true) {
			auto question = find_if(questionList->begin(), questionList->end(), [currentLevel, played](Word const& obj)->bool {
				if (obj.level == currentLevel)
					return played.find(obj.str) == string::npos;
				});
			played.append((*question).str);
			if (distance(question, questionList->end()) == 1)
				if (finishFlag) {
					attrset(A_BOLD);
					mvprintw(LINES / 2, COLS / 2 - 14, "Congratulations! You have passed all ranks!");
					attrset(A_NORMAL);
					mvprintw(LINES / 2, COLS / 2 - 2, "Press any key to quit");
					refresh();
					break;
				}
				else
					finishFlag = true;
			move(LINES / 2, 0);
			clrtoeol();
			refresh();
			attrset(A_BOLD);
			mvprintw(LINES / 2 - 1, COLS / 2 - 4, (*question).str.c_str());
			attrset(A_NORMAL);
			for (int i = 5; i >= 0; i--) {
				mvprintw(LINES / 2 + 4, COLS / 2 - 15, "Word will disapper in %d seconds", i);
				refresh();
				Sleep(1000);
			}
			move(LINES / 2 - 1, 0);
			clrtoeol();
			move(LINES / 2 + 4, 0);
			clrtoeol();
			mvprintw(LINES / 2 + 4, COLS / 2 - 10, "Your answer:");
			refresh();
			curs_set(1);//show the curs
			echo();
			auto answer = new char[20];
			getnstr(answer, 20);
			move(LINES / 2 + 4, 0);
			clrtoeol();
			refresh();
			if ((*question).str._Equal(answer)) {
				exp += 10;
				count++;
				if (exp / 100 > level)
					level++;//upgrade
				attrset(A_REVERSE);
				for (int i = 0; i < COLS; ++i)
					mvaddch(0, i, ' ');
				mvprintw(0, COLS / 2 - 20, "Level:%d\tExp:%d\tPassed Ranks:%d", currentLevel, exp, count);
				attrset(A_NORMAL);
				mvprintw(LINES / 2, COLS / 2 - 21, "Press any key to continue, press q to quit.");
				refresh();
				if (int ch = getch(); ch == 'q')
					break;
				else {
					move(LINES / 2, 0);
					clrtoeol();
					refresh();
					continue;
				}
			}
			else {
				attrset(A_BOLD);
				mvprintw(LINES / 2 - 4, COLS / 2 - 6, "Game Over!");
				attrset(A_NORMAL);
				mvprintw(LINES / 2 - 3, COLS / 2 - 18, "Current answer: %s, you answer is %s", (*question).str.c_str(), answer);
				mvprintw(LINES / 2 - 2, COLS / 2 - 8, "Current Exp: %d", exp);
				mvprintw(LINES / 2, COLS / 2 - 2, "Press any key to quit");
				refresh();
				getch();
				break;
			}
		}
	endwin();
	sql::updateUser(this);
	cout << "Game over." << endl;
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