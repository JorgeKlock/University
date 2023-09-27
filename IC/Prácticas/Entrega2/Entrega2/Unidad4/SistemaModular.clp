;;;;;Unión de sistemas expertos simples
;;Se ha utilizado el sistema de Valentino Lugli a parte del original de Jorge Gangoso Klock
;;Se ha modificado ligeramente el modulo H2 (proveniente del sistema experto de Jorge G.K.) para adaptarse a las
;;necesidades del ejercicio

(defrule introduccion
    (declare (salience 100))
    =>
    (printout t "======= Bienvenido al asistente de eleccion de rama multihipotesis =======" crlf)
    (focus H1)
)

;Sistema Experto simple de Valentino

(defmodule H1
    (export ?ALL))

(deftemplate branch
    (field id)
    (field name)
)

;   Definición de las ramas y su nombre completo.
(deffacts defBranches
    (branch (id CSI) (name "Computacion y Sistemas Inteligentes"))
    (branch (id IS) (name "Ingenieria del Software"))
    (branch (id SI) (name "Sistemas de Informacion"))
    (branch (id IC) (name "Ingenieria de Computadores"))
    (branch (id TI) (name "Tecnologias de la Informacion"))
)

;   Definición de preguntas a realizar.
(deffacts questions
    (question hardware)
    (question programar)
    (question matematicas)
    (question trabajo)
    (question hardware)
    (question promedio)
)

;   Registro de las preguntas y las respuestas válidas que poseen.
(deftemplate validAnswers
    (field questionName)
    (multifield validAns)
)

;   Rellenar las preguntas existentes y su respuestas válidas.
(deffacts fillValidAnswers
    (validAnswers (questionName hardware)
        (validAns "si" "no" "me da igual")
    )

    (validAnswers (questionName programar)
        (validAns "si" "no" "me da igual")
    )

    (validAnswers (questionName promedio)
        (validAns "alto" "medio" "bajo")
    )

    (validAnswers (questionName matematicas)
        (validAns "si" "no" "me da igual")
    )

    (validAnswers (questionName trabajo)
        (validAns "mucho" "medio" "poco")
    )
)

;   Registro de que rama recomendar en relación a las distintas preguntas; con más de una respuesta válida.
(deftemplate recommendation
    (field branchID)
    (multifield likesHardware)
    (multifield likesToProgram)
    (multifield howMuchWork)
    (multifield averageGrade)
    (multifield likesMath)
    (field explanation)
    (field author)
)

;   Definición propiamente de los registros para las ramas de Ingeniería Informática.
(deffacts branchRecc
    (recommendation (branchID CSI)
        (likesHardware  "no" "me da igual")
        (likesToProgram "si")
        (howMuchWork "")
        (averageGrade "medio" "alto")
        (likesMath "si" "me da igual")
        (explanation "Esto es debido a que te gusta programar, tienes afinidad por las matematicas, el trabajo arduo y esto se refleja en tu promedio.")
        (author "Valentino Lugli")
    )

    (recommendation (branchID IC)
        (likesHardware "si" "me da igual")
        (likesToProgram "no")
        (howMuchWork "medio" "alto")
        (averageGrade "alto" "medio" "bajo")
        (likesMath "si" "no" "me da igual")
        (explanation "Esto es debido a que te gusta el hardware mas que todo, lo cual rapidamente me permite realizarte la recomendacion.")
        (author "Valentino Lugli")
    )

    (recommendation (branchID IS)
        (likesHardware "no" "me da igual")
        (likesToProgram "si")
        (howMuchWork "mucho")
        (averageGrade "medio")
        (likesMath "si" "no" "me da igual")
        (explanation "Esto es debido a que te gusta programar, te gusta trabajar y/o posees afinidad por las matematicas y un promedio que debe ser medio.")
        (author "Valentino Lugli")
    )

    (recommendation (branchID SI)
        (likesHardware "no" "me da igual")
        (likesToProgram "si" "me da igual")
        (howMuchWork "medio")
        (averageGrade "alto" "medio" "bajo")
        (likesMath "no" "me da igual")
        (explanation "Esto es debido a que posees un gusto por programar, trabajas de manera moderada y prefieres no tocar muchos las mates.")
        (author "Valentino Lugli")
    )

    (recommendation (branchID TI)
        (likesHardware "no" "me da igual")
        (likesToProgram "no" "me da igual")
        (howMuchWork "poco" "medio")
        (averageGrade "medio" "bajo")
        (likesMath "no" "me da igual" "si")
        (explanation "Esto es debido a que prefieres de carga de trabajo bajas, prefieres alejarte un poco de la programacion y las mates y tratar con informacion de otras maneras.")
        (author "Valentino Lugli")
    )
)


