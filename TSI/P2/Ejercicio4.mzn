include "globals.mzn";
%Ejercicio 4 - Amigos
%Creamos enums para determinar los dias de la semana y las personas que intervienen en la conversacion
enum Dia = {lunes, martes, miercoles, jueves, viernes, sabado, domingo};
enum Personas = {Juan, Maria, Carmen, Francisco, Marta, Olga, Pepe};
%Creamos un array donde cada posición del array es una de las afirmaciones de cada miembro, y el valor 0 implica que es falsa
%Mientras que el valor 1 indica que es cierta
array [1..7] of var 0..1: afirmaciones;
var Dia: dia_actual;
var Personas: emisor;
%Utilizamos constraints para determinar según que afirmación sea cierta el día que es
constraint dia_actual == martes <-> afirmaciones[1]=1;
constraint dia_actual == lunes <-> afirmaciones[2]=1;
constraint dia_actual == miercoles <-> afirmaciones[3]=1;
constraint dia_actual == domingo <-> afirmaciones[4]=1;
constraint dia_actual == jueves <-> afirmaciones[5]=1;
constraint dia_actual == viernes <-> afirmaciones[5]=1;
constraint dia_actual == domingo <-> afirmaciones[6]=1;
constraint dia_actual != domingo <-> afirmaciones[7]=1;
%Y esta constraint es vital para asegurar que cumplimos la restricción del problema de que sólo una afirmación es correcta
constraint sum(afirmaciones) == 1;
%Usamos este constraint para obtener el emisor que ha dicho la afirmacion cierta
constraint forall(i in 1..7)
(if afirmaciones[i]==1 then emisor = Personas[i] endif);
%Formateamos el output
output["hoy: " ++ show(dia_actual) ++ "\n" ++
       "emisor: " ++ show(emisor)]
