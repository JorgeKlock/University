%{
#include "y.tab.h"
#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"
extern YYSTYPE yylval;
int linea = 1;
%}
letra	[a-zA-Z]
letraEspacio	[a-zA-Z ]
letraEspacioCorchete	[a-zA-Z%*=^\\ ]
letraCorchete	[a-zA-Z%]
digito	[0-9]
bool ("Verdadero"|"Falso")
tipo_dato_basico ("entero"|"real"|"booleano"|"caracter")
binarios (">"|">="|"<"|"<="|"=="|"&"|"||"|"&&"|"^"|"--"|"**"|"!=")
especiales ("_"|"\\")
espacio (" ")
otros .
%%
{binarios}        			{ 
						if( strcmp(strdup(yytext),">") == 0)
						{
							yylval.atrib=0;
						}
						else if(strcmp(strdup(yytext),">=") == 0)
						{
							yylval.atrib=1;
						} 
						else if (strcmp(strdup(yytext),"<") == 0 )
						{
							yylval.atrib=2;
						} 
						else if (strcmp(strdup(yytext),"<=") == 0 )
						{
							yylval.atrib=3;
						}
						else if (strcmp(strdup(yytext),"==") == 0 )
						{
							yylval.atrib=4;
						}
						else if (strcmp(strdup(yytext),"&") == 0 )
						{
							yylval.atrib=5;
						}
						else if (strcmp(strdup(yytext),"||") == 0 )
						{
							yylval.atrib=6;
						}
						else if (strcmp(strdup(yytext),"&&") == 0 )
						{
							yylval.atrib=7;
						}
						else if (strcmp(strdup(yytext),"^") == 0 )
						{
							yylval.atrib=8;
						}
						else if (strcmp(strdup(yytext),"--") == 0 )
						{
							yylval.atrib=9;
						}
						else if (strcmp(strdup(yytext),"**") == 0 )
						{
							yylval.atrib=10;
						}
						else if (strcmp(strdup(yytext),"!=") == 0 )
						{
							yylval.atrib=11;
						}
						else
						{
							yylval.atrib=12;
						}  
						return OP_BINARIO; 
					}
{tipo_dato_basico}        		{ 
						if( strcmp(strdup(yytext),"entero") == 0)
						{
							yylval.tipo=0;
						}
						else if(strcmp(strdup(yytext),"real") == 0)
						{
							yylval.tipo=1;
						} 
						else if (strcmp(strdup(yytext),"caracter") == 0 )
						{
							yylval.tipo=2;
						}
						else if (strcmp(strdup(yytext),"booleano") == 0 ) 
						{
							yylval.tipo=3;
						} 
						else if (strcmp(strdup(yytext),"lista") == 0 ) 
						{
							yylval.tipo=4;
						} 						
						else
						{
							yylval.tipo=5;
						} 

						return TIPO_DATO_BASICO;
					}
("lista de")            		{ 	
						yylval.tipo = 4;
						return LISTA; 
					}
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
("{")                			{  yylval.lexema = "{"; return CIZQ; }
("}")                			{ yylval.lexema="}" ;return CDCH; }
(".")                			{ yylval.lexema=strdup(yytext) ;return PUNTO; }
(",")                			{ return COMA; }
(";")					{ return PYC; }
("\"")                			{ return COMILLAS_DOBLES; }
("[")                			{ return COR_ABRE; }
("]")                			{ return COR_CIERRA; }
("++")                			{ return MASMAS; }
("!"|"?")				{ 
                            if( strcmp(strdup(yytext),"!")==0)
                            {
                               yylval.atrib=0;
                            }
                            else if (strcmp(strdup(yytext),"?")==0)
                            {
                                yylval.atrib=1;
                            }
                            else
                            {   yylval.atrib=2;}
                            return EXCLAINTER;
                        }


("@")                			{ return ARROBA; }
("$")                			{ return COMIENZO_LISTA; }
("#")                			{ return ALMOHADILLA; }
(">>"|"<<")            			{ return MOV_CURSOR; }
{bool}            			{ yylval.lexema=strdup(yytext);
						if( strcmp(strdup(yytext),"Verdadero") == 0)
						{
							yylval.atrib=0;
						}
						else if(strcmp(strdup(yytext),"Falso") == 0)
						{
							yylval.atrib=1;
						} 
						return BOOLEANO; }
"\""{letra}*"\""|"\""{letraEspacio}*"\""|"\""{letraCorchete}*"\""|"\""{letraEspacioCorchete}*"\""			{ yylval.lexema=strdup(yytext) ;return ALFABETICOPRIO; }
[a-zA-Z][a-zA-Z0-9]*    		{ yylval.lexema=strdup(yytext) ;return IDENTIFICADOR; }
{digito}*				{ yylval.lexema=strdup(yytext) ;return NUMERICO; }
{letra}*				{ yylval.lexema=strdup(yytext) ;return ALFABETICO; }
{especiales}*				{ return C_ESPE; }
("*"|"%"|"/")				{ 
						if( strcmp(strdup(yytext),"*") == 0)
						{
							yylval.atrib=0;
						}
						else if(strcmp(strdup(yytext),"%") == 0)
						{
							yylval.atrib=1;
						} 
						else if (strcmp(strdup(yytext),"/") == 0 )
						{
							yylval.atrib=2;
						}
						else
						{
							yylval.atrib=3;
						} 
						return MULTIPLICATIVO;
					}
("+"|"-")				{ 
						if( strcmp(strdup(yytext),"+") == 0)
						{
							yylval.atrib=0;
						}
						else if(strcmp(strdup(yytext),"-") == 0)
						{
							yylval.atrib=1;
						} 
						else
						{
							yylval.atrib=2;
						} 
						return ADITIVO; 
					}
[ \t\n] 				{ if ( yytext[0]=='\n' )++linea; }
.	  				{ printf("\n%sLÉXICAL ERROR linea %d: El caracter %s en la línea no fue encontrado\n%s",KRED,linea,yytext,KNRM); }
%%
int yywrap() { return 1; }

