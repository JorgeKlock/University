/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "sintactico.y" /* yacc.c:339  */

#include <stdio.h>
#include<stdbool.h>  
#include "definiciones.h"
#define KBLU  "\x1B[34m"
#define KNRM  "\x1B[0m"
#define GREEN "\033[0;32m"
#define YELLOW  "\033[33m"
#define KCYN  "\x1B[36m"

#define MAX_TS 500



unsigned long int TOPE=0 ;

typedef enum {
	marca,
	funcion,
	variable,
	parametro_formal,
	descriptor
} tipoEntrada ;


dtipo TIPO;
dtipo SUBTIPO;
int DIM = 0;
char* NOMBRE_F;
bool doMostrarTabla = false;


typedef struct {
	tipoEntrada entrada;
	char *nombre;
	dtipo tipoDato;
	unsigned int parametros;
	unsigned int dimension;
	dtipo subTipoLista;
	DescriptorDeInstrControl descriptor;
} entradaTS ;

char* variables;


#define YYSTYPE atributo


entradaTS tablaSimbolos[MAX_TS];


/*FUNCIONES DE MANEJO DE LA TS*/

void introducirBloque(tipoEntrada tipoE, char* nombre, dtipo tipoD, int param, int dimen, dtipo subTipo){

	TOPE += 1;

	if(TOPE >= MAX_TS){

		printf("Error, TABLA DE SIMBOLOS LLENA");

	} else {

		tablaSimbolos[TOPE].entrada = tipoE;
		tablaSimbolos[TOPE].nombre = nombre;
		tablaSimbolos[TOPE].tipoDato = tipoD;
		tablaSimbolos[TOPE].parametros = param;
		tablaSimbolos[TOPE].dimension = dimen;
		tablaSimbolos[TOPE].subTipoLista = subTipo;
	}

	if(doMostrarTabla){
		mostrarTabla();
	}
}

void introducirIdentificador(tipoEntrada tipoE, char* nombre, dtipo tipoD, int param, int dimen,dtipo subtipo){
	
	bool duplicado = false;
    	bool findebloque = false;
	//El identificador no debe encontarse en el mismo bloque ya definido
	for(int i = 0 ; i < TOPE ; i++){
		if (tablaSimbolos[TOPE-i].entrada == 0 )
		{
		   findebloque = true;
		   if(tablaSimbolos[TOPE-1-i].entrada == funcion){
			for(int j = 1 ; j <= tablaSimbolos[TOPE-1-i].parametros  ; j++){
				if(strcmp(tablaSimbolos[TOPE-1-i-j].nombre,nombre) == 0){
					printf("ERROR, la entrada de nombre [%s] ya esta definida en sus parametros\n",nombre);
					duplicado = true;
				}
			}
		   }
		}
		else if(strcmp(tablaSimbolos[TOPE-i].nombre,nombre) == 0 && !findebloque){
			printf("ERROR, la entrada de nombre [%s] ya existe en ese bloque\n",nombre);
			duplicado = true;
		}
	}
	
	if( !duplicado ) {
		if(tipoD == lista)
		{
			introducirBloque(tipoE,nombre,tipoD,param,dimen,subtipo);
		} else {
			introducirBloque(tipoE,nombre,tipoD,param,dimen,noasignado);
		}
	}

	
}

void eliminarBloque(){


	while(tablaSimbolos[TOPE].entrada != marca ){

		TOPE -= 1;

		if(TOPE < 0){

			printf("Error, NO SE INTRODUJO NINGUN BLOQUE");

		}
	}

	TOPE -= 1;

	if(TOPE < 0){

		printf("Error, NO SE INTRODUJO NINGUN BLOQUE");

	}

	if(doMostrarTabla){
		mostrarTabla();
	}


}

void mostrarTabla(){



	printf("_________________________________________________________________________________________________\n");

	printf("\n|    INDICE \t|    NOMBRE \t|     ENTRADA \t|    TIPO \t|  PARAMETROS \t|    DIMENSION \t|    SUBTIPO \t|\n");

	for(int i = 1; i <= TOPE; i++){
		
		printf("|\t %d \t|\t",i);
		printf("%s \t|\t",tablaSimbolos[i].nombre);
		printf("%d \t|\t",tablaSimbolos[i].entrada);
		printf("%d \t|\t",tablaSimbolos[i].tipoDato);
		printf("%d \t|\t",tablaSimbolos[i].parametros);
		printf("%d \t|\t",tablaSimbolos[i].dimension);
		printf("%d \t|\n",tablaSimbolos[i].subTipoLista);
		
	}

	printf("_________________________________________________________________________________________________\n");


}

atributo comprobacionOperacionMasMenos(atributo op1 , atributo op2 , atributo operador){

	atributo resultante;
	resultante.tipo = noasignado;

	if(op1.tipo == (booleano|caracter) || op2.tipo == (booleano|caracter))
	{
		printf( "%sERROR SEMÁNTICO: operacion no compatible con booleanos ni caracteres %s\n",GREEN,KNRM);
	}
	// Sumas
	else if (operador.atrib==0)
	{
		// Lista y numero
		if(op1.tipo == lista && op2.tipo == (entero|real))
		{
			resultante.tipo = lista;
		}
		// Numero y lista
		else if(op1.tipo == (entero|real) && op2.tipo == lista)
		{
			resultante.tipo = lista;
		}
		// Numero y numero
		else if(op1.tipo == real || op2.tipo == real)
		{
			resultante.tipo = real;
		}
		else
		{
			resultante.tipo = entero;
		}

	}
	// Restas
	else if (operador.atrib==1)
	{
		if(op2.tipo == lista)
		{
			printf( "%sERROR SEMÁNTICO: no se esperaba lista a la derecha de una operacion '-' %s\n",GREEN,KNRM);
		}
		// Lista y numero
		else if(op1.tipo == lista && op2.tipo == (entero|real))
		{
			resultante.tipo = lista;
		}
		// Numero y numero
		else if(op1.tipo == real || op2.tipo == real)
		{
			resultante.tipo = real;
		}
		else
		{
			resultante.tipo = entero;
		}

	}
	// Casos de Error
	else
	{
		printf( "%sERROR SEMÁNTICO sumaresta: tipo no compatible con operación '%s' (%s,%s) %s\n",GREEN,operador.lexema,op1.lexema,op2.lexema,KNRM);
	}

	return resultante;
}

