#pragma once
#include "Dump.h"
#include <fstream>
#include <iostream>


Dump::Dump(std::string& _file_name)
{
	file_name = _file_name;
}

void Dump::work(Flow &cur_flow)
{
	std::ofstream file_output;

	file_output.open(file_name);

	std::vector <std::string> cur_text = cur_flow.get_text();

	for (auto& i : cur_text)
	{
		file_output << i << "\n";
	}

	file_output.close();
}