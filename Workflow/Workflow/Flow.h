#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class Flow
{
private:
	std::vector <std::string> text; //full text
	std::unordered_map <int, std::vector <std::string>> blocks_map; //<id, vector[0] =  "block_name", vector[X] = "Xth-argument">
	std::vector <int> commands_queue; //idX->idY->idZ->...
public:
	Flow() = default;

	std::vector <std::string> get_text();
	bool checkId(int id);
	void set_text(std::vector <std::string> &new_text);
	void set_block_id(int id, std::vector <std::string> &new_block);
	void set_command(int id);
	void begin();
};