atributo comprobacionOperacionMultiplicativa(atributo op1, atributo op2, atributo operador)
{
	atributo resultante;
	resultante.tipo = noasignado;

	// Casos concretos con listas
	if(op1.tipo == lista) // y es una lista de enteros o reales COMPROBAR
	{
		if(op2.tipo == (entero | real))
		{
			resultante.tipo = lista;
		}
		else
		{
			printf( "ERROR SEMÁNTICO: no se puede realizar esa operación con listas" );
		}
	}
	else if (op2.tipo == lista) // y es una lista de enteros o reales COMPROBAR
	{
		if(operador.atrib != 0 || op1.tipo != (entero | real))
		{
			printf( "ERROR SEMÁNTICO: no se puede realizar esa operación con listas" );
		}
		else
		{
			resultante.tipo = lista;
		}
	}

	// Casos siempre correctos

	else if ((op1.tipo == entero || op1.tipo == real) && (op2.tipo == entero || op2.tipo == real))
	{
		if(operador.atrib == (1 | 2))
		{
			//Comprobaríamos la división por 0
		}

		if(op1.tipo == real || op2.tipo == real)
		{
			resultante.tipo = real;
		}
		else
		{
			resultante.tipo = entero;
		}
	}

	// El resto son incorrectos

	else
	{
		printf( "%sERROR SEMÁNTICO: tipo no compatible con operación '*' (%d,%d) %s\n",GREEN,op1.tipo,op2.tipo,KNRM);
	}

	return resultante;
}
atributo comprobacionBinaria(atributo op1, atributo op2, atributo operador)
{
	atributo resultante;
	resultante.tipo = noasignado;

	//printf( "%sCOMPROBACION BINARIA DE LA OPERACION %s PARA (%s,%s) con tipos %d , %d %s\n",YELLOW,operador.lexema,op1.lexema,op2.lexema,op1.tipo,op2.tipo,KNRM);

	// Casos concretos con listas
	if(op1.tipo == lista) // Si el primer operador es lista
	{
		if(operador.atrib == 9) // Y la operacion es el --
		{
			// El segundo operador debe ser entero y se devuelve lista
			if(op2.tipo == entero)
			{
				resultante.tipo = lista;
			}
			else
			{
				printf( "%sERROR SEMÁNTICO op_bin: tipo no compatible con operación '--' (%s,%s) %s\n",GREEN,op1.lexema,op2.lexema,KNRM);
			}
		}

		if(operador.atrib == 10) // Y la operacion es el * *
		{
			// El segundo operador debe ser una lista y se devuelve lista
			if(op2.tipo == lista)
			{
				resultante.tipo = lista;
			}
			else
			{
				printf( "%sERROR SEMÁNTICO op_bin: tipo no compatible con operación '**' (%s,%s) %s\n",GREEN,op1.lexema,op2.lexema,KNRM);
			}
		}

		else
		{
			printf( "%sERROR SEMÁNTICO op_bin: tipo no compatible con operación '%s' (%s,%s) %s\n",GREEN,operador.lexema,op1.lexema,op2.lexema,KNRM);
		}
	}

	// Casos que siempre son correctos

	else if ((op1.tipo == entero ||op1.tipo ==real||op1.tipo ==booleano) && (op2.tipo == entero ||op2.tipo ==real||op2.tipo ==booleano))
	{
		resultante.tipo = booleano;
	}

	//En cualquier otro caso es incorrecto
	else
	{
		printf( "%sERROR SEMÁNTICO op_bin_r: tipo no compatible con operación '%s' (%s,%s) %s\n",GREEN,operador.lexema,op1.lexema,op2.lexema,KNRM);
	}

	return resultante;
}

atributo comprobacionExclaInter(atributo op1, atributo operador)
{
	atributo resultante;
	resultante.tipo = noasignado;

	if (operador.atrib == 0)
	{
		resultante.tipo = op1.subt;
		//printf( "%sCOMPROBACION EXCLAINTER %s CON RESULTADO %d %s\n",YELLOW,operador.lexema,op1.subt,KNRM);
	}
	else if (operador.atrib == 1)
	{
		if(op1.tipo == lista)
		{
			resultante.tipo = op1.subt;
			//printf( "%sCOMPROBACION EXCLAINTER %s CON RESULTADO %d %s\n",YELLOW,operador.lexema,op1.subt,KNRM);
		}
		else
		{
			printf( "%sERROR SEMÁNTICO: tipo no compatible con operación '%s' (%s) %s\n",GREEN,operador.lexema,op1.lexema,KNRM);
		}
	}
	else
	{
		printf( "%sERROR SEMÁNTICO exclainter: tipo no compatible con operación '%s' (%s) %s\n",GREEN,operador.lexema,op1.lexema,KNRM);
	}

	return resultante;
}

atributo comprobacionAlmohadilla(atributo op1, atributo operador)
{
	atributo resultante;
	resultante.tipo = noasignado;

	if (op1.tipo == lista)
	{
		resultante.tipo = entero;
	}
	else
	{
		printf( "%sERROR SEMÁNTICO almohadilla: tipo no compatible con operación '%s' (%s) %s\n",GREEN,operador.lexema,op1.lexema,KNRM);
	}
	return resultante;
}

atributo comprobacionArroba(atributo op1, atributo op2, atributo operador)
{
	atributo resultante;
	resultante.tipo = noasignado;

	if ((op1.tipo == lista) && (op2.tipo == entero))
	{
		//printf( "%sCOMPROBACION ARROBA %s CON RESULTADO %d %s\n",YELLOW,operador.lexema,op1.subt,KNRM);
		resultante.tipo =op1.subt;
	}
	else
	{
		printf( "%sERROR SEMÁNTICO arroba: tipo no compatible con operación '%s' (%s) %s\n",GREEN,operador.lexema,op1.lexema,KNRM);
	}
	return resultante;
}

atributo comprobacionTernaria(atributo op1, atributo op2, atributo op3, atributo operando1, atributo operando2)
{
	atributo resultante;
	resultante.tipo = noasignado;

	if( (op1.tipo == lista) && (op2.tipo != lista) && (op3.tipo == entero) )
	{
		resultante.tipo = lista;
	}
	else
	{
		printf( "%sERROR SEMÁNTICO: tipo no compatible con operación '++ @' (%s,%s,%s) %s\n",GREEN,op1.lexema,op2.lexema,op3.lexema,KNRM);
	}
	return resultante;
}

atributo EsLista(atributo op1)
{
	if(op1.tipo != lista)
	{
		printf( "%sERROR SEMÁNTICO: La operacion solo es realizable sobre listas %s\n",GREEN,KNRM);
	}

	
}


// Se encarga de buscar para un identificador de una expresion su atributo en la tabla
atributo buscarVariableDefinida(atributo entrada){

	atributo encontrado;
	bool definido = false;

	for(int i = TOPE ; i > 0 ; i-- ){
		if((strcmp(entrada.lexema, tablaSimbolos[i].nombre)) == 0){
			encontrado.tipo = tablaSimbolos[i].tipoDato;
			encontrado.lexema = tablaSimbolos[i].nombre;
			encontrado.cantidad = tablaSimbolos[i].parametros;
			encontrado.subt = tablaSimbolos[i].subTipoLista;
			definido = true;
		}
	}

	if(!definido){
		printf( "%sERROR SEMÁNTICO : la variable (%s) no esta definida %s\n",GREEN,entrada.lexema,KNRM);
		//¿Deberiamos detener el analisis si el programa encuentra una variable no definida?
		encontrado.lexema = entrada.lexema;
		encontrado.tipo = entrada.tipo;
	}

	return encontrado;

}

