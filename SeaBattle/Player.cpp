#include "Player.h"

char Define_name_column_by_num(int& num) {
    switch (num)
    {
        case 0:
            return 'A';
        case 1:
            return 'B';
        case 2:
            return 'C';
        case 3:
            return 'D';
        case 4:
            return 'E';
        case 5:
            return 'F';
        case 6:
            return 'G';
        case 7:
            return 'H';
        case 8:
            return 'I';
        case 9:
            return 'J';
        default:
            return 'Z';
    }
}

Gamer::Gamer() {
    //Создаем поле для игрока
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < columns; y++)
        {
            gameBoard[x][y] = '*';
            attackBoard[x][y] = '*';
        }
    }

    ship_size.push_back(4);//ship_size[0] = 4
    ship_size.push_back(3);//ship_size[1] = 3
    ship_size.push_back(2);//ship_size[2] = 2
    ship_size.push_back(1);//ship_size[3] = 1

    shipRow = 0;
    shipColumn = '-';
    shipDirection = '-';
}

int Gamer::Get_count_of_ships() {
    return count_ships;
}

void Gamer::PrintBoard() {
    std::cout << "\t\t<YOUR BOARD>" << std::endl;
    std::cout << "   [A][B][C][D][E][F][G][H][I][J]\n";

    for (int x = 0; x < rows; x++)
    {
        std::cout << "[" << x << "]";
        for (int y = 0; y < columns; y++)
        {
            std::cout << " " << gameBoard[x][y] << " ";
        }
        std::cout << std::endl;
    }
}

void Gamer::Print_attack_board() {
    std::cout << "\t\t<ENEMY BOARD>" << std::endl;
    std::cout << "   [A][B][C][D][E][F][G][H][I][J]\n";

    for (int x = 0; x < rows; x++)
    {
        std::cout << "[" << x << "]";
        for (int y = 0; y < columns; y++)
        {
            std::cout << " " << attackBoard[x][y] << " ";
        }
        std::cout << std::endl;
    }
}


//Определить по букве положение в массиве
int Gamer::ConvertColumn(char column) {
    switch (column) {
        case 'A': {
            return 0;
        }
        case 'B': {
            return 1;
        }
        case 'C': {
            return 2;
        }
        case 'D': {
            return 3;
        }
        case 'E': {
            return 4;
        }
        case 'F': {
            return 5;
        }
        case 'G': {
            return 6;
        }
        case 'H': {
            return 7;
        }
        case 'I': {
            return 8;
        }
        case 'J': {
            return 9;
        }
        default:
            return 'Z';
    }
}


