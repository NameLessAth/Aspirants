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

SRC_SIMPANAN = Simpanan.cpp
OBJ_SIMPANAN = ../bin/$(SRC_SIMPANAN:.cpp=.o)

SRC_TOKO = Toko.cpp
OBJ_TOKO = ../bin/$(SRC_TOKO:.cpp=.o)

SRC_LOAD = Load.cpp
OBJ_LOAD = ../bin/$(SRC_LOAD:.cpp=.o)

EXECUTABLE = ../bin/main_program

all: directories $(EXECUTABLE)

directories:
	mkdir -p ../bin

$(EXECUTABLE): $(OBJ_MAIN) $(OBJ_PEMAIN) $(OBJ_GAME) $(OBJ_MATRIX) $(OBJ_SIMPANAN) $(OBJ_TOKO) $(OBJ_LOAD)
	$(CC) $(CFLAGS) -o $@ $^

../bin/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLE) $(OBJ_MAIN) $(OBJ_PEMAIN) $(OBJ_GAME) $(OBJ_MATRIX) $(OBJ_SIMPANAN) $(OBJ_TOKO) $(OBJ_LOAD)

run: all
	$(EXECUTABLE)
	