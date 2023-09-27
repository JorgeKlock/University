;;;;;;; JUGADOR DE 4 en RAYA ;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 
;;;;;;;;;; Version de 4 en raya clásico: Tablero de 6x7, donde se introducen fichas por arriba
;;;;;;;;;;;;;;;;;;;;;;; y caen hasta la posicion libre mas abajo
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;; Hechos para representar un estado del juego

;;;;;;; (Turno M|J)   representa a quien corresponde el turno (M maquina, J jugador)
;;;;;;; (Tablero Juego ?i ?j _|M|J) representa que la posicion i,j del tablero esta vacia (_), o tiene una ficha propia (M) o tiene una ficha del jugador humano (J)

;;;;;;;;;;;;;;;; Hechos para representar estado del analisis
;;;;;;; (Tablero Analisis Posicion ?i ?j _|M|J) representa que en el analisis actual la posicion i,j del tablero esta vacia (_), o tiene una ficha propia (M) o tiene una ficha del jugador humano (J)
;;;;;;; (Sondeando ?n ?i ?c M|J)  ; representa que estamos analizando suponiendo que la ?n jugada h sido ?i ?c M|J
;;;

;;;;;;;;;;;;; Hechos para representar una jugadas

;;;;;;; (Juega M|J ?columna) representa que la jugada consiste en introducir la ficha en la columna ?columna 


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; INICIALIZAR ESTADO


(deffacts Estado_inicial
(Tablero Juego 1 1 _) (Tablero Juego 1 2 _) (Tablero Juego 1 3 _) (Tablero Juego  1 4 _) (Tablero Juego  1 5 _) (Tablero Juego  1 6 _) (Tablero Juego  1 7 _)
(Tablero Juego 2 1 _) (Tablero Juego 2 2 _) (Tablero Juego 2 3 _) (Tablero Juego 2 4 _) (Tablero Juego 2 5 _) (Tablero Juego 2 6 _) (Tablero Juego 2 7 _)
(Tablero Juego 3 1 _) (Tablero Juego 3 2 _) (Tablero Juego 3 3 _) (Tablero Juego 3 4 _) (Tablero Juego 3 5 _) (Tablero Juego 3 6 _) (Tablero Juego 3 7 _)
(Tablero Juego 4 1 _) (Tablero Juego 4 2 _) (Tablero Juego 4 3 _) (Tablero Juego 4 4 _) (Tablero Juego 4 5 _) (Tablero Juego 4 6 _) (Tablero Juego 4 7 _)
(Tablero Juego 5 1 _) (Tablero Juego 5 2 _) (Tablero Juego 5 3 _) (Tablero Juego 5 4 _) (Tablero Juego 5 5 _) (Tablero Juego 5 6 _) (Tablero Juego 5 7 _)
(Tablero Juego 6 1 _) (Tablero Juego 6 2 _) (Tablero Juego 6 3 _) (Tablero Juego 6 4 _) (Tablero Juego 6 5 _) (Tablero Juego 6 6 _) (Tablero Juego 6 7 _)
(Jugada 0)
)

(defrule Elige_quien_comienza
=>
(printout t "Quien quieres que empieze: (escribre M para la maquina o J para empezar tu) ")
(assert (Turno (read)))
)

