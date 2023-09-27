; Miguel Lentisco Ballesteros
; Ejercicio 8: Escribir en datos.txt los valores de un vector

(deffacts Hechos
  (WRITE cosa 3 numero como estas prueba 3.2 "toca")
  (Escribir)
)

; Abrimos archivo
(defrule AbrirArchivo
  ?g <- (Escribir)
    =>
  (open "datos.txt" file "w")
  (retract ?g)
  (printout t "Archivo datos.txt abierto." crlf)
  (assert (ArchivoAbierto))
)

; Escribimos mientra s hayan cosas en el vector
(defrule Escribir
  (ArchivoAbierto)
  ?g <- (WRITE ?var $?resto)
    =>
  (printout file ?var " ")
  (retract ?g)
  (assert (WRITE $?resto))
)

; Cerramos archivo cuando terminemos de escribir
(defrule CerrarArchivo
  ?f <- (ArchivoAbierto)
  ?g <- (WRITE)
    =>
  (close file)
  (printout t "Archivo datos.txt cerrado." crlf)
  (retract ?f ?g)
)
