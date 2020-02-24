#include <iostream>
#include "getopt.h"
#include "GameInterface.h"

int main(int argc, char** argv) {

	Type_player first_player_type = random_player;
	Type_player second_player_type = random_player;

	int count_of_rounds = 1;

	//Разбор аргументов командной строки
	int c;
	while (true)
	{
		static struct option long_opt[] = {
				{"help", 0, nullptr, 'h'},
				{"count", 1, nullptr,'c'},
				{"first", 1, nullptr,'f'},
				{"second", 1, nullptr, 's'},
				{nullptr,0,nullptr,0}
		};
		int opt_index;
		if ((c = getopt_long(argc, argv, "h:c:f:s", long_opt, &opt_index)) == -1)
			break;

		switch (c)
		{
		case 'h': {
			Manual();
			return 1;
		}

		case 'c': {
			count_of_rounds = std::stoi(optarg);
			break;
		}

		case 'f': {
			first_player_type = define_type_of_player(optarg);
			break;
		}

		case 's': {
			second_player_type = define_type_of_player(optarg);
			break;
		}
		default: {
			return 1;
		}
		}
	}

	std::cout << "\n\tWelcome to ShipBattle!\n";
	std::cout << "\tCount of the rounds:" << count_of_rounds << "\n" << std::endl;
	std::cout << "\tFirst player type:" << Print_type(first_player_type) << std::endl;
	std::cout << "\tSecond player type:" << Print_type(second_player_type) << std::endl;
	std::cout << "\n\n" << std::endl;

	Game_process(count_of_rounds, first_player_type, second_player_type);

	return 0;
}