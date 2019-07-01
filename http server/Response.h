#pragma once
#include <sstream>
#include "Headers.h"


class Response
{
private:
	string body;
	string status_message;
	int status;
public:
	Headers* headers;
	
	Response(string body, int status, string status_message);
	string generate_response();


};