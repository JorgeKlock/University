BIN = bin

SRC = src

OBJ = obj

LIB = lib

INCLUDE = include



$(BIN)/central: $(LIB)/libformas.a $(OBJ)/central.o
	g++ -o $(BIN)/central $(OBJ)/central.o -L$(LIB)/ -lformas 
$(LIB)/libformas.a: $(OBJ)/punto.o $(OBJ)/circulo.o 
	ar rsv $(LIB)/libformas.a $(OBJ)/punto.o $(OBJ)/circulo.o
$(OBJ)/central.o: $(SRC)/central.cpp
	g++ -c $(SRC)/central.cpp -std=c++0x -o $(OBJ)/central.o -I$(INCLUDE)
$(OBJ)/punto.o: $(SRC)/punto.cpp $(INCLUDE)/punto.h 
	g++ -c $(SRC)/punto.cpp -std=c++0x -o $(OBJ)/punto.o -I$(INCLUDE)/
$(OBJ)/circulo.o: $(SRC)/circulo.cpp $(INCLUDE)/circulo.h $(INCLUDE)/punto.h 
	g++ -c $(SRC)/circulo.cpp -std=c++0x -o $(OBJ)/circulo.o -I$(INCLUDE)/

#comprobado su funcionamiento correcto a 05/03/2019, creacion de libreria libformas.a y central.exe a partir del comando make
	
