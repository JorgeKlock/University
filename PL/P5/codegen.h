#include "definiciones.h"
#ifndef CODEGEN
    #define CODEGEN

    void openFile();

    void closeFile();

    char* variablesGlobales();

    char* generarIntermedio();

    char* concatenarConComa(char* izq, char* dch);

    char* concatenarTipoVariable(atributo izq, char* dch);
#endif
