include "globals.mzn";
%Ejercicio 5 - Asignar Horario
enum Profesores = {P1, P2, P3, P4};
enum Grupos = {G1, G2, G3, G4};
enum Aulas = {A1, A2, A3};
enum Asignaturas = {IA, TSI, FBD};
enum Horas = {H9, H10, H11, H12};
%Creamos un array 3dimensional horario que será donde almacenemos nuestra solución
%Dimension 1- Hora, Dimension 2-Aula, Dimension 3-Asignatura+Grupo+Profesor
array [1..4, 1..3, 1..3] of var int: horario;
%Creamos un array para darle un valor diferente a cada conjunto asignatura-grupo y asegurarnos de que no se repitan a lo largo de la semana
array [1..16] of var int: AHPvalue;
constraint forall (i in Horas)
(forall (j in Aulas)
(AHPvalue[4*(i-1)+j] = 100*horario[i,j,1]+horario[i,j,2]));
%Una misma asignatura solo puede darla un grupo una vez  
constraint all_different( AHPvalue );

%Establecemos el ámbito de las variables asignatura-grupo-profesor dentro del array 3dimensional
constraint forall (i in Horas) 
          (forall (j in Aulas) 
          (horario[i,j,1] > 0 /\ horario[i,j,1] <= 3));
constraint forall (i in Horas) 
          (forall (j in Aulas) 
          (horario[i,j,2] > 0 /\ horario[i,j,2] <= 4));
constraint forall (i in Horas) 
          (forall (j in Aulas) 
          (horario[i,j,3] > 0 /\ horario[i,j,3] <= 4));      
              
%A una misma hora, los profesores de cada aula deben ser distintos
constraint forall (i in Horas) 
(horario[i,1,3] != horario[i,2,3] /\ 
horario[i,1,3] != horario[i,3,3] /\ 
horario[i,2,3] != horario[i,3,3]);

%A una misma hora, un mismo grupo solo puede estar en un aula
constraint forall (i in Horas) 
(horario[i,1,2] != horario[i,2,2] /\ 
horario[i,1,2] != horario[i,3,2] /\ 
horario[i,2,2] != horario[i,3,2]);

%Si el profesor es el 2, el aula es la 2
constraint forall (i in Horas) 
          (forall (j in Aulas) 
          (horario[i,j,3] == 2 -> j == 2));   
%Si el profesor es el 4, el aula es la 3
constraint forall (i in Horas) 
          (forall (j in Aulas) 
          (horario[i,j,3] == 4 -> j == 3));   
%Si la asignatura es TSI el aula es 2 or 3
constraint forall (i in Horas) 
          (forall (j in Aulas) 
          (horario[i,j,1] == TSI -> j == 2 \/ j==3));
%Si el grupo es el 1 y la asignatura IA la hora es las 9
constraint forall (i in Horas) 
          (forall (j in Aulas) 
          (horario[i,j,2] == 1 /\ horario[i,j,1] == IA -> i == H9));
%Si el grupo es el 3 y la asignatura IA la hora es las 11 y el aula la 1
constraint forall (i in Horas) 
          (forall (j in Aulas) 
          (horario[i,j,2] == 3 /\ horario[i,j,1] == IA -> (i == H11 /\ j==1)));
%Aqui añadimos los constraints asociados a cada profesor concreto, qué asignaturas y grupos puede dar, y si tienen limitación de horario
%Si el profesor es el 1...
constraint forall (i in Horas) 
          (forall (j in Aulas) 
          (horario[i,j,3] == 1 ->
          (horario[i,j,1] == FBD /\ (horario[i,j,2] == G1 \/ horario[i,j,2] == G2 \/ horario[i,j,2] == G3) \/
          (horario[i,j,1] == IA /\ (horario[i,j,2] == G1)
          ))));  