;;;;;;;;;;;;;;;;;;;;;;; MUESTRA POSICION ;;;;;;;;;;;;;;;;;;;;;;;
(defrule muestra_posicion
(declare (salience 100))
(muestra_posicion)
(Tablero Juego 1 1 ?p11) (Tablero Juego 1 2 ?p12) (Tablero Juego 1 3 ?p13) (Tablero Juego 1 4 ?p14) (Tablero Juego 1 5 ?p15) (Tablero Juego 1 6 ?p16) (Tablero Juego 1 7 ?p17)
(Tablero Juego 2 1 ?p21) (Tablero Juego 2 2 ?p22) (Tablero Juego 2 3 ?p23) (Tablero Juego 2 4 ?p24) (Tablero Juego 2 5 ?p25) (Tablero Juego 2 6 ?p26) (Tablero Juego 2 7 ?p27)
(Tablero Juego 3 1 ?p31) (Tablero Juego 3 2 ?p32) (Tablero Juego 3 3 ?p33) (Tablero Juego 3 4 ?p34) (Tablero Juego 3 5 ?p35) (Tablero Juego 3 6 ?p36) (Tablero Juego 3 7 ?p37)
(Tablero Juego 4 1 ?p41) (Tablero Juego 4 2 ?p42) (Tablero Juego 4 3 ?p43) (Tablero Juego 4 4 ?p44) (Tablero Juego 4 5 ?p45) (Tablero Juego 4 6 ?p46) (Tablero Juego 4 7 ?p47)
(Tablero Juego 5 1 ?p51) (Tablero Juego 5 2 ?p52) (Tablero Juego 5 3 ?p53) (Tablero Juego 5 4 ?p54) (Tablero Juego 5 5 ?p55) (Tablero Juego 5 6 ?p56) (Tablero Juego 5 7 ?p57)
(Tablero Juego 6 1 ?p61) (Tablero Juego 6 2 ?p62) (Tablero Juego 6 3 ?p63) (Tablero Juego 6 4 ?p64) (Tablero Juego 6 5 ?p65) (Tablero Juego 6 6 ?p66) (Tablero Juego 6 7 ?p67)
=>
(printout t crlf)
(printout t ?p11 " " ?p12 " " ?p13 " " ?p14 " " ?p15 " " ?p16 " " ?p17 crlf)
(printout t ?p21 " " ?p22 " " ?p23 " " ?p24 " " ?p25 " " ?p26 " " ?p27 crlf)
(printout t ?p31 " " ?p32 " " ?p33 " " ?p34 " " ?p35 " " ?p36 " " ?p37 crlf)
(printout t ?p41 " " ?p42 " " ?p43 " " ?p44 " " ?p45 " " ?p46 " " ?p47 crlf)
(printout t ?p51 " " ?p52 " " ?p53 " " ?p54 " " ?p55 " " ?p56 " " ?p57 crlf)
(printout t ?p61 " " ?p62 " " ?p63 " " ?p64 " " ?p65 " " ?p66 " " ?p67 crlf)
(printout t  crlf)
)


;;;;;;;;;;;;;;;;;;;;;;; RECOGER JUGADA DEL CONTRARIO ;;;;;;;;;;;;;;;;;;;;;;;
(defrule mostrar_posicion
(declare (salience 9999))
(Turno J)
=>
(assert (muestra_posicion))
)

(defrule jugada_contrario
?f <- (Turno J)
=>
(printout t "en que columna introduces la siguiente ficha? ")
(assert (Juega J (read)))
(retract ?f)
)

(defrule juega_contrario_check_entrada_correcta
(declare (salience 1))
?f <- (Juega J ?c)
(test (and (neq ?c 1) (and (neq ?c 2) (and (neq ?c 3) (and (neq ?c 4) (and (neq ?c 5) (and (neq ?c 6) (neq ?c 7))))))))
=>
(printout t "Tienes que indicar un numero de columna: 1,2,3,4,5,6 o 7" crlf)
(retract ?f)
(assert (Turno J))
)

(defrule juega_contrario_check_columna_libre
(declare (salience 1))
?f <- (Juega J ?c)
(Tablero Juego 1 ?c ?X) 
(test (neq ?X _))
=>
(printout t "Esa columna ya esta completa, tienes que jugar en otra" crlf)
(retract ?f)
(assert (Turno J))
)

(defrule juega_contrario_actualiza_estado
?f <- (Juega J ?c)
?g <- (Tablero Juego ?i ?c _)
(Tablero Juego ?j ?c ?X) 
(test (= (+ ?i 1) ?j))
(test (neq ?X _))
=>
(retract ?f ?g)
(assert (Turno M) (Tablero Juego ?i ?c J))
)

(defrule juega_contrario_actualiza_estado_columna_vacia
?f <- (Juega J ?c)
?g <- (Tablero Juego 6 ?c _)
=>
(retract ?f ?g)
(assert (Turno M) (Tablero Juego 6 ?c J))
)


;;;;;;;;;;; ACTUALIZAR  ESTADO TRAS JUGADA DE CLISP ;;;;;;;;;;;;;;;;;;

(defrule juega_clisp_actualiza_estado
?f <- (Juega M ?c)
?g <- (Tablero Juego ?i ?c _)
(Tablero Juego ?j ?c ?X) 
(test (= (+ ?i 1) ?j))
(test (neq ?X _))
=>
(retract ?f ?g)
(assert (Turno J) (Tablero Juego ?i ?c M))
)

(defrule juega_clisp_actualiza_estado_columna_vacia
?f <- (Juega M ?c)
?g <- (Tablero Juego 6 ?c _)
=>
(retract ?f ?g)
(assert (Turno J) (Tablero Juego 6 ?c M))
)