//Проверка ввозможности разместить корабль
bool Gamer::ValidCoordinate(int curr_shipRow, char curr_shipColumn, char direction, int size_of_ship) {
    int good_cords = 0;//Число правильных координат корабля, должно быть равно его размеру, если все корректно
    int tmp = int(curr_shipColumn);
    if ((curr_shipRow >= 0 && curr_shipRow <= rows - 1) && (tmp >= 65 && tmp <= 74))
    {
        if (direction == 'H')
        {
            for (int i = 1; (i <= size_of_ship) && (ConvertColumn(curr_shipColumn) + i - 1 < columns); i++) {
                if (gameBoard[curr_shipRow][(ConvertColumn(curr_shipColumn)) + i - 1] == '*')
                    good_cords++;

                if (curr_shipRow - 1 >= 0)
                {
                    if (gameBoard[curr_shipRow - 1][(ConvertColumn(curr_shipColumn)) + i - 1] != '*')
                        good_cords--;
                }

                if (curr_shipRow + 1 <= rows - 1)
                {
                    if (gameBoard[curr_shipRow + 1][(ConvertColumn(curr_shipColumn)) + i - 1] != '*')
                        good_cords--;
                }
            }

            if (ConvertColumn(curr_shipColumn) - 1 >= 0)
            {
                if (gameBoard[curr_shipRow][(ConvertColumn(curr_shipColumn)) - 1] != '*')
                    good_cords--;

                if (curr_shipRow - 1 >= 0)
                {
                    if (gameBoard[curr_shipRow - 1][(ConvertColumn(curr_shipColumn)) - 1] != '*')
                        good_cords--;
                }

                if (curr_shipRow + 1 <= rows - 1)
                {
                    if (gameBoard[curr_shipRow + 1][(ConvertColumn(curr_shipColumn)) - 1] != '*')
                        good_cords--;
                }
            }

            if (ConvertColumn(curr_shipColumn) + size_of_ship <= columns - 1)
            {
                if (gameBoard[curr_shipRow][(ConvertColumn(curr_shipColumn)) + size_of_ship] != '*')
                    good_cords--;

                if (curr_shipRow - 1 >= 0)
                {
                    if (gameBoard[curr_shipRow - 1][(ConvertColumn(curr_shipColumn)) + size_of_ship] != '*')
                        good_cords--;
                }

                if (curr_shipRow + 1 <= rows - 1)
                {
                    if (gameBoard[curr_shipRow + 1][(ConvertColumn(curr_shipColumn)) + size_of_ship] != '*')
                        good_cords--;
                }
            }
        }
        else if (direction == 'V')
        {
            for (int i = 1; (i <= size_of_ship) && curr_shipRow - i + 1 >= 0; i++) {
                if (gameBoard[curr_shipRow - i + 1][ConvertColumn(curr_shipColumn)] == '*')
                    good_cords++;

                if (ConvertColumn(curr_shipColumn) - 1 >= 0)
                {
                    if (gameBoard[curr_shipRow - i + 1][ConvertColumn(curr_shipColumn) - 1] != '*')
                        good_cords--;
                }

                if (ConvertColumn(curr_shipColumn) + 1 <= columns - 1)
                {
                    if (gameBoard[curr_shipRow - i + 1][ConvertColumn(curr_shipColumn) + 1] != '*')
                        good_cords--;
                }
            }

            if (curr_shipRow - size_of_ship >= 0)
            {
                if (gameBoard[curr_shipRow - size_of_ship][ConvertColumn(curr_shipColumn)] != '*')
                    good_cords--;

                if (ConvertColumn(curr_shipColumn) - 1 >= 0)
                {
                    if (gameBoard[curr_shipRow - size_of_ship][ConvertColumn(curr_shipColumn) - 1] != '*')
                        good_cords--;
                }

                if (ConvertColumn(curr_shipColumn) + 1 <= columns - 1)
                {
                    if (gameBoard[curr_shipRow - size_of_ship][ConvertColumn(curr_shipColumn) + 1] != '*')
                        good_cords--;
                }
            }

            if (curr_shipRow + 1 <= rows - 1)
            {
                if (gameBoard[curr_shipRow + 1][ConvertColumn(curr_shipColumn)] != '*')
                    good_cords--;

                if (ConvertColumn(curr_shipColumn) - 1 >= 0)
                {
                    if (gameBoard[curr_shipRow + 1][ConvertColumn(curr_shipColumn) - 1] != '*')
                        good_cords--;
                }

                if (ConvertColumn(curr_shipColumn) + 1 <= columns - 1)
                {
                    if (gameBoard[curr_shipRow + 1][ConvertColumn(curr_shipColumn) + 1] != '*')
                        good_cords--;
                }
            }
        }
    }
    return good_cords == size_of_ship;
}


char Gamer::Find_on_attack_board(int row, char column) {
    int column_num = ConvertColumn(column);
    return (attackBoard[row][column_num]);
}

char Gamer::Find(int row, char column) {
    int column_num = ConvertColumn(column);
    return (gameBoard[row][column_num]);
}

bool Gamer::Check_for_win() {
    return count_ships == 0;
}

