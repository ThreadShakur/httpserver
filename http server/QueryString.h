#pragma once
#include <map>
#include <string>

using namespace std;

class QueryString
{
private:
	map<string, string> params;
public:
	QueryString();
	QueryString(string query);
	string get(string key);
};