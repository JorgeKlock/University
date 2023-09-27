; Ejercicio Ranzomaiento por defecto
; Miguel Lentisco Ballesteros

; -------------------
; Representación
; -------------------

; (ave ?x) representa "?x es un ave"
; (animal ?x) representa "?x es un animal"
; (vuela x si|no seguro|por_defecto) representa "?x vuela si|no con esa certeza"

; -------------------
; Hechos
; -------------------

(deffacts datos
  (ave gorrion) (ave paloma) (ave aguila) (ave pinguino)
  (mamifero vaca) (mamifero perro) (mamifero caballo)
  (vuela pinguino no seguro)
)

; -------------------
; Reglas seguras
; -------------------

; Las aves son animales
(defrule aves_son_animales
  (ave ?x)
    =>
  (assert (animal ?x))
  (bind ?expl (str-cat "Sabemos que un " ?x " es un animal porque las aves son un tipo de animal."))
  (assert (explicacion animal ?x ?expl))
)

; Los mamiferos son animales
(defrule mamiferos_son_animales
  (mamifero ?x)
    =>
  (assert (animal ?x))
  (bind ?expl (str-cat "Sabemos que un " ?x " es un animal porque los mamiferos son un tipo de animal."))
  (assert (explicacion animal ?x ?expl))
)

; -------------------
; Reglas por defecto
; -------------------

; Casi todas las aves vuelan (asumimos por defecto)
(defrule ave_vuela_por_defecto
  (declare (salience -1))
  (ave ?x)
    =>
  (assert (vuela ?x si por_defecto))
  (bind ?expl (str-cat "Asumo que un " ?x " vuela, porque casi todas las aves vuelan."))
  (assert (explicacion vuela ?x ?expl))
)

; Retractamos cuando hay algo en contra
(defrule retracta_vuela_por_defecto
  (declare (salience 1))
  ?f <- (vuela ?x ?r por_defecto)
  (vuela ?x ?s seguro)
    =>
  (retract ?f)
  (bind ?expl (str-cat "Retractamos que un " ?x " " ?r " vuela por defecto, porque sabemos que " ?x " " ?s " vuela."))
  (assert (explicacion retracta_vuela ?x ?expl))
)

; La mayor parte de los animales no vuela (asumis por defecto que no vuelan)
(defrule mayor_parte_animales_no_vuelan
  (declare (salience -2))
  (animal ?x)
  (not (vuela ?x ? ?))
    =>
  (assert (vuela ?x no por_defecto))
  (bind ?expl (str-cat "Asumo que " ?x " no vuela, porque la mayor parte de los animales no vuelan."))
  (assert (explicacion vuela ?x ?expl))
)


; -------------------
; Reglas pregunta
; -------------------

; Pregunta
(deffacts preguntar
  (preguntar)
)

; Preguntamos el nombre de un animal
(defrule pregunta_animal
  ; Preguntar va lo último
  (declare (salience -3))
  ?f <- (preguntar)
    =>
  (retract ?f)
  (printout t "Dime el nombre de un animal: ")
  (assert (pregunta_animal (lowcase (read))))
)

; Si el animal está en la BBDD con explicación retractada
(defrule animal_en_bbdd_retract
  (declare (salience 1))
  ?f <- (pregunta_animal ?x)
  (vuela ?x ?r ?)
  (explicacion retracta_vuela ?x ?expl)
    =>
  (retract ?f)
  (printout t "El animal " ?x " " ?r " vuela." crlf)
  (printout t "Razon: " ?expl crlf)
)

; Si el animal está en la BDDD con explicación por defecto
(defrule animal_en_bbdd
  ?f <- (pregunta_animal ?x)
  (vuela ?x ?r ?)
  (explicacion vuela ?x ?expl)
    =>
  (retract ?f)
  (printout t "El animal " ?x " " ?r " vuela." crlf)
  (printout t "Razon: " ?expl crlf)
)

; Si el animal no está en la BDDD preguntamos si es un ave
(defrule animal_no_en_bbdd_ave
  (declare (salience -3))
  (pregunta_animal ?x)
    =>
  (printout t "El animal " ?x " es un ave?(s/n): ")
  (bind ?r (lowcase (read)))
  (if (= 0 (str-compare ?r "s")) then (assert (ave ?x)))
)

; Si el animal no está en la BDDD preguntamos si es un mamifero
(defrule animal_no_en_bbdd_mamifero
  (declare (salience -3))
  (pregunta_animal ?x)
    =>
  (printout t "El animal " ?x " es un mamifero?(s/n): ")
  (bind ?r (lowcase (read)))
  (if (= 0 (str-compare ?r "s")) then (assert (mamifero ?x)))
)

; Si no es mamífero ni ave
(defrule animal_no_en_bbdd_animal
  (declare (salience -4))
  (pregunta_animal ?x)
    =>
  (assert (animal ?x))
)
