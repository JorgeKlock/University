include "globals.mzn";
%Ejercicio 6 - Asignar Horario P2
array [1..5] of int: Horas = [08, 09, 10, 12, 13];
enum Dias = {lunes, martes, miercoles, jueves, viernes};
enum Asignaturas = {A1, A2, A3, A4, A5, A6, A7, A8, A9};
enum Profesores = {P1, P2, P3, P4};

array [1..9] of int: horas_semanales = [4,2,4,4,4,2,2,2,1];
array [1..9] of int: tam_bloque = [2,1,2,2,2,1,1,1,2];

%Dimension 1- Hora, Dimension 2-Dia, Dimension 3-Asignatura+Bloque+Profesor
array [1..6, 1..5, 1..3] of var int: horario;

%Establecemos el ámbito de las variables asignatura-bloque-profesor dentro del array 3dimensional
constraint forall (i in 1..6) 
          (forall (j in Dias) 
          (horario[i,j,1] > 0 /\ horario[i,j,1] <= 9));
constraint forall (i in 1..6) 
          (forall (j in Dias) 
          (horario[i,j,2] > 0 /\ horario[i,j,2] <= 2));
constraint forall (i in 1..6) 
          (forall (j in Dias) 
          (horario[i,j,3] > 0 /\ horario[i,j,3] <= 4));      
          
          
%Las asignaturas 1,3,4,5,8 se imparten en bloques de 2
%Las asignaturas 2,6,7,8 se imparten en bloques de 1  
constraint forall (i in 1..5) 
          (forall (j in Dias) 
          (if horario[i,j,1] in {1,3,4,5,8} then
          horario[i,j,1] == horario[i+1,j,1]
          else horario[i,j,1] != horario[i+1,j,1]
          endif)); 
%En cada dia de la semana solo se puede impartir un bloque de cada asignatura
%Para cada dia, si la asignatura que se da es doble se permiten 2 clases, si no, se permite 1.
constraint forall (a in Asignaturas) 
          (forall (j in Dias) 
          (if tam_bloque[a] == 2 then sum(i in 1..6)(horario[i,j,1]==i) = 2
          else sum(i in 1..6)(horario[i,j,1]==i) = 1 endif));
          
          
          
          
          
          
          
          
%Formateamos la salida
output 
["\t\t" ++ "Lunes" ++ "\t" ++ "   Martes" ++ "\t" ++ "   Miercoles" ++ "\t" ++ "   Jueves" ++ "\t" ++ "   Viernes" ++ "\n"]++
[show(Horas[i]) ++ ":00-" ++ show(Horas[i]+1) ++ ":00  ->\t" ++
show(Asignaturas[horario[i,1,1]]) ++ "-" ++ show(horario[i,1,2]) ++ "-" ++ show(Profesores[horario[i,1,3]]) ++ "\t   " ++
show(Asignaturas[horario[i,2,1]]) ++ "-" ++ show(horario[i,2,2]) ++ "-" ++ show(Profesores[horario[i,2,3]]) ++ "\t   " ++
show(Asignaturas[horario[i,3,1]]) ++ "-" ++ show(horario[i,3,2]) ++ "-" ++ show(Profesores[horario[i,3,3]]) ++ "\t   " ++
show(Asignaturas[horario[i,4,1]]) ++ "-" ++ show(horario[i,4,2]) ++ "-" ++ show(Profesores[horario[i,4,3]]) ++ "\t   " ++
show(Asignaturas[horario[i,5,1]]) ++ "-" ++ show(horario[i,5,2]) ++ "-" ++ show(Profesores[horario[i,5,3]]) ++ "\t   " ++
"\n"  | i in 1..6]
      