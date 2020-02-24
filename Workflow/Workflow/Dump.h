#pragma once
#include "Worker.h"

class Dump : public Worker
{
public:
	explicit Dump(std::string& _file_name);
	void work(Flow& flow) override;
private:
	std::string file_name;
};

