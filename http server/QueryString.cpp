#include "QueryString.h"

QueryString::QueryString()
{

}

QueryString::QueryString(string query)
{
	int length = query.length();

	for (int i = 0; i < length; i++)
	{
		for (int k = i; k < length; k++)
		{
			if (query[k] == '=')
			{
				string key = query.substr(i, k - i);
				for (int m = k; m < length; m++)
				{
					if (query[m] == '&')
					{
						string value = query.substr(k + 1, m - (k + 1));
						params.insert(pair<string, string>(key, value));
						i = m;
						break;
					}
					else if (m == length - 1)
					{
						string value = query.substr(k + 1, m - k);
						params.insert(pair<string, string>(key, value));
						i = m;
						break;
					}
				}

				break;
			}
		}
	}
}

string QueryString::get(string key)
{
	for (auto it = params.begin(); it != params.end(); it++)
	{
		if (it->first == key) return it->second;
	}

	return "";
}