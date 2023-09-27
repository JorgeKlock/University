////////////////////////////////////////////////////////////
/// PROCESADORED DE LENGUAJES - P3

ARCHIVOS DISPONIBLES:

lexico.l -> contiene la especificación lexica en lex

sintactico.y -> contiene la especificación sintáctica en yacc

_______________________________________________________

Makefile -> A partir de los ficheros anteriores genera:

y.tab.c lex.yy.c -> analizadores en C

y.tab.h -> contiene la tabla de simbolos que usa el analizador téxico ( Antes teníamos una escrita manualmente, pero esto puede incurrir en más errores )

y.out.put - > Fichero que da feedback de como se han construido las tablas de análisis, variable terminales y no terminales, reglas aplicadas, ampliación de la gramática...

analizador -> ejecutable que realiza el analisis sintactico + léxico

______________________________________________________


ejemploPrograma -> se le puede pasar al analizador para ver como funciona
