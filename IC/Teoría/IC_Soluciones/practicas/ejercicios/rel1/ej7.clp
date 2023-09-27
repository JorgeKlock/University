; Miguel Lentisco Ballesteros
; Ejercicio 7: Mostrar el nombre y la altura de la persona más alta

; Template de jugadores
(deftemplate Jugadores
  (field Nombre)
  (field Altura)
)

; Jugadores con distintas alturas
(deffacts Hechos
  (Jugadores (Nombre Antonio) (Altura 159))
  (Jugadores (Nombre Maria) (Altura 180))
  (Jugadores (Nombre Laura) (Altura 179))
  (Jugadores (Nombre Antonio) (Altura 168))
  (CalcularJugadorMasAlto)
)

; Imprime por pantalla el nombre y la altura del jugador más alto
(defrule JugadorMasAlto
  ; Calculamos cuando se nos diga
  ?f <- (CalcularJugadorMasAlto)
  ; El más alto será el Jugador para el cual no exista otro más alto que él
  (Jugadores (Nombre ?nom) (Altura ?a1))
  (not (Jugadores (Altura ?a2 & :(> ?a2 ?a1))))
    =>
  (retract ?f)
  (printout t "La persona mas alta es " ?nom " con " ?a1 " cm." crlf)
)