ComprobacionLlamadaFuncion(atributo nombre_funcion, atributo parametros_predefinidos)
{
    atributo encontrado;
    // Comprobar que la función existe

    encontrado = buscarVariableDefinida(nombre_funcion);

    // Comprobar que el numero y tipo de parámetros es correcto


    if (encontrado.cantidad != parametros_predefinidos.cantidad)
    {
        printf( "%sERROR SEMÁNTICO: Cantidad de parámetros incorrecta, se esperaban %i y se proporcionaron %i %s\n",GREEN, encontrado.cantidad, parametros_predefinidos.cantidad, KNRM);
    }
}

comprobarTipoParametro(atributo parametro, atributo parametros)
{
    atributo nombre_funcion;

    //NOMBRE_F

    //printf( "%sComprobando el tipo del parametro numero %i. Nombre del parametro: %s Tipo: %i %s\n",GREEN, parametros.cantidad, parametro.lexema, parametro.tipo ,KNRM);

    // Nos movemos hasta la ubicacion de la TS donde esta NOMBRE_F, y subimos tantas posiciones como parametros tenga - parametros.cantidad
    for(int i = TOPE ; i > 0 ; i-- )
    {
    		if((strcmp(NOMBRE_F, tablaSimbolos[i].nombre)) == 0)
    		{
    			// Comprobamos que el tipo del parámetro número i coincide con el actual
    			int n_parametros = tablaSimbolos[i].parametros;
    			int posicion = i-(n_parametros - parametros.cantidad)-1;
    			if ( tablaSimbolos[posicion].tipoDato != parametro.tipo )
    			{
    		        printf( "%sERROR SEMÁNTICO: Tipo del parametro %i incorrecto. Se esperaba %i y se encontro %i %s\n",GREEN, parametros.cantidad, tablaSimbolos[posicion].tipoDato, parametro.tipo,KNRM);
    		        printf( "%sINFO_ERROR: se han comparado las variables (%s,%s) %s\n",GREEN,tablaSimbolos[posicion].nombre, parametro.lexema,KNRM);
    		    }
    		}
    }

}

//Comprueba que en una asignación el tipo de la derecha coincide con el de la izquierda ( evita : entero a = Verdadero )

void comprobacionTiposAsignacion(int tipoIzq,int tipoDch,char* s){

	//Si es una lista intereda el subtipo
	if(tipoIzq != 4){
		if(tipoIzq != tipoDch){
			if( ! ( (tipoIzq == 0 && tipoDch == 1) || (tipoIzq == 1 && tipoDch == 0) ) ){
				printf( "%sERROR SEMÁNTICO : intentando asignar tipo %d a la variable \"%s\" de tipo %d %s\n",GREEN,tipoDch,s,tipoIzq,KNRM);
			}
			if( (tipoIzq == 0 && tipoDch == 1) ){
				printf( "%sWARNING : intentando asignar tipo real a tipo entero en variable  \"%s\"  %s\n",KCYN,s,KNRM);
			} 
		}
	} 
}

void comprobacionTiposAsignacionLista(int tipoIzq,int tipoDch,char* s){

	//Si es una lista intereda el subtipo
		if(tipoIzq != tipoDch){
			if( ! ( (tipoIzq == 0 && tipoDch == 1) || (tipoIzq == 1 && tipoDch == 0) ) ){
				printf( "%sERROR SEMÁNTICO : intentando asignar tipo %d a la variable lista \"%s\" de subtipo %d %s\n",GREEN,tipoDch,s,tipoIzq,KNRM);
			}
			if( (tipoIzq == 0 && tipoDch == 1) ){
				printf( "%sWARNING : intentando asignar tipo real a lista de sub tipo entero en variable  \"%s\"  %s\n",KCYN,s,KNRM);
			} 
		}
}


void comprobacionTiposAsignacion2(int tipoIzq,int tipoDch,char* s, int subtipoIzq, int subtipoDch){

	
	//Si es una lista intereda el subtipo
	if(tipoIzq != 4){
		if(tipoIzq != tipoDch){
			if( ! ( (tipoIzq == 0 && tipoDch == 1) || (tipoIzq == 1 && tipoDch == 0) ) ){
				printf( "%sERROR SEMÁNTICO : intentando asignar tipo %d a la variable \"%s\" de tipo %d %s\n",GREEN,tipoDch,s,tipoIzq,KNRM);
			}
			if( (tipoIzq == 0 && tipoDch == 1) ){
				printf( "%sWARNING : intentando asignar tipo real a tipo entero en variable  \"%s\"  %s\n",KCYN,s,KNRM);
			} 
		}
	} else {
		//printf( "%sWARNINGGGGGGGGGGGGGGGGGGGGG\"%s\"  %s\n",KCYN,s,KNRM);
		if(tipoIzq != tipoDch){
			printf( "%sERROR SEMÁNTICO : intentando asignar tipo %d a la variable \"%s\" de tipo %d %s\n",GREEN,tipoDch,s,tipoIzq,KNRM);
		} else {
			comprobacionTiposAsignacionLista(subtipoIzq,subtipoDch,s);
		}
	
	}
}

void comprobacionAgregado(int tipoIzq,int tipoDch){

	
	if(tipoIzq != tipoDch){
		printf( "%sERROR SEMÁNTICO : creacion de lista no homogenea de tipos %d %d\n",GREEN,tipoDch,tipoIzq,KNRM);
	}
	
}

void insertarDescriptor(char* intro, char* outro, char* sino, char* control){
	TOPE += 1;
	tablaSimbolos[TOPE].entrada = descriptor;
	tablaSimbolos[TOPE].descriptor.EtiquetaEntrada = intro;
	tablaSimbolos[TOPE].descriptor.EtiquetaSalida = outro;
	tablaSimbolos[TOPE].descriptor.EtiquetaElse = sino;
	tablaSimbolos[TOPE].descriptor.NombreVarControl = control;

}

void  eliminarDescriptor(){
	while(tablaSimbolos[TOPE].entrada != descriptor){
		TOPE -= 1;
	}
	TOPE -= 1;
}

char * getVarControl(){
	int aux = TOPE;
	while( tablaSimbolos[aux].entrada != descriptor ){
		aux -= 1;
	}
	return tablaSimbolos[aux].descriptor.NombreVarControl;
}

