#pragma once
class Word
{
public:
	Word(char* word, int level, int committer): level(level), committerID(committer) {
		str = std::string(word);
	};
	~Word()=default;
	std::string str;
	int level;
private:
	int committerID;
};
