BIN = bin
SRC = src

OBJ = obj

LIB = lib

INCLUDE = include



$(BIN)/main: $(LIB)/libfrutas.a $(OBJ)/main.o
	g++ -o $(BIN)/main $(OBJ)/main.o -L$(LIB)/ -lfrutas
$(LIB)/libfrutas.a: $(OBJ)/producto.o $(OBJ)/compra.o 
	ar rsv $(LIB)/libfrutas.a $(OBJ)/producto.o $(OBJ)/compra.o
$(OBJ)/main.o: $(SRC)/main.cpp
	g++ -c $(SRC)/main.cpp -std=c++11 -o $(OBJ)/main.o -I$(INCLUDE)
$(OBJ)/producto.o: $(SRC)/producto.cpp $(INCLUDE)/producto.h 
	g++ -c $(SRC)/producto.cpp -std=c++11 -o $(OBJ)/producto.o -I$(INCLUDE)/
$(OBJ)/compra.o: $(SRC)/compra.cpp $(INCLUDE)/compra.h $(INCLUDE)/producto.h 
	g++ -c $(SRC)/compra.cpp -std=c++11 -o $(OBJ)/compra.o -I$(INCLUDE)/

#comprobado su funcionamiento correcto a 05/03/2019