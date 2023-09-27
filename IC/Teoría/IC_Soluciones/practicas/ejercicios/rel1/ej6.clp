; Miguel Lentisco Ballesteros
; Ejercicio 6: Mostrar la altura de la persona más alta

; Template de Jugadores
(deftemplate Jugadores
  (field Nombre)
  (field Altura)
)

; Añadimos unos cuantos jugadores con distintas alturas
(deffacts Hechos
  (Jugadores (Nombre Antonio) (Altura 159))
  (Jugadores (Nombre Maria) (Altura 180))
  (Jugadores (Nombre Laura) (Altura 179))
  (Jugadores (Nombre Antonio) (Altura 168))
  (CalcularAlturaMaxima)
)

; Imprime por pantalla la altura máxima de los jugadores
(defrule AlturaMaxima
  ; Calculamos la altura maxima cuando se nos indique
  ?f <- (CalcularAlturaMaxima)
  ; El más alto será el Jugador para el cual no exista otro más alto que él
  (Jugadores (Altura ?a1))
  (not (Jugadores (Altura ?a2 & :(> ?a2 ?a1))))
    =>
  (printout t "La altura maxima es " ?a1 " cm." crlf)
  (retract ?f)
)
