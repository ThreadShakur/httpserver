#include "Cookies.h"

Cookies::Cookies(string body)
{
	// Finding start of cookie
	for (int i = 0; i < body.length(); i++)
	{
		// Finding key
		for (int k = i; k < body.length(); k++)
		{
			if (body[k] == '=')
			{
				string key = body.substr(i, k - i);

				// Finding value
				for (int m = k; m < body.length(); m++)
				{
					if (body[m] == ';' || m == body.length() - 1)
					{
						string value = body.substr(k + 1, m - (k + 1));
						cookies.insert(pair<string, string>(key, value));
						
						i = m + 1;
						break;
					}
				}

				break;
			}
		}
	}
}

void Cookies::insert(string key, string value)
{
	cookies.insert(pair<string, string>(key, value));
}

string Cookies::get(string key)
{
	for (auto it = cookies.begin(); it != cookies.end(); it++)
	{
		if (it->first == key) return it->second;
	}

	return "";
}