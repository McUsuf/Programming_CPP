#pragma once

#include <vector>

class Ship
{
private:
    int length_of_the_ship = 0;
    std::vector<std::pair<int, int>> coordinates_of_ship;
public:
    explicit Ship(int length);

    int Get_length();//Длина корабля

    void Add_coordinate(int row, int column);//Набор элементов матрицы, которые заняты данным кораблем

    bool Check_for_hit(int row, int column);//Поврежден ли один из отсеков корабля

    std::vector<std::pair<int, int>> ReturnCoordinates();
};