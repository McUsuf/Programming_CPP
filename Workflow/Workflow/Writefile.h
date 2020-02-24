#pragma once
#include "Worker.h"

class Writefile: public Worker
{
public:
	explicit Writefile(std::string &_file_name);
	void work(Flow &flow) override;
private:
	std::string file_name;
};

