#pragma once
#ifndef SQL_H
#define SQL_H
class sql
{
public:
	static void init();
	static void close();
	static User* fetchUserByName(const std::string name);
	static bool queryPassword(const std::string username, const std::string password);
	template<typename T>
	static void updateUserOneCol(const char* column, const T& toUpdate, int id);
	static void updateSession(std::string session, int id);
	static User fetchUserBySession(const std::string& session);
	static std::vector<Word>* fetchQestion(const int difficulty);
	template<typename T>
	static std::vector<User>* fetchUsersByCondition(std::string properties, const T& value);
	static std::vector<User>* fetchUsersByCondition();
	static void addWord(const char* word, int difficulty, int committerID);
private:
	sql();
	~sql();
	static sql* _instance;
	daotk::mysql::connection con;
};
/*-----------inline methods-----------*/
template<typename T>
inline std::vector<User>* sql::fetchUsersByCondition(std::string properties, const T& value) {
	std::vector<User>* toReturn = nullptr;
	string sqlCommand = "select id,name,isPlayer,count,exp,level from user where %s like ";
	if constexpr (std::is_same<std::decay<T>::type, string>::value
		|| std::is_same<std::decay<T>::type, char*>::value)
		sqlCommand.append("'");
	if constexpr (std::is_same<std::decay<T>::type, bool>::value)
		sqlCommand += value ? "true" : "false";
	else
		sqlCommand += std::to_string((int)value);
	if constexpr (std::is_same<std::decay<T>::type, string>::value
		|| std::is_same<std::decay<T>::type, char*>::value)
		sqlCommand.append("'");
	_instance->con.query(sqlCommand.c_str(), properties.c_str()).each([&toReturn](int id, string name, bool isPlayer, int count, int exp, int level) {
		if (toReturn == nullptr)
			toReturn = new std::vector<User>();
		toReturn->push_back(User(name, id, isPlayer, count, exp, level));
		return true;
		});
	return toReturn;
}

template<typename T>
inline void sql::updateUserOneCol(const char* column, const T& toUpdate, int id) {
	std::string sqlCommand;
	if constexpr (std::is_same<std::decay<T>::type, string>::value) {
		sqlCommand = "update user set %s = '";
		sqlCommand += toUpdate;
	}
	else {
		sqlCommand = "update user set %s = ";
		sqlCommand += std::to_string((int)toUpdate);
	}
	if constexpr (std::is_same<std::decay<T>::type, string>::value)
		sqlCommand.append("' where id=%d");
	else
		sqlCommand.append(" where id=%d");
	_instance->con.exec(sqlCommand.c_str(), column, id);
}

#endif // !SQL_H