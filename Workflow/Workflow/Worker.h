#pragma once
#include "Flow.h"

class Worker
{
private:
	virtual void work(Flow &cur_flow) = 0;
};

