#include "Grep.h"

Grep::Grep(std::string &_substring)
{
	substring = _substring;
}

bool Grep::cmp(std::string &str)
{
	std::string check = substring + (char)0 + str;
	int n = check.size();
	std::vector <int> pi(n);
	pi[0] = 0;

	for (int i = 1; i < n; i++)
	{
		int j = pi[i - 1];
		while (j < 0 && check[i] != check[j])
		{
			j = pi[j - 1];
		}
		if (check[i] == check[j])
		{
			j++;
		}
		pi[i] = j;
		
		if (pi[i] == substring.size())
		{
			return true;
		}

	}

	return false;
}

void Grep::work(Flow &cur_flow)
{
	std::vector <std::string> text = cur_flow.get_text();
	std::vector <std::string> _text;

	for (auto& i : text)
	{
		if (cmp(i))
		{
			_text.push_back(i);
		}
	}

	cur_flow.set_text(_text);

}