#include "pch.h"
#include "sql.h"
#include "client.h"

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
		cout << "Sorry, passwords do not match" << endl;
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
		return sql::addUser(userName, password, isPlayer);
	else
		return sql::addUser(userName, password, isPlayer);
}


void cmdPlayer(Player* currentUser, vector<Word>* questionList) {
	cout << endl << endl << "Welcome, " << currentUser->name << "(UID:" << currentUser->id << ")" << ". You are " << "Player" << "(Level " << currentUser->level << ")" << endl;
	cout << "You have played " << currentUser->count << " Ranks. Current EXP:" << currentUser->exp << endl;
	cout << "Type \"help\" for help" << endl;
	//simple shell implement
	while (true) {
		cout << endl;
		cout << ">";
		string current;
		cin >> current;
		if (current._Equal("help")) {
			//print help
			cout << endl << "Help:" << endl;
			cout << "start\t\tStart a game" << endl;
			cout << "rank\t\tView the Ranking list." << endl;
			cout << "stat\t\tView my status." << endl;
			cout << "exit\t\tQuit this game." << endl;
		}
		else if (current._Equal("start"))
			currentUser->startGame(questionList);
		else if (current._Equal("rank"))
			Player::showRank();
		else if (current._Equal("stat"))
			currentUser->showStat();
		else if (current._Equal("exit"))
			exit(0);
		else
			cout << "Unrecognized command: " << current << endl << " Type \"help\" for help" << endl;
	}
}

void cmdCommitter(Committer* currentUser, vector<Word>* questionList) {
	cout << endl << endl << "Welcome, " << currentUser->name << "(UID:" << currentUser->id << ")" << ". You are " << "Committer" << "(Level " << currentUser->level << ")" << endl;
	cout << "You have commited " << currentUser->count << " Questions." << endl;
	cout << "Type \"help\" for command list" << endl;
	while (true) {
		cout << endl;
		cout << ">";
		string current;
		cin >> current;
		if (current._Equal("help")) {
			//print help
			cout << endl << "Help:" << endl;
			cout << "commit\t\tCommit a word" << endl;
			cout << "rank\t\tView the Ranking list." << endl;
			cout << "stat\t\tView my status." << endl;
			cout << "exit\t\tQuit this game." << endl;
			cout << endl;
		}
		else if (current._Equal("commit")) {
			string toCommit;
			int difficuty;
			cout << endl << "Word:";
			cin >> toCommit;
		SetDifficuty:
			cout << "Difficuty(1-10):";
			cin >> difficuty;
			if (difficuty > 10 || difficuty < 1) {
				cout << "Invaild input." << endl;
				goto SetDifficuty;
			}
			currentUser->commit(toCommit,difficuty);
			questionList->push_back(Word(toCommit.c_str(), difficuty, currentUser->id));
			cout << "Word added." << endl;
		}
		else if (current._Equal("rank"))
			Committer::showRank();
		else if (current._Equal("stat"))
			currentUser->showStat();
		else if (current._Equal("exit"))
			exit(0);
		else
			cout << "Uncongonized command: " << current << " Type \"help\" for help" << endl;
	}
}
