// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../include/pch.h"
#include "../include/utils.h"
#include "../include/sql.h"
#include "../include/handler.h"
#include <signal.h>
#ifndef _WIN32
#include <unistd.h>
extern char* optarg;
extern int optind, opterr, optopt;
#endif // !_WIN32

using namespace std;
using namespace rapidjson;
void signalHandler(int sig);
void listen(uvw::Loop& loop, int port) {
	std::shared_ptr<uvw::TCPHandle> tcp = loop.resource<uvw::TCPHandle>();
	auto ErrorEventEmitter = tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent & event, uvw::TCPHandle&) {
		cout << "Error occurred:" << event.what() << endl;
		});
	auto ListenEventEmitter = tcp->on<uvw::ListenEvent>([](const uvw::ListenEvent&, uvw::TCPHandle & srv) {
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
		srv.accept(*client);
#ifdef DEBUG
		uvw::Addr remote = client->peer();
		std::cout << std::endl
			<< remote.ip << ":" << remote.port << " Connected" << std::endl;
		auto CloseEventEmitter = client->on<uvw::CloseEvent>([remote](const uvw::CloseEvent&, uvw::TCPHandle&) {
			std::cout << "Connection from " << remote.ip << " closed." << std::endl
				<< std::endl;
			});
#endif // DEBUG
		auto EndEventEmitter = client->on<uvw::EndEvent>([](const uvw::EndEvent&, uvw::TCPHandle & client) {
			client.close();
			});
		auto ErrorEventEmitter = client->on<uvw::ErrorEvent>([](const uvw::ErrorEvent & event, uvw::TCPHandle & client) {
			cout << "Error occurred:" << event.what() << endl;
			client.close();
			});
		auto DataEventEmitter = client->on<uvw::DataEvent>([](const uvw::DataEvent & event, uvw::TCPHandle & client) {
			if (event.length == 0)
				return;
			auto temp = new char[event.length + 1];
#ifdef _MSC_VER
			memcpy_s(temp, event.length, event.data.get(), event.length);
#else
			memcpy(temp, event.data.get(), event.length);
#endif
			temp[event.length] = '\0';
			auto response = handler::mainHandler(temp, client);
			auto toWrite = new char[response.size()];
#ifdef _MSC_VER
			memcpy_s(toWrite, response.size(), response.c_str(), response.size());
#else
			memcpy(toWrite, response.c_str(), response.size());
#endif
			client.tryWrite(toWrite, (unsigned)response.size());
			delete[] toWrite;
			delete[] temp;
			});
		client->read();
		});
	tcp->bind<uvw::IPv6>("[::]", port);
	tcp->listen();
}
std::shared_ptr<uvw::Loop> loop;
void usage() {
	cout << "Usage:" << endl;
	cout << "-p [port]\tSpecific the port to listen." << endl;
}

int main(int argc, char* argv[]) {
	int port = 4000;
#ifndef _WIN32
	char opt;
	while ((opt = getopt(argc, argv, "p:h")) != -1)
	{
		switch (opt)
		{
		case 'p':
			port = atoi(optarg);
			break;
		case 'h':
			usage();
			exit(0);
			break;
		default:
			usage();
			exit(1);
			break;
		}
	}
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);
#endif // !_WIN32
	sql::init();
	loop = uvw::Loop::getDefault();
	listen(*loop, port);
	cout << "listen at 0.0.0.0:" << port << endl;
	cout << "listen at [::]:" << port << endl;
	loop->run();
}

//capture the Ctrl+C event
void signalHandler(int sig) {
	cout << endl;
	switch (sig)
	{
	case SIGINT:
		cout << "Captured Signal SIGINT Events,exitting..." << endl;
		break;
	case SIGTERM:
		cout << "Captured Signal SIGTERM Events,exitting..." << endl;
		break;
	default:
		cout << "Captured Signal" << sig << " Events,exitting..." << endl;
		break;
	}
	sql::close();
	loop->close();
	exit(sig);
}