char * getEtiquetaEntrada(){
	int aux = TOPE;
	while( tablaSimbolos[aux].entrada != descriptor ){
		aux -= 1;
	}
	return tablaSimbolos[aux].descriptor.EtiquetaEntrada;
}


char * getEtiquetaSalida(){
	int aux = TOPE;
	while( tablaSimbolos[aux].entrada != descriptor ){
		aux -= 1;
	}
	return tablaSimbolos[aux].descriptor.EtiquetaSalida;
}


char * getEtiquetaElse(){
	int aux = TOPE;
	while( tablaSimbolos[aux].entrada != descriptor ){
		aux -= 1;
	}
	return tablaSimbolos[aux].descriptor.EtiquetaElse;
}



#include "generador.c"



#line 693 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFICADOR = 258,
    TIPO_DATO_BASICO = 259,
    LISTA = 260,
    SI = 261,
    MIENTRAS = 262,
    PARA = 263,
    BAJANDO_HASTA = 264,
    HASTA = 265,
    HACER = 266,
    SALIDA = 267,
    ENTRADA = 268,
    SINO = 269,
    RETORNO = 270,
    PRINCIPAL = 271,
    VAR = 272,
    VAREND = 273,
    PIZQ = 274,
    PDCH = 275,
    CIZQ = 276,
    CDCH = 277,
    PUNTO = 278,
    COMA = 279,
    COMILLAS_DOBLES = 280,
    COR_ABRE = 281,
    COR_CIERRA = 282,
    COMIENZO_LISTA = 283,
    MOV_CURSOR = 284,
    ARROBA = 285,
    ALFABETICO = 286,
    NUMERICO = 287,
    BOOLEANO = 288,
    C_ESPE = 289,
    PYC = 290,
    OP_ASIGNACION = 291,
    ALFABETICOPRIO = 292,
    OP_BINARIO = 293,
    ADITIVO = 294,
    MULTIPLICATIVO = 295,
    ALMOHADILLA = 296,
    EXCLAINTER = 297,
    MASMAS = 298
  };
#endif
/* Tokens.  */
#define IDENTIFICADOR 258
#define TIPO_DATO_BASICO 259
#define LISTA 260
#define SI 261
#define MIENTRAS 262
#define PARA 263
#define BAJANDO_HASTA 264
#define HASTA 265
#define HACER 266
#define SALIDA 267
#define ENTRADA 268
#define SINO 269
#define RETORNO 270
#define PRINCIPAL 271
#define VAR 272
#define VAREND 273
#define PIZQ 274
#define PDCH 275
#define CIZQ 276
#define CDCH 277
#define PUNTO 278
#define COMA 279
#define COMILLAS_DOBLES 280
#define COR_ABRE 281
#define COR_CIERRA 282
#define COMIENZO_LISTA 283
#define MOV_CURSOR 284
#define ARROBA 285
#define ALFABETICO 286
#define NUMERICO 287
#define BOOLEANO 288
#define C_ESPE 289
#define PYC 290
#define OP_ASIGNACION 291
#define ALFABETICOPRIO 292
#define OP_BINARIO 293
#define ADITIVO 294
#define MULTIPLICATIVO 295
#define ALMOHADILLA 296
#define EXCLAINTER 297
#define MASMAS 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 830 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   245

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  178

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   673,   673,   676,   679,   680,   683,   684,   687,   690,
     691,   692,   695,   698,   701,   704,   707,   708,   711,   711,
     712,   712,   715,   716,   717,   720,   723,   726,   727,   728,
     729,   732,   733,   736,   737,   741,   741,   744,   745,   746,
     749,   750,   751,   754,   755,   759,   760,   761,   762,   763,
     764,   765,   766,   767,   768,   771,   774,   775,   776,   779,
     780,   783,   786,   787,   790,   793,   796,   799,   800,   803,
     804,   809,   810,   811,   812,   813,   814,   815,   816,   817,
     818,   819,   820,   821,   822,   829,   830,   831,   832,   836,
     839,   840,   843,   844,   847,   848,   849,   850,   851,   854,
     857,   860,   861,   864
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFICADOR", "TIPO_DATO_BASICO",
  "LISTA", "SI", "MIENTRAS", "PARA", "BAJANDO_HASTA", "HASTA", "HACER",
  "SALIDA", "ENTRADA", "SINO", "RETORNO", "PRINCIPAL", "VAR", "VAREND",
  "PIZQ", "PDCH", "CIZQ", "CDCH", "PUNTO", "COMA", "COMILLAS_DOBLES",
  "COR_ABRE", "COR_CIERRA", "COMIENZO_LISTA", "MOV_CURSOR", "ARROBA",
  "ALFABETICO", "NUMERICO", "BOOLEANO", "C_ESPE", "PYC", "OP_ASIGNACION",
  "ALFABETICOPRIO", "OP_BINARIO", "ADITIVO", "MULTIPLICATIVO",
  "ALMOHADILLA", "EXCLAINTER", "MASMAS", "$accept", "S", "cabezaPrograma",
  "bloque", "declar_subprogs", "declar_subprog", "declar_var_locales",
  "marca_ini_declar_variables", "marca_fin_declar_variables",
  "inicio_bloque", "fin_bloque", "variables_locales", "cuerpo_declar_var",
  "$@1", "$@2", "sentencia_declaracion", "tipo_dato",
  "tipo_de_dato_compuesto", "cabecera_subprog", "parametros", "parametro",
  "llamada_funcion", "$@3", "parametros_predefinidos",
  "parametro_predefinido", "sentencias", "sentencia", "retorno",
  "sentencia_asignacion", "sentencia_if", "sentencia_while",
  "sentencia_for", "sentencia_entrada", "nombre_entrada",
  "sentencia_salida", "sentencia_lista", "lista_de_expresiones",
  "expresion", "constante", "lista", "agregado", "cadena",
  "contenido_cadena", "real", "punto_coma", "coma", "tratamiento_error", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

