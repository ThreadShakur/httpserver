// http server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Server.h"
#include "Response.h"
#include "Request.h"

#include <fstream>
#include <string>


using namespace std;

string get_content_type(string file)
{
	for (int i = 0; i < (int)file.length(); i++)
	{
		if (file[i] == '.')
		{
			string ext = file.substr(i + 1, file.length() - (i + 1));
			if (ext == "html") return "text/html";
			if (ext == "css") return "text/css";
			if (ext == "js") return "text/javascript";
			if (ext == "png") return "image/png";
			if (ext == "jpg") return "image/jpg";
			if (ext == "jpeg") return "image/jpeg";
		}
	}

	return "text";
}

Response callback(Request request)
{
	int status = 200;
	string status_message = "OK";

	std::ifstream t(request.path.substr(1, request.path.length() - 1), ios_base::binary);
	string content((std::istreambuf_iterator<char>(t)), (std::istreambuf_iterator<char>()));
	t.close();

	
	if (content.length() == 0)
	{
		status = 404;
		status_message = "Not Found";
		content = "<title>Not Found</title><h1>404 - Not Found</h1>";
	}
	

	Response resp = *new Response(content, status, status_message);

	resp.headers->insert("My_Header", "Test");
	resp.headers->insert("Content-Type", get_content_type(request.path));


	printf("[%s][%s] %s - %d %s\n", request.method.c_str(), request.ip.c_str(), request.path.c_str(), status, status_message.c_str());
	return resp;
}

int main()
{
	HttpServer* server = new HttpServer(&callback);
	server->serve(80);
}
