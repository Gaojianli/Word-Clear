// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "client.h"
#include "sql.h"
bool ctrlhandler(DWORD fdwctrltype);
int main() {
	sql::init("database.db");
	auto questionList = sql::getQuestions();//import data
	User* currentUser;
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlhandler, true);
SignOrLog:
	cout << "Login/Sign up? (L/S):";
	switch (char signUpFlag = getchar(); signUpFlag) {
	case 'L':
	case 'l':
		currentUser = login();
		break;
	case 'S':
	case 's':
		currentUser = signUp();
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
		cmdPlayer(static_cast<Player*>(currentUser), questionList);
	else
		cmdCommitter(static_cast<Committer*>(currentUser), questionList);
	delete currentUser;
	delete questionList;
}

bool ctrlhandler(DWORD fdwctrltype) {
	auto WcharToChar = [](const wchar_t* wp, size_t m_encode = CP_ACP)->string {
		string str;
		int len = WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
		char* m_char = new char[len + 1];
		WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		str = m_char;
		delete m_char;
		return str;
	};
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	const char* argv[] = { "client", nullptr };
	switch (fdwctrltype) {
	case CTRL_C_EVENT:
		system("cls");
		GetModuleFileNameW(hModule, path, MAX_PATH);
		_execvp(WcharToChar(path).c_str(), argv);
		return(false);
	default:
		return false;
	}
}
