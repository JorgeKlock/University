%{
#include "y.tab.h"
#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"
extern YYSTYPE yylval;
int linea = 1;
%}
letra	[a-zA-Z]
digito	[0-9]
bool ("Verdadero"|"Falso")
tipo_dato_basico ("entero"|"real"|"booleano"|"caracter")
binarios (">"|">="|"<"|"<="|"=="|"&"|"||"|"&&"|"^"|"--"|"**"|"!=")
especiales ("_"|"\\")
otros .
%%
{binarios}        			{ return OP_BINARIO; }
{tipo_dato_basico}        		{ return TIPO_DATO_BASICO; }
("lista de")            		{ return LISTA; }
("si")                			{ return SI; }
("mientras")            		{ return MIENTRAS; }
("para")            			{ return PARA; }
("bajando_hasta")        		{ return BAJANDO_HASTA; }
("hasta")            			{ return HASTA; }
("hacer")            			{ return HACER; }
("salida")            			{ return SALIDA; }
("entrada")            			{ return ENTRADA; }
("sino")            			{ return SINO; }
("retorno")            			{ return RETORNO; }
("=")                			{ return OP_ASIGNACION; }
("Principal")            		{ return PRINCIPAL; }
("var")                			{ return VAR; }
("varend")            			{ return VAREND; }
("(")                			{ return PIZQ; }
(")")                			{ return PDCH; }
("{")                			{ return CIZQ; }
("}")                			{ return CDCH; }
(".")                			{ return PUNTO; }
(",")                			{ return COMA; }
(";")					{ return PYC; }
("\"")                			{ return COMILLAS_DOBLES; }
("[")                			{ return COR_ABRE; }
("]")                			{ return COR_CIERRA; }
("++")                			{ return MASMAS; }
("!"|"?")				{ return EXCLAINTER; }
("@")                			{ return ARROBA; }
("$")                			{ return COMIENZO_LISTA; }
("#")                			{ return ALMOHADILLA; }
(">>"|"<<")            			{ return MOV_CURSOR; }
{bool}            			{ return BOOLEANO; }
("\""{letra}*"\"")			{ return ALFABETICOPRIO; }
[a-zA-Z][a-zA-Z0-9]*    		{ return IDENTIFICADOR; }
{digito}*				{ return NUMERICO; }
{letra}*				{ return ALFABETICO; }
{especiales}*				{ return C_ESPE; }
("*"|"%"|"/")				{ return MULTIPLICATIVO;}
("+"|"-")				{ return ADITIVO;}
[ \t\n] 				{ if ( yytext[0]=='\n' )++linea; }
.	  				{ printf("\n%sLÉXICAL ERROR linea %d: El caracter %s en la línea no fue encontrado\n%s",KRED,linea,yytext,KNRM); }
%%
int yywrap() { return 1; }

