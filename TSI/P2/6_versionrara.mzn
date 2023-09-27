enum Asignaturas = {A1B1, A1B2, A2B1, A2B2, A3B1, A3B2, A4B1, A4B2, A5B1, A5B2, A6B1, A6B2, A7B1, A7B2, A8B1, A9B1};
enum Profesores = {P1, P2, P3, P4};
enum Dias = {lunes, martes, miercoles, jueves, viernes};
array [1..5] of int: Horas = [8, 9, 10, 12, 13];

array [1..16] of var int: horario_dia;
array [1..16] of var int: horario_hora;
array [1..16] of var int: horario_profesor;

constraint forall (i in 1..16)
(horario_dia[i] in Dias);
constraint forall (i in 1..16)
(horario_hora[i] in 1..5);
constraint forall (i in 1..16)
(horario_profesor[i] in Profesores);

%Los dias de los distintos bloques tienen que ser distintos y anteriores los bloques 1 a los 2
constraint horario_dia[A1B1] < horario_dia[A1B2];
constraint horario_dia[A2B1] < horario_dia[A2B2];
constraint horario_dia[A3B1] < horario_dia[A3B2];
constraint horario_dia[A4B1] < horario_dia[A4B2];
constraint horario_dia[A5B1] < horario_dia[A5B2];
constraint horario_dia[A6B1] < horario_dia[A6B2];
constraint horario_dia[A7B1] < horario_dia[A7B2];

%Los profesores son los siguientes:
constraint horario_profesor[A1B1] = P1;
constraint horario_profesor[A1B2] = P1;
constraint horario_profesor[A2B1] = P4;
constraint horario_profesor[A2B2] = P4;
constraint horario_profesor[A3B1] = P1;
constraint horario_profesor[A3B2] = P1;
constraint horario_profesor[A4B1] = P2;
constraint horario_profesor[A4B2] = P2;
constraint horario_profesor[A5B1] = P2;
constraint horario_profesor[A5B2] = P2;
constraint horario_profesor[A6B1] = P3;
constraint horario_profesor[A6B2] = P3;
constraint horario_profesor[A7B1] = P4;
constraint horario_profesor[A7B2] = P4;
constraint horario_profesor[A8B1] = P4;
constraint horario_profesor[A9B1] = P3;

%Cada profesor solo puede impartir un bloque (!MENOS EL 4)
%a!=i significa bloques distintos. Si bloques distintos y el profesor es el mismo, el dia tiene que ser distinto
constraint 
forall (i in 1..16)
(forall (a in 1..16)
(if a!=i /\ horario_profesor[i] == horario_profesor[a] /\ horario_profesor[i] != P4 then horario_dia[i] != horario_dia[a]
endif));

%Restricciones de profesor
%P1 solo en las dos ultimas horas
constraint 
forall (i in 1..16)
(horario_profesor[i] == 1 -> horario_hora[i] = 4 \/ horario_hora[i] = 5);
%P2 solo en las dos primeras horas
constraint 
forall (i in 1..16)
(horario_profesor[i] == 2 -> horario_hora[i] = 1 \/ horario_hora[i] = 2);
%P3 solo justo antes del recreo
constraint 
forall (i in 1..16)
(horario_profesor[i] == 3 -> horario_hora[i] = 3);

constraint horario_dia[A1B1] = lunes \/ horario_dia[A1B1] = martes;
constraint horario_dia[A1B2] = lunes \/ horario_dia[A1B2] = martes;
constraint horario_dia[A3B1] = miercoles \/ horario_dia[A3B1] = jueves;
constraint horario_dia[A3B2] = miercoles \/ horario_dia[A3B2] = jueves;
constraint horario_dia[A4B1] = lunes \/ horario_dia[A4B1] = martes;
constraint horario_dia[A4B2] = lunes \/ horario_dia[A4B2] = martes;
constraint horario_dia[A5B1] = jueves \/ horario_dia[A5B1] = viernes;
constraint horario_dia[A5B2] = jueves \/ horario_dia[A5B2] = viernes;
constraint horario_dia[A6B1] = miercoles \/ horario_dia[A6B1] = viernes;
constraint horario_dia[A6B2] = miercoles \/ horario_dia[A6B2] = viernes;
constraint horario_dia[A7B1] = martes \/ horario_dia[A7B1] = viernes;
constraint horario_dia[A7B2] = martes \/ horario_dia[A7B2] = viernes;
constraint horario_dia[A8B1] = miercoles;
constraint horario_dia[A9B1] = lunes;

%Horas[i] == Horas[i+1]
output 
["\t\t" ++ "Lunes" ++ "\t" ++ "   Martes" ++ "\t" ++ "   Miercoles" ++ "\t" ++ "   Jueves" ++ "\t" ++ "   Viernes" ++ "\n"]++
[show(Horas[i]) ++ ":00-" ++ show(Horas[i]+1) ++ ":00  ->\t" ++
show(Asignaturas[i]) ++ "-" ++ show(Profesores[1]) ++ "\t   " ++
show(Asignaturas[i]) ++ "-" ++ show(Profesores[1]) ++ "\t   " ++
show(Asignaturas[i]) ++ "-" ++ show(Profesores[1]) ++ "\t   " ++
show(Asignaturas[i]) ++ "-" ++ show(Profesores[1]) ++ "\t   " ++
show(Asignaturas[i]) ++ "-" ++ show(Profesores[1]) ++ "\t   " ++
"\n"  | i in horario_hora]
      