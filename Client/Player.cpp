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
void Player::startGame() {
	
	initscr();
	raw();
	noecho();
	int currentDifficulty = 1;
	int currentLevelCorrectCount = 0;//the number of passed ranks with current leve;
	//draw the border
	attrset(A_REVERSE);
	for (int i = 0; i < COLS; ++i)
		mvaddch(0, i, ' ');
	mvprintw(0, COLS / 2 - 16, "Level:%d   Exp:%d   Passed Ranks:%d", currentDifficulty, exp, count);
	attrset(A_NORMAL);
	curs_set(0);//disable cursor
	mvprintw(LINES / 2, COLS / 2 - 27, "Press ENTER to start, press any other key to quit.");
	refresh();
	string played;
	if (auto ch = getch(); ch == 13)
		while (true) {
			auto questionList = sql::fetchQuestions(currentDifficulty);
			if (questionList->empty()) {
				if (currentDifficulty >= 10) {
					attrset(A_BOLD);
					mvprintw(LINES / 2, COLS / 2 - 14, "Congratulations! You have passed all ranks!");
					attrset(A_NORMAL);
					mvprintw(LINES / 2, COLS / 2 - 2, "Press any key to quit");
					refresh();
					getch();
					break;
				}
				else {
					currentDifficulty++;
					played.clear();
					continue;
				}
			}
			int random = rand() % questionList->size();
			auto question = questionList->at(random);
			questionList->erase(questionList->begin() + random);//remove selected word
			move(LINES / 2, 0);
			clrtoeol();
			refresh();
			attrset(A_BOLD);
			mvprintw(LINES / 2 - 1, COLS / 2 - 4, question.str.c_str());
			attrset(A_NORMAL);
			int showTime = 5 - currentDifficulty / 5; //time decrease 1 sec per 5 levels
			for (int i = showTime; i >= 0; i--) {
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
			flushinp();//flush the input
			getnstr(answer, 20);
			move(LINES / 2 + 4, 0);
			clrtoeol();
			refresh();
			if (question.str._Equal(answer)) {
				exp += 10;
				count++;
				if (exp / 100 > level)
					level++;//upgrade
				//increase the difficuty
				if (currentLevelCorrectCount >= currentDifficulty) {
					currentDifficulty++;
					currentLevelCorrectCount = 0;
				}
				else
					currentLevelCorrectCount++;
				attrset(A_REVERSE);
				for (int i = 0; i < COLS; ++i)
					mvaddch(0, i, ' ');
				mvprintw(0, COLS / 2 - 20, "Level:%d\tExp:%d\tPassed Ranks:%d", currentDifficulty, exp, count);
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
				mvprintw(LINES / 2 - 3, COLS / 2 - 18, "Current answer: %s, you answer is %s", question.str.c_str(), answer);
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
		delete item;
		});
	delete playerList;
	cout << endl;
}
void Player::showStat() {
	cout << "UID\tName\t\tLevel\tPassed Ranks\tExp" << endl;
	cout << id << "\t" << name << "\t\t" << level << "\t\t" << count << "\t" << exp << endl;
}
;