#include <iostream>
#include "Replace.h"

Replace::Replace(std::string _src, std::string _dst)
{
	src = _src;
	dst = _dst;
}

std::vector <int> Replace::find_substring_pos(std::string& str)
{
	std::string check = src + (char)0 + str;
	int n = check.size();
	std::vector <int> pi(n);
	std::vector <int> pos;
	pi[0] = 0;
	
	for (int i = 1; i < n; ++i) 
	{
		int j = pi[i - 1];

		while (j > 0 && check[i] != check[j]) 
		{
			j = pi[j - 1];
		}

		if (check[i] == check[j]) 
		{
			j++;
		}
		pi[i] = j;
		
		if (pi[i] == src.size()) 
		{
			pos.push_back(i - src.size() - 1);
			pi[i] = 0;
		}
	}
	return pos;
}

void Replace::work(Flow &cur_flow)
{
	std::vector <std::string> text = cur_flow.get_text();
	std::vector <std::string> new_text;
	
	for (auto& i : text) 
	{
		std::vector<int> pos = find_substring_pos(i);
		if (pos.empty()) {
			new_text.push_back(i);
			continue;
		}
		std::vector<std::string> splits;
		splits.push_back(i.substr(0, pos[0] - src.size() + 1));
		for (int j = 1; j < pos.size(); ++j) {
			splits.push_back(i.substr(pos[j - 1] + 1,
				pos[j] - pos[j - 1] - src.size()));
		}
		if (pos.back() != i.size() - 1) {
			splits.push_back(i.substr(pos.back() + 1,
				i.size() - pos.back() - 1));
		}
		else {
			splits.emplace_back("");
		}
		std::string new_str;
		for (int j = 0; j < splits.size(); ++j) {
			new_str += splits[j];
			if (j != splits.size() - 1) {
				new_str += dst;
			}
		}
		new_text.push_back(new_str);
	}
	cur_flow.set_text(new_text);
}