#define YYPACT_NINF -83

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-83)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,   -83,    27,     9,   -83,   -83,   -83,    34,   -83,   -83,
      60,   152,   -83,    36,   -83,   -83,    60,   -83,   -83,   -83,
     -83,    12,    50,    56,    32,    70,   -83,   101,   -83,    89,
     -83,   -83,   -83,    91,    96,     9,   -83,   169,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,    84,   -83,   -83,   -83,   -83,
     -83,    82,    82,   -83,   -83,   -83,   -83,   101,    32,   101,
     101,    10,   138,   101,   -83,    -4,   101,   -83,   208,    37,
     -83,   -83,   101,   101,   -83,   -83,   188,   -83,   -83,   -83,
     -83,   -83,   -83,   102,   104,   -83,   -83,   -83,    98,   -83,
      13,   -83,   -83,    29,   181,   -83,    68,    92,   101,   101,
      -3,   188,   165,   137,   113,   114,   112,   111,   111,   101,
     101,   101,   101,   101,    18,   205,   108,   101,    82,   147,
     -83,    23,   -83,   -83,   -83,   -83,   186,   186,    41,    57,
     -83,   101,   -83,   -83,   -83,   -83,   -83,   -83,   208,   -83,
     -83,   188,   111,   111,   111,   199,   -83,   175,   180,    52,
     -83,   -83,    85,   -83,   181,   -83,   -83,    29,   172,   -83,
     186,   186,   188,   -83,   101,   -83,   -83,   -83,   218,   -83,
     -83,   -83,   186,   -83,   -83,   188,   -83,   -83
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     0,     1,    14,     2,    11,    12,     7,
       0,     0,    25,     0,    13,    10,     0,    17,    18,    20,
      58,     0,     0,     0,     0,     0,    65,     0,    15,     0,
      45,     6,     5,     0,     0,     0,    52,     0,    44,    54,
      46,    47,    48,    49,    50,     0,    51,    53,    26,     9,
      16,     0,     0,   102,    35,   101,    67,     0,     0,     0,
       0,     0,     0,     0,   103,    77,     0,    98,     0,    85,
      87,    93,     0,     0,    80,    83,    55,    78,    79,    88,
      86,    84,    68,     0,     0,     8,     4,    43,     0,    24,
       0,    19,    21,    39,     0,    57,     0,     0,     0,     0,
       0,    69,     0,     0,    90,     0,     0,    72,    73,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    40,
      42,     0,    38,    41,   100,    56,     0,     0,     0,     0,
      66,     0,    71,    92,    94,    95,    96,    97,     0,    89,
      99,    81,    74,    76,    75,     0,    28,     0,     0,     0,
      32,    30,     0,    64,     0,    23,    36,     0,    59,    61,
       0,     0,    70,    91,     0,    33,    34,    27,     0,    29,
      22,    37,     0,    63,    62,    82,    31,    60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -83,   -83,   -83,     7,   -83,   -83,   -83,   -83,   184,   -83,
     151,   -83,   190,   -83,   -83,   -45,   103,   129,   -83,    81,
      44,   -11,   -83,   -83,    45,   -83,   -36,   -83,    -8,   -83,
     -83,   -83,   -83,   -83,   -83,    -9,   -83,   -54,   -64,   -83,
      75,   -83,   -83,   -83,    61,   -82,   -83
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    30,    11,    31,     9,    10,    15,     7,
      32,    16,    17,    51,    52,    91,   147,   148,    35,   149,
     150,    74,    93,   121,   122,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    75,   100,    76,    77,    78,
     105,    79,   103,    80,   125,    58,    81
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      36,    87,    47,    94,   104,    96,    97,    92,   118,   101,
       6,    53,   102,    53,    53,    54,    62,   130,   107,   108,
       1,   131,    12,    13,    53,    56,    36,     4,    47,   123,
       5,    54,   119,    20,    55,    61,    55,    55,   146,   157,
      48,    56,    85,   156,   128,   129,    57,    55,    57,   117,
      95,     8,   160,    53,    67,   141,   142,   143,   144,   145,
     106,    69,    70,   154,    12,    13,    71,   168,   161,    59,
     168,   109,   167,   155,   104,    60,    55,   162,    14,   110,
     111,   112,   120,    89,   113,    90,    53,   109,   126,    63,
     158,   159,    82,   123,    83,   110,   111,   112,   109,    84,
     113,   116,    64,    88,    65,   169,   110,   111,   112,    55,
     175,   113,   127,    18,    33,    36,    36,    47,    47,    18,
      66,   114,   109,   115,   173,   174,    67,    68,   153,    29,
     110,   111,   112,    69,    70,   113,   177,   138,    71,    19,
      34,   139,    72,    73,   140,    19,   120,    98,    99,    36,
      36,    47,    47,    20,   113,    21,    12,    13,    22,    23,
      24,    36,   133,    47,    25,    26,    54,    27,   134,   135,
      20,   136,    21,     5,    28,    22,    23,    24,   165,   137,
      29,    25,    26,   166,    27,   132,   172,    20,    86,    21,
       5,    28,    22,    23,    24,   109,   152,    29,    25,    26,
      49,    27,   171,   110,   111,   112,    50,     5,   113,    12,
      13,   109,   176,   163,    29,   170,   124,     0,   109,   110,
     111,   112,    12,    13,   113,   151,   110,   111,   112,   164,
       0,   113,     0,    67,     0,     0,     0,   110,   111,   112,
      69,    70,   113,     0,     0,    71
};

