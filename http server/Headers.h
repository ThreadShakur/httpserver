#pragma once
#include <string>
#include <map>

using namespace std;

class Headers
{
public:
	map<string, string> headers;

	Headers(string body);
	Headers();
	string get(string key);
	void insert(string key, string value);
};