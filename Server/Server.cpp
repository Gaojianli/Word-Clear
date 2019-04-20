// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "schema.h"
#include "handler.h"
#pragma comment(lib,"ws2_32.lib")
#ifdef _DEBUG
#pragma comment(lib,"Socketd.lib")
#else
#pragma comment(lib,"Socket.lib")
#endif // DEBUG

std::list<Socket*> globalConnections;
using namespace std;
using namespace rapidjson;

int main(){
	const int port = 3000;
	SocketServer in(port, 5);
	cout << "listen at port:" << port << endl;
	auto threadPool = new list<thread*>();
	while (true) {
		auto connect = in.Accept();
		auto a = new thread([connect]()->unsigned {
			globalConnections.push_back(connect);
			//waiting for data
			while (true) {
				auto str = connect->ReceiveBytes();
				if (str.empty())
					continue;
				else {
					Document dc;
					string response;
					if (dc.Parse(str.c_str()).HasParseError() || !dc.IsObject())
						response = schema::throwError("Invaild Request", 406);
					else if (dc.HasMember("operation")) {
						string operation = dc["operation"].GetString();
						if (operation._Equal("close")) {//close connection
							connect->Close();
							break;
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
					connect->SendLine(response);
				}
			}
			globalConnections.remove(connect);
			delete connect;
			return 0;
			});
		threadPool->push_back(a);
	}
}

