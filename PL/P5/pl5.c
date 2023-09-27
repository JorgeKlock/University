#include <stdio.h> 
#include <stdlib.h> 

extern FILE *yyin; // tiene que ser extern? 
int yyparse(); // Qué es esto??? 

FILE *open(int argc, char ** argv)
{
    FILE * fichero = NULL; 
    if (argc > 1)
    {
        fichero = fopen(argv[1], "r"); 
        if (fichero == NULL)
        {
            fprintf(stderr, "fichero no encontrado"); 
            exit(EXIT_FAILURE); 
        }
        else 
            printf("Procesando el archivo"); 
    }
    return fichero; 
}

int main (int argc, char **argv) 
{
    yyin = open(argc, argv); 
    return yyparse(); 
}