;;;;;;;;;;; CLISP JUEGA SIN CRITERIO ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defrule elegir_jugada_aleatoria
(declare (salience -9998))
?f <- (Turno M)
=>
(assert (Jugar (random 1 7)))
(retract ?f)
)

(defrule comprobar_posible_jugada_aleatoria
?f <- (Jugar ?c)
(Tablero Juego 1 ?c M|J)
=>
(retract ?f)
(assert (Turno M))
)

(defrule clisp_juega_sin_criterio
(declare (salience -9999))
?f<- (Jugar ?c)
=>
(printout t "JUEGO en la columna (sin criterio) " ?c crlf)
(retract ?f)
(assert (Juega M ?c))
)


;;;;;;;;;;;;;;;;;;;;;;;;;;;  Comprobar si hay 4 en linea ;;;;;;;;;;;;;;;;;;;;;

(defrule cuatro_en_linea_horizontal
(declare (salience 9999))
(Tablero ?t ?i ?c1 ?jugador)
(Tablero ?t ?i ?c2 ?jugador) 
(test (= (+ ?c1 1) ?c2))
(Tablero ?t ?i ?c3 ?jugador)
(test (= (+ ?c1 2) ?c3))
(Tablero ?t ?i ?c4 ?jugador)
(test (= (+ ?c1 3) ?c4))
(test (or (eq ?jugador M) (eq ?jugador J) ))
=>
(assert (Cuatro_en_linea ?t ?jugador horizontal ?i ?c1))
)

(defrule cuatro_en_linea_vertical
(declare (salience 9999))
?f <- (Turno ?X)
(Tablero ?t ?i1 ?c ?jugador)
(Tablero ?t ?i2 ?c ?jugador)
(test (= (+ ?i1 1) ?i2))
(Tablero ?t ?i3 ?c  ?jugador)
(test (= (+ ?i1 2) ?i3))
(Tablero ?t ?i4 ?c  ?jugador)
(test (= (+ ?i1 3) ?i4))
(test (or (eq ?jugador M) (eq ?jugador J) ))
=>
(assert (Cuatro_en_linea ?t ?jugador vertical ?i1 ?c))
)

(defrule cuatro_en_linea_diagonal_directa
(declare (salience 9999))
?f <- (Turno ?X)
(Tablero ?t ?i ?c ?jugador)
(Tablero ?t ?i1 ?c1 ?jugador)
(test (= (+ ?i 1) ?i1))
(test (= (+ ?c 1) ?c1))
(Tablero ?t ?i2 ?c2  ?jugador)
(test (= (+ ?i 2) ?i2))
(test (= (+ ?c 2) ?c2))
(Tablero ?t ?i3 ?c3  ?jugador)
(test (= (+ ?i 3) ?i3))
(test (= (+ ?c 3) ?c3))
(test (or (eq ?jugador M) (eq ?jugador J) ))
=>
(assert (Cuatro_en_linea ?t ?jugador diagonal_directa ?i ?c))
)

(defrule cuatro_en_linea_diagonal_inversa
(declare (salience 9999))
?f <- (Turno ?X)
(Tablero ?t ?i ?c ?jugador)
(Tablero ?t ?i1 ?c1 ?jugador)
(test (= (+ ?i 1) ?i1))
(test (= (- ?c 1) ?c1))
(Tablero ?t ?i2 ?c2  ?jugador)
(test (= (+ ?i 2) ?i2))
(test (= (- ?c 2) ?c2))
(Tablero ?t ?i3 ?c3  ?jugador)
(test (= (+ ?i 3) ?i3))
(test (= (- ?c 3) ?c3))
(test (or (eq ?jugador M) (eq ?jugador J) ))
=>
(assert (Cuatro_en_linea ?t ?jugador diagonal_inversa ?i ?c))
)

;;;;;;;;;;;;;;;;;;;; DESCUBRE GANADOR
(defrule gana_fila
(declare (salience 9999))
?f <- (Turno ?X)
(Cuatro_en_linea Juego ?jugador horizontal ?i ?c)
=>
(printout t ?jugador " ha ganado pues tiene cuatro en linea en la fila " ?i crlf)
(retract ?f)
(assert (muestra_posicion))
) 

(defrule gana_columna
(declare (salience 9999))
?f <- (Turno ?X)
(Cuatro_en_linea Juego ?jugador vertical ?i ?c)
=>
(printout t ?jugador " ha ganado pues tiene cuatro en linea en la columna " ?c crlf)
(retract ?f)
(assert (muestra_posicion))
) 