; REGLAS

; Regla inicial.
(defrule startUp
    (declare (salience 100))
        =>
    (printout t crlf crlf"--- Sistema Experto Simple ---" crlf)
    (printout t "- RECOMENDACIONES SOBRE RAMAS -" crlf crlf)
    ; Se usa este hecho para evitar que se dispare una sola recomendacion.
    (assert (deduction))
)


; Reglas que obtienen informacion del usuario.
(defrule hardwareQuestion
    (deduction)
    ?rule <- (question hardware)
        =>
    (retract ?rule)
    (printout t crlf "--- PREGUNTA ---" crlf ">>Te gusta el hardware?" crlf ">>(Si | No | Me da igual)" crlf ">")
    ; Leer la entrada con espacios y convertirla a minuscula.
    (assert(answer hardware (lowcase (readline))))
)

(defrule programmingQuestion
    (deduction)
    ?rule <- (question programar)
        =>
    (retract ?rule)
    (printout t crlf "--- PREGUNTA ---" crlf ">>Te gusta programar?" crlf ">>(Si | No | Me da igual)" crlf ">")
    (assert(answer programar (lowcase (readline))))
)

(defrule mathQuestion
    (deduction)
    ?rule <- (question matematicas)
        =>
    (retract ?rule)
    (printout t crlf "--- PREGUNTA ---" crlf ">>Te gustan las matematicas?" crlf ">>(Si | No | Me da igual)" crlf ">")
    (assert(answer matematicas (lowcase(readline))))
)

(defrule workQuestion
    (deduction)
    ?rule <- (question trabajo)
        =>
    (printout t crlf "--- PREGUNTA ---" crlf ">>Que tanto trabajas?" crlf ">>(Mucho | Medio | Poco)" crlf ">")
    (assert(answer trabajo (lowcase(readline))))
    (retract ?rule)
)

(defrule gradesQuestion
    (deduction)
    (answer matematicas "si"|"me da igual")
    ?rule <- (question promedio)
        =>
    (retract ?rule)
    (printout t crlf "--- PREGUNTA ---" crlf ">>Cual es tu promedio?" crlf ">>(Numero fraccional entre 5 y 10)" crlf ">")
    ; Primero se crea este hecho para convertir de número a un valor discreto.
    (assert(answerNum promedio (read)))
)

;   Convertir promedio a valor discreto.
(defrule gradeQuestionConvertAnswer
    ?rule <- (answerNum promedio ?avg)
    ; Comprobar que el número está entre 5 y 10
    (test ( and (>= ?avg 5) (<= ?avg 10) ) )
        =>
    (retract ?rule)
    ; Si está entre 5 y 6.99; es promedio bajo. Entre 7 y 8.99 es promedio medio y de 9 en adelante es promedio alto.
    (if (and (>= ?avg 5)(< ?avg 6.99) ) then
        ( assert(answer promedio "bajo") )
    else (if (and (>= ?avg 7) (< ?avg 8.99) ) then
        ( assert(answer promedio "medio") )
    else ( assert (answer promedio "alto") ) )
    )
)

;   Reglas de selección de rama
;   - Estas reglas capturan las diferentes maneras que un usuario puede responder, por ejemplo, solamente se puede responder a
;     la primera pregunta y esto dispare una respuesta.
(defrule reccomender1
    (declare (salience 100))
    ?rule <- (deduction)

    (answer hardware ?a)

    (recommendation (branchID ?name) (likesHardware ?a) (explanation ?expl))
    (branch (id ?name) (name ?fullName))

        =>

    (retract ?rule)
    (assert (ans ?fullName ?expl))
)

;   - Estas dos siguientes reglas comprenden el resto de las hojas del "arbol de decisión" implícito que se utiliza, capturan
;     las diversas respuestas y acorde a lo que se posee en la base de conocimientos, se da una respuesta.
(defrule reccomender2
    (declare (salience 100))
    ?rule <- (deduction)

    (answer hardware ?a)
    (answer programar ?b)
    (answer promedio ?c)
    (answer matematicas ?d)
;   Utilizar el $? permite que si encuentra un valor de los que puede tener esa respuesta, se acepta y dispara la regla.
    (recommendation (branchID ?name) (likesHardware $? ?a $?) (likesToProgram $? ?b $?) (averageGrade $? ?c $?) (likesMath $? ?d $?) (explanation ?expl))
    (branch (id ?name) (name ?fullName))

        =>

    (retract ?rule)
    (assert (ans ?fullName ?expl))
)

