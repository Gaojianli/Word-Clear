#include "pch.h"
#include "Committer.h"


Committer::Committer(std::string name, int id) : User(name, id) {
	isPlayer = false;
}

Committer::Committer(std::string username, int id, int count, int level) : User(username, id, true, count, level) {
}

Committer::~Committer() {
}
