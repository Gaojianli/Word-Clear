// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "client.h"
#include "sql.h"

int main() {
	sql::init("database.db");
	auto questionList = sql::getQuestions();//import data
	User* currentUser;

SignOrLog:
	cout << "Login/Sign up? (L/S):";
	switch (char signUpFlag = getchar(); signUpFlag) {
	case 'L':
	case 'l':
		currentUser=login();
		break;
	case 'S':
	case 's':
		currentUser=signUp();
		break;
	default:
		cout << "Invaild input." << endl;
		goto SignOrLog;
	}
	if (currentUser == nullptr) {
		cerr << "Error ocurred!";
		exit(-1);
	}
	if (currentUser->isPlayer)
		cmdPlayer(static_cast<Player*>(currentUser),questionList);
	else
		cmdCommitter(static_cast<Committer*>(currentUser),questionList);
	delete currentUser;
	delete questionList;
}

