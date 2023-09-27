include "globals.mzn";
%Ejercicio 10 - Mochila explorador
%Guardamos los nombres de los objetos asi como sus respectivos pesos y preferencias
enum objetos = {Mapa, Cuchillo, Prismaticos, Agua, Linterna, Cerveza, Novela, ManualDeSupervivencia, Platanos, Caramelos, Cerillas, Espejo};
array [1..12] of var int: peso_objetos = [50, 500, 1000, 3000, 1500, 3000, 500, 1000, 2000, 500, 250, 500];
array [1..12] of var int: preferencia_objetos = [100, 90, 75, 95, 85, 10, 5, 70, 90, 20, 50, 40];
%Creamos una array que simulará la mochila, con un maximo de los 12 objetos, en cada posicion valdra 1 si el objeto se lleva y 0 si no
array [1..12] of var 0..1: mochila;
var int: peso_mochila;
var int: funcion_objetivo;
%Calculamos la funcion objetivo como el sumatorio del producto de los objetos que llevamos por sus respectivas preferencias, será el valor
%a maximizar
constraint funcion_objetivo = sum(i in 1..12)(mochila[i]*preferencia_objetos[i]);
%Calculamos el peso de la mochila como el sumatorio del producto de los objetos que llevamos por sus respectivos pesos, este debe ser menor a 
%5000 para cumplir con la restriccion del problema
constraint peso_mochila = sum(i in 1..12)(mochila[i]*peso_objetos[i]);
constraint peso_mochila <= 5000;
%Indicamos al solver que deseamos maximizar la funcion explicada anteriormente
solve maximize funcion_objetivo;
%Formateamos la salida
output
["Objetos: "]++
[if fix(mochila[i])==1 then show(objetos[i]) ++ "\n" else "" endif | i in 1..12]++
["Preferencias: "]++
[show(funcion_objetivo) ++ "\n"]++
["Peso Final: "]++
[show(peso_mochila) ++ "\n"];