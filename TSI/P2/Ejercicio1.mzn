include "globals.mzn";
%Ejercicio 1 - Puzzle Cripto-Aritmético
%Definimos cada dígito dentro de un array para poder comprobar rápidamente que no haya dos letras codificadas con el mismo dígito
array[0..8] of var 0..9: digitos;
%Asignamos una posición del array dígitos a cada letra
var 0..9: S=digitos[0];
var 0..9: I=digitos[1];
var 0..9: X=digitos[2];
var 0..9: E=digitos[3];
var 0..9: V=digitos[4];
var 0..9: N=digitos[5];
var 0..9: T=digitos[6];
var 0..9: W=digitos[7];
var 0..9: Y=digitos[8];
%Definimos nuestros números como unidades, decenas, centenas,..
var int: six = (S*100+I*10+X);
var int: seven = (S*10000+E*1000+V*100+E*10+N);
var int: twenty = (T*100000+W*10000+E*1000+N*100+T*10+Y);
%Comprobamos gracias al array digitos que todos los números que se asignan son diferentes para cada letra
constraint all_different(digitos);
%Añadimos la restricción principal del problema
constraint six+seven+seven = twenty;
solve satisfy;
%Formateamos la salida
output["    \(S)\(I)\(X)\n"++
       "+ \(S)\(E)\(V)\(E)\(N)\n"++
       "+ \(S)\(E)\(V)\(E)\(N)\n"++
       "-------\n"++
       " \(T)\(W)\(E)\(N)\(T)\(Y)\n"]