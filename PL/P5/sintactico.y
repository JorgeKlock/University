/* P3 ESPECIFICACIÓN SINTÁCTICA */
%{
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

%right ARROBA
%left OP_BINARIO
%left ADITIVO
%left MULTIPLICATIVO
%left ALMOHADILLA
%right EXCLAINTER
%right MASMAS





%%

S	: cabezaPrograma bloque {generarIntermedio(variables,$2.traduccion);closeFile();}
	;

cabezaPrograma : PRINCIPAL { openFile();}
	;

bloque	: inicio_bloque declar_var_locales declar_subprogs sentencias fin_bloque {eliminarBloque();$$.traduccion = concatenarCuadruple($1.traduccion,$3.traduccion,$4.traduccion,$5.traduccion);}
	| inicio_bloque declar_var_locales declar_subprogs fin_bloque {eliminarBloque();$$.traduccion = concatenarTriple($1.traduccion,$3.traduccion,$4.traduccion);}
	;

declar_subprogs: declar_subprogs declar_subprog {$$.traduccion = "subporgramas";}
	| {$$.traduccion = "";}
	;

declar_subprog: cabecera_subprog bloque
	;

declar_var_locales : marca_ini_declar_variables variables_locales marca_fin_declar_variables {variables = concatenarVariables(variables,$2.traduccion);}
	|  marca_ini_declar_variables marca_fin_declar_variables
	|
	;

marca_ini_declar_variables: VAR
	;

marca_fin_declar_variables: VAREND
	;

inicio_bloque : CIZQ { introducirBloque(marca,$1.lexema,noasignado,0,0,noasignado); $$.traduccion = concatenar($1.lexema,"\n");}//PUSH TS(marca) 
	;

fin_bloque : CDCH {$$.traduccion = concatenar($1.lexema,"\n");}
	;

variables_locales : variables_locales cuerpo_declar_var { $$.traduccion = concatenar($1.traduccion,$2.traduccion);}
	| cuerpo_declar_var { $$.traduccion = $1.traduccion;}
	;

cuerpo_declar_var : tipo_dato { TIPO = $1.tipo; SUBTIPO = 5;DIM = 0;} sentencia_declaracion { $$.traduccion = concatenarTipoVariable($1,$3.traduccion);}
	| tipo_de_dato_compuesto { TIPO = $1.tipo; SUBTIPO = $1.subt;} sentencia_declaracion { $$.traduccion = concatenarTipoVariable($1,$3.traduccion);}
	;

sentencia_declaracion : IDENTIFICADOR OP_ASIGNACION expresion punto_coma { comprobacionTiposAsignacion2(TIPO,$3.tipo,$1.lexema,SUBTIPO,$3.subt); introducirIdentificador(variable,$1.lexema,TIPO,0,$3.dim,SUBTIPO); DIM = $3.dim; $$.traduccion = concatenarAsignacion($1.lexema,"=",$3.traduccion,";");} // sentencia_asignacion.dim = expresion.dim 
	| IDENTIFICADOR coma sentencia_declaracion { introducirIdentificador(variable,$1.lexema,TIPO,0,DIM,SUBTIPO); $$.traduccion = concatenarConComa($1.lexema,$3.traduccion); }
	| error
	;

tipo_dato :  TIPO_DATO_BASICO { $$.tipo = $1.tipo; }
	;

tipo_de_dato_compuesto: LISTA TIPO_DATO_BASICO { $$.tipo = $1.tipo; $$.subt = $2.tipo; }//ATENCIÓN AL TIPO LISTA
	;

cabecera_subprog : tipo_dato IDENTIFICADOR PIZQ parametros PDCH {introducirIdentificador(funcion,$2.lexema, $1.tipo, $4.cantidad,0,0);} // PUSH ( tipoEntrada: funcion, NOMBRE: IDENTIFICADOR , tipoDato : tipo_dato, parametros = parametros.cantidad )
	| tipo_dato IDENTIFICADOR PIZQ PDCH {introducirIdentificador(funcion,$2.lexema, $1.tipo,0,0,0);} // PUSH ( tipoEntrada: funcion, NOMBRE: IDENTIFICADOR , tipoDato : tipo_dato, parametros = 0 )
	| tipo_de_dato_compuesto IDENTIFICADOR PIZQ parametros PDCH {introducirIdentificador(funcion,$2.lexema, $1.tipo, $4.cantidad,0,$1.subt);}// PUSH ( tipoEntrada: funcion, NOMBRE: IDENTIFICADOR , tipoDato : LISTA, parametros = parametros.cantidad )
	| tipo_de_dato_compuesto IDENTIFICADOR PIZQ PDCH {introducirIdentificador(funcion,$2.lexema, $1.tipo,0,0,$1.subt);} // PUSH ( tipoEntrada: funcion, NOMBRE: IDENTIFICADOR , tipoDato : LISTA, parametros = 0 )
	;

parametros : parametros coma parametro { $$.cantidad = 1 + $1.cantidad; }//parametros.cantidad = 1 + parametros2.cantidad
	| parametro {$$.cantidad = 1; }//parametros.cantidad = 1
	;

parametro : tipo_dato IDENTIFICADOR {$$.lexema = $2.lexema; introducirIdentificador(parametro_formal,$2.lexema,$1.tipo,0,0,0);} //DUDA repeticion parametros formales //PUSH ( tipoEntrada : parametros_formal, NOMBRE: IDENTIFICADOR , tipoDato : tipo_dato )
	|  tipo_de_dato_compuesto IDENTIFICADOR {$$.lexema = $2.lexema; introducirIdentificador(parametro_formal,$2.lexema,$1.tipo,0,0,$1.subt);} //PUSH ( tipoEntrada : parametros_formal, NOMBRE: IDENTIFICADOR , tipoDato : LISTA)
	;


llamada_funcion : IDENTIFICADOR PIZQ { NOMBRE_F = $1.lexema; } parametros_predefinidos PDCH { ComprobacionLlamadaFuncion($1, $4); $$.tipo = $1.tipo; }           //Comprobacion de llamada correcta
	;

parametros_predefinidos: parametros_predefinidos coma parametro_predefinido { $$.cantidad = 1 + $1.cantidad; comprobarTipoParametro($3, $$); } //parametros_predefinidos.cantidad = 1 + parametros2_predefinidos.cantidad
	                    | parametro_predefinido {$$.cantidad = 1;  comprobarTipoParametro($1, $$);  } //parametros.cantidad = 1
                    	|
	                    ;

parametro_predefinido: IDENTIFICADOR { $$ = buscarVariableDefinida($1); }
	| constante { $$.tipo = $1.tipo ;}
	| llamada_funcion //pendiente de hacer
	;

sentencias : sentencias sentencia {$$.traduccion = concatenar($1.traduccion,$2.traduccion);}
	| sentencia  {$$.traduccion = $1.traduccion;}
	;


sentencia : bloque
	| sentencia_asignacion { $$.traduccion = concatenarTriple("{\n",$1.traduccion,"}\n");}
	| sentencia_if { $$.traduccion = concatenar("{\n",$1.traduccion);}
	| sentencia_while { $$.traduccion = concatenar("{\n",$1.traduccion);}
	| sentencia_for  { $$.traduccion = concatenar("{\n",$1.traduccion);}
	| sentencia_entrada { $$.tipo = $1.tipo; }
	| sentencia_salida
	| llamada_funcion { $$.tipo = $1.tipo; }
	| sentencia_lista
	| retorno { $$.traduccion = $1.traduccion;}
	;

retorno : RETORNO expresion { $$.traduccion = concatenarTriple("return ",$2.traduccion,";");}
	;

sentencia_asignacion : IDENTIFICADOR OP_ASIGNACION expresion punto_coma { $1 = buscarVariableDefinida($1); comprobacionTiposAsignacion2($1.tipo,$3.tipo,$1.lexema,$1.subt,$3.subt); $$.tipo = $1.tipo; $$.dim = $3.dim; $$.traduccion = concatenarTriple($3.traduccion,concatenarCuadruple($1.lexema,"=",$3.varTemporal,";"),"\n"); } // sentencia_asignacion.dim = expresion.dim
	| IDENTIFICADOR coma sentencia_asignacion { $1 = buscarVariableDefinida($1); comprobacionTiposAsignacion2($1.tipo,$3.tipo,$1.lexema,$1.subt,$3.subt);  $$.tipo = $1.tipo; $$.traduccion = concatenarConComa($1.lexema,$3.traduccion); }
	| error
	;

sentencia_if : SI PIZQ expresion PDCH sentencia {insertarDescriptor("",etiqueta(),etiqueta(),$3.varTemporal); $$.traduccion = concatenarElse2(getEtiquetaElse(),"{}",getEtiquetaSalida(),concaternarIfSalida(getEtiquetaSalida(),concatenarTriple($3.traduccion,comprobacionIf(getVarControl(),getEtiquetaElse()),$5.traduccion)));eliminarDescriptor();}
	| SI PIZQ expresion PDCH sentencia SINO sentencia { insertarDescriptor("",etiqueta(),etiqueta(),$3.varTemporal); $$.traduccion = concatenarElse(getEtiquetaElse(),$7.traduccion,getEtiquetaSalida(),concaternarIfSalida(getEtiquetaSalida(),concatenarTriple($3.traduccion,comprobacionIf(getVarControl(),getEtiquetaElse()),$5.traduccion)));eliminarDescriptor();}
	;

sentencia_while : MIENTRAS PIZQ expresion PDCH sentencia {insertarDescriptor(etiqueta(),etiqueta(),"",$3.varTemporal); $$.traduccion = concatenarEtiquetaSalida(getEtiquetaSalida(),concatenarEtiqueta2(getEtiquetaEntrada(),concatenarTriple(concatenarEtiqueta(getEtiquetaEntrada(),$3.traduccion),comprobacionWhile(getVarControl(),getEtiquetaSalida()),$5.traduccion))); eliminarDescriptor(); }
	;

sentencia_for : PARA sentencia_asignacion HASTA expresion HACER sentencia { insertarDescriptor(etiqueta(),etiqueta(),"",$3.varTemporal);$$.traduccion = concatenarFor(getEtiquetaEntrada(),getEtiquetaSalida(),$2,$4,$6);}
	| PARA sentencia_asignacion BAJANDO_HASTA expresion HACER sentencia
	;

sentencia_entrada : nombre_entrada PIZQ IDENTIFICADOR PDCH { $$.traduccion = concatenaSentenciaEntrada($3); }
	;

nombre_entrada : ENTRADA
	;

sentencia_salida : SALIDA PIZQ lista_de_expresiones PDCH { $$.traduccion = concatenaSentenciaSalida($3.traduccion); }
	;

sentencia_lista : IDENTIFICADOR MOV_CURSOR { $$ = EsLista($1); } // id (<<|>>)
	| COMIENZO_LISTA IDENTIFICADOR	{ $$ = EsLista($1); } // $ id
	;

lista_de_expresiones : expresion {$$.traduccion =$1.traduccion;}
	| lista_de_expresiones COMA expresion {$$.traduccion = concatenarConComa($1.traduccion,$3.traduccion);}
	;



expresion : PIZQ expresion PDCH { $$.tipo = $2.tipo; $$.dim = 0 ; $$ = $2; $$.varTemporal = $2.varTemporal;$$.traduccion = $2.traduccion;}
	| ALMOHADILLA expresion %prec ALMOHADILLA { $$ = comprobacionAlmohadilla($2, $1); $$.dim = 0 ;} // # exp
	| EXCLAINTER expresion %prec ALMOHADILLA {$$ = comprobacionExclaInter($2, $1); $$.dim = 0 ;} // (!|?) exp
	| expresion OP_BINARIO expresion %prec ALMOHADILLA { $$ = comprobacionBinaria($1,$3,$2); $$.dim = 0 ; $$.varTemporal = temporal();$$.traduccion = concatenarOpBinario($$.varTemporal,$1,$2,$3.traduccion,";"); } // exp (OP_BINARIO) exp
	| expresion MULTIPLICATIVO expresion %prec ALMOHADILLA { $$ = comprobacionOperacionMultiplicativa($1,$3,$2); $$.dim = 0 ; $$.varTemporal = temporal();$$.traduccion = concatenarMultiplicativo($$.varTemporal,$1,$2,$3.traduccion,";");  } // exp (*|%|/) exp
	| expresion ADITIVO expresion %prec ALMOHADILLA { $$ = comprobacionOperacionMasMenos($1,$3,$2); $$.dim = 0 ;$$.varTemporal = temporal();$$.traduccion = concatenarAditivo($$.varTemporal,$1,$2,$3.traduccion,";");  } // exp (+|-) exp
	| IDENTIFICADOR { $$ = buscarVariableDefinida($1);$$.dim = 0; $$.traduccion = $1.lexema; $$.varTemporal = "nulo";}
	| constante {$$.dim = 0 ; $$.traduccion = $1.traduccion;$$.varTemporal = "nulo";}
	| lista {$$.tipo = lista; $$.subt = $1.subt ; $$.dim = $1.dim;}
	| llamada_funcion { $$.tipo = $1.tipo; }
	| expresion ARROBA expresion %prec ARROBA{ $$ = comprobacionArroba($1, $3, $2); } // @exp
	| expresion MASMAS expresion ARROBA expresion %prec ARROBA  { $$ = comprobacionTernaria($1, $3, $5, $2, $4); }// exp ++ exp @ exp
	| sentencia_lista { $$.tipo = $1.tipo; $$.subt = $1.subt; }//$$ = buscarVariableDefinida($1);}
	| tratamiento_error
	;




//¿Que hacemos con caracter para detectar asignaciones correctas ?
constante : NUMERICO {$$.tipo = 0; $$.traduccion = $1.lexema; }
	| real {$$.tipo = 1; $$.traduccion = $1.traduccion; }
	| BOOLEANO {$$.tipo = 3; $$.traduccion = traducirBool($1); }
	| cadena {$$.tipo = 2;$$.traduccion = $1.traduccion;}
	;


lista : COR_ABRE agregado COR_CIERRA {$$.tipo = lista;$$.subt = $2.subt; $$.dim = $2.dim;} // lista.dim = agregado.dim
	;

agregado : constante { $$.subt = $1.tipo; $$.dim = 1; }// expresion.dim = 1 
	|  constante COMA agregado {$$.subt = $3.subt; $$.dim = $1.dim + 1; comprobacionAgregado($1.tipo,$3.subt);}// agregado.dim = agregado2.dim + 1
	;

cadena : COMILLAS_DOBLES contenido_cadena COMILLAS_DOBLES {$$.traduccion = crearCadena($2.lexema);}
	| ALFABETICOPRIO {$$.traduccion = $1.lexema;}
	;

contenido_cadena : contenido_cadena ALFABETICO
	| contenido_cadena NUMERICO
	| contenido_cadena C_ESPE
	| contenido_cadena EXCLAINTER
	|
	;

real 	: NUMERICO PUNTO NUMERICO { $$.traduccion = concatenarConPunto($1.lexema,$3.lexema);}
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


