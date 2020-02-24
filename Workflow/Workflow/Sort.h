#pragma once
#include "Worker.h"

class Sort: public Worker
{
public:
	explicit Sort() = default;
	void work(Flow &cur_flow) override;
};

