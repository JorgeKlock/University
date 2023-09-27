
(deftemplate recommendation2
    (field branchID)
)


(defrule pregunta
=>
   (printout t "Voy a aconsejarte para ayudarte a decidir rama de Informatica, te gustan las asignaturas de hardware?(si|no): " crlf)
   (assert (Hardware (upcase (read))))
)

;;;; RESPUESTA EN CASO DE QUE SI
(defrule respuesta
    (Hardware SI)
    =>
    (recommendation2 (branchID IC))
    (printout t "En tal caso deberias escoger directamente la rama de IC, tiene buenas salidas y esta falta de alumnos" crlf)
)
;;;; SEGUIR PREGUNTANDO SI NO
(defrule pregunta2
    (Hardware NO)
    =>
    (printout t "Vale, y te gusta programar?(si|no)" crlf)
    (assert (Programacion (upcase (read))))
)
;;;; RESPUESTA EN CASO DE QUE NO
(defrule respuesta2
    (Programacion NO)
    =>
    (recommendation2 (branchID TI))
    (printout t "Ya veo, entonces deberias probar con la rama de TI, no tiene una carga excesiva ni de programacion ni de hardware, y se ven muchos conceptos variados")
)
;;;; SEGUIR PREGUNTANDO EN CASO CONTRARIO
(defrule pregunta3
    (Programacion SI)
    =>
    (printout t "Pues para la ultima pregunta dime como de trabajador te consideras?(poco|normal|mucho): " crlf)
    (assert (Trabajador (upcase (read))))
)
;;;; RESPUESTAS FINALES
(defrule respuesta3
    (Trabajador POCO)
    =>
    (recommendation2 (branchID IS))
    (printout t "Entonces la rama de IS es la que menor carga de trabajo tiene de entre las ramas de programacion")
)
(defrule respuesta4
    (Trabajador NORMAL)
    =>
    (recommendation2 (branchID SI))
    (printout t "La rama de SI es para ti, se estudian mecanismos programacion a un nivel avanzado sin exceso de dificultad")
)
(defrule respuesta5
    (Trabajador MUCHO)
    =>
    (recommendation2 (branchID CSI))
    (printout t "Deberias probar la rama de CSI, aunque la alta carga matematica puede ser complicada de sobrellevar, deberias estar listo para dedicarle mucho tiempo")
)