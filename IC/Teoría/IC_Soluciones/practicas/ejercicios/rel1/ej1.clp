; Miguel Lentisco Ballesteros
; Ejercicio 1: Mostrar opciones y recoger la opción, pidiendolo de nuevo si hay errores

; Opciones que tenemos
(deffacts Hechos
  (Preguntar)
  (Opcion 1)
  (Opcion 2)
  (Opcion 3)
  (Opcion 4)
)

; Preguntamos las opciones y recogemos la respuesta
(defrule PreguntarOpcion
  ?f <- (Preguntar)
    =>
  (retract ?f)
  (printout t "Elige una de las siguientes opciones: " crlf)
  (printout t " 1) - Opcion uno" crlf)
  (printout t " 2) - Opcion dos" crlf)
  (printout t " 3) - Opcion tres" crlf)
  (printout t " 4) - Opcion cuatro" crlf)
  (printout t "Opcion: ")
  (assert (OpcionElegida (read)))
)

; Si no es una opción de las que tenemos pedimos de nuevo la opcion
(defrule ComprobarOpcion
  (declare (salience 1))
  ?f <- (OpcionElegida ?x)
  (not (Opcion ?x))
    =>
  (retract ?f)
  (assert (Preguntar))
  (printout t "Error: opcion " ?x " no reconocida." crlf crlf)
)

; Si la opción es correcta
(defrule OpcionCorrecta
  (OpcionElegida ?x)
    =>
  (printout t "Has elegido la opcion " ?x "." crlf)
)
