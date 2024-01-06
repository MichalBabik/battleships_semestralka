cmake_minimum_required(VERSION 3.18)
project(battleships_semestralka)

set(CMAKE_CXX_STANDARD 17)

add_executable(battleships_semestralka main.cpp
                Battleship.cpp
                Battleship.h
                Board.cpp
                Board.h
                Game.cpp
                Game.h
                Client.cpp
                Client.h
                Server.cpp
                Server.h)

target_link_libraries(battleships_semestralka pthread)
