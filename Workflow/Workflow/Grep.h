#pragma once
#include "Worker.h"
class Grep: public Worker
{
public:
	explicit Grep(std::string &_substring);
	void work(Flow &flow) override;
private:
	std::string substring;
	bool cmp(std::string &cur_str);

};

