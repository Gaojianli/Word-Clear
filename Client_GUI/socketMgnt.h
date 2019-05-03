#pragma once
#ifndef socket_H
#define socket_H
#include "Player.h"
#include "schema.h"
#include "Committer.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace Newtonsoft::Json;
using namespace Newtonsoft::Json::Linq;
public ref class socketMgnt
{
public:
	static socketMgnt^ getInstance();
	User^ login(String^ username, String^ password);
	User^ signup(String^ username, String^ password, bool isPlayer);
	bool commit(String^ word, int difficulty, User^ committer);
	//get the users which have the same role
	List<UserSchema^>^ getSameRoleUser(User^ user);
	List<UserSchema^>^ getDifferentRoleUser(User^ user);
	List<wordSchema^>^ getQuestionsByLevel(User^ user, int difficulty);
	void updatePlayer(Player^ user);
	template<typename T>
	List<UserSchema^>^ customizeQuery(User^ user, String^ Property, bool isPlayer, T value);
private:
	static socketMgnt^ _instance;
	bool socketConnected();
	String^ sendAndRec(String^ toSend);
	System::Net::Sockets::Socket^ connection;
	socketMgnt();
	~socketMgnt();
};

#endif // !socket_H

template<typename T>
inline List<UserSchema^>^ socketMgnt::customizeQuery(User^ user, String^ Property, bool isPlayer, T value) {
	String^ json;
	json= JsonConvert::SerializeObject(gcnew schemaWithSession("getUsersByCondition", user->session, gcnew querySchema<T>(isPlayer ? "player" : "committer", Property, value)));
	auto response = sendAndRec(json);
	List<UserSchema^>^ toReturn = nullptr;
	try {
		JObject^ jo = JObject::Parse(response);
		if (int code = (int)jo["code"]; code == 200) {
			auto data = (JObject^)jo["data"];
			auto userArray = (JArray^)data["Users"];
			toReturn = gcnew List<UserSchema^>();
			for each (auto item in userArray) {
				if ((bool)item["isPlayer"])
					toReturn->Add(gcnew PlayerSchema((String^)item["name"], (int)item["id"], (int)item["count"], (int)item["level"], (int)item["exp"]));
				else
					toReturn->Add(gcnew CommitterSchema((String^)item["name"], (int)item["id"], (int)item["count"], (int)item["level"]));
			}
			return toReturn;
		}
		else
			throw gcnew Exception((String^)jo["msg"]);
	}
	catch (Exception^ e) {
		System::Windows::Forms::MessageBox::Show("Invaild response: " + e->ToString(), "Error");
		return nullptr;
	}
}
