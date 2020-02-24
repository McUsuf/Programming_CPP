#pragma once
#include "Worker.h"
class Readfile: public Worker
{
public:
	explicit Readfile(std::string &_file_name);
	void work(Flow &cur_flow) override;
private:
	std::string file_name;
};

