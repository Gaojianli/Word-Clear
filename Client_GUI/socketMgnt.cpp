#include "socketMgnt.h"
using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
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
