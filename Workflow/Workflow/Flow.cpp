#include "Flow.h"
#include <iostream>
#include "Dump.h"
#include "Grep.h"
#include "Readfile.h"
#include "Replace.h"
#include "Sort.h"
#include "Writefile.h"

bool Flow::checkId(int id) 
{
	return blocks_map.count(id);
}

void Flow::set_block_id(int id, std::vector<std::string> &new_block) {
	blocks_map[id] = new_block;
}

void Flow::set_command(int id) {
	commands_queue.push_back(id);
}

void Flow::set_text(std::vector <std::string> &new_text)
{
	text = new_text;
}

std::vector <std::string> Flow::get_text()
{
	return text;
}

void Flow::begin()
{
	for (int i = 0; i < commands_queue.size(); ++i) {
        if (i == 0 && blocks_map[commands_queue[i]][0] != "readfile") {
            std::cerr << "EXCEPTION: the first command in the flow must be \"readfile\"\n";
            exit(1);
        }
        if (i == commands_queue.size() - 1 && blocks_map[commands_queue[i]][0] != "writefile") {
            std::cerr << "EXCEPTION: the last command in the flow must be \"writefile\"\n";
            exit(1);
        }
        if (blocks_map[commands_queue[i]][0] == "readfile" && i != 0) {
            std::cerr << "EXCEPTION: command \"readfile\" can only be at the beginning of the flow\n";
            exit(1);
        }
        if (blocks_map[commands_queue[i]][0] == "writefile" && i != commands_queue.size() - 1) {
            std::cerr << "EXCEPTION: command \"writefile\" can only be at the end of the flow\n";
            exit(1);
        }

        if (blocks_map[commands_queue[i]][0] == "readfile") {
            Readfile readFile(blocks_map[commands_queue[i]][1]);
            readFile.work(*this);
        }
        if (blocks_map[commands_queue[i]][0] == "writefile") {
            Writefile writeFile(blocks_map[commands_queue[i]][1]);
            writeFile.work(*this);
        }
        if (blocks_map[commands_queue[i]][0] == "grep") {
            Grep grep(blocks_map[commands_queue[i]][1]);
            grep.work(*this);
        }
        if (blocks_map[commands_queue[i]][0] == "sort") {
            Sort sort;
            sort.work(*this);
        }
        if (blocks_map[commands_queue[i]][0] == "replace") {
            Replace replace(blocks_map[commands_queue[i]][1], blocks_map[commands_queue[i]][2]);
            replace.work(*this);
        }
        if (blocks_map[commands_queue[i]][0] == "dump") {
            Dump dump(blocks_map[commands_queue[i]][1]);
            dump.work(*this);
        }
    }
}