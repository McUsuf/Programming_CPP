#include "Player.h"

//Специфика умного выбора
Type_player OptimalGamer::return_type_player() {
    return optimal_player;
}

void OptimalGamer::Add_ships(int number_of_ships) {

    /*Изначально умный ИИ расстановит большие корабли по краям поля, чтобы получить максимальное число свободных
      клеток, для расстановки маленьких кораблей*/
    const std::vector<int> big_ship_size = { 4, 3, 3, 2, 2, 2 };
    std::cout << "Create optimal ships location..." << std::endl;
    for (unsigned long long i = 0; i < big_ship_size.size(); i++)
    {
        shipDirection = 'V';//Все большие корабли расположим вертикально, вдоль границы карты
        int size = big_ship_size[i];
        if (size == 4)//Устанавливаем линкор
        {
            shipColumn = 'A';
            shipRow = 3;

            Ship tmp_ship(size);
            for (int j = 1; j <= size; j++)
            {
                gameBoard[shipRow - j + 1][ConvertColumn(shipColumn)] = 'S';
                tmp_ship.Add_coordinate(shipRow - j + 1, ConvertColumn(shipColumn));
            }
            player_ships.push_back(tmp_ship);
            ship_size[size - 1]--;
        }
        else if (size == 3)//Устанавливаем крейсеры
        {
            shipColumn = 'J';
            if (ship_size[size - 1] == 2)
            {
                shipRow = 2;
                Ship tmp_ship(size);
                for (int j = 1; j <= size; j++)
                {
                    gameBoard[shipRow - j + 1][ConvertColumn(shipColumn)] = 'S';
                    tmp_ship.Add_coordinate(shipRow - j + 1, ConvertColumn(shipColumn));
                }
                player_ships.push_back(tmp_ship);
                ship_size[size - 1]--;
            }
            else if (ship_size[size - 1] == 1)
            {
                shipRow = 9;
                Ship tmp_ship(size);
                for (int j = 1; j <= size; j++)
                {
                    gameBoard[shipRow - j + 1][ConvertColumn(shipColumn)] = 'S';
                    tmp_ship.Add_coordinate(shipRow - j + 1, ConvertColumn(shipColumn));
                }
                player_ships.push_back(tmp_ship);
                ship_size[size - 1]--;
            }
        }
        else if (size == 2)//Устанавливаем эсминцы
        {
            if (ship_size[size - 1] > 1)
            {
                shipColumn = 'A';
                if (ship_size[size - 1] == 3)
                {
                    shipRow = 6;
                    Ship tmp_ship(size);
                    for (int j = 1; j <= size; j++)
                    {
                        gameBoard[shipRow - j + 1][ConvertColumn(shipColumn)] = 'S';
                        tmp_ship.Add_coordinate(shipRow - j + 1, ConvertColumn(shipColumn));
                    }
                    player_ships.push_back(tmp_ship);
                    ship_size[size - 1]--;
                }
                else if (ship_size[size - 1] == 2)
                {
                    shipRow = 9;
                    Ship tmp_ship(size);
                    for (int j = 1; j <= size; j++)
                    {
                        gameBoard[shipRow - j + 1][ConvertColumn(shipColumn)] = 'S';
                        tmp_ship.Add_coordinate(shipRow - j + 1, ConvertColumn(shipColumn));
                    }
                    player_ships.push_back(tmp_ship);
                    ship_size[size - 1]--;
                }
            }
            else if (ship_size[size - 1] == 1)
            {
                shipColumn = 'J';
                shipRow = 5;
                Ship tmp_ship(size);
                for (int j = 1; j <= size; j++)
                {
                    gameBoard[shipRow - j + 1][ConvertColumn(shipColumn)] = 'S';
                    tmp_ship.Add_coordinate(shipRow - j + 1, ConvertColumn(shipColumn));
                }
                player_ships.push_back(tmp_ship);
                ship_size[size - 1]--;
            }
        }
    }
    //Устанавливаем случайным образом одноклеточные корабли (4 шт).
    for (int i = 0; i < 4; i++)
    {
        bool correct_input = false;
        while (!correct_input)
        {
            int size = 1;
            ship_size[size - 1]--;
            shipDirection = 'H';//Для одноклеточных кораблей направление не имеет значения
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
    }
    PrintBoard();
}

void OptimalGamer::Choose_coordinates_for_attack(int& coord_row, char& coord_column) {
    coord_row = rand() % 10;
    int Column_num = rand() % 10;
    coord_column = Define_name_column_by_num(Column_num);
}