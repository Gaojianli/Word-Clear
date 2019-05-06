#include "socketMgnt.h"
using namespace System;
using namespace System::Text;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace Newtonsoft::Json;
using namespace Newtonsoft::Json::Linq;
socketMgnt^ socketMgnt::getInstance() {
	if (!_instance)
		_instance = gcnew socketMgnt();
	return _instance;
}

socketMgnt::socketMgnt() {
	int port = 4000;
	auto host = gcnew String("127.0.0.1");
	auto ip = IPAddress::Parse(host);
	auto ipe = gcnew IPEndPoint(ip, port);
	connection = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
	try {
		connection->Connect(ipe);
	}
	catch (...) {
		System::Windows::Forms::MessageBox::Show("Can't connect to server!", "Error");
		System::Environment::Exit(-1);
	}
}

socketMgnt::~socketMgnt(){
	if (connection->Connected)
		connection->Close();
	delete connection;
}

User^ socketMgnt::login(String^ username, String^ password) {
	auto json = JsonConvert::SerializeObject(gcnew schema("login", (Object^)gcnew loginSchema(username, password)));
	auto response = sendAndRec(json);
	JObject^ jo;
	String^ name;
	String^ session;
	bool isPlayer;
	int count;
	int level;
	int id;
	int exp;
	try {
		jo = JObject::Parse(response);
		auto data = jo["data"];
		switch (int code = (int)jo["code"]; code) {
		case 200:
			name = (String^)data["username"];
			session = (String^)data["session"];
			isPlayer = (bool)data["isPlayer"];
			count = (int)data["count"];
			level = (int)data["level"];
			id = (int)data["id"];
			if (isPlayer)
				exp = (int)data["exp"];
			break;
		default:
			System::Windows::Forms::MessageBox::Show((String^)jo["msg"], "Error " + code.ToString());
			return nullptr;
		}
	}
	catch (Exception^ e) {
		System::Windows::Forms::MessageBox::Show("Invaild response: " + e->ToString(), "Error");
		System::Environment::Exit(255);
	}
	User^ user;
	if (isPlayer)
		user = gcnew Player(name, id, session, count, level, exp);
	else
		user = gcnew Committer(name, id, session, count, level);
	return user;
}

User^ socketMgnt::signup(String^ username, String^ password, bool isPlayer) {
	auto json = JsonConvert::SerializeObject(gcnew schema("register", gcnew signUpSchema(username, password, isPlayer)));
	auto response = sendAndRec(json);
	JObject^ jo;
	String^ name;
	String^ session;
	int count;
	int level;
	int id;
	int exp;
	try {
		jo = JObject::Parse(response);
		if (int code = (int)jo["code"];code == 200) {
			auto data = jo["data"];
			name = (String^)data["username"];
			session = (String^)data["session"];
			count = (int)data["count"];
			level = (int)data["level"];
			id = (int)data["id"];
			if (isPlayer)
				exp = (int)data["exp"];
		}
		else if (code == 401) {
			System::Windows::Forms::MessageBox::Show((String^)jo["msg"], "Error");
			return nullptr;
		}
		else
			throw gcnew Exception((String^)jo["msg"]);
	}
	catch (Exception^ e) {
		System::Windows::Forms::MessageBox::Show("Invaild response: " + e->ToString(), "Error");
		System::Environment::Exit(255);
	}
	User^ user;
	if (isPlayer)
		user = gcnew Player(name, id, session, count, level, exp);
	else
		user = gcnew Committer(name, id, session, count, level);
	return user;
}

bool socketMgnt::socketConnected() {
	bool condition1 = connection->Poll(200, SelectMode::SelectRead);
	bool condition2 = (connection->Available == 0);
	if (condition1 && condition2)
		return false;
	else
		return true;
}

