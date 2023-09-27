all: pl5.exe 

clean: 
	rm -f pl5.exe *.o y.tab.* lex.yy.c 

semantica.o: semantica.c
	gcc -c semantica.c 

generador.o: generador.c 
	gcc -c generador.c 

lex.yy.c: lexico.l 
	flex lexico.l 

y.tab.c: sintactico.y lex.yy.c generador.o semantica.o
	yacc -d -t sintactico.y 

y.tab.o: y.tab.c 
	gcc -c y.tab.c 

pl5.o: pl5.c 
	gcc -c pl5.c 

pl5.exe: pl5.o y.tab.o 
	gcc -o pl5.exe pl5.o y.tab.o 