static const yytype_int16 yycheck[] =
{
      11,    37,    11,    57,    68,    59,    60,    52,    90,    63,
       3,     1,    66,     1,     1,    19,    24,    20,    72,    73,
      16,    24,     4,     5,     1,    29,    37,     0,    37,    93,
      21,    19,     3,     1,    24,     3,    24,    24,    20,   121,
       4,    29,    35,    20,    98,    99,    36,    24,    36,    36,
      58,    17,    11,     1,    25,   109,   110,   111,   112,   113,
      23,    32,    33,   117,     4,     5,    37,   149,    11,    19,
     152,    30,    20,   118,   138,    19,    24,   131,    18,    38,
      39,    40,    93,     1,    43,     3,     1,    30,    20,    19,
     126,   127,     3,   157,     3,    38,    39,    40,    30,     3,
      43,     3,     1,    19,     3,    20,    38,    39,    40,    24,
     164,    43,    20,    10,    11,   126,   127,   126,   127,    16,
      19,    19,    30,    19,   160,   161,    25,    26,    20,    28,
      38,    39,    40,    32,    33,    43,   172,    24,    37,    10,
      11,    27,    41,    42,    32,    16,   157,     9,    10,   160,
     161,   160,   161,     1,    43,     3,     4,     5,     6,     7,
       8,   172,    25,   172,    12,    13,    19,    15,    31,    32,
       1,    34,     3,    21,    22,     6,     7,     8,     3,    42,
      28,    12,    13,     3,    15,    20,    14,     1,    37,     3,
      21,    22,     6,     7,     8,    30,   115,    28,    12,    13,
      16,    15,   157,    38,    39,    40,    16,    21,    43,     4,
       5,    30,   168,   138,    28,   154,    35,    -1,    30,    38,
      39,    40,     4,     5,    43,    20,    38,    39,    40,    30,
      -1,    43,    -1,    25,    -1,    -1,    -1,    38,    39,    40,
      32,    33,    43,    -1,    -1,    37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    16,    45,    46,     0,    21,    47,    53,    17,    50,
      51,    48,     4,     5,    18,    52,    55,    56,    60,    61,
       1,     3,     6,     7,     8,    12,    13,    15,    22,    28,
      47,    49,    54,    60,    61,    62,    65,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,     4,    52,
      56,    57,    58,     1,    19,    24,    29,    36,    89,    19,
      19,     3,    72,    19,     1,     3,    19,    25,    26,    32,
      33,    37,    41,    42,    65,    79,    81,    82,    83,    85,
      87,    90,     3,     3,     3,    47,    54,    70,    19,     1,
       3,    59,    59,    66,    81,    72,    81,    81,     9,    10,
      80,    81,    81,    86,    82,    84,    23,    81,    81,    30,
      38,    39,    40,    43,    19,    19,     3,    36,    89,     3,
      65,    67,    68,    82,    35,    88,    20,    20,    81,    81,
      20,    24,    20,    25,    31,    32,    34,    42,    24,    27,
      32,    81,    81,    81,    81,    81,    20,    60,    61,    63,
      64,    20,    63,    20,    81,    59,    20,    89,    70,    70,
      11,    11,    81,    84,    30,     3,     3,    20,    89,    20,
      88,    68,    14,    70,    70,    81,    64,    70
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    47,    47,    48,    48,    49,    50,
      50,    50,    51,    52,    53,    54,    55,    55,    57,    56,
      58,    56,    59,    59,    59,    60,    61,    62,    62,    62,
      62,    63,    63,    64,    64,    66,    65,    67,    67,    67,
      68,    68,    68,    69,    69,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    71,    72,    72,    72,    73,
      73,    74,    75,    75,    76,    77,    78,    79,    79,    80,
      80,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    82,    82,    82,    82,    83,
      84,    84,    85,    85,    86,    86,    86,    86,    86,    87,
      88,    89,    89,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     5,     4,     2,     0,     2,     3,
       2,     0,     1,     1,     1,     1,     2,     1,     0,     3,
       0,     3,     4,     3,     1,     1,     2,     5,     4,     5,
       4,     3,     1,     2,     2,     0,     5,     3,     1,     0,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     4,     3,     1,     5,
       7,     5,     6,     6,     4,     1,     4,     2,     2,     1,
       3,     3,     2,     2,     3,     3,     3,     1,     1,     1,
       1,     3,     5,     1,     1,     1,     1,     1,     1,     3,
       1,     3,     3,     1,     2,     2,     2,     2,     0,     3,
       1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 673 "sintactico.y" /* yacc.c:1646  */
    {generarIntermedio(variables,(yyvsp[0]).traduccion);closeFile();}
#line 2058 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 676 "sintactico.y" /* yacc.c:1646  */
    { openFile();}
#line 2064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 679 "sintactico.y" /* yacc.c:1646  */
    {eliminarBloque();(yyval).traduccion = concatenarCuadruple((yyvsp[-4]).traduccion,(yyvsp[-2]).traduccion,(yyvsp[-1]).traduccion,(yyvsp[0]).traduccion);}
#line 2070 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 680 "sintactico.y" /* yacc.c:1646  */
    {eliminarBloque();(yyval).traduccion = concatenarTriple((yyvsp[-3]).traduccion,(yyvsp[-1]).traduccion,(yyvsp[0]).traduccion);}
#line 2076 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 683 "sintactico.y" /* yacc.c:1646  */
    {(yyval).traduccion = "subporgramas";}
#line 2082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 684 "sintactico.y" /* yacc.c:1646  */
    {(yyval).traduccion = "";}
#line 2088 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 690 "sintactico.y" /* yacc.c:1646  */
    {variables = concatenarVariables(variables,(yyvsp[-1]).traduccion);}
#line 2094 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 701 "sintactico.y" /* yacc.c:1646  */
    { introducirBloque(marca,(yyvsp[0]).lexema,noasignado,0,0,noasignado); (yyval).traduccion = concatenar((yyvsp[0]).lexema,"\n");}
#line 2100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 704 "sintactico.y" /* yacc.c:1646  */
    {(yyval).traduccion = concatenar((yyvsp[0]).lexema,"\n");}
#line 2106 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 707 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = concatenar((yyvsp[-1]).traduccion,(yyvsp[0]).traduccion);}
#line 2112 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 708 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = (yyvsp[0]).traduccion;}
#line 2118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 711 "sintactico.y" /* yacc.c:1646  */
    { TIPO = (yyvsp[0]).tipo; SUBTIPO = 5;DIM = 0;}
#line 2124 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 711 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = concatenarTipoVariable((yyvsp[-2]),(yyvsp[0]).traduccion);}
#line 2130 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 712 "sintactico.y" /* yacc.c:1646  */
    { TIPO = (yyvsp[0]).tipo; SUBTIPO = (yyvsp[0]).subt;}
#line 2136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 712 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = concatenarTipoVariable((yyvsp[-2]),(yyvsp[0]).traduccion);}
#line 2142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 715 "sintactico.y" /* yacc.c:1646  */
    { comprobacionTiposAsignacion2(TIPO,(yyvsp[-1]).tipo,(yyvsp[-3]).lexema,SUBTIPO,(yyvsp[-1]).subt); introducirIdentificador(variable,(yyvsp[-3]).lexema,TIPO,0,(yyvsp[-1]).dim,SUBTIPO); DIM = (yyvsp[-1]).dim; (yyval).traduccion = concatenarAsignacion((yyvsp[-3]).lexema,"=",(yyvsp[-1]).traduccion,";");}
#line 2148 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 716 "sintactico.y" /* yacc.c:1646  */
    { introducirIdentificador(variable,(yyvsp[-2]).lexema,TIPO,0,DIM,SUBTIPO); (yyval).traduccion = concatenarConComa((yyvsp[-2]).lexema,(yyvsp[0]).traduccion); }
#line 2154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 720 "sintactico.y" /* yacc.c:1646  */
    { (yyval).tipo = (yyvsp[0]).tipo; }
#line 2160 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 723 "sintactico.y" /* yacc.c:1646  */
    { (yyval).tipo = (yyvsp[-1]).tipo; (yyval).subt = (yyvsp[0]).tipo; }
#line 2166 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 726 "sintactico.y" /* yacc.c:1646  */
    {introducirIdentificador(funcion,(yyvsp[-3]).lexema, (yyvsp[-4]).tipo, (yyvsp[-1]).cantidad,0,0);}
#line 2172 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 727 "sintactico.y" /* yacc.c:1646  */
    {introducirIdentificador(funcion,(yyvsp[-2]).lexema, (yyvsp[-3]).tipo,0,0,0);}
#line 2178 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 728 "sintactico.y" /* yacc.c:1646  */
    {introducirIdentificador(funcion,(yyvsp[-3]).lexema, (yyvsp[-4]).tipo, (yyvsp[-1]).cantidad,0,(yyvsp[-4]).subt);}
#line 2184 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 729 "sintactico.y" /* yacc.c:1646  */
    {introducirIdentificador(funcion,(yyvsp[-2]).lexema, (yyvsp[-3]).tipo,0,0,(yyvsp[-3]).subt);}
#line 2190 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 732 "sintactico.y" /* yacc.c:1646  */
    { (yyval).cantidad = 1 + (yyvsp[-2]).cantidad; }
#line 2196 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 733 "sintactico.y" /* yacc.c:1646  */
    {(yyval).cantidad = 1; }
#line 2202 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 736 "sintactico.y" /* yacc.c:1646  */
    {(yyval).lexema = (yyvsp[0]).lexema; introducirIdentificador(parametro_formal,(yyvsp[0]).lexema,(yyvsp[-1]).tipo,0,0,0);}
#line 2208 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 737 "sintactico.y" /* yacc.c:1646  */
    {(yyval).lexema = (yyvsp[0]).lexema; introducirIdentificador(parametro_formal,(yyvsp[0]).lexema,(yyvsp[-1]).tipo,0,0,(yyvsp[-1]).subt);}
#line 2214 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 741 "sintactico.y" /* yacc.c:1646  */
    { NOMBRE_F = (yyvsp[-1]).lexema; }
#line 2220 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 741 "sintactico.y" /* yacc.c:1646  */
    { ComprobacionLlamadaFuncion((yyvsp[-4]), (yyvsp[-1])); (yyval).tipo = (yyvsp[-4]).tipo; }
#line 2226 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 744 "sintactico.y" /* yacc.c:1646  */
    { (yyval).cantidad = 1 + (yyvsp[-2]).cantidad; comprobarTipoParametro((yyvsp[0]), (yyval)); }
#line 2232 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 745 "sintactico.y" /* yacc.c:1646  */
    {(yyval).cantidad = 1;  comprobarTipoParametro((yyvsp[0]), (yyval));  }
#line 2238 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 749 "sintactico.y" /* yacc.c:1646  */
    { (yyval) = buscarVariableDefinida((yyvsp[0])); }
#line 2244 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 750 "sintactico.y" /* yacc.c:1646  */
    { (yyval).tipo = (yyvsp[0]).tipo ;}
#line 2250 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 754 "sintactico.y" /* yacc.c:1646  */
    {(yyval).traduccion = concatenar((yyvsp[-1]).traduccion,(yyvsp[0]).traduccion);}
#line 2256 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 755 "sintactico.y" /* yacc.c:1646  */
    {(yyval).traduccion = (yyvsp[0]).traduccion;}
#line 2262 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 760 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = concatenarTriple("{\n",(yyvsp[0]).traduccion,"}\n");}
#line 2268 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 761 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = concatenar("{\n",(yyvsp[0]).traduccion);}
#line 2274 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 762 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = concatenar("{\n",(yyvsp[0]).traduccion);}
#line 2280 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 763 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = concatenar("{\n",(yyvsp[0]).traduccion);}
#line 2286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 764 "sintactico.y" /* yacc.c:1646  */
    { (yyval).tipo = (yyvsp[0]).tipo; }
#line 2292 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 766 "sintactico.y" /* yacc.c:1646  */
    { (yyval).tipo = (yyvsp[0]).tipo; }
#line 2298 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 768 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = (yyvsp[0]).traduccion;}
#line 2304 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 771 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = concatenarTriple("return ",(yyvsp[0]).traduccion,";");}
#line 2310 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 774 "sintactico.y" /* yacc.c:1646  */
    { (yyvsp[-3]) = buscarVariableDefinida((yyvsp[-3])); comprobacionTiposAsignacion2((yyvsp[-3]).tipo,(yyvsp[-1]).tipo,(yyvsp[-3]).lexema,(yyvsp[-3]).subt,(yyvsp[-1]).subt); (yyval).tipo = (yyvsp[-3]).tipo; (yyval).dim = (yyvsp[-1]).dim; (yyval).traduccion = concatenarTriple((yyvsp[-1]).traduccion,concatenarCuadruple((yyvsp[-3]).lexema,"=",(yyvsp[-1]).varTemporal,";"),"\n"); }
#line 2316 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 775 "sintactico.y" /* yacc.c:1646  */
    { (yyvsp[-2]) = buscarVariableDefinida((yyvsp[-2])); comprobacionTiposAsignacion2((yyvsp[-2]).tipo,(yyvsp[0]).tipo,(yyvsp[-2]).lexema,(yyvsp[-2]).subt,(yyvsp[0]).subt);  (yyval).tipo = (yyvsp[-2]).tipo; (yyval).traduccion = concatenarConComa((yyvsp[-2]).lexema,(yyvsp[0]).traduccion); }
#line 2322 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 779 "sintactico.y" /* yacc.c:1646  */
    {insertarDescriptor("",etiqueta(),etiqueta(),(yyvsp[-2]).varTemporal); (yyval).traduccion = concatenarElse2(getEtiquetaElse(),"{}",getEtiquetaSalida(),concaternarIfSalida(getEtiquetaSalida(),concatenarTriple((yyvsp[-2]).traduccion,comprobacionIf(getVarControl(),getEtiquetaElse()),(yyvsp[0]).traduccion)));eliminarDescriptor();}
#line 2328 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 780 "sintactico.y" /* yacc.c:1646  */
    { insertarDescriptor("",etiqueta(),etiqueta(),(yyvsp[-4]).varTemporal); (yyval).traduccion = concatenarElse(getEtiquetaElse(),(yyvsp[0]).traduccion,getEtiquetaSalida(),concaternarIfSalida(getEtiquetaSalida(),concatenarTriple((yyvsp[-4]).traduccion,comprobacionIf(getVarControl(),getEtiquetaElse()),(yyvsp[-2]).traduccion)));eliminarDescriptor();}
#line 2334 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 783 "sintactico.y" /* yacc.c:1646  */
    {insertarDescriptor(etiqueta(),etiqueta(),"",(yyvsp[-2]).varTemporal); (yyval).traduccion = concatenarEtiquetaSalida(getEtiquetaSalida(),concatenarEtiqueta2(getEtiquetaEntrada(),concatenarTriple(concatenarEtiqueta(getEtiquetaEntrada(),(yyvsp[-2]).traduccion),comprobacionWhile(getVarControl(),getEtiquetaSalida()),(yyvsp[0]).traduccion))); eliminarDescriptor(); }
#line 2340 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 786 "sintactico.y" /* yacc.c:1646  */
    { insertarDescriptor(etiqueta(),etiqueta(),"",(yyvsp[-3]).varTemporal);(yyval).traduccion = concatenarFor(getEtiquetaEntrada(),getEtiquetaSalida(),(yyvsp[-4]),(yyvsp[-2]),(yyvsp[0]));}
#line 2346 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 790 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = concatenaSentenciaEntrada((yyvsp[-1])); }
#line 2352 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 796 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = concatenaSentenciaSalida((yyvsp[-1]).traduccion); }
#line 2358 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 799 "sintactico.y" /* yacc.c:1646  */
    { (yyval) = EsLista((yyvsp[-1])); }
#line 2364 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 800 "sintactico.y" /* yacc.c:1646  */
    { (yyval) = EsLista((yyvsp[-1])); }
#line 2370 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 803 "sintactico.y" /* yacc.c:1646  */
    {(yyval).traduccion =(yyvsp[0]).traduccion;}
#line 2376 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 804 "sintactico.y" /* yacc.c:1646  */
    {(yyval).traduccion = concatenarConComa((yyvsp[-2]).traduccion,(yyvsp[0]).traduccion);}
#line 2382 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 809 "sintactico.y" /* yacc.c:1646  */
    { (yyval).tipo = (yyvsp[-1]).tipo; (yyval).dim = 0 ; (yyval) = (yyvsp[-1]); (yyval).varTemporal = (yyvsp[-1]).varTemporal;(yyval).traduccion = (yyvsp[-1]).traduccion;}
#line 2388 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 810 "sintactico.y" /* yacc.c:1646  */
    { (yyval) = comprobacionAlmohadilla((yyvsp[0]), (yyvsp[-1])); (yyval).dim = 0 ;}
#line 2394 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 811 "sintactico.y" /* yacc.c:1646  */
    {(yyval) = comprobacionExclaInter((yyvsp[0]), (yyvsp[-1])); (yyval).dim = 0 ;}
#line 2400 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 812 "sintactico.y" /* yacc.c:1646  */
    { (yyval) = comprobacionBinaria((yyvsp[-2]),(yyvsp[0]),(yyvsp[-1])); (yyval).dim = 0 ; (yyval).varTemporal = temporal();(yyval).traduccion = concatenarOpBinario((yyval).varTemporal,(yyvsp[-2]),(yyvsp[-1]),(yyvsp[0]).traduccion,";"); }
#line 2406 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 813 "sintactico.y" /* yacc.c:1646  */
    { (yyval) = comprobacionOperacionMultiplicativa((yyvsp[-2]),(yyvsp[0]),(yyvsp[-1])); (yyval).dim = 0 ; (yyval).varTemporal = temporal();(yyval).traduccion = concatenarMultiplicativo((yyval).varTemporal,(yyvsp[-2]),(yyvsp[-1]),(yyvsp[0]).traduccion,";");  }
#line 2412 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 814 "sintactico.y" /* yacc.c:1646  */
    { (yyval) = comprobacionOperacionMasMenos((yyvsp[-2]),(yyvsp[0]),(yyvsp[-1])); (yyval).dim = 0 ;(yyval).varTemporal = temporal();(yyval).traduccion = concatenarAditivo((yyval).varTemporal,(yyvsp[-2]),(yyvsp[-1]),(yyvsp[0]).traduccion,";");  }
#line 2418 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 815 "sintactico.y" /* yacc.c:1646  */
    { (yyval) = buscarVariableDefinida((yyvsp[0]));(yyval).dim = 0; (yyval).traduccion = (yyvsp[0]).lexema; (yyval).varTemporal = "nulo";}
#line 2424 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 816 "sintactico.y" /* yacc.c:1646  */
    {(yyval).dim = 0 ; (yyval).traduccion = (yyvsp[0]).traduccion;(yyval).varTemporal = "nulo";}
#line 2430 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 817 "sintactico.y" /* yacc.c:1646  */
    {(yyval).tipo = lista; (yyval).subt = (yyvsp[0]).subt ; (yyval).dim = (yyvsp[0]).dim;}
#line 2436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 818 "sintactico.y" /* yacc.c:1646  */
    { (yyval).tipo = (yyvsp[0]).tipo; }
#line 2442 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 819 "sintactico.y" /* yacc.c:1646  */
    { (yyval) = comprobacionArroba((yyvsp[-2]), (yyvsp[0]), (yyvsp[-1])); }
#line 2448 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 820 "sintactico.y" /* yacc.c:1646  */
    { (yyval) = comprobacionTernaria((yyvsp[-4]), (yyvsp[-2]), (yyvsp[0]), (yyvsp[-3]), (yyvsp[-1])); }
#line 2454 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 821 "sintactico.y" /* yacc.c:1646  */
    { (yyval).tipo = (yyvsp[0]).tipo; (yyval).subt = (yyvsp[0]).subt; }
#line 2460 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 829 "sintactico.y" /* yacc.c:1646  */
    {(yyval).tipo = 0; (yyval).traduccion = (yyvsp[0]).lexema; }
#line 2466 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 830 "sintactico.y" /* yacc.c:1646  */
    {(yyval).tipo = 1; (yyval).traduccion = (yyvsp[0]).traduccion; }
#line 2472 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 831 "sintactico.y" /* yacc.c:1646  */
    {(yyval).tipo = 3; (yyval).traduccion = traducirBool((yyvsp[0])); }
#line 2478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 832 "sintactico.y" /* yacc.c:1646  */
    {(yyval).tipo = 2;(yyval).traduccion = (yyvsp[0]).traduccion;}
#line 2484 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 836 "sintactico.y" /* yacc.c:1646  */
    {(yyval).tipo = lista;(yyval).subt = (yyvsp[-1]).subt; (yyval).dim = (yyvsp[-1]).dim;}
#line 2490 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 839 "sintactico.y" /* yacc.c:1646  */
    { (yyval).subt = (yyvsp[0]).tipo; (yyval).dim = 1; }
#line 2496 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 840 "sintactico.y" /* yacc.c:1646  */
    {(yyval).subt = (yyvsp[0]).subt; (yyval).dim = (yyvsp[-2]).dim + 1; comprobacionAgregado((yyvsp[-2]).tipo,(yyvsp[0]).subt);}
#line 2502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 843 "sintactico.y" /* yacc.c:1646  */
    {(yyval).traduccion = crearCadena((yyvsp[-1]).lexema);}
#line 2508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 844 "sintactico.y" /* yacc.c:1646  */
    {(yyval).traduccion = (yyvsp[0]).lexema;}
#line 2514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 854 "sintactico.y" /* yacc.c:1646  */
    { (yyval).traduccion = concatenarConPunto((yyvsp[-2]).lexema,(yyvsp[0]).lexema);}
#line 2520 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2524 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 866 "sintactico.y" /* yacc.c:1906  */


#include "lex.yy.c"

extern FILE * yyin;


/* main(int argc, char **argv) 
{
	if (argc > 1) {
		 yyin = fopen(argv[1],"r");
	}
	yydebug=0;
	yyparse();
}*/ 

yyerror(char *s) {
	printf( "%sERROR SINTACTICO linea %d: %s%s\n",KBLU,linea,s,KNRM);
}