(defrule reccomender3
    (declare (salience 100))
    ?rule <- (deduction)

    (answer hardware ?a)
    (answer programar ?b)
    (answer trabajo ?c)
    (answer matematicas ?d)

    (recommendation (branchID ?name) (likesHardware $? ?a $?) (likesToProgram $? ?b $?) (howMuchWork $? ?c $?)  (likesMath $? ?d $?) (explanation ?expl))
    (branch (id ?name) (name ?fullName))

        =>

    (retract ?rule)
    (assert (ans ?fullName ?expl))
)

;   Imprimir recomendación
(defrule giveRecc
    (ans ?fullName ?expl)
        =>
    (printout t crlf "======= Opinion del primer asistente de rama: =======" crlf ">>Te recomiendo " ?fullName "." crlf ">>" ?expl "."crlf)
    (focus H2)
)

;   Esta regla se dispara cuando el razonador no encuentra una recomendacion de rama por falta de información.
(defrule reccomendDefault
    (declare (salience -10))

    (answer hardware ? )
    (answer programar ? )
    (answer matematicas ?)
    (answer promedio|trabajo ? )

    ?rule <- (deduction)
        =>
    (printout t crlf "### RESPUESTA ###" crlf ">>Lo siento, con la informacion que me has dado no puedo llegar a una conclusion satisfactoria." crlf)
    (retract ?rule)
    (focus H2)
)

;   Reglas de verificación de correctitud de las respuestas.
;   - Verificar que en las preguntas textuales se responde acordemente.
(defrule checkAns
    (declare (salience 90))

    ; Leer cualquier regla de respuesta.
    ?rule <- (answer ?type ?ans)

    ; Si no encuentra que la respuesta ?ans corresponde con alguna de las respuestas validas, disparar la regla.
    (not (validAnswers (questionName ?type) (validAns $? ?ans $?)))

        =>
    ; Imprimir mensaje, borrar la regla de la respuesta y retornar a la pregunta.
    (printout t ">>Perdona, pero '"?ans "' no es una respuesta valida sobre " ?type ". Vuelve a responder." crlf)
    (retract ?rule)
    (assert (question ?type))
)

;   - Verificar en la pregunta de promedio que se responde correctamente.
(defrule checkNumAns
    (declare (salience 90))
    ?rule <- (answerNum ?type ?ans)
    ; Si el numero es menos de 5 o mayor que 10 o diferente de 0...
    (test ( or (< ?ans 5) (> ?ans 10) ) )
        =>
    ; ... Imprimir el mensaje y retornar a la pregunta.
    (printout t ">>Perdona, pero '"?ans "' no es una respuesta valida sobre " ?type ". Vuelve a responder." crlf)
    (retract ?rule)
    (assert (question ?type))
)
;Sistema Experto simple de Jorge

(defmodule H2
    (import H1 ?ALL))

(defrule union
    (declare (salience 100))
    =>
    (printout t "======= Opinion del segundo asistente de rama: =======" crlf)
)
;;;; RESPUESTA EN CASO DE QUE SI
(defrule respuesta
    (answer hardware "si")
    =>
    (printout t "En tal caso deberias escoger directamente la rama de IC, tiene buenas salidas y esta falta de alumnos" crlf)
)

;;;; RESPUESTA EN CASO DE QUE NO
(defrule respuesta2
    (answer hardware "no" | "me da igual")
    (answer programar "no" | "me da igual")
    =>
    (printout t "Ya veo, entonces deberias probar con la rama de TI, no tiene una carga excesiva ni de programacion ni de hardware, y se ven muchos conceptos variados")
)

;;;; RESPUESTAS FINALES
(defrule respuesta3
    (answer hardware "no" | "me da igual")
    (answer programar "si")
    (answer trabajo "poco")
    =>
    (printout t "Entonces la rama de IS es la que menor carga de trabajo tiene de entre las ramas de programacion")
)
(defrule respuesta4
    (answer hardware "no" | "me da igual")
    (answer programar "si")
    (answer trabajo "medio")
    =>
    (printout t "La rama de SI es para ti, se estudian mecanismos programacion a un nivel avanzado sin exceso de dificultad")
)
(defrule respuesta5
    (answer hardware "no" | "me da igual")
    (answer programar "si")
    (answer trabajo "mucho")
    =>
    (printout t "Deberias probar la rama de CSI, aunque la alta carga matematica puede ser complicada de sobrellevar, deberias estar listo para dedicarle mucho tiempo")
)

;Estructura multihipótesis utilizando ambos sistemas expertos

