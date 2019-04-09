// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "sql.h"
#include "client.h"

#pragma comment(lib, "sqlite3.lib")

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
	cout << endl << endl << "Welcome, " << currentUser->name << "(UID:" << currentUser->id << ")" << ". You are " << (currentUser->isPlayer ? "Player" : "Committer") << "(Level " << currentUser->level << ")" << endl;
	if (currentUser->isPlayer)
		cout << "You have played " << currentUser->count << " Ranks." << endl;
	else
		cout << "You have commited " << currentUser->count << " Questions." << endl;
}

User* login() {
login:
	string userName;
	string password;
	char ch;
	cout << "Login:";
	cin >> userName;
	cout << "Password:";
	while ((ch = _getch()) != 13) {
		if (ch == '\b')
			cout << "\b \b";
		else {
			password += ch;
			cout << "*";
		}
	}
	cout << endl;

	if (!sql::queryPassword(userName, password)) {
		cout << "Access denied, try again." << endl << endl;
		goto login;
	}
	return sql::getUserByName(userName);

}

User* signUp() {
	string userName;
	string password;
	string comfirmPassword;
	char ch;
	cout << "Username:";
	cin >> userName;

SettingPassword:
	cout << "Setting password for " << userName << "." << endl;
	cout << "Password:";
	while ((ch = _getch()) != 13) {
		if (ch == '\b')
			cout << "\b \b";
		else {
			password += ch;
			cout << "*";
		}
	}
	cout << endl << "Retype Password:";
	while ((ch = _getch()) != 13) {
		if (ch == '\b')
			cout << "\b \b";
		else {
			comfirmPassword += ch;
			cout << "*";
		}
	}
	cout << endl;
	if (!comfirmPassword._Equal(password)) {
		cout << "Sorry, passwords do not match"<<endl;
		password.clear();
		comfirmPassword.clear();
		goto SettingPassword;
	}

	bool isPlayer;
SettingRole:
	cout << "Are you player?(y/n):";
	getchar();//remove \n
	switch (ch = getchar(); ch) {
	case 'Y':
	case 'y':
		isPlayer = true;
		break;
	case 'N':
	case 'n':
		isPlayer = false;
		break;
	default:
		cout << "Invaild input." << endl;
		goto SettingRole;
	}
	if (isPlayer)
		return sql::AddUser(userName,password,isPlayer);
	else
		return sql::AddUser(userName, password, isPlayer);
}