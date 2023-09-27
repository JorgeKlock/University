include "globals.mzn";
%Ejercicio 2 - Monedas
%Definimos el importe que hay que sumar con las monedas
var int: importe_deseado = 799;
%Creamos un array donde guardaremos la cantidad de monedas de cada tipo
array [0..7] of var int: monedas;
%Definimos el total de monedas como la suma de cada elemento en el array de monedas
var int: total_monedas = monedas[0]+monedas[1]+monedas[2]+monedas[3]+monedas[4]+monedas[5]+monedas[6]+monedas[7];
%Especificamos que todas las cantidades de monedas sean positivas
constraint forall(i in 0..7) (monedas[i] >= 0);
%Añadimos la restriccion principal del problema donde la suma de las monedas por sus valores debe dar el importe deseado
constraint monedas[0]*0.01+monedas[1]*2+monedas[2]*5+monedas[3]*10+monedas[4]*20+monedas[5]*50+monedas[6]*100+monedas[7]*200 == importe_deseado;
%Especificamos que es un problema de minimización donde queremos usar el mínimo número de monedas
solve minimize total_monedas;
%Formateamos la salida
output["monedas: " ++ show(monedas) ++
       "\ntotal monedas: " ++ show(total_monedas)]