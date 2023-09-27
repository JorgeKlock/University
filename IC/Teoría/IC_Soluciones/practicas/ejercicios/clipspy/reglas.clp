(deffacts Prueba
  (hecho1)
)

(defrule RuleTonta
  (hecho1)
    =>
  (assert (hecho2))
)
