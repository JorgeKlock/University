include "globals.mzn";
%Ejercicio 3 - Colorear Mapa
%Definimos los precios de cada color (En el intervalo 1..5 pq son los valores que devuelve el enum, no en 0..4)
array [1..5] of var int: precios_colores;
constraint precios_colores[1] = 100;
constraint precios_colores[2] = 200;
constraint precios_colores[3] = 300;
constraint precios_colores[4] = 400;
constraint precios_colores[5] = 500;
%Creamos un enumerado color con los colores distintos
enum Color = { verde, naranja, rojo, azul, amarillo };
%Definimos cada pais como un elemento de tipo color
var Color: argentina;
var Color: bolivia;
var Color: brasil;
var Color: chile;
var Color: colombia;
var Color: ecuador;
var Color: guayana_francesa;
var Color: guyana;
var Color: paraguay;
var Color: peru;
var Color: surinam;
var Color: uruguay;
var Color: venezuela;
%Especificamos que los paises fronterizos deben tener valores distintos
constraint argentina != bolivia /\ argentina != brasil /\ argentina != chile /\ argentina != paraguay /\ argentina != uruguay;
constraint bolivia != argentina /\ bolivia != brasil /\ bolivia != chile /\ bolivia != paraguay /\ bolivia != peru;
constraint brasil != argentina /\ brasil != bolivia /\ brasil != colombia /\ brasil != guayana_francesa /\ brasil != guyana /\ brasil != paraguay /\ brasil != peru /\ brasil != surinam /\ brasil != uruguay /\ brasil != venezuela;
constraint chile != argentina /\ chile != bolivia /\ chile != peru;
constraint colombia != brasil /\ colombia != ecuador /\ colombia != peru /\ colombia != venezuela;
constraint ecuador != colombia /\ colombia != peru;
constraint guayana_francesa != brasil /\ guayana_francesa != surinam;
constraint guyana != brasil /\ guayana_francesa != surinam /\ guayana_francesa != venezuela;
constraint paraguay != argentina /\ paraguay != bolivia /\ paraguay != brasil /\ paraguay != uruguay;
constraint peru != bolivia /\ peru != brasil /\ peru != chile /\ peru != colombia /\ peru != ecuador;
constraint surinam != brasil /\ surinam != guayana_francesa /\ surinam != guyana;
constraint uruguay != argentina /\ uruguay != brasil /\ uruguay != paraguay;
constraint venezuela != brasil /\ venezuela != colombia /\ venezuela != guyana;
%Definimos la funcion de coste total como la suma de los precios de cada color empleado
var int: coste_total = precios_colores[argentina]+precios_colores[bolivia]+precios_colores[brasil]+precios_colores[chile]+precios_colores[colombia]+precios_colores[ecuador]+precios_colores[guayana_francesa]+precios_colores[guyana]+precios_colores[paraguay]+precios_colores[peru]+precios_colores[surinam]+precios_colores[uruguay]+precios_colores[venezuela];
%Especificamos que el objetivo a minimizar es la funcion de coste total
solve minimize coste_total;
%Formateamos la salida
output["total: " ++ show(coste_total) ++ "\n" ++
       "Argentina\t" ++ show(argentina) ++ "\t" ++ show(precios_colores[argentina]) ++ "\n" ++
       "Bolivia\t" ++ "\t" ++ show(bolivia) ++ "\t" ++ show(precios_colores[bolivia]) ++ "\n" ++
       "Brasil\t" ++ "\t" ++ show(brasil) ++ "\t" ++ show(precios_colores[brasil]) ++ "\n" ++
       "Chile\t" ++ "\t" ++ show(chile) ++ "\t" ++ show(precios_colores[chile]) ++ "\n" ++
       "Colombia\t" ++ "\t" ++ show(colombia) ++ "\t" ++ show(precios_colores[colombia]) ++ "\n" ++
       "Ecuador\t" ++ "\t" ++ show(ecuador) ++ "\t" ++ show(precios_colores[ecuador]) ++ "\n" ++
       "Guayana_francesa\t" ++ show(guayana_francesa) ++ "\t" ++ show(precios_colores[guayana_francesa]) ++ "\n" ++
       "Guyana\t" ++ "\t" ++ show(guyana) ++ "\t" ++ show(precios_colores[guyana]) ++ "\n" ++
       "Paraguay\t" ++ "\t" ++ show(paraguay) ++ "\t" ++ show(precios_colores[paraguay]) ++ "\n" ++
       "Peru\t" ++ "\t" ++ show(peru) ++ "\t" ++ show(precios_colores[peru]) ++ "\n" ++
       "Surinam\t" ++ "\t" ++ show(surinam) ++ "\t" ++ show(precios_colores[surinam]) ++ "\n" ++
       "Uruguay\t" ++ "\t" ++ show(uruguay) ++ "\t" ++ show(precios_colores[uruguay]) ++ "\n" ++
       "Venezuela\t" ++ show(venezuela) ++ "\t" ++ show(precios_colores[venezuela]) ++ "\n"]