%Si el profesor es el 2...
constraint forall (i in Horas) 
          (forall (j in Aulas) 
          (horario[i,j,3] == 2 -> 
          (i == H9 \/ i == H10) /\
          ((horario[i,j,1] == IA /\ (horario[i,j,2] == G2) \/
          (horario[i,j,1] == FBD /\ (horario[i,j,2] == G4))
          ))));
%Si el profesor es el 3...
constraint forall (i in Horas) 
          (forall (j in Aulas) 
          (horario[i,j,3] == 3 -> (horario[i,j,1] == IA /\ (horario[i,j,2] == G3) \/
          (horario[i,j,1] == TSI /\ (horario[i,j,2] == G1 \/ horario[i,j,2] == G2 \/ horario[i,j,2] == G4)
          ))));
%Si el profesor es el 4...
constraint forall (i in Horas) 
          (forall (j in Aulas) 
          (horario[i,j,3] == 4 -> 
          (horario[i,j,1] == IA /\ (horario[i,j,2] == G4) \/
          (horario[i,j,1] == TSI /\ (horario[i,j,2] == G3)))));
solve satisfy;
%Formateamos la salida
output ["\t\t" ++ "Aula 1" ++ "\t" ++ "   Aula 2" ++ "\t" ++ "   Aula 3" ++ "\n" ++
" 9 - 10 ->\t" ++ 
show(Asignaturas[horario[1,1,1]]) ++ "-" ++ show(Grupos[horario[1,1,2]]) ++ " (" ++                   show(Profesores[horario[1,1,3]]) ++ ")  " ++ show(Asignaturas[horario[1,2,1]]) ++ "-" ++ show(Grupos[horario[1,2,2]]) ++ " (" ++ show(Profesores[horario[1,2,3]]) ++ ")\t"++ show(Asignaturas[horario[1,3,1]]) ++ "-" ++ show(Grupos[horario[1,3,2]]) ++ " (" ++ show(Profesores[horario[1,3,3]]) ++ ")" ++ "\n" ++

" 10 - 11 ->\t" ++ 
show(Asignaturas[horario[2,1,1]]) ++ "-" ++ show(Grupos[horario[2,1,2]]) ++ " (" ++                   show(Profesores[horario[2,1,3]]) ++ ")  " ++ show(Asignaturas[horario[2,2,1]]) ++ "-" ++ show(Grupos[horario[2,2,2]]) ++ " (" ++ show(Profesores[horario[2,2,3]]) ++ ")\t"++ show(Asignaturas[horario[2,3,1]]) ++ "-" ++ show(Grupos[horario[2,3,2]]) ++ " (" ++ show(Profesores[horario[2,3,3]]) ++ ")" ++ "\n" ++

" 11 - 12 ->\t" ++ 
show(Asignaturas[horario[3,1,1]]) ++ "-" ++ show(Grupos[horario[3,1,2]]) ++ " (" ++                   show(Profesores[horario[3,1,3]]) ++ ")  " ++ show(Asignaturas[horario[3,2,1]]) ++ "-" ++ show(Grupos[horario[3,2,2]]) ++ " (" ++ show(Profesores[horario[3,2,3]]) ++ ")\t"++ show(Asignaturas[horario[3,3,1]]) ++ "-" ++ show(Grupos[horario[3,3,2]]) ++ " (" ++ show(Profesores[horario[3,3,3]]) ++ ")" ++ "\n" ++

" 12 - 13 ->\t" ++ 
show(Asignaturas[horario[4,1,1]]) ++ "-" ++ show(Grupos[horario[4,1,2]]) ++ " (" ++                   show(Profesores[horario[4,1,3]]) ++ ")  " ++ show(Asignaturas[horario[4,2,1]]) ++ "-" ++ show(Grupos[horario[4,2,2]]) ++ " (" ++ show(Profesores[horario[4,2,3]]) ++ ")\t"++ show(Asignaturas[horario[4,3,1]]) ++ "-" ++ show(Grupos[horario[4,3,2]]) ++ " (" ++ show(Profesores[horario[4,3,3]]) ++ ")" ++ "\n"
]
      