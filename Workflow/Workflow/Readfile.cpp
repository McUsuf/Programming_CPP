#include "Readfile.h"
#include <fstream>
#include <iostream>

Readfile::Readfile(std::string &_file_name)
{
	file_name = _file_name;
}

void Readfile::work(Flow& flow)
{
	std::ifstream fin;
	fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		fin.open(file_name);
	}
	catch (std::ifstream::failure & e) 
	{
		std::cerr << "EXCEPTION: can't open file \"" << file_name << "\"\n";
		exit(1);
	}
	std::vector <std::string> _text;
	std::string s;
	while (fin)
	{
		try 
		{
			getline(fin, s);
			_text.push_back(s);
		}
		catch (std::ifstream::failure & e)
		{
			break;
		}
	}
	flow.set_text(_text);
	fin.close();
}