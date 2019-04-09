#include "pch.h"
#include "Committer.h"
#include "sql.h"

Committer::Committer(std::string name, int id) : User(name, id) {
	isPlayer = false;
}

Committer::Committer(std::string username, int id, int count, int level) : User(username, id, false, count, level) {
}

void Committer::commit()
{
}

void Committer::showStat(){
	cout << "id\tName\t\tLevel\tCommited questions" << endl;
	cout << id << "\t" << name << "\t\t" << level << "\t" << count << endl;
}

void Committer::showRank(){
	auto committererList = sql::getAllUsers();
	sort(committererList->begin(), committererList->end(), [](User * a, User * b)->bool {
		return a->count > b->count;//sort by count
		});
	cout << "Name\t\tLevel\tCommited questions" << endl;
	for_each(committererList->begin(), committererList->end(), [](User * item)->void {
		if (item->isPlayer)
			cout << item->name << "\t\t" << item->level << "\t\t" << item->count << endl;
		});
	cout << endl;
}

Committer::~Committer() {
}
