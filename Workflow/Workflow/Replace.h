#pragma once
#include "Worker.h"

class Replace : public Worker
{
public:
	explicit Replace(std::string _src, std::string _dst);
	void work(Flow &cur_flow) override;
private:

	std::vector <int> find_substring_pos(std::string &str);
	std::string src;
	std::string dst;
};

