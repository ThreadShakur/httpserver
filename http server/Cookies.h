#pragma once
#include <string>
#include <map>

using namespace std;

class Cookies
{
private:
	map<string, string> cookies;
public:
	Cookies(string body);
	void insert(string key, string value);
	string get(string key);
};