#pragma once
using namespace std;
User* login();
User* signUp();
void cmdPlayer(Player* currentUser, vector<Word>* questionList);
void cmdCommitter(Committer* currentUser, vector<Word>* questionList);