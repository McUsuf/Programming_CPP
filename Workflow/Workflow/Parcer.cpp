#include "Parcer.h"
#include <sstream>

Parser::Parser(std::string& _file_name)
{
	file_name = _file_name;
}

void Parser::wrong_id_ex(std::string& id, int itr)
{
	std::cerr << "!ERROR! \n Illegal id: " << id << "\n Line: " << itr << std::endl;
	f_in.close();
	exit(1);
}

int Parser::str_to_int(std::string &str, int itr) 
{
	if (str.size() > 9 || (str.size() > 1 && str[0] == '0')) 
	{
		wrong_id_ex(str, itr);
	}
	int id = 0, p10 = 1;
	for (int i = str.size() - 1; i >= 0; --i) 
	{
		if (str[i] < '0' || str[i] > '9') 
		{
			wrong_id_ex(str, itr);
		}
		id += p10 * (str[i] - '0');
		p10 *= 10;
	}
	return id;
}

std::vector<std::string> Parser::split(const std::string& str, char delim) 
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string item;
	while (getline(ss, item, delim)) 
	{
		result.push_back(item);
	}
	return result;
}

void Parser::pars(Flow& cur_flow)
{
	f_in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		f_in.open(file_name);
	}
	catch (std::ifstream::failure & e) {
		std::cerr << "EXCEPTION: can't open file \"" << file_name << "\"\n";
		exit(1);
	}
	std::string tmp;
	try {
		getline(f_in, tmp);
	}
	catch (std::ifstream::failure & e) {
		std::cerr << "EXCEPTION: unexpected end of file \"" << file_name << "\"\n";
		f_in.close();
		exit(1);
	}
	std::vector <std::string> splited = split(tmp, ' ');
	if (splited.size() > 1) {
		std::cerr << "EXCEPTION: invalid input format (line " <<
			1 << ")\n";
		f_in.close();
		exit(1);
	}
	if (splited[0] != "desc") {
		std::cerr << "EXCEPTION: string \"desc\" is not found\n";
		f_in.close();
		exit(1);
	}

	std::unordered_map <std::string, int> commands;
	commands["readfile"] = 1;
	commands["writefile"] = 1;
	commands["grep"] = 1;
	commands["sort"] = 0;
	commands["replace"] = 2;
	commands["dump"] = 1;

	int it = 2;
	while (true) {
		try {
			getline(f_in, tmp);
		}
		catch (std::ifstream::failure & e) {
			std::cerr << "EXCEPTION: unexpected end of file \"" << file_name << "\"\n";
			f_in.close();
			exit(1);
		}
		splited = split(tmp, ' ');
		if (splited.size() == 1) {
			if (splited[0] == "csed") {
				break;
			}
			else {
				std::cerr << "EXCEPTION: string \"csed\" is not found\n";
				f_in.close();
				exit(1);
			}
		}
		if (splited.size() < 3) {
			std::cerr << "EXCEPTION: " << file_name <<": invalid input format  after split (line " << it << ")\n";
			f_in.close();
			exit(1);
		}
		int id = str_to_int(splited[0], it);
		if (cur_flow.checkId(id)) {
			std::cerr << "EXCEPTION: ID \"" << id << "\" was reused (line " << it << ")\n";
			f_in.close();
			exit(1);
		}
		//std::cout << id << "\n";
		if (splited[1] != "=") {
			std::cerr << "EXCEPTION: \"=\" is not found (line " << it << ")\n";
			f_in.close();
			exit(1);
		}

		if (commands.count(splited[2]) == 0) {
			std::cerr << "EXCEPTION: command \"" << splited[2] <<
				"\" is not found (line " << it << ")\n";
			f_in.close();
			exit(1);
		}

		if (commands[splited[2]] != splited.size() - 3) {
			std::cerr << "EXCEPTION: invalid number of arguments for command \"" <<
				splited[2] << "\", expected " << commands[splited[2]] <<
				", have " << splited.size() - 3 << " (line " << it << ")\n";
			f_in.close();
			exit(1);
		}
		splited.erase(splited.begin(), splited.begin() + 2);
		cur_flow.set_block_id(id, splited);
		it++;
	}
	try {
		getline(f_in, tmp);
	}
	catch (std::ifstream::failure & e) {
		std::cerr << "EXCEPTION: unexpected end of file \"" << file_name << "\"\n";
		f_in.close();
		exit(1);
	}
	splited = split(tmp, ' ');
	if (splited.size() % 2 == 0) {
		std::cerr << "EXCEPTION: " << file_name << ": invalid input format (line " << it << ")\n";
		f_in.close();
		exit(1);
	}

	for (int i = 0; i < splited.size(); i += 2) {
		int id = str_to_int(splited[i], it);
		if (!cur_flow.checkId(id)) {
			std::cerr << "EXCEPTION: ID \"" << id << "\" is not found (line " <<
				it << ")\n";
			f_in.close();
			exit(1);
		}
		cur_flow.set_command(id);
		if (i != splited.size() - 1 && splited[i + 1] != "->") {
			std::cerr << "EXCEPTION: \"->\" is not found (line " << it << ")\n";
			f_in.close();
			exit(1);
		}
	}
	f_in.close();
}


