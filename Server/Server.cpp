// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "schema.h"
#include "handler.h"
#include "sql.h"

bool ctrlhandler(DWORD fdwctrltype);

using namespace std;
using namespace rapidjson;

void listen(uvw::Loop& loop, int port) {
	std::shared_ptr<uvw::TCPHandle> tcp = loop.resource<uvw::TCPHandle>();
	tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent& event, uvw::TCPHandle&) {
		cout << "error occurred:" << event.what() << endl;
		});
	tcp->once<uvw::ListenEvent>([](const uvw::ListenEvent&, uvw::TCPHandle & srv) {
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();

		client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent&, uvw::TCPHandle&) {
			std::cout << "Server closed." << std::endl;
			ptr->close(); });
		client->on<uvw::EndEvent>([](const uvw::EndEvent&, uvw::TCPHandle & client) { client.close(); });
		client->on<uvw::ErrorEvent>([](const uvw::ErrorEvent& event, uvw::TCPHandle&) {
			cout << "error occurred:" << event.what() << endl;
			});
		srv.accept(*client);
		uvw::Addr remote = client->peer();
		std::cout << remote.ip << ":" << remote.port << " Connected" << std::endl;
		client->on<uvw::DataEvent>([](const uvw::DataEvent & event, uvw::TCPHandle& client) {
			if (event.length == 0)
				return;
			Document dc;
			auto temp = new char[event.length + 1];
			memcpy_s(temp, event.length, event.data.get(), event.length);
			temp[event.length] = '\0';
			string response;
			if (dc.Parse(temp).HasParseError() || !dc.IsObject())
				response = schema::throwError("Invaild Request", 406);
			else if (dc.HasMember("operation")) {
				string operation = dc["operation"].GetString();
				if (operation._Equal("close")) {//close connection
					client.close();
				}
				else if (operation._Equal("login")) {
					response = handler::login(dc);
				}
				else {
					response = schema::throwError("Operation can't be recognized", 404);
				}
			}
			else
				response = schema::throwError("Invaild operation", 406);
			auto toWrite = new char[response.size()];
			memcpy_s(toWrite, response.size(), response.c_str(), response.size());
			client.tryWrite(toWrite, (unsigned)response.size());
			delete[] toWrite;
			delete[] temp;
			});
		client->read();
		});
	
	tcp->bind("127.0.0.1", port);
	tcp->listen();
}
std::shared_ptr<uvw::Loop> loop;

int main() {
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlhandler, true);
	sql::init();
	loop = uvw::Loop::getDefault();
	const int port = 4000;
	listen(*loop, port);
	cout << "listen at 127.0.0.1:" << port << endl;
	loop->run();
}

//capture the Ctrl+C event
bool ctrlhandler(DWORD fdwctrltype) {
	switch (fdwctrltype) {
	case CTRL_C_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		cout << "Captured " << fdwctrltype << " Events,exitting..." << endl;
		loop->close();
		sql::close();
		exit(fdwctrltype);
		return(false);
	default:
		return false;
	}
}