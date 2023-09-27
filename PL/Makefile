#ARCHIVO MAKEFILE QUE GENERA EL PROYECTO COMPLETO
# TUTORIAL YACC : https://campusvirtual.ull.es/ocw/pluginfile.php/2312/mod_resource/content/0/perlexamples/node276.html

programa: y.tab.c lex.yy.c
	gcc -DYYDEBUG=1 -g -o analizador y.tab.c 

y.tab.c  y.tab.h: sintactico.y
	yacc -v --verbose --debug -d -y sintactico.y

lex.yy.c: lexico.l y.tab.h
	flex -l lexico.l

clean:
	rm -f y.tab.* y.output lex.yy.c *.o programa

