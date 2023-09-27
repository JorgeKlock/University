;;;;;;;;;;;;;;;;;;Representación ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; (ave ?x) representa “?x es un ave ”
; (animal ?x) representa “?x es un animal”
; (vuela ?x si|no seguro|por_defecto) representa
;“?x vuela si|no con esa certeza”

(deffacts datos
(ave gorrion) (ave paloma) (ave aguila) (ave pinguino)
(mamifero vaca) (mamifero perro) (mamifero caballo)
(vuela pinguino no seguro) )



;;;;;; OBTENER INFORMACIÓN ;;;;;;

(defrule que_animal_es
    (declare (salience 10))
    =>
    (printout t "En que animal esta interesado?" crlf)
    (assert (animalEntrada (lowcase (read))))
)

(defrule animal_presente
    (declare (salience -5))
    (animal ?x)
    (animalEntrada ?x)
    =>
    (assert (animalEncontrado))
)

(defrule tipo_animal_desconocido
    (declare (salience -6))
    (not (animalEncontrado))
    (animalEntrada ?x)
    =>
    (printout t "Ese animal es un ave o un mamifero? (ave | mamifero | desconocido)" crlf)
    (assert (esun (lowcase (read)) ?x))
)

(defrule almacenar_tipo_ave
    (declare (salience -7))
    (esun ave ?x)
    =>
    (assert (ave ?x))
)
(defrule almacenar_tipo_mamifero
    (declare (salience -7))
    (esun mamifero ?x)
    =>
    (assert (mamifero ?x))
)
(defrule almacenar_tipo_otros
    (declare (salience -8))
    (esun ?t ?x)
    =>
    (assert (animal ?x))
)


(defrule responder
    (declare (salience -100))
    (animalEntrada ?x)
    (not (respondido))
    (explicacion vuela ?x ?expl)
    =>
    (printout t ?expl crlf)
    (assert (respondido))
)


; Las aves son animales
(defrule aves_son_animales
(ave ?x)
=>
(assert (animal ?x))
(bind ?expl (str-cat "sabemos que un " ?x " es un animal porque las aves son un tipo de animal"))
(assert (explicacion animal ?x ?expl)) )
; añadimos un hecho que contiene la explicación de la deducción

; Los mamiferos son animales (A3)
(defrule mamiferos_son_animales
(mamifero ?x)
=>
(assert (animal ?x))
(bind ?expl (str-cat "sabemos que un " ?x " es un animal porque los mamiferos son un tipo de animal"))
(assert (explicacion animal ?x ?expl)) )
; añadimos un hecho que contiene la explicación de la deducción

;;; Casi todos las aves vuela --> puedo asumir por defecto que las aves vuelan
; Asumimos por defecto
(defrule ave_vuela_por_defecto
(declare (salience -1)) ; para disminuir probabilidad de añadir erróneamente
(ave ?x)
=>
(assert (vuela ?x si por_defecto))
(bind ?expl (str-cat "asumo que un " ?x " vuela, porque casi todas las aves
vuelan"))
(assert (explicacion vuela ?x ?expl)) )
)

; Retractamos cuando hay algo en contra
(defrule retracta_vuela_por_defecto
(declare (salience 1)) ; para retractar antes de inferir cosas erroneamente
?f<- (vuela ?x ?r por_defecto)
(vuela ?x ?s seguro)
=>
(retract ?f)
(bind ?expl (str-cat "retractamos que un " ?x " " ?r " vuela por defecto, porque
sabemos seguro que " ?x " " ?s " vuela"))
(assert (explicacion vuela ?x ?expl)) )

;;; La mayor parte de los animales no vuelan --> puede interesarme asumir por defecto
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;que un animal no va a volar
(defrule mayor_parte_animales_no_vuelan
(declare (salience -2)) ;;;; es mas arriesgado, mejor después de otros razonamientos
(animal ?x)
(not (vuela ?x ? ?))
=>
(assert (vuela ?x no por_defecto))
(bind ?expl (str-cat "asumo que " ?x " no vuela, porque la mayor parte de los animales no vuelan"))
(assert (explicacion vuela ?x ?expl)) )
