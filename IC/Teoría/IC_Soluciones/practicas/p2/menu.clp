; Archivo: menu.clp
; Autor: Miguel Lentisco Ballesteros
; Menú principal del sistema que nos permite escoger el recomendador que queramos

; Inicio del Menu
(deffacts HechosMenuInicial
  (Comando MostrarMenu)
  (MActual MMenu)
  (Opciones a b c)
  (Activar a MHacerPreguntasRR RecomendarRama)
  (Activar b MMenuRA MostrarMenu)
)

; Mostramos el menú inicial
(defrule MostrarMenuPrincipal
  (MActual MMenu)
  ?f <- (Comando MostrarMenu)
    =>
  ; Mostramos menú
  (printout t crlf "Sistema de recomendaciones: " crlf)
  (printout t " [a] Recomendador de rama." crlf)
  (printout t " [b] Recomendador de asignaturas." crlf)
  (printout t " [c] Salir." crlf)
  (printout t "Opcion: " )
  ; Cogemos salida y transformamos a simbolo
  (assert (Opcion (lowcase (sym-cat (readline)))))
  (retract ?f)
)

; Comprueba que la opción sea correcta
(defrule ChequearOpcionPrincipal
  (declare (salience 1))
  (MActual MMenu)
  ?f <- (Opcion ?opt)
  ; Si la opción no está entre las válidas
  (not (Opciones $? ?opt $?))
    =>
  (retract ?f)
  (printout t "Opcion invalida." crlf)
  (assert (Comando MostrarMenu))
)

; Según la opción escogida se ejecuta el modulo correspondiente
(defrule EjecutarOpcionPrincipal
  ?f1 <- (MActual MMenu)
  ; Opción y módulo
  ?f2 <- (Opcion ?opt)
  (Activar ?opt ?modulo ?comando)
    =>
  ; Quitamos el modulo actual y pasamos al siguiente
  (retract ?f1 ?f2)
  (assert (MActual ?modulo))
  (assert (Comando ?comando))
)

; Salir del programa
(defrule SalirPrincipal
  ?f1 <- (MActual MMenu)
  ?f2 <- (Opcion c)
    =>
  (retract ?f1 ?f2)
)