(defrule gana_diagonal_directa
(declare (salience 9999))
?f <- (Turno ?X)
(Cuatro_en_linea Juego ?jugador diagonal_directa ?i ?c)
=>
(printout t ?jugador " ha ganado pues tiene cuatro en linea en la diagonal que empieza la posicion " ?i " " ?c   crlf)
(retract ?f)
(assert (muestra_posicion))
) 

(defrule gana_diagonal_inversa
(declare (salience 9999))
?f <- (Turno ?X)
(Cuatro_en_linea Juego ?jugador diagonal_inversa ?i ?c)
=>
(printout t ?jugador " ha ganado pues tiene cuatro en linea en la diagonal hacia arriba que empieza la posicin " ?i " " ?c   crlf)
(retract ?f)
(assert (muestra_posicion))
) 


;;;;;;;;;;;;;;;;;;;;;;;  DETECTAR EMPATE

(defrule empate
(declare (salience -9999))
(Turno ?X)
(Tablero Juego 1 1 M|J)
(Tablero Juego 1 2 M|J)
(Tablero Juego 1 3 M|J)
(Tablero Juego 1 4 M|J)
(Tablero Juego 1 5 M|J)
(Tablero Juego 1 6 M|J)
(Tablero Juego 1 7 M|J)
=>
(printout t "EMPATE! Se ha llegado al final del juego sin que nadie gane" crlf)
)

