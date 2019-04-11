#pragma once
using namespace std;
class sql
{
public:
	static void init(string dbConnection);
	~sql();
	static vector<Word>* getQuestions();
	static bool queryPassword(string userName, string password);
	static User* getUserByName(string userName);
	//Add a user, return the new User's id.
	static User* addUser(string name, string password, bool isPlayer);
	static vector<User*>* getAllUsers();
	static void addWord(string word, int level, int committerID);
	static void updateUser(User* const toUpdate);
	static vector<User*>* fetchByCondition(property pro, string value, bool isPlayer);
	static User* getHighest(property pro, bool high, bool isPlayer);
private:
	sql(string);
	static sql* _instance;
	sqlite3* db;
};
