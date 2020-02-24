cmake_minimum_required(VERSION 3.14)
project(Botvinko_SeaBattle)

set(CMAKE_CXX_STANDARD 14)

add_executable(Botvinko_SeaBattle main.cpp Player.cpp Player.h Ship.cpp Ship.h GameInterface.cpp GameInterface.h OptimalGamer.cpp RandomGamer.cpp ConsoleGamer.cpp)