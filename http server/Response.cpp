#include "Response.h"


Response::Response(string body_, int status_, string status_message_)
{
	body = body_;
	status = status_;
	status_message = status_message_;
	headers = new Headers();
}

string Response::generate_response()
{
	stringstream response; // сюда будет записываться ответ клиенту

	// Формируем весь ответ вместе с заголовками
	response << "HTTP/1.1 "<< status <<" " << status_message << "\r\n"
			 << "Content-Length: " << body.length() << "\r\n"
			 << "Server: My C++ Server\r\n";
			 
	for (auto header = headers->headers.begin(); header != headers->headers.end(); ++header)
	{
		response << header->first << ": " << header->second << "\r\n";
	}

	response << "\r\n" << body;
	return response.str();
}