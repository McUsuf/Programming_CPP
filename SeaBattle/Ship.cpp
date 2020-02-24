#include "Ship.h"

Ship::Ship(int length) {
    length_of_the_ship = length;
}

int Ship::Get_length() {
    return length_of_the_ship;
}

void Ship::Add_coordinate(int row, int column) {
    std::pair<int, int> newPairCoordinates;
    newPairCoordinates.first = row;
    newPairCoordinates.second = column;
    coordinates_of_ship.push_back(newPairCoordinates);
}

bool Ship::Check_for_hit(int row, int column) {
    for (auto& i : coordinates_of_ship)
    {
        if (i.first == row && i.second == column) {
            length_of_the_ship--;
            return true;
        }
    }
    return false;
}

std::vector<std::pair<int, int>> Ship::ReturnCoordinates() {
    return coordinates_of_ship;
}