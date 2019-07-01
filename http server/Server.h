#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include "Request.h"
#include "Response.h"

#pragma comment(lib, "ws2_32.lib")

typedef Response(*request_handler)(Request request);

using namespace std;

class HttpServer
{
private:
	SOCKET sock;
	WSAData wData;
	request_handler callback;

	void handle();
public:
	HttpServer(request_handler func);
	void serve(int port);
};