void Gamer::Get_Fire(int row, char column, Gamer* enemy) {
    bool retry = true;//Повторная попытка если пользователь ввел координаты, которые уже проверял ранее
    while (retry)
    {
        char PotentialRetry = Find_on_attack_board(row, column);//Ищем введенные координаты на поле противника
        if (PotentialRetry == '#' || (PotentialRetry == 'O' && enemy->return_type_player() == optimal_player))
        {
            //Если в данной координате уже был допущен промах
            if (enemy->return_type_player() == console_player)
            {
                std::cout << "You have already missed at this location! Please retry!\n";
            }
            enemy->Choose_coordinates_for_attack(row, column);
            continue;
        }
        if (PotentialRetry == 'H' || PotentialRetry == 'X')
        {
            //Если в данной позиции уже был нанесен удар или в ней обломки убитого корабля
            if (enemy->return_type_player() == console_player)
            {
                std::cout << "You have already heated at this location! Please retry!\n";
            }
            enemy->Choose_coordinates_for_attack(row, column);
            continue;
        }
        retry = false;
    }

    char location = Find(row, column);//Проверяем на карте с кораблями, куда попал удар
    if (location == '*')
    {
        //Пустая клетка
        if (enemy->return_type_player() == console_player)
        {
            std::cout << "You have missed at position:[" << column << "][" << row << "]\n";
        }
        else if (enemy->return_type_player() == random_player)
        {
            std::cout << "CPU(random) have missed at position:[" << column << "][" << row << "]\n";
        }
        else if (enemy->return_type_player() == optimal_player)
        {
            std::cout << "CPU(optimal) have missed at position:[" << column << "][" << row << "]\n";
        }
        attackBoard[row][ConvertColumn(column)] = '#';//M - missed промах
        return;
    }
    else if (location == 'S')
    {
        //Палуба корабля
        //Проверяем в какой из кораблей мы попали
        for (auto& player_ship : player_ships)
        {
            if (player_ship.Check_for_hit(row, ConvertColumn(column)))
            {
                if (enemy->return_type_player() == console_player)
                {
                    std::cout << "You hit at location:[" << column << "][" << row << "]\n";
                }
                else if (enemy->return_type_player() == random_player)
                {
                    std::cout << "CPU(random) hit at location:[" << column << "][" << row << "]\n";
                }
                else if (enemy->return_type_player() == optimal_player)
                {
                    std::cout << "CPU(optimal) hit at location:[" << column << "][" << row << "]\n";
                }

                attackBoard[row][ConvertColumn(column)] = 'H';//H - hit нанесен урон палубе
                gameBoard[row][ConvertColumn(column)] = 'H';
                //Если это была последняя палуба корабля
                if (player_ship.Get_length() == 0)
                {
                    count_ships--;

                    if (enemy->return_type_player() == console_player)
                    {
                        std::cout << "You sunk a ship!\n";
                    }
                    else if (enemy->return_type_player() == random_player)
                    {
                        std::cout << "CPU(random) sunk a ship!\n";
                    }
                    else if (enemy->return_type_player() == optimal_player)
                    {
                        std::cout << "CPU(optimal) sunk a ship!\n";
                    }

                    std::vector<std::pair<int, int>> ship_coords = player_ship.ReturnCoordinates();
                    for (auto& ship_coord : ship_coords)
                    {
                        gameBoard[ship_coord.first][ship_coord.second] = 'X';
                        attackBoard[ship_coord.first][ship_coord.second] = 'X';

                        if (enemy->return_type_player() == optimal_player)
                        {
                            //Клетки окружения уничтоженного корабля рассматриваться не будут в дальнейшем (если противник наносивший удар умный ИИ)
                            if (ship_coord.first - 1 >= 0 && attackBoard[ship_coord.first - 1][ship_coord.second] != 'X')
                            {
                                attackBoard[ship_coord.first - 1][ship_coord.second] = 'O';

                                if (ship_coord.second + 1 <= columns - 1 && attackBoard[ship_coord.first - 1][ship_coord.second + 1] != 'X')
                                    attackBoard[ship_coord.first - 1][ship_coord.second + 1] = 'O';

                                if (ship_coord.second - 1 >= 0 && attackBoard[ship_coord.first - 1][ship_coord.second - 1] != 'X')
                                    attackBoard[ship_coord.first - 1][ship_coord.second - 1] = 'O';
                            }

                            if (ship_coord.first + 1 <= rows - 1 && attackBoard[ship_coord.first + 1][ship_coord.second] != 'X')
                            {
                                attackBoard[ship_coord.first + 1][ship_coord.second] = 'O';

                                if (ship_coord.second + 1 <= columns - 1 && attackBoard[ship_coord.first][ship_coord.second + 1] != 'X')
                                    attackBoard[ship_coord.first + 1][ship_coord.second + 1] = 'O';

                                if (ship_coord.second - 1 >= 0 && attackBoard[ship_coord.first][ship_coord.second - 1] != 'X')
                                    attackBoard[ship_coord.first + 1][ship_coord.second - 1] = 'O';
                            }

                            if (ship_coord.second + 1 <= columns - 1 && attackBoard[ship_coord.first][ship_coord.second + 1] != 'X')
                                attackBoard[ship_coord.first][ship_coord.second + 1] = 'O';

                            if (ship_coord.second - 1 >= 0 && attackBoard[ship_coord.first][ship_coord.second - 1] != 'X')
                                attackBoard[ship_coord.first][ship_coord.second - 1] = 'O';
                        }
                    }
                }
            }
        }
    }
}