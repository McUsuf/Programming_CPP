#include <iostream>
#include <string>
#include "Worker.h"
#include "ReadFile.h"
#include "WriteFile.h"
#include "Grep.h"
#include "Sort.h"
#include "Dump.h"
#include "Parcer.h"
#include "Replace.h"

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		std::cerr << "EXCEPTION: expected 1 program argument with file name\n";
		exit(1);
	}
	std::string workflowFile = argv[1];
	Parser parser(workflowFile);
	Flow flow;
	parser.pars(flow);
	flow.begin();
	return 0;
}