#include "Server.h"

HttpServer::HttpServer(request_handler func)
{
	callback = func;
}

void HttpServer::serve(int port)
{
	if (WSAStartup(MAKEWORD(2, 2), &wData) == 0) printf("WSA successful started\n");

	SOCKADDR_IN addr;

	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	sock = socket(AF_INET, SOCK_STREAM, NULL);

	if (sock == SOCKET_ERROR) printf("ERROR While starting server\n");
	if (bind(sock, (sockaddr*)& addr, sizeof(addr)) != SOCKET_ERROR) printf("SUCCESSFULLY BINDED\n");
	if (listen(sock, SOMAXCONN) != SOCKET_ERROR) printf("LISTEN STARTED\n");

	handle();
}

void HttpServer::handle()
{
	while (true)
	{
		const int MAX_BUF = 4096;

		int in_sock = INVALID_SOCKET;
		SOCKADDR_IN addr;
		int addrlen = sizeof(addr);

		if ((in_sock = accept(sock, (sockaddr*)& addr, &addrlen)) != 0)
		{
			char ip[128];
			sprintf_s(ip, "%d.%d.%d.%d", 
						  addr.sin_addr.S_un.S_un_b.s_b1,
						  addr.sin_addr.S_un.S_un_b.s_b2,
				          addr.sin_addr.S_un.S_un_b.s_b3,
				          addr.sin_addr.S_un.S_un_b.s_b4
			);


			char buf[MAX_BUF];
			string input;

			while (true)
			{
				int num = recv(in_sock, buf, MAX_BUF, 0);
				input.append(buf);
				if (num < MAX_BUF) break;
			}

			Request req = *new Request(input);
			req.ip.append(ip);

			Response resp = callback(req);
			string response = resp.generate_response();
			
			if (send(in_sock, response.c_str(), response.length(), 0) == SOCKET_ERROR) printf("Send error");
			int iResult;


			iResult = shutdown(in_sock, SD_SEND);
			if (iResult == SOCKET_ERROR) {
				printf("shutdown failed with error: %d\n", WSAGetLastError());
				closesocket(in_sock);
				//WSACleanup();
				continue;
			}

			// Receive until the peer closes the connection
			do {

				iResult = recv(in_sock, buf, MAX_BUF, 0);
			} while (iResult > 0);

			// close the socket
			iResult = closesocket(in_sock);
			//WSACleanup();
			continue;
			if (iResult == SOCKET_ERROR) {
				printf("close failed with error: %d\n", WSAGetLastError());
				//WSACleanup();
				continue;
			}

			
		}

		Sleep(50);
	};
}