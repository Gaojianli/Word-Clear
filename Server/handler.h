#pragma once
using namespace rapidjson;
struct handler{
public:
	static std::string login(Document& dc);
	static std::string sessionOperationRouter(Document& dc,string & operation);
private:
	static std::string getQuesiontList(Document& dc);
	template<typename ...T>
	static std::string getUsers(const char* condition, T... args);
	template<typename user_ptr>
	static std::string commit(user_ptr user, Document& dc);
};
