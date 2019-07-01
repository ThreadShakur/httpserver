#include "Headers.h"

Headers::Headers(string body) 
{
	int line_start = 0;
	int length = body.length();
	bool got_method = false;

	for (int i = 0; i < length; i++)
	{

		if (body[i] == ':')
		{
			// Finding end of line (\n) and moving to next line
			for (int k = i; k < length; k++)
			{
				if (body[k] == '\r')
				{
					string key = body.substr(line_start + 1, i - (line_start + 1));
					string value = body.substr(i + 2, k - (i + 2));


					headers.insert(pair<string, string>(key[0] == '\n' ? key.substr(1, key.length() - 1) : key , value));

					i = k;
					line_start = i;
					break;
				}
			}
		}
	}
}

Headers::Headers()
{

}

string Headers::get(string key)
{
	for (auto it = headers.begin(); it != headers.end(); it++)
	{
		if (it->first == key) return it->second;
	}

	return "";
}

void Headers::insert(string key, string value)
{
	headers.insert(pair<string, string>(key, value));
}