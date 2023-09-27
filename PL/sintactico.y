/* P3 ESPECIFICACIÓN SINTÁCTICA */
%{
#define YYSTYPE double
#include <stdio.h>
#define KBLU  "\x1B[34m"
#define KNRM  "\x1B[0m"

%}
%error-verbose
%start S
%token IDENTIFICADOR
%token TIPO_DATO_BASICO
%token LISTA
%token SI
%token MIENTRAS
%token PARA
%token BAJANDO_HASTA
%token HASTA
%token HACER
%token SALIDA ENTRADA
%token SINO
%token RETORNO
%token PRINCIPAL
%token VAR VAREND
%token PIZQ PDCH
%token CIZQ CDCH
%token PUNTO COMA COMILLAS_DOBLES
%token COR_ABRE COR_CIERRA
%token COMIENZO_LISTA
%token MOV_CURSOR
%token ARROBA
%token ALFABETICO
%token NUMERICO
%token BOOLEANO
%token C_ESPE
%token PYC
%token OP_ASIGNACION
%token ALFABETICOPRIO


%left OP_BINARIO
%left ADITIVO
%left MULTIPLICATIVO
%left ALMOHADILLA
%left EXCLAINTER
%right ARROBA
%right MASMAS



%%

S	: cabezaPrograma bloque
	;

cabezaPrograma : PRINCIPAL
	;

bloque	: inicio_bloque declar_var_locales declar_subprogs sentencias fin_bloque
	| inicio_bloque declar_var_locales declar_subprogs  fin_bloque
	;

declar_subprogs: declar_subprogs declar_subprog
	|
	;

declar_subprog: cabecera_subprog bloque
	;

declar_var_locales : marca_ini_declar_variables variables_locales marca_fin_declar_variables
	|  marca_ini_declar_variables marca_fin_declar_variables
	|
	;

marca_ini_declar_variables: VAR
	;

marca_fin_declar_variables: VAREND
	;

inicio_bloque : CIZQ
	;

fin_bloque : CDCH
	;

variables_locales : variables_locales cuerpo_declar_var
	| cuerpo_declar_var
	;

cuerpo_declar_var : tipo_dato sentencia_asignacion
	;

tipo_dato : TIPO_DATO_BASICO
	| tipo_de_dato_compuesto
	;

tipo_de_dato_compuesto: LISTA TIPO_DATO_BASICO
	;

cabecera_subprog : tipo_dato IDENTIFICADOR PIZQ parametros PDCH
	| tipo_dato IDENTIFICADOR PIZQ PDCH
	;

parametros : parametros coma parametro
	| parametro
	;

parametros_predefinidos: parametro_predefinido coma parametro_predefinido
	| parametro_predefinido
	|
	;

parametro : tipo_dato IDENTIFICADOR
	;

parametro_predefinido: IDENTIFICADOR
	| llamada_funcion
	;

sentencias : sentencias sentencia
	| sentencia
	;


sentencia : bloque
	| sentencia_asignacion
	| sentencia_if
	| sentencia_while
	| sentencia_for
	| sentencia_entrada
	| sentencia_salida
	| llamada_funcion
	| sentencia_lista
	| retorno
	;

retorno : RETORNO expresion
	;

sentencia_asignacion : IDENTIFICADOR OP_ASIGNACION expresion punto_coma
	| IDENTIFICADOR coma sentencia_asignacion
	| error
	;

sentencia_if : SI PIZQ expresion PDCH sentencia
	| SI PIZQ expresion PDCH sentencia SINO sentencia
	;

sentencia_while : MIENTRAS PIZQ expresion PDCH sentencia
	;

sentencia_for : PARA sentencia_asignacion HASTA expresion HACER sentencia
	| PARA sentencia_asignacion BAJANDO_HASTA expresion HACER sentencia
	;

sentencia_entrada : nombre_entrada PIZQ lista_variables PDCH
	;

nombre_entrada : ENTRADA
	;
lista_variables : IDENTIFICADOR
	| lista_variables COMA IDENTIFICADOR
	;
sentencia_salida : SALIDA PIZQ lista_de_expresiones PDCH
	;

sentencia_lista : IDENTIFICADOR MOV_CURSOR
	| COMIENZO_LISTA IDENTIFICADOR
	;

lista_de_expresiones : expresion
	| lista_de_expresiones COMA expresion
	;



expresion : PIZQ expresion PDCH
	| ALMOHADILLA expresion %prec ALMOHADILLA
	| EXCLAINTER expresion %prec ALMOHADILLA
	| expresion OP_BINARIO expresion %prec ALMOHADILLA
	| expresion MULTIPLICATIVO expresion %prec ALMOHADILLA
	| expresion ADITIVO expresion %prec ALMOHADILLA
	| IDENTIFICADOR
	| constante
	| llamada_funcion
	| expresion MASMAS expresion ARROBA expresion %prec ALMOHADILLA
	| sentencia_lista
	| tratamiento_error
	;

llamada_funcion : IDENTIFICADOR PIZQ parametros_predefinidos PDCH
	;

constante : NUMERICO 
	| real
	| BOOLEANO
	| lista
	| cadena
	;

lista : COR_ABRE agregado COR_CIERRA
	;

agregado : expresion
	| agregado COMA expresion
	;

cadena : COMILLAS_DOBLES contenido_cadena COMILLAS_DOBLES
	| ALFABETICOPRIO
	;

contenido_cadena : contenido_cadena ALFABETICO
	| contenido_cadena NUMERICO
	| contenido_cadena C_ESPE
	| contenido_cadena EXCLAINTER
	|
	;

real 	: NUMERICO PUNTO NUMERICO
	;

punto_coma : PYC
	;

coma : COMA
	| error
	;

tratamiento_error : error
	;
%%

#include "lex.yy.c"

extern FILE * yyin;

main(int argc, char **argv) 
{
	if (argc > 1) {
		 yyin = fopen(argv[1],"r");
	}
	yydebug=0;
	yyparse();
}

yyerror(char *s) {
	printf( "%sERROR SINTACTICO linea %d: %s%s\n",KBLU,linea,s,KNRM);
}
