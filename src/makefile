CC = g++
CFLAGS = -Wall -g

SRC_MAIN = main.cpp
OBJ_MAIN = ../bin/$(SRC_MAIN:.cpp=.o)

SRC_GAME = Game.cpp
OBJ_GAME = ../bin/$(SRC_GAME:.cpp=.o)

SRC_PEMAIN = Pemain.cpp
OBJ_PEMAIN = ../bin/$(SRC_PEMAIN:.cpp=.o)

SRC_MATRIX = Matrix.cpp
OBJ_MATRIX = ../bin/$(SRC_MATRIX:.cpp=.o)

EXECUTABLE = ../bin/main_program

all: directories $(EXECUTABLE)

directories:
	mkdir -p ../bin

$(EXECUTABLE): $(OBJ_MAIN) $(OBJ_PEMAIN) $(OBJ_GAME) $(OBJ_MATRIX) 
	$(CC) $(CFLAGS) -o $@ $^

../bin/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLE) $(OBJ_MAIN) $(OBJ_PEMAIN) $(OBJ_GAME) $(OBJ_MATRIX) 

run: all
	$(EXECUTABLE)
