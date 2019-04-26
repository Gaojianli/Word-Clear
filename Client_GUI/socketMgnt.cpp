#include "socketMgnt.h"
#include "schema.h"
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
	auto host=gcnew String("127.0.0.1");
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
		switch (int code = (int)jo["code"];code){
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
		System::Windows::Forms::MessageBox::Show("Invaild response" + e->ToString(), "Error");
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
		if ((int)jo["code"] == 200) {
			auto data = jo["data"];
			name = (String^)data["username"];
			session = (String^)data["session"];
			count = (int)data["count"];
			level = (int)data["level"];
			id = (int)data["id"];
			if (isPlayer)
				exp = (int)data["exp"];
		}
		else
			throw gcnew Exception((String^)jo["msg"]);
	}
	catch (Exception^ e) {
		System::Windows::Forms::MessageBox::Show("Invaild response" + e->ToString(), "Error");
		System::Environment::Exit(255);
	}
	User^ user;
	if (isPlayer)
		user = gcnew Player(name, id, session, count, level, exp);
	else
		user = gcnew Committer(name, id, session, count, level);
	return user;
}

String^ socketMgnt::sendAndRec(String^ toSend) {
	auto sendByte = Encoding::Default->ASCII->GetBytes(toSend);
	connection->Send(sendByte);
	auto recStr = gcnew String("");
	auto recBytes = gcnew array<unsigned char>(4096);
	int bytes = connection->Receive(recBytes);
	recStr += Encoding::Default->ASCII->GetString(recBytes, 0, bytes);
	return recStr;
}