;;;;;;;;;;;;;;;;;;;;;; CONOCIMIENTO EXPERTO ;;;;;;;;;;
;;;;; ¡¡¡¡¡¡¡¡¡¡ Añadir conocimiento para que juege como vosotros jugariais !!!!!!!!!!!!
;;Reglas para representar conocimiento
;Comprobar las posiciones siguientes y anteriores en todas las direcciones
(defrule Posicion_Siguiente_h
    (Tablero Juego ?f ?c ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (<= (+ 1 ?c) 7))
        =>
    (assert (siguiente h ?f (+ 1 ?c) ?player))
)
(defrule Posicion_Siguiente_v
    (Tablero Juego ?f ?c ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (<= (+ ?f 1) 6))
        =>
    (assert (siguiente v (+ ?f 1) ?c ?player))
)
(defrule Posicion_Siguiente_d1
    (Tablero Juego ?f ?c ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (and (<= (+ ?f 1) 6) (<= (+ 1 ?c) 7)))
        =>
    (assert (siguiente d1 (+ ?f 1) (+ 1 ?c) ?player))
)
(defrule Posicion_Siguiente_d2
    (Tablero Juego ?f ?c ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (and (>= (- ?f 1) 1) (<= (+ 1 ?c) 7)))
        =>
    (assert (siguiente d1 (- ?f 1) (+ 1 ?c) ?player))
)
(defrule Posicion_Anterior_v
    (Tablero Juego ?f ?c ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (>= (- ?f 1) 1))
        =>
    (assert (anterior v (- ?f 1) ?c ?player))
)
(defrule Posicion_Anterior_h
    (Tablero Juego ?f ?c ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (>= (- ?c 1) 1))
        =>
    (assert (anterior h ?f (- ?c 1) ?player))
)
(defrule Posicion_Anterior_d1
    (Tablero Juego ?f ?c ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (>= (- ?c 1) 1))
    (test (>= (- ?f 1) 1))
        =>
    (assert (anterior d1 (- ?f 1) (- ?c 1) ?player))
)
(defrule Posicion_Anterior_d2
    (Tablero Juego ?f ?c ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (<= (+ ?f 1) 6))
    (test (>= (- ?c 1) 1))
        =>
    (assert (anterior d1 (+ ?f 1) (- ?c 1) ?player))
)
;comprobar donde caeria la pieza
(defrule Caeria_sobra
    (declare (salience 100))
    (Turno M)
    (Tablero Juego 6 ?c _)
        =>
    (assert (caeria 6 ?c))
)
(defrule Caeria
    (declare (salience 100))
    (Turno M)
    (Tablero Juego ?f ?c _)
    (Tablero Juego ?f1 ?c M|J)
    (test (= (+ ?f 1) ?f1))
        =>
    (assert (caeria ?f ?c))
)
;Comprobar donde hay parejas de piezas contiguas
(defrule Conectado_h
    (declare (salience 100))
    (Turno M)
    (Tablero Juego ?f ?c1 ?player)
    (Tablero Juego ?f ?c2 ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (= (+ ?c1 1) ?c2))
        =>
    (assert (conectado h ?player ?f ?c1 ?f ?c2))
)
(defrule Conectado_v
    (declare (salience 100))
    (Turno M)
    (Tablero Juego ?f1 ?c ?player)
    (Tablero Juego ?f2 ?c ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (= (+ ?f1 1) ?f2))
        =>
    (assert (conectado v ?player ?f1 ?c ?f2 ?c))
)
(defrule Conectado_d1
    (declare (salience 100))
    (Turno M)
    (Tablero Juego ?f1 ?c1 ?player)
    (Tablero Juego ?f2 ?c2 ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (= (+ ?f1 1) ?f2))
    (test (= (+ ?c1 1) ?c2))
        =>
    (assert (conectado d1 ?player ?f1 ?c1 ?f2 ?c2))
)
(defrule Conectado_d2
    (declare (salience 100))
    (Turno M)
    (Tablero Juego ?f1 ?c1 ?player)
    (Tablero Juego ?f2 ?c2 ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (= (- ?f1 1) ?f2))
    (test (= (+ ?c1 1) ?c2))
        =>
    (assert (conectado d2 ?player ?f1 ?c1 ?f2 ?c2))
)
;Comprobar donde hay 3 piezas contiguas
(defrule 3_en_linea_v
    (declare (salience 100))
    (Turno M)
    (Tablero Juego ?f1 ?c ?player)
    (Tablero Juego ?f2 ?c ?player)
    (Tablero Juego ?f3 ?c ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (= (+ ?f1 1) ?f2))
    (test (= (+ ?f1 2) ?f3))
        =>
    (assert (3_en_linea v ?player ?f1 ?c ?f3 ?c))
)
(defrule 3_en_linea_h
    (declare (salience 100))
    (Turno M)
    (Tablero Juego ?f ?c1 ?player)
    (Tablero Juego ?f ?c2 ?player)
    (Tablero Juego ?f ?c3 ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (= (+ ?c1 1) ?c2))
    (test (= (+ ?c1 2) ?c3))
        =>
    (assert (3_en_linea h ?player ?f ?c1 ?f ?c3))
)
(defrule 3_en_linea_d1
    (declare (salience 100))
    (Turno M)
    (Tablero Juego ?f1 ?c1 ?player)
    (Tablero Juego ?f2 ?c2 ?player)
    (Tablero Juego ?f3 ?c3 ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (= (+ ?c1 1) ?c2))
    (test (= (+ ?c1 2) ?c3))
    (test (= (+ ?f1 1) ?f2))
    (test (= (+ ?f1 2) ?f3))
        =>
    (assert (3_en_linea d1 ?player ?f1 ?c1 ?f3 ?c3))
)
(defrule 3_en_linea_d2
    (declare (salience 100))
    (Turno M)
    (Tablero Juego ?f1 ?c1 ?player)
    (Tablero Juego ?f2 ?c2 ?player)
    (Tablero Juego ?f3 ?c3 ?player)
    (test (or (eq ?player M) (eq ?player J)))
    (test (= (+ ?c1 1) ?c2))
    (test (= (+ ?c1 2) ?c3))
    (test (= (- ?f1 1) ?f2))
    (test (= (- ?f1 2) ?f3))
        =>
    (assert (3_en_linea d2 ?player ?f1 ?c1 ?f3 ?c3))
)
;Comprobar si uno de los jugadores puede ganar en el siguiente turno TAL Y COMO ESTA EL ESTADO DEL JUEGO AL INICIO DEL TURNO
;no se verifica si alguien puede ganar tras el movimiento decidido
(defrule ganaria_v
    (declare (salience 100))
    (Turno M)
    (3_en_linea v ?player ?f1 ?c ?f3 ?c)
    (Tablero Juego ?f4 ?c _)
    (test (= (- ?f1 1) ?f4))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c))
)
(defrule ganaria_h_derecha
    (declare (salience 100))
    (Turno M)
    (3_en_linea h ?player ?f ?c1 ?f ?c3)
    (caeria ?f ?c4)
    (test (= (+ ?c3 1) ?c4))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c4))
)
(defrule ganaria_h_izquierda
    (declare (salience 100))
    (Turno M)
    (3_en_linea h ?player ?f ?c1 ?f ?c3)
    (caeria ?f ?c4)
    (test (= (- ?c1 1) ?c4))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c4))
)
(defrule ganaria_h_derecha_espacio
    (declare (salience 100))
    (Turno M)
    (conectado h ?player ?f ?c1 ?f ?c2)
    (caeria ?f ?c3)
    (Tablero Juego ?f ?c4 ?player)
    (test (= (+ ?c1 2) ?c3))
    (test (= (+ ?c1 3) ?c4))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c3))
)
(defrule ganaria_h_izquierda_espacio
    (declare (salience 100))
    (Turno M)
    (conectado h ?player ?f ?c3 ?f ?c4)
    (caeria ?f ?c2)
    (Tablero Juego ?f ?c1 ?player)
    (test (= (+ ?c1 1) ?c2))
    (test (= (+ ?c1 3) ?c4))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c2))
)
(defrule ganaria_d1_normal
    (declare (salience 100))
    (Turno M)
    (3_en_linea d1 ?player ?f1 ?c1 ?f3 ?c3)
    (caeria ?f4 ?c4)
    (test (= (+ ?c3 1) ?c4))
    (test (= (+ ?f3 1) ?f4))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c4))
)
(defrule ganaria_d1_reves
    (declare (salience 100))
    (Turno M)
    (3_en_linea d1 ?player ?f1 ?c1 ?f3 ?c3)
    (caeria ?f4 ?c4)
    (test (= (- ?c1 1) ?c4))
    (test (= (- ?f1 1) ?f4))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c4))
)
(defrule ganaria_d1_salto_2
    (declare (salience 100))
    (Turno M)
    (conectado d1 ?player ?f3 ?c3 ?f4 ?c4)
    (caeria ?f2 ?c2)
    (Tablero Juego ?f1 ?c1 ?player)
    (test (= (- ?c3 1) ?c2))
    (test (= (- ?c3 2) ?c1))
    (test (= (- ?f3 1) ?f2))
    (test (= (- ?f3 2) ?f1))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c2))
)
(defrule ganaria_d1_salto_3
    (declare (salience 100))
    (Turno M)
    (conectado d1 ?player ?f1 ?c1 ?f2 ?c2)
    (caeria ?f3 ?c3)
    (Tablero Juego ?f4 ?c4 ?player)
    (test (= (+ ?c2 1) ?c3))
    (test (= (+ ?c2 2) ?c4))
    (test (= (+ ?f2 1) ?f3))
    (test (= (+ ?f2 2) ?f4))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c3))
)
(defrule ganaria_d2_normal
    (declare (salience 100))
    (Turno M)
    (3_en_linea d2 ?player ?f1 ?c1 ?f3 ?c3)
    (caeria ?f4 ?c4)
    (test (= (+ ?c3 1) ?c4))
    (test (= (- ?f3 1) ?f4))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c4))
)
(defrule ganaria_d2_reves
    (declare (salience 100))
    (Turno M)
    (3_en_linea d2 ?player ?f1 ?c1 ?f3 ?c3)
    (caeria ?f4 ?c4)
    (test (= (- ?c1 1) ?c4))
    (test (= (+ ?f1 1) ?f4))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c4))
)
(defrule ganaria_d2_salto_2
    (declare (salience 100))
    (Turno M)
    (conectado d2 ?player ?f3 ?c3 ?f4 ?c4)
    (caeria ?f2 ?c2)
    (Tablero Juego ?f1 ?c1 ?player)
    (test (= (+ ?c1 1) ?c2))
    (test (= (+ ?c1 2) ?c3))
    (test (= (- ?f1 1) ?f2))
    (test (= (- ?f1 2) ?f3))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c2))
)
(defrule ganaria_d2_salto_3
    (declare (salience 100))
    (Turno M)
    (conectado d2 ?player ?f1 ?c1 ?f2 ?c2)
    (caeria ?f3 ?c3)
    (Tablero Juego ?f4 ?c4 ?player)
    (test (= (+ ?c2 1) ?c3))
    (test (= (+ ?c2 2) ?c4))
    (test (= (- ?f2 1) ?f3))
    (test (= (- ?f2 2) ?f4))
    (test (or (eq ?player M) (eq ?player J)))
        =>
    (assert (ganaria ?player ?c2))
)
;;;;;;;;;;;;;Reglas para aplicar el conocimiento
;;;NOTA: estas reglas podrian pulirse mucho comprobando por ejemplo si un 3 en raya es relevante o no, porque ya este tapado
;;;o por que sea imposible hacer 4enraya sin salirse de los limites del tablero, pero como entiendo que no es la finalidad de la
;;;practica se han quedado en su version mas simple
;Si hay una jugada ganadora aplicarla sin dudar
(defrule ganar
    (declare (salience 20))
    ?turno <- (Turno M)
    (ganaria M ?c)
        =>
    (assert (Juega M ?c))
    (printout t "Esta jugada me hace ganar (s20)" crlf)
    (retract ?turno)
)
;Si no puedo ganar directamente pero mi oponente si, evitarlo
(defrule no_perder
    (declare (salience 19))
    ?turno <- (Turno M)
    (ganaria J ?c)
        =>
    (assert (Juega M ?c))
    (printout t "Tengo que hacer esta jugada para no perder (s19)" crlf)
    (retract ?turno)
)
;Evitar el truco basico de provocar una victoria asegurada colocando 3 piezas contiguas en una fila con huecos a ambos lados -xxx-
;poner en el centro cuando el oponente tiene una situacion asi x-x para evitarlo (xox)
(defrule evitar_cm_h
    (declare (salience 18))
    ?turno <- (Turno M)
    (Tablero Juego ?f ?c1 ?player)
    (Tablero Juego ?f ?c3 ?player)
    (caeria ?f ?c2)
    (test (or (eq ?player M) (eq ?player J)))
    (test (= (+ ?c1 1) ?c2))
    (test (= (+ ?c2 1) ?c3))
        =>
    (assert (Juega M ?c2))
    (printout t "Esta jugada evita un tipo de mate habitual (s18)" crlf)
    (retract ?turno)
)
;Si no hay nada mas urgente que hacer, evitar que nos pongan en amenaza de checkmate en 2 turnos
(defrule evitacm2_h_derecha
    (declare (salience 15))
    ?turno <- (Turno M)
    (conectado h J ?f ?c1 ?f ?c2)
    (caeria ?f ?c3)
    (test (= (+ ?c2 1) ?c3))
        =>
    (assert (Juega M ?c3))
    (printout t "Esta jugada evita agresion enemiga (s15)" crlf)
    (retract ?turno)
)
(defrule evitacm2_h_izquierda
    (declare (salience 15))
    ?turno <- (Turno M)
    (conectado h J ?f ?c1 ?f ?c2)
    (caeria ?f ?c3)
    (test (= (- ?c1 1) ?c3))
        =>
    (assert (Juega M ?c3))
    (printout t "Esta jugada evita agresion enemiga (s15)" crlf)
    (retract ?turno)
)
(defrule evitacm2_d1_izquierda
    (declare (salience 14))
    ?turno <- (Turno M)
    (conectado d1 J ?f1 ?c1 ?f2 ?c2)
    (caeria ?f3 ?c3)
    (test (= (- ?c1 1) ?c3))
    (test (= (- ?f1 1) ?f3))
        =>
    (assert (Juega M ?c3))
    (printout t "Esta jugada evita agresion enemiga (s14)" crlf)
    (retract ?turno)
)
(defrule evitacm2_d1_derecha
    (declare (salience 14))
    ?turno <- (Turno M)
    (conectado d1 J ?f1 ?c1 ?f2 ?c2)
    (caeria ?f3 ?c3)
    (test (= (+ ?c2 1) ?c3))
    (test (= (+ ?f2 1) ?f3))
        =>
    (assert (Juega M ?c3))
    (printout t "Esta jugada evita agresion enemiga (s14)" crlf)
    (retract ?turno)
)
(defrule evitacm2_d2_izquierda
    (declare (salience 14))
    ?turno <- (Turno M)
    (conectado d2 J ?f1 ?c1 ?f2 ?c2)
    (caeria ?f3 ?c3)
    (test (= (- ?c1 1) ?c3))
    (test (= (+ ?f1 1) ?f3))
        =>
    (assert (Juega M ?c3))
    (printout t "Esta jugada evita agresion enemiga (s14)" crlf)
    (retract ?turno)
)
(defrule evitacm2_d2_derecha
    (declare (salience 14))
    ?turno <- (Turno M)
    (conectado d2 J ?f1 ?c1 ?f2 ?c2)
    (caeria ?f3 ?c3)
    (test (= (+ ?c2 1) ?c3))
    (test (= (- ?f2 1) ?f3))
        =>
    (assert (Juega M ?c3))
    (printout t "Esta jugada evita agresion enemiga (s14)" crlf)
    (retract ?turno)
)

