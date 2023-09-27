; (FactorCerteza ?h si|no ?f) representa que ?h se ha deducido con factor de certeza ?f
;?h podrá_ser:
;    - problema_starter
;    - problema_bujias
;    - problema_batería
;    - motor_llega_gasolina
; (Evidencia ?e si|no) representa el hecho de si evidencia ?e se da
; ?e podrá ser:
;    - hace_intentos_arrancar
;    - hay_gasolina_en_deposito
;    - encienden_las_luces
;    - gira_motor


;;;; Preguntas ;;;;
(defrule evidencia1
    (declare (salience 10))
    =>
    (printout t "El coche hace intentos de arrancar?(si|no)")
    (assert (Evidencia hace_intentos_arrancar (lowcase (read))))
)
(defrule evidencia2
    (declare (salience 9))
    =>
    (printout t "El coche tiene gasolina en el deposito?(si|no)")
    (assert (Evidencia hay_gasolina_en_deposito (lowcase (read))))
)
(defrule evidencia3
    (declare (salience 8))
    =>
    (printout t "Se le encienden las luces al coche?(si|no)")
    (assert (Evidencia encienden_las_luces (lowcase (read))))
)
(defrule evidencia4
    (declare (salience 7))
    =>
    (printout t "El motor del coche gira?(si|no)")
    (assert (Evidencia gira_motor (lowcase (read))))
)


;;;; SELECCION MEJOR HIPOTESIS ;;;;
;;Convertir los factores de certeza en hipotesis
(defrule convertir_a_Hs
    (declare (salience -1))
    (FactorCerteza problema_starter si ?f)
    =>
    (assert (averia starter ?f))
)
(defrule convertir_a_Hbuj
    (declare (salience -1))
    (FactorCerteza problema_bujias si ?f)
    =>
    (assert (averia bujias ?f))
)
(defrule convertir_a_Hbat
    (declare (salience -1))
    (FactorCerteza problema_bateria si ?f)
    =>
    (assert (averia bateria ?f))
)

;;Comprobar la mayor
(defrule 3problemas
    (declare (salience -2))
    (averia ?p1 ?f1)
    (averia ?p2 ?f2)
    (averia ?p3 ?f3)
    (test (and (> ?f1 ?f2) (> ?f1 ?f3)))
    (not (respondido))
    =>
    (printout t "El problema esta en " ?p1 " con una certeza de " ?f1 crlf)
    (assert (respondido))
)
(defrule 2problemas
    (declare (salience -3))
    (averia ?p1 ?f1)
    (averia ?p2 ?f2)
    (test (> ?f1 ?f2))
    (not (respondido))
    =>
    (printout t "El problema esta en " ?p1 " con una certeza de " ?f1 crlf)
    (assert (respondido))
)
(defrule 1problema
    (declare (salience -4))
    (averia ?p1 ?f1)
    (not (respondido))
    =>
    (printout t "El problema esta en " ?p1 " con una certeza de " ?f1 crlf)
    (assert (respondido))
)




;;; convertimos cada evidencia en una afirmación sobre su factor de certeza
(defrule certeza_evidencias
    (Evidencia ?e ?r)
    =>
(assert (FactorCerteza ?e ?r 1)) )
;; También podríamos considerar evidencias con una cierta
;;incertidumbre: al preguntar por la evidencia, pedir y recoger
;;directamente el grado de certeza


(deffunction encadenado (?fc_antecedente ?fc_regla)
    (if (> ?fc_antecedente 0)
        then
        (bind ?rv (* ?fc_antecedente ?fc_regla))
    else
        (bind ?rv 0)
    );?rv
)


;R1: SI el motor obtiene gasolina Y el motor gira ENTONCES problemas ;
con las bujías con certeza 0.7
(defrule R1
    (FactorCerteza motor_llega_gasolina si ?f1)
    (FactorCerteza gira_motor si ?f2)
    (test (and (> ?f1 0) (> ?f2 0)))
    =>
    (assert (FactorCerteza problema_bujias si (encadenado (* ?f1 ?f2) 0.7)))
)

(defrule R2
    (FactorCerteza gira_motor no ?f1)
    (test (> ?f1 0))
    =>
    (assert (FactorCerteza problema_starter si (* ?f1 0.8)))
)
(defrule R3
    (FactorCerteza encienden_las_luces no ?f1)
    (test (> ?f1 0))
    =>
    (assert (FactorCerteza problema_bateria si (* ?f1 0.9)))
)
(defrule R4
    (FactorCerteza hay_gasolina_en_deposito si ?f1)
    (test (> ?f1 0))
    =>
    (assert (FactorCerteza motor_llega_gasolina si (* ?f1 0.9)))
)
(defrule R5
    (FactorCerteza hace_intentos_arrancar si ?f1)
    (test (> ?f1 0))
    =>
    (assert (FactorCerteza problema_starter no (* ?f1 -0.6)))
)
(defrule R6
    (FactorCerteza hace_intentos_arrancar si ?f1)
    (test (> ?f1 0))
    =>
    (assert (FactorCerteza problema_bateria si (* ?f1 0.5)))
)



(deffunction combinacion (?fc1 ?fc2)
    (if (and (> ?fc1 0) (> ?fc2 0) )
        then
        (bind ?rv (- (+ ?fc1 ?fc2) (* ?fc1 ?fc2) ) )
    else
    (if (and (< ?fc1 0) (< ?fc2 0) )
        then
        (bind ?rv (+ (+ ?fc1 ?fc2) (* ?fc1 ?fc2) ) )
    else
        (bind ?rv (/ (+ ?fc1 ?fc2) (- 1 (min (abs ?fc1) (abs ?fc2))) ))
    )
    )?rv
)

;;;;;; Combinar misma deduccion por distintos caminos
(defrule combinar
    (declare (salience 1))
    ?f <- (FactorCerteza ?h ?r ?fc1)
    ?g <- (FactorCerteza ?h ?r ?fc2)
    (test (neq ?fc1 ?fc2))
    =>
    (retract ?f ?g)
    (assert (FactorCerteza ?h ?r (combinacion ?fc1 ?fc2)))
)

