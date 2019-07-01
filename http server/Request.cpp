#include "Request.h"

Request::Request(string request)
{
	int length = request.length();
	for (int i = 0; i < length; i++)
	{
		// Finding method
		for (int k = i; k < length; k++)
		{
			if (request[k] == ' ')
			{
				method = request.substr(i, k - i);
				i = k + 1;
				break;
			}
		}

		//finding path
		for (int k = i; k < length; k++)
		{
			if (request[k] == ' ')
			{
				path = request.substr(i, k - i);

				// Finding GET query
				for (int m = 0; m < (int)path.length(); m++)
				{
					if (path[m] == '?')
					{
						params = new QueryString(path.substr(m + 1, (int)path.length() - (m + 1)));
						path = path.substr(0, m);
						
					}
				}

				i = k;
				break;
			}
		}

		// Finding end of line (\n)
		for (int k = i; k < length; k++)
		{
			if (request[k] == '\n')
			{
				i = k;
				break;
			}
		}

		headers = new Headers(request.substr(i, length - i));
		break;
	}

	cookies = new Cookies(headers->get("Cookie"));
}