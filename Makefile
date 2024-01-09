CXX = g++
CXXFLAGS = -std=c++11 -Wall
EXECUTABLE_CLIENT = battleships_semestralka_client
EXECUTABLE_SERVER_CLIENT = battleships_semestralka_server

SRC_FILES_CLIENT = mainClient.cpp Client.cpp Board.cpp Battleship.cpp Game.cpp
SRC_FILES_SERVER_CLIENT = mainServerClient.cpp Server.cpp Client.cpp Board.cpp Battleship.cpp Game.cpp

OBJ_FILES_CLIENT = $(SRC_FILES_CLIENT:.cpp=.o)
OBJ_FILES_SERVER_CLIENT = $(SRC_FILES_SERVER_CLIENT:.cpp=.o)

all: $(EXECUTABLE_CLIENT) $(EXECUTABLE_SERVER_CLIENT)

$(EXECUTABLE_CLIENT): $(OBJ_FILES_CLIENT)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(EXECUTABLE_SERVER_CLIENT): $(OBJ_FILES_SERVER_CLIENT)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES_CLIENT) $(OBJ_FILES_SERVER_CLIENT) $(EXECUTABLE_CLIENT) $(EXECUTABLE_SERVER_CLIENT)

