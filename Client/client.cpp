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
		if (ch == '\b') {
			if (password.length() > 0) {
				cout << "\b \b";
				password.pop_back();
			}
		}
		else {
			password += ch;
			cout << "*";
		}
	}
	cout << endl;
	ch = getchar();//remove return
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
		if (ch == '\b') {
			if (password.length() > 0) {
				cout << "\b \b";
				password.pop_back();
			}
		}
		else {
			password += ch;
			cout << "*";
		}
	}
	cout << endl << "Retype Password:";
	while ((ch = _getch()) != 13) {
		if (ch == '\b') {
			if (comfirmPassword.length() > 0) {
				cout << "\b \b";
				comfirmPassword.pop_back();
			}
		}
		else {
			comfirmPassword += ch;
			cout << "*";
		}
	}
	cout << endl;
	if (!comfirmPassword._Equal(password)) {
		cout << "Sorry, passwords do not match." << endl;
		password.clear();
		comfirmPassword.clear();
		goto SettingPassword;
	}

	bool isPlayer;
SettingRole:
	cout << "Are you player?(y/n):";
	ch = getchar();//remove \n
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
		auto buffer = new char[50];
		cin.getline(buffer, 50);
		string command(buffer);
		delete[] buffer;
		if (command._Equal("help")) {
			//print help
			cout << endl << "Help:" << endl;
			cout << "start\t\tStart a game" << endl;
			cout << "rank\t\tView the Ranking list." << endl;
			cout << "stat\t\tView my status." << endl;
			cout << "find\t\tfind a user." << endl;
			cout << "exit\t\tQuit this game." << endl;
		}
		else if (command._Equal("start"))
			currentUser->startGame(questionList);
		else if (command._Equal("rank"))
			Player::showRank();
		else if (command._Equal("stat"))
			currentUser->showStat();
		else if (command.find("find") != string::npos)
			find(command);
		else if (command._Equal("exit"))
			exit(0);
		else
			cout << "Unrecognized command: " << command << endl << " Type \"help\" for help" << endl;
	}
}

void cmdCommitter(Committer* currentUser, vector<Word>* questionList) {
	cout << endl << endl << "Welcome, " << currentUser->name << "(UID:" << currentUser->id << ")" << ". You are " << "Committer" << "(Level " << currentUser->level << ")" << endl;
	cout << "You have commited " << currentUser->count << " Questions." << endl;
	cout << "Type \"help\" for command list" << endl;
	while (true) {
		auto commit = [currentUser, questionList]()->void {
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
			currentUser->commit(toCommit, difficuty);
			questionList->push_back(Word(toCommit.c_str(), difficuty, currentUser->id));
			cout << "Word added." << endl;
			cin.get();
		};//commit function

		cout << endl;
		cout << ">";
		auto buffer = new char[50];
		cin.getline(buffer, 50);
		string command(buffer);
		delete[] buffer;
		if (command._Equal("help")) {
			//print help
			cout << endl << "Help:" << endl;
			cout << "commit\t\tCommit a word" << endl;
			cout << "rank\t\tView the Ranking list." << endl;
			cout << "stat\t\tView my status." << endl;
			cout << "exit\t\tQuit this game." << endl;
			cout << endl;
		}
		else if (command._Equal("commit")) {
			commit();
		}
		else if (command._Equal("rank"))
			Committer::showRank();
		else if (command._Equal("stat"))
			currentUser->showStat();
		else if (command.find("find") != string::npos)
			find(command);
		else if (command._Equal("exit"))
			exit(0);
		else
			cout << "Uncongonized command: " << command << " Type \"help\" for help" << endl;
	}
}

