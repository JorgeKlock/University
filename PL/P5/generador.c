#include "codegen.h"
#include <stdio.h>
#include "definiciones.h"

FILE *output;
FILE *fichero_funciones;

int numVariable= 0;
int numEtiqueta= 0;
int primera = 0;

#define SIZE_MALLOC 2048


void openFile()
{
    output = fopen("output.c", "w");
    fichero_funciones = fopen("dec_func.h", "w");
}

void closeFile()
{
    fclose(output);
    fclose(fichero_funciones);
}

char * temporal()
{
    char* res = malloc(SIZE_MALLOC);
    sprintf(res, "tmp%i", numVariable);
    numVariable += 1;
    return res;
}

char * etiqueta()
{
    char* res = malloc(SIZE_MALLOC);
    sprintf(res, "etiqueta%i", numEtiqueta);
    numEtiqueta += 1;
    return res;
}

char * comprobacionIf(char *var,char*etiqueta)
{
    char* res = malloc(SIZE_MALLOC);
    sprintf(res, "if(!%s) goto %s ; \n", var,etiqueta);
    return res;
}

char * comprobacionWhile(char *var,char*etiqueta)
{
    char* res = malloc(SIZE_MALLOC);
    sprintf(res, "if(!%s) goto %s ; \n", var,etiqueta);
    return res;
}

char * concaternarIfSalida(char*etiqueta,char *sentenciaIf)
{
    char* res = malloc(SIZE_MALLOC);
    sprintf(res, "%s goto %s;\n", sentenciaIf,etiqueta);
    return res;
}

char * concatenarElse(char*etiquetaE,char * sentencias, char* etiSalida,char *anterior)
{
    char* res = malloc(SIZE_MALLOC);
    sprintf(res, "%s %s: \n %s \n } \n%s: \n{}\n", anterior,etiquetaE,sentencias ,etiSalida);
    return res;
}

char * concatenarElse2(char*etiquetaE,char * sentencias, char* etiSalida,char *anterior)
{
    char* res = malloc(SIZE_MALLOC);
    sprintf(res, "%s %s: \n %s \n } \n%s: \n{}\n", anterior,etiquetaE,sentencias ,etiSalida);
    return res;
}

char* concatenar(char* izq, char* dch){
	char* total = malloc(10000);
	sprintf(total,"%s%s",izq,dch);
	return total;
}

char* concatenarVariables(char* izq, char* dch){
	char* total = malloc(10000);
	if(primera==0){
	sprintf(total,"%s",dch);
	primera+=1;
	} else {
	sprintf(total,"%s%s",izq,dch);
	}
	return total;
}

char* crearCadena(char* cadena){
	char* total = malloc(10000);
	sprintf(total,"\"%s\"",cadena);
	return total;
}

char* concatenarConComa(char* izq, char* dch){
	char* total = malloc(10000);
	sprintf(total,"%s,%s",izq,dch);
	return total;
}

char* concatenarConPunto(char* izq, char* dch){
	char* total = malloc(10000);
	sprintf(total,"%s.%s",izq,dch);
	return total;
}

char* concatenarAsignacion(char *c1,char *c2,char *c3,char *c4){
	char* total = malloc(10000);
	sprintf(total,"%s %s %s %s \n",c1,c2,c3,c4);
	return total;
}

char* concatenarTriple(char *c1,char *c2,char *c3){
	char* total = malloc(10000);
	sprintf(total,"%s%s%s",c1,c2,c3);
	return total;
}



char* concatenarCuadrupleAsignacion(char *c1,char *c2,atributo c3,char *c4){
	char* total = malloc(10000);
	if( strcmp(c3.varTemporal,"nulo") == 0){
	sprintf(total,"\n%s%s%s",c1,c2,c3.traduccion);
	} else {
	sprintf(total,"%s%s%s",c1,c2,c3.varTemporal);
	}
	return total;
}

char* concatenarCuadruple(char *c1,char *c2,char *c3,char *c4){
	char* total = malloc(10000);
	sprintf(total,"%s%s%s%s",c1,c2,c3,c4);
	return total;
}

char* concatenarFor(char *etiE,char *etiS,atributo asig,atributo exp,atributo sentencia){
	char* total = malloc(10000);
	char* aux = malloc(10000);
	char* tmp = temporal();
	sprintf(aux ,"if(!%s) goto %s;\n %s \n %s = %s + 1; \n goto %s; \n } \n } %s:",exp.varTemporal,etiS,sentencia.traduccion, tmp,tmp,etiE,etiS);
	sprintf(total,"int %s; \n %s = 1;  \n %s: \n { \n %s \n %s",tmp,tmp,etiE,exp.traduccion,aux);
	return total;
}

char* concatenaSentenciaSalida(char* s){
	 char* total = malloc(10000);
	 sprintf(total,"printf(%s);\n",s);
	return total;
}

char* concatenaSentenciaEntrada(atributo s){
	 char* total = malloc(10000);
	char* tipoc = malloc(10000);
	if( s.tipo == entero){
		sprintf(tipoc,"%%d ");
	} else if (s.tipo == real){
		sprintf(tipoc,"%%f ");
	} else if (s.tipo == booleano){
		sprintf(tipoc,"%%d ");
	} else if (s.tipo == caracter){
		sprintf(tipoc,"%%s ");
	}
	 sprintf(total,"scanf(\"%s\",&%s);\n",tipoc,s.lexema);
	return total;
}

char* concatenarEtiqueta(char *c1,char *c2){
	char* total = malloc(10000);
	sprintf(total,"%s: \n { \n %s",c1,c2);
	return total;
}

