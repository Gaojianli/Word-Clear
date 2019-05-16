#pragma once
class Word
{
public:
	Word(const char *word, int level, int committer) : level(level), committerID(committer)
	{
		str = std::string(word);
	};
	~Word() = default;
	std::string str;
	int level;

private:
	int committerID;
};

class WordWithCommitter : public Word
{
public:
	WordWithCommitter(const char *word, int level, int committer, std::string committerName) : Word(word, level, committer), committerUserName(std::move(committerName))
	{
		str = std::string(word);
	};
	std::string committerUserName;
};