void find(string cmd) {
	auto printHelp = [cmd](bool help) ->void {
		if (!help)
			cout << "error: unknown command \"" << cmd << "\"" << endl;
		cout << "Usage: find [<options>] <role> <property> [<data>]" << endl;
		cout << "   or: find <role> <property> --highest" << endl;
		cout << "   or: find <role> <property> --lowest" << endl;
		cout << "\t-h\t\t\tPrint this help" << endl;
		cout << "\t--highest\t\tShow user with the highest given property." << endl;
		cout << "\t--lowest\t\tShow user with the lowest given property." << endl;
		cout << endl << "Role:" << endl << "\tplayer" << endl << "\tcommitter" << endl;
		cout << endl << "Properties:" << endl;
		cout << "\tname" << endl;
		cout << "\tid\t\tUser's unique id" << endl;
		cout << "\tcount\t\tPasswd ranks/committed questions' number" << endl;
		cout << "\tlevel" << endl;
		cout << "\texp\t\t(Player only)The experience" << endl;
		cout << endl << "Examples:" << endl;
		cout << "\t find player name bob" << endl;
		cout << "\t find player count --highest" << endl;
	};
	auto opt = cmd.substr(5);
	if ((opt.find("--help") != string::npos || cmd.find("-h") != string::npos) && cmd.find("--highest") == string::npos) {//"--highest" include "-h"
		printHelp(true);
		return;
	}
	//process role
	bool playerFlag;
	if (opt.find("player") != string::npos) {
		playerFlag = true;
	}
	else if (opt.find("committer") != string::npos) {
		playerFlag = false;
	}
	else {
		printHelp(false);
		return;
	}

	property queryType;
	if (opt.find("id") != string::npos)
		queryType = property::id;
	else if (opt.find("name") != string::npos)
		queryType = property::name;
	else if (opt.find("count") != string::npos)
		queryType = property::count;
	else if (opt.find("level") != string::npos)
		queryType = property::level;
	else if (opt.find("exp") != string::npos)
		queryType = property::exp;
	else {
		printHelp(false);
		return;
	}
	//process options
	int highestFlag = 2;//0 means lowest, 1 means highest, 2 means values
	if (queryType != property::id && queryType != property::name)
		if (opt.find("--highest") != string::npos)
			highestFlag = 1;
		else if (opt.find("--lowest") != string::npos)
			highestFlag = 0;

	//get values
	auto getValues = [opt](string options)->string {
		auto offset = opt.find(options);
		if (offset == string::npos)
			return string();
		else {
			return opt.substr(offset + options.length() + 1);
		}
	};
	if (highestFlag == 2) {
		string value;
		if (auto temp = getValues("id"); !temp.empty())
			value = temp;
		else if (auto temp = getValues("name"); !temp.empty())
			value = temp;
		else if (auto temp = getValues("count"); !temp.empty())
			value = temp;
		else if (auto temp = getValues("level"); !temp.empty())
			value = temp;
		else if (auto temp = getValues("exp"); !temp.empty())
			value = temp;
		else {
			printHelp(false);
			return;
		}
		auto result = sql::fetchByCondition(queryType, value, playerFlag);
		if (result->empty()) {
			cout << "NO suitable user found!" << endl;
			delete result;
			return;
		}
		cout << "Found " << result->size() << " results:" << endl;
		if (playerFlag) {
			cout << "Name\tlevel\tcount\tEXP" << endl;
			for_each(result->begin(), result->end(), [](User * item)->void {
				if (item->isPlayer)
					cout << item->name << "\t" << item->level << "\t" << item->count << "\t" << static_cast<Player*>(item)->exp << endl;
				delete item;
				});
		}
		else {
			cout << "Name\t\tLevel\tcount" << endl;
			for_each(result->begin(), result->end(), [](User * item)->void {
				if (!item->isPlayer)
					cout << item->name << "\t" << item->level << "\t" << item->count << endl;
				delete item;
				});
		}
		delete result;
		return;
	}
	else {
		auto result = sql::getHighest(queryType, highestFlag == 1 ? true : false, playerFlag);
		if (!result) {
			cout << "NO suitable user found!" << endl;
			return;
		}
		if (playerFlag)
			static_cast<Player*>(result)->showStat();
		else
			static_cast<Committer*>(result)->showStat();
		delete result;
	}
}