char* concatenarEtiqueta2(char *etiqueta,char *c1){
	char* total = malloc(10000);
	sprintf(total,"%s\n goto %s; \n } \n",c1,etiqueta);
	return total;
}

char* concatenarEtiquetaSalida(char *etiqueta,char *c1){
	char* total = malloc(10000);
	sprintf(total,"%s } \n  %s: \n",c1,etiqueta);
	return total;
}



char* concatenarAditivo(char* temporal,atributo c1,atributo atr,char *c3,char *c4){
	char* total = malloc(10000);
	char* aux = malloc(10000);
	char* signo = malloc(10000);
	char* tipoTemporal = malloc(10000);
	char* declaracion = malloc(10000);

	if(c1.tipo == 0){
		sprintf(tipoTemporal,"int");
	} else {
		sprintf(tipoTemporal,"double");
	}

	if(atr.atrib == 1){
		signo = "-";
	} else {
		signo = "+";
	}
	if( strcmp(c1.varTemporal,"nulo") == 0){
		sprintf(declaracion,"%s %s;\n",tipoTemporal,temporal);
		sprintf(total,"%s = %s%s%s%s\n",temporal,c1.traduccion,signo,c3,c4);
		total = concatenar(declaracion,total);
	} else {
		sprintf(declaracion,"%s %s;\n",tipoTemporal,temporal);
		sprintf(aux,"%s = %s%s%s%s\n",temporal,c1.varTemporal,signo,c3,c4);
		total = concatenarTriple(declaracion,c1.traduccion,aux);
	}
	return total;
}

char* concatenarMultiplicativo(char* temporal,atributo c1,atributo atr,char *c3,char *c4){
	char* total = malloc(10000);
	char* aux = malloc(10000);
	char* signo = malloc(10000);
	char* tipoTemporal = malloc(10000);
	char* declaracion = malloc(10000);

	if(c1.tipo == 0){
		sprintf(tipoTemporal,"int");
	} else {
		sprintf(tipoTemporal,"double");
	}

	if(atr.atrib == 0){
		signo = "*";
	} else if (atr.atrib == 1) {
		signo = "%";
	} else {
		signo = "/";
	}

	if( strcmp(c1.varTemporal,"nulo") == 0){
		sprintf(declaracion,"%s %s;\n",tipoTemporal,temporal);
		sprintf(total,"%s = %s%s%s%s\n",temporal,c1.traduccion,signo,c3,c4);
		total = concatenar(declaracion,total);
	} else {
		sprintf(declaracion,"%s %s;\n",tipoTemporal,temporal);
		sprintf(aux,"%s = %s%s%s%s\n",temporal,c1.varTemporal,signo,c3,c4);
		total = concatenarTriple(declaracion,c1.traduccion,aux);
	}
	return total;
}

char* concatenarOpBinario(char* temporal,atributo c1,atributo atr,char *c3,char *c4){
	char* total = malloc(10000);
	char* aux = malloc(10000);
	char* signo = malloc(10000);
	char* tipoTemporal = malloc(10000);
	char* declaracion = malloc(10000);



	if(atr.atrib == 0){
		signo = ">";
	} else if (atr.atrib == 1) {
		signo = ">=";
	}  else if (atr.atrib == 2) {
		signo = "<";
	}  else if (atr.atrib == 3) {
		signo = "<=";
	}  else if (atr.atrib == 4) {
		signo = "==";
	}  else if (atr.atrib == 5) {
		signo = "&";
	}  else if (atr.atrib == 6) {
		signo = "||";
	}   else if (atr.atrib == 7) {
		signo = "&&";
	}  else if (atr.atrib == 8) {
		signo = "^";
	}  else if (atr.atrib == 9) {
		signo = "--";
	}  else if (atr.atrib == 10) {
		signo = "**";
	}  else if (atr.atrib == 11) {
		signo = "!=";
	}  

	if( strcmp(c1.varTemporal,"nulo") == 0){
		sprintf(declaracion,"bool %s;\n",temporal);
		sprintf(total,"%s = %s%s%s%s\n",temporal,c1.traduccion,signo,c3,c4);
		total = concatenar(declaracion,total);
	} else {
		sprintf(declaracion,"bool %s;\n",temporal);
		sprintf(aux,"%s = %s%s%s%s\n",temporal,c1.varTemporal,signo,c3,c4);
		total = concatenarTriple(declaracion,c1.traduccion,aux);
	}
	return total;
}

char* traducirBool(atributo atr){
	char* total = malloc(10000);	

	if(atr.atrib == 0){
		sprintf(total,"true");
	} else {
		sprintf(total,"false");
	}
	
	return total;
}


char* concatenarTipoVariable(atributo izq, char* dch){
	char* tipoc = malloc(10000);
	if( izq.tipo == entero){
		sprintf(tipoc,"int ");
	} else if (izq.tipo == real){
		sprintf(tipoc,"double ");
	} else if (izq.tipo == booleano){
		sprintf(tipoc,"bool ");
	} else if (izq.tipo == caracter){
		sprintf(tipoc,"char ");
	}
	char* resultados = malloc(10000);
	resultados = concatenar(tipoc,dch);
	return resultados;
}


char* generarIntermedio(char *var,char* cuerpo){
	fprintf(output,"#include <stdio.h>\n");
	//REVISAR INLCUDES POR DEFECTO
	fprintf(output,"#include<stdbool.h>\n");
	//char* variables = variablesGlobales();
	//fprintf(output,"%s",variables);
	fprintf(output,"%s\n",var);
	fprintf(output,"int main(int argc,char* argv[])");
	fprintf(output,"%s\n",cuerpo);

}


