#include "Player.h"

//Специфика случайного выбора выбора

Type_player RandomGamer::return_type_player() {
    return random_player;
}


void RandomGamer::Add_ships(int number_of_ships) {
    std::cout << "Create random ships location..." << std::endl;
    for (int i = 0; i < number_of_ships; i++)
    {
        bool correct_input = false;
        while (!correct_input)
        {

            int size = 0;
            //Задаем рамер добавляемого корабля
            while (true) {
                size = rand() % 4 + 1;
                if (size > 0 && size <= 4) {
                    if (ship_size[size - 1] > 0) {
                        ship_size[size - 1]--;
                        break;
                    }
                }
            }

            //Определяем в каком положени располагается корабль
            int dir = rand() % 2 + 1;
            if (dir == 1)
                shipDirection = 'H';
            else
                shipDirection = 'V';


            if (shipDirection == 'H')
            {
                int Column = rand() % 10;
                shipColumn = Define_name_column_by_num(Column);
                shipRow = rand() % 10;

                if (ValidCoordinate(shipRow, shipColumn, shipDirection, size))
                {
                    correct_input = true;
                    Ship tmp_ship(size);//Создаем наш корабль, чтобы поместить его на карту
                    for (int j = 1; j <= size; j++)
                    {
                        gameBoard[shipRow][(ConvertColumn(shipColumn)) + j - 1] = 'S';//S - палуба корабля
                        tmp_ship.Add_coordinate(shipRow, (ConvertColumn(shipColumn)) + j - 1);
                    }
                    player_ships.push_back(tmp_ship);
                }
                else
                {
                    ship_size[size - 1]++;
                }
            }
            else if (shipDirection == 'V')
            {
                int Column = rand() % 10;
                shipColumn = Define_name_column_by_num(Column);
                shipRow = rand() % 10;

                if (ValidCoordinate(shipRow, shipColumn, shipDirection, size))
                {
                    correct_input = true;
                    Ship tmp_ship(size);
                    for (int j = 1; j <= size; j++)
                    {
                        gameBoard[shipRow - j + 1][ConvertColumn(shipColumn)] = 'S';
                        tmp_ship.Add_coordinate(shipRow - j + 1, ConvertColumn(shipColumn));
                    }
                    player_ships.push_back(tmp_ship);
                }
                else
                {
                    ship_size[size - 1]++;
                }
            }
            else {
                ship_size[size - 1]++;
            }
        }
    }
    PrintBoard();
}


void RandomGamer::Choose_coordinates_for_attack(int& coord_row, char& coord_column) {
    coord_row = rand() % 10;
    int Column_num = rand() % 10;
    coord_column = Define_name_column_by_num(Column_num);
}