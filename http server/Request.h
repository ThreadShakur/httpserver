#pragma once
#include <string>
#include <map>
#include "Cookies.h"
#include "Headers.h"
#include "QueryString.h"

using namespace std;


class Request
{
public:
	string method;
	string path;
	string ip;
	Cookies* cookies;
	Headers* headers;
	QueryString* params;

	Request(string request);

};