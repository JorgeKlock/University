; Archivo: recomendar_rama.clp
; Autor: Miguel Lentisco Ballesteros
; Sistema para aconsejar a un estudiante de IF sobre que rama deberia escoger


; ---------------------------------------------------------------------------
;                             MHacerPreguntasRR
; ---------------------------------------------------------------------------
; Modulo correspondiente a la parte de hacer preguntas al usuario para extraer
; la informacion necesaria para su evaluación

; ---------------------------------------------------------------------------
;                           EXPLICACIÓN_INICIAL
; ---------------------------------------------------------------------------

; Explicacion inicial al usuario, que se le va a hacer una serie de preguntas.
(defrule HacerExplicacionInicial
  (declare (salience 9999))
  (MActual MHacerPreguntasRR)
  ?f <- (Comando RecomendarRama)
    =>
  (retract ?f)
  (printout t "Te voy a hacer una serie de preguntas para aconsejarte que rama debes coger." crlf)
  (printout t "Si en una pregunta no sabes que responder o no quieres escribe NS." crlf)
  (printout t "Si no quieres responder mas escribe STOP y te dare un resultado, aunque ten en cuenta que si no respondes todo no te puedo aconsejar lo mejor." crlf)
  (printout t "" crlf)
  ; Añadimos preguntas
  (assert (HacerPregunta Matematicas))
  (assert (HacerPregunta Hardware))
  (assert (HacerPregunta BigData))
  (assert (HacerPregunta Software))
  (assert (HacerPregunta Web))
  (assert (HacerPregunta NotaMedia))
)

; ---------------------------------------------------------------------------
;                           PREGUNTA SI_NO
; ---------------------------------------------------------------------------

(deffacts HechosRamaAux
  ; Preguntas
  (PreguntaSINO Matematicas "Te gustan las matematicas aplicadas a la informatica (IA, RV, ...)?")
  (PreguntaSINO Hardware "Te gusta el hardware (robots, procesadores...)?")
  (PreguntaSINO BigData "Te gusta el bigdata (ciencia de datos, analisis...)?")
  (PreguntaSINO Software "Te gusta programar software (juegos, programas...)?")
  (PreguntaSINO Web "Te gusta trabajar con paginas web? (programacion, estilo, bbdd...)?")
  ; Resuestas válidas
  (RespuestasSINO SI NO NS STOP)
  ; Nota media  categorica a discreta
  (VarCategoricaRR BAJA 1)
  (VarCategoricaRR MEDIA 2)
  (VarCategoricaRR ALTA 3)
  (VarCategoricaRR STOP STOP)
  (VarCategoricaRR NS NS)
  ; Nota media continua a discreta
  (VarNumericaRR 0 6 1)
  (VarNumericaRR 6 7.5 2)
  (VarNumericaRR 7.5 10.1 3)
)


; Se hace una pregunta de SI o NO
(defrule Preguntar_SI_NO
  (MActual MHacerPreguntasRR)
  (PreguntaSINO ?tema ?pregunta)
  ?f <- (HacerPregunta ?tema)
    =>
  (retract ?f)
  (printout t ?pregunta " (SI, NO o NS)" crlf)
  (bind ?res (upcase (read)))
  (assert (Gusta ?tema ?res))
)

; Comprobamos que se ha dado una respuesta valida, si no se vuelve a preguntar
(defrule Chequear_SI_NO
  (declare (salience 1))
  (MActual MHacerPreguntasRR)
  ?f <- (Gusta ?tema ?res)
  (not (RespuestasSINO $? ?res $?))
    =>
  (retract ?f)
  (printout t "Lo siento, no he entendido tu respuesta." crlf)
  (assert (HacerPregunta ?tema))
)

; Si la respuesta es STOP, paramos y damos una respuesta
(defrule Acabar_SI_NO
  ?f1 <- (MActual MHacerPreguntasRR)
  ?f2 <- (Gusta ? STOP)
    =>
  (retract ?f1 ?f2)
  (assert (MActual MCalcularRamaRR))
)

; ---------------------------------------------------------------------------
;                                NOTA_MEDIA
; ---------------------------------------------------------------------------

; Regla que se encarga de hacer la pregunta sobre la NotaMedia del estudiante
; Se representa por (Calificacion_media Alta|Media|Baja|NS)
(defrule Preguntar_NotaMedia
  (MActual MHacerPreguntasRR)
  ?f <- (HacerPregunta NotaMedia)
    =>
  (retract ?f)
  (printout t "Cual es tu nota media? (numero, Baja|Media|Alta o NS)" crlf)
  (bind ?nota (string-to-field (implode$ (explode$ (upcase (readline))))))
  (assert (NotaMedia ?nota check))
)

; Comprobamos que la nota media numerica está en [0, 10]
(defrule Chequear_NotaMedia
  (declare (salience 1))
  (MActual MHacerPreguntasRR)
  ?f <- (NotaMedia ?nota check)
  (test (numberp ?nota))
  (or (test (> ?nota 10))
      (test (< ?nota 0))
  )
    =>
  (printout t crlf "Perdon pero la nota " ?nota " no es valida." crlf)
  (retract ?f)
  (assert (HacerPregunta NotaMedia))
)

; Comprobamos que la nota media categórica es una de las válidas
(defrule Chequear_NotaCategorica
  (declare (salience 1))
  (MActual MHacerPreguntasRR)
  ?f <- (NotaMedia ?nota check)
  (not (test (numberp ?nota)))
  (not (VarCategoricaRR ?nota ?))
    =>
  (printout t crlf "Lo siento pero " ?nota " no es una opcion valida." crlf)
  (retract ?f)
  (assert (HacerPregunta NotaMedia))
)

; Transformación nota categorica a numerica
(defrule Convertir_NotaCategorica
  (MActual MHacerPreguntasRR)
  ?f <- (NotaMedia ?nota check)
  (VarCategoricaRR ?nota ?nueva_nota)
    =>
  (retract ?f)
  (assert (NotaMedia ?nueva_nota))
)

; Transformación nota continua a discreta
(defrule Convertir_NotaContinua
  (MActual MHacerPreguntasRR)
  ?f <- (NotaMedia ?nota check)
  (test (numberp ?nota))
  (VarNumericaRR ?lim_inf ?lim_sup ?nueva_nota)
  (and (test (>= ?nota ?lim_inf))
       (test (< ?nota ?lim_sup))
  )
    =>
  (retract ?f)
  (assert (NotaMedia ?nueva_nota))
)

; Si el usuario hace STOP
(defrule Acabar_NotaMedia
  ?f1 <- (MActual MHacerPreguntasRR)
  ?f2 <- (NotaMedia STOP)
    =>
  (retract ?f1 ?f2)
  (assert (MActual MCalcularRamaRR))
)

; ---------------------------------------------------------------------------
;                                Sin preguntas
; ---------------------------------------------------------------------------

; Si hemos hecho todas las preguntas pasamos a calcular la rama
(defrule SinPreguntas
  (declare (salience -1))
  ?f <- (MActual MHacerPreguntasRR)
  (not (HacerPregunta ?))
    =>
  (retract ?f)
  (assert (MActual MCalcularRamaRR))
)

; ---------------------------------------------------------------------------
;                            MCalcularRamaRR
; ---------------------------------------------------------------------------
; Modulo correspondiente a la parte de tomar en consideracion las respuestas
; del usuario y aconsejar sobre la rama que deberia coger

; Si alguien le gusta el Hardware, indiferente de lo demas, deberia tomar IC
(defrule GustaHardware
  (MActual MCalcularRamaRR)
  (Gusta Hardware SI)
    =>
  (assert (Consejo "IC" "Te recomiendo IC ya que hardware no le suele encantar a nadie, y puedes meterte mas en profundidad de lo poco que se ve en la carrera." "Mike"))
  (assert (Aviso "IC"))
)

; Si a alguien le gusta las Matematicas y no el Hardware recomiendo que tome CSI
(defrule GustaMatematicas
  (MActual MCalcularRamaRR)
  (Gusta Matematicas SI)
  (not (exists (Gusta Hardware SI)))
    =>
  (assert (Consejo "CSI" "Te aconsejo CSI porque no a mucha gente le gustan las matematicas y en esta rama es donde se usan mas, tienes muchisimas aplicaciones y salidas laborales." "Mike"))
  (assert (Aviso "CSI"))
)

; Si le gusta Bigdata (y no mates / hardware) y t recomiendo SI
(defrule GustaBigdata
  (MActual MCalcularRamaRR)
  (Gusta BigData SI)
  (not (exists (Gusta Matematicas SI)))
  (not (exists (Gusta Hardware SI)))
    =>
  (assert (Consejo "SI" "La rama SI es una muy buena opcion para ti, ya que tienes mucho analisis de datos que no se ven en las ramas troncales y actualmente con muchas salidas." "Mike"))
)

; Si le gusta Software (y no mates / hardware /bigdata) recomiendo IS
(defrule GustaSoftware
  (MActual MCalcularRamaRR)
  (Gusta Software SI)
  (not (exists (Gusta Matematicas SI)))
  (not (exists (Gusta Hardware SI)))
  (not (exists (Gusta BigData SI)))
    =>
  (assert (Consejo "IS" "La rama mejor para ti es IS, aqui programas un poco de todo, lo que se ha ido haciendo en la carrera generalmente, y te vale para cualquier puesto general de informatico." "Mike"))
  (assert (Aviso "IS"))
)

; Si le gusta web nada mas recomiendo TI
(defrule GustaWeb
  (MActual MCalcularRamaRR)
  (Gusta Web SI)
  (not (exists (Gusta Matematicas SI)))
  (not (exists (Gusta Hardware SI)))
  (not (exists (Gusta BigData SI)))
  (not (exists (Gusta Software SI)))
    =>
  (assert (Consejo "TI" "La rama TI es para ti, todo lo que tu quieras de tecnologias web esta aqui, muchas cosas sobre webs que no has visto en el grado y un gran numero de puestos de trabajo." "Mike"))
)

; Si no tenemos las notas y no le gusta nada
(defrule NoGustaNada
  (MActual MCalcularRamaRR)
  (exists (Gusta ? NO))
  (not (exists (Gusta ? SI)))
  (not (exists (NotaMedia $?)))
    =>
  (assert (Consejo "IS" "Con lo que me has dicho te tengo que recomendar IS, que es la rama generica de informatica, aunque no te guste programar, por defecto te puede valer luego para cualquier trabajo de informatico." "Mike"))
)

; Basamos la decision solo con la nota (baja)
(defrule SoloNotas_Baja
  (MActual MCalcularRamaRR)
  (not (exists (Gusta ? SI)))
  (NotaMedia 1)
    =>
  (assert (Consejo "TI" "Tienes la nota baja por lo que una rama como TI, que tiene cosas faciles con paginas web que no requieren mucha complicacion te puede ir bien." "Mike"))
  (assert (Consejo "SI" "Tambian te vale SI si le pones requiera un poco mas de esfuerzo, ya que en cuestion de analisis de datos es un poco mas dura." "Mike"))
)

; Basamos la decision solo con la nota (media)
(defrule SoloNotas_Media
  (MActual MCalcularRamaRR)
  (not (exists (Gusta ? SI)))
  (NotaMedia 2)
    =>
  (assert (Consejo "IS" "Por tu nota media creo que te puede valer una rama de dificultad media como lo es IS, donde se tienen asignaturas mas de programar software." "Mike"))
  (assert (Consejo "SI" "Tambien te vale SI por tener la ciencia de datos, que requiere algo de esfuerzo pero relativamente." "Mike"))
  (assert (Consejo "IC" "Finalmente, si te interesa algo el hardware puedes intentar hacer IC tambien, aunque solo si tienes algo de interes." "Mike"))
)

; Basamos la decision solo con la nota (alta)
(defrule SoloNotas_Alta
  (MActual MCalcularRamaRR)
  (not (exists (Gusta ? SI)))
  (NotaMedia 3)
    =>
  (assert (Consejo "CSI" "Debido a tu gran media te aconsejo que vayas a por CSI, ya que es una rama que requiere mucho trabajo y entendimiento con temas dificiles donde hay matematicas." "Mike"))
)

; Añade un aviso si se tiene la nota media baja
(defrule Aviso
  (MActual MCalcularRamaRR)
  ?f <- (Aviso ?rama)
  ?g <- (Consejo ?rama ?motivo ?autor)
  (NotaMedia 1)
    =>
  (retract ?f)
  (retract ?g)
  (assert (Consejo ?rama (str-cat ?motivo " Aunque te advierto que igual tienes que esforzarte un poco mas dada tu nota media baja." ) ?autor))
)

; Si el usuario no ha respondido nada, recomendamos IS ya que es un tema que gusta en general
(defrule SinRespuestas
  (declare (salience -2))
  (MActual MCalcularRamaRR)
  (not (exists (Consejo)))
    =>
  (assert (Consejo "IS" "No puedo decirte mucho puesto que no me has respondido a nada, te recomiendo IS por ejemplo puesto que programar software va con la linea general del grado y por lo que suelen hacer el grado los estudiantes, pero realmente puedes escoger cualquiera." "Mike"))
)

; Una vez se hayan calculado las ramas, se coge el nombre del experto y se cambia al
; modulo de dar los consejos calculados
(defrule RamaCalculada
  (declare (salience -1))
  ?f <- (MActual MCalcularRamaRR)
  (Consejo ? ? ?experto)
    =>
  (retract ?f)
  (assert (Experto ?experto))
  (assert (MActual MRespuestaRamaRR))
)

; ---------------------------------------------------------------------------
;                              MRespuestaRamaRR
; ---------------------------------------------------------------------------
; Modulo correspondiente a la parte de tomar en consideracion las respuestas
; del usuario y aconsejar sobre la rama que deberia coger

; Mensaje inicial para dar respuesta
(defrule RespuestaExperto
  (declare (salience 9999))
  (MActual MRespuestaRamaRR)
  (Experto ?experto)
    =>
  (printout t "" crlf)
  (printout t "Segun las recomendaciones del experto " ?experto ", te aconsejamos lo siguiente: " crlf)
)

; Imprime consejo
(defrule ImprimeConsejo
  (MActual MRespuestaRamaRR)
  (Consejo ?rama ?motivo ?)
    =>
  (printout t " -" ?rama ": " ?motivo  crlf)
)

; Limpia los hechos
(defrule LimpiarHechosRama
  (declare (salience -9999))
  (MActual MRespuestaRamaRR)
  ?f <- (Experto ?)
    =>
  (retract ?f)
  (assert (Comando LimpiarRama))
)

; Limpia consejos
(defrule LimpiarConsejos
  (MActual MRespuestaRamaRR)
  (Comando LimpiarRama)
  ?f <- (Consejo $?)
    =>
  (retract ?f)
)

; Limpia gustos
(defrule LimpiaGustos
  (MActual MRespuestaRamaRR)
  (Comando LimpiarRama)
  ?f <- (Gusta $?)
    =>
  (retract ?f)
)

; Limpia gustos
(defrule LimpiaPreguntas
  (MActual MRespuestaRamaRR)
  ?f <- (HacerPregunta ?)
    =>
  (retract ?f)
)

; Limpia nota media
(defrule LimpiaNotaMedia
  (MActual MRespuestaRamaRR)
  (Comando LimpiarRama)
  ?f <- (NotaMedia $?)
    =>
  (retract ?f)
)

; Limpia avisos
(defrule LimpiaAvisos
  (MActual MRespuestaRamaRR)
  (Comando LimpiarRama)
  ?f <- (Aviso $?)
    =>
  (retract ?f)
)

; Después de limpiar todo volvemos al menú principal
(defrule VolverMenuPrincipal
  (declare (salience -1))
  ?f1 <- (MActual MRespuestaRamaRR)
  ?f2 <- (Comando LimpiarRama)
    =>
  (retract ?f1 ?f2)
  (assert (MActual MMenu))
  (assert (Comando MostrarMenu))
)