String^ socketMgnt::sendAndRec(String^ toSend) {
	//deal with connection lost
	if (!socketConnected()) {
		try {
			connection->Close();
			int port = 4000;
			auto host = gcnew String("127.0.0.1");
			auto ip = IPAddress::Parse(host);
			auto ipe = gcnew IPEndPoint(ip, port);
			connection = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			connection->Connect(ipe);
		}
		catch (SocketException^ e) {
			System::Windows::Forms::MessageBox::Show("Can't connect to server!\n" + e->ToString(), "Error");
			System::Environment::Exit(-1);
		}
	}
	
	auto sendByte = Encoding::Default->ASCII->GetBytes(toSend);
	try {
		connection->Send(sendByte);
	}
	catch (SocketException^ e) {
		System::Windows::Forms::MessageBox::Show("Server error: " + e->ToString(), "Error");
		System::Environment::Exit(-2);
	}
	auto recStr = gcnew String("");
	auto recBytes = gcnew array<unsigned char>(4096);
	int bytes = connection->Receive(recBytes);
	recStr += Encoding::Default->ASCII->GetString(recBytes, 0, bytes);
	return recStr;
}

bool socketMgnt::commit(String^ word, int difficulty, User^ committer) {
	auto json = JsonConvert::SerializeObject(gcnew schemaWithSession("commit", committer->session, gcnew commitSchema(word, difficulty)));
	auto response = sendAndRec(json);
	JObject^ jo;
	try
	{
		jo = JObject::Parse(response);
		if (int code = (int)jo["code"]; code == 201)
			return true;
		else {
			if (code == 202) {
				System::Windows::Forms::MessageBox::Show("Word is already existed!", "Error");
				return false;
			}
			else {
				throw gcnew Exception((String^)jo["msg"]);
			}
		}
	}
	catch (Exception^ e) {
		System::Windows::Forms::MessageBox::Show("Invaild response: " + e->ToString(), "Error");
		return false;
	}
}

List<UserSchema^>^ socketMgnt::getSameRoleUser(User^ user) {
	auto json = JsonConvert::SerializeObject(gcnew schemaWithSession("getSameUsers", user->session, nullptr));
	auto response = sendAndRec(json);
	JObject^ jo;
	List<UserSchema^>^ toReturn = nullptr;
	try
	{
		jo = JObject::Parse(response);
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

List<UserSchema^>^ socketMgnt::getDifferentRoleUser(User^ user) {
	auto json = JsonConvert::SerializeObject(gcnew schemaWithSession("getDifferentUsers", user->session, nullptr));
	auto response = sendAndRec(json);
	JObject^ jo;
	List<UserSchema^>^ toReturn = nullptr;
	try
	{
		jo = JObject::Parse(response);
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

List<wordSchema^>^ socketMgnt::getQuestionsByLevel(User^ user, int difficulty){
	auto json = JsonConvert::SerializeObject(gcnew schemaWithSession("getQuestionList", user->session, gcnew getQuestionListSchema(difficulty)));
	auto response = sendAndRec(json);
	JObject^ jo;
	List<wordSchema^>^ toReturn = nullptr;
	try
	{
		jo = JObject::Parse(response);
		if (int code = (int)jo["code"]; code == 200) {
			auto data = (JObject^)jo["data"];
			auto userArray = (JArray^)data["Words"];
			toReturn = gcnew List<wordSchema^>();
			for each (auto item in userArray) {
				toReturn->Add(gcnew wordSchema((String^)item["Word"], (int)item["level"]));
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

void socketMgnt::updatePlayer(Player^ user) {
	auto json = JsonConvert::SerializeObject(gcnew schemaWithSession("updateUser", user->session, gcnew updateUserSchema(user->count, user->exp, user->level)));
	auto response = sendAndRec(json);
	JObject^ jo;
	try
	{
		jo = JObject::Parse(response);
		if (int code = (int)jo["code"]; code == 202)
			return;
		else
			throw gcnew Exception((String^)jo["msg"]);
	}
	catch (Exception^ e) {
		System::Windows::Forms::MessageBox::Show("Invaild response: " + e->ToString(), "Error");
	}
}