(defrule cercanas_h_d
    (declare (salience 2))
    ?turno <- (Turno M)
    (siguiente h ?f ?c M)
    (caeria ?f ?c)
    =>
    (assert (Juega M ?c))
    (printout t "Esta jugada es a falta de algo mejor (s2)" crlf)
    (retract ?turno)
)
(defrule cercanas_h_i
    (declare (salience 2))
    ?turno <- (Turno M)
    (anterior h ?f ?c M)
    (caeria ?f ?c)
    =>
    (assert (Juega M ?c))
    (printout t "Esta jugada es a falta de algo mejor (s2)" crlf)
    (retract ?turno)
)
(defrule cercanas_v
    (declare (salience 1))
    ?turno <- (Turno M)
    (anterior v ?f ?c M)
    (caeria ?f ?c)
    =>
    (assert (Juega M ?c))
    (printout t "Esta jugada es a falta de algo mejor (s1)" crlf)
    (retract ?turno)
)
(defrule amenazar_cm_h_d
    (declare (salience 13))
    ?turno <- (Turno M)
    (conectado h M ?f ?c1 ?f ?c2)
    (caeria ?f ?c)
    (test (= (+ ?c2 1) ?c))
    =>
    (assert (Juega M ?c))
    (printout t "Esta es una decente jugada agresiva (s13)" crlf)
    (retract ?turno)
)
(defrule amenazar_cm_h_i
    (declare (salience 13))
    ?turno <- (Turno M)
    (conectado h M ?f ?c1 ?f ?c2)
    (caeria ?f ?c)
    (test (= (+ ?c 1) ?c1))
    =>
    (assert (Juega M ?c))
    (printout t "Esta es una decente jugada agresiva (s6)" crlf)
    (retract ?turno)
)
(defrule amenazar_cm_v
    (declare (salience 13))
    ?turno <- (Turno M)
    (conectado v M ?f1 ?c ?f2 ?c)
    (caeria ?f ?c)
    (test (= (- ?f1 1) ?f))
    =>
    (assert (Juega M ?c))
    (printout t "Esta es una decente jugada agresiva (s13)" crlf)
    (retract ?turno)
)
(defrule amenazar_cm_d1_derecha
    (declare (salience 12))
    ?turno <- (Turno M)
    (conectado d1 M ?f1 ?c1 ?f2 ?c2)
    (caeria ?f ?c)
    (test (= (+ ?f2 1) ?f))
    (test (= (+ ?c1 1) ?c))
    =>
    (assert (Juega M ?c))
    (printout t "Creo que puedo ganar pronto (s12)" crlf)
    (retract ?turno)
)
(defrule amenazar_cm_d1_izquierda
    (declare (salience 12))
    ?turno <- (Turno M)
    (conectado d1 M ?f1 ?c1 ?f2 ?c2)
    (caeria ?f ?c)
    (test (= (- ?f1 1) ?f))
    (test (= (- ?c1 1) ?c))
    =>
    (assert (Juega M ?c))
    (printout t "Creo que puedo ganar pronto (s12)" crlf)
    (retract ?turno)
)
(defrule amenazar_cm_d2_derecha
    (declare (salience 12))
    ?turno <- (Turno M)
    (conectado d2 M ?f1 ?c1 ?f2 ?c2)
    (caeria ?f ?c)
    (test (= (- ?f2 1) ?f))
    (test (= (+ ?c2 1) ?c))
    =>
    (assert (Juega M ?c))
    (printout t "Creo que puedo ganar pronto (s12)" crlf)
    (retract ?turno)
)
(defrule amenazar_cm_d2_izquierda
    (declare (salience 12))
    ?turno <- (Turno M)
    (conectado d2 M ?f1 ?c1 ?f2 ?c2)
    (caeria ?f ?c)
    (test (= (+ ?f1 1) ?f))
    (test (= (- ?c1 1) ?c))
    =>
    (assert (Juega M ?c))
    (printout t "Creo que puedo ganar pronto (s12)" crlf)
    (retract ?turno)
)
(defrule inicio
    (declare (salience 1))
    ?turno <- (Turno M)
    =>
    (assert (Juega M 4))
    (printout t "Normalmente es mejor jugar por el centro (s1)" crlf)
    (retract ?turno)
)
(defrule retractar_caeria
    (declare (salience 1))
    (Juega M ?)
    ?rule <- (caeria ?f ?c)
        =>
    (retract ?rule)
)
(defrule retractar_ganaria
    (declare (salience 1))
    (Juega M ?)
    ?rule <- (ganaria ?player ?c)
        =>
    (retract ?rule)
)