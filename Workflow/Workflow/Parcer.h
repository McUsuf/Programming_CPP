#pragma once

#include <iostream>
#include <fstream>
#include "Flow.h"

class Parser
{
public:
	explicit Parser(std::string& _file_name);
	void pars(Flow& cur_flow);

private:
	std::string file_name;

	int str_to_int(std::string &str, int itr);
	void wrong_id_ex(std::string &id, int itr);
	std::vector <std::string> split(const std::string &str, char delim);

	std::ifstream f_in;
};

