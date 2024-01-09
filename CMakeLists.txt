cmake_minimum_required(VERSION 3.18)
project(battleships_semestralka)

set(CMAKE_CXX_STANDARD 17)

add_executable(battleships_semestralka_server mainServerClient.cpp
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

add_executable(battleships_semestralka_client mainClient.cpp
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

add_custom_target(All)
add_dependencies(All battleships_semestralka_client battleships_semestralka_server)
add_custom_target(
       Clean
       COMMAND rm -f battleships_semestralka_client
       COMMAND rm -f battleships_semestralka_server
)

target_link_libraries(battleships_semestralka_server pthread)
target_link_libraries(battleships_semestralka_client pthread)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
