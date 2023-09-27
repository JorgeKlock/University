; Sistema para aconsejar a un estudiante de IF sobre que rama deberia escoger
; Autor: Miguel Lentisco Ballesteros

; Inicio del programa
(defrule Iniciar
    =>
  (focus MHacerPreguntas)
)

; ---------------------------------------------------------------------------
; Modulo correspondiente a la parte de hacer preguntas al usuario para extraer
; la informacion necesaria para su evaluacion
; ---------------------------------------------------------------------------
(defmodule MHacerPreguntas (export ?ALL))


  ; Las preguntas que se van a hacer
  (deffacts Preguntas
    (PreguntaSINO Matematicas "Te gustan las matematicas aplicadas a la informatica (IA, RV, ...)?")
    (PreguntaSINO Hardware "Te gusta el hardware (robots, procesadores...)?")
    (PreguntaSINO Bigdata "Te gusta el bigdata (ciencia de datos, analisis...)?")
    (PreguntaSINO Software "Te gusta programar software (juegos, programas...)?")
    (PreguntaSINO Web "Te gusta trabajar con paginas web? (programacion, estilo, bbdd...)?")
    (PreguntaNotaMedia)
    (ModActivo HacerPreguntas)
  )

  ; ---------------------------------------------------------------------------
  ;                           EXPLICACIÓN_INICIAL
  ; ---------------------------------------------------------------------------

  ; Explicacion inicial al usuario, que se le va a hacer una serie de preguntas.
  (defrule HacerExplicacionInicial
    (declare (salience 9999))
    (ModActivo HacerPreguntas)
      =>
    (printout t "Te voy a hacer una serie de preguntas para aconsejarte que rama debes coger." crlf)
    (printout t "Si en una pregunta no sabes que responder o no quieres escribe NS." crlf)
    (printout t "Si no quieres responder mas escribe STOP y te dare un resultado, aunque ten en cuenta que si no respondes todo no te puedo aconsejar lo mejor." crlf)
    (printout t "" crlf)
  )

  ; ---------------------------------------------------------------------------
  ;                           PREGUNTA SI_NO
  ; ---------------------------------------------------------------------------

  ; Se hace una pregunta de SI o NO
  (defrule Preguntar_SI_NO
    (ModActivo HacerPreguntas)
    ?f <- (PreguntaSINO ?tema ?pregunta)
      =>
    (retract ?f)
    (printout t ?pregunta " (si, no o NS)" crlf)
    (bind ?res (read))
    (assert (Gusta_check ?tema ?res ?pregunta))
  )

  ; Comprobamos que se ha dado una respuesta valida, si no se vuelve a preguntar
  (defrule Chequear_SI_NO_NoSimbolo
    (declare (salience 1))
    (ModActivo HacerPreguntas)
    ?f <- (Gusta_check ?tema ?res ?pregunta)
    (test (neq (type ?res) SYMBOL))
      =>
    (retract ?f)
    (printout t "Lo siento, no he entendido tu respuesta." crlf)
    (assert (PreguntaSINO ?tema ?pregunta))
  )

  ; Comprobamos que se ha dado una respuesta valida, si no se vuelve a preguntar
  (defrule Chequear_SI_NO_ResNoValida
    (declare (salience 1))
    (ModActivo HacerPreguntas)
    ?f <- (Gusta_check ?tema ?res ?pregunta)
    (test (eq (type ?res) SYMBOL))
    (test (and (neq (upcase ?res) SI) (neq (upcase ?res) NO) (neq (upcase ?res) NS) (neq (upcase ?res) STOP)))
      =>
    (retract ?f)
    (printout t "Lo siento, no he entendido tu respuesta." crlf)
    (assert (PreguntaSINO ?tema ?pregunta))
  )

  (defrule Respuesta_Upcase
    (ModActivo HacerPreguntas)
    ?f <- (Gusta_check ?tema ?res ?)
      =>
    (retract ?f)
    (assert (Gusta ?tema (upcase ?res)))
  )

  ; Si la respuesta es STOP, paramos y damos una respuesta
  (defrule Acabar_SI_NO
    ?f <- (Gusta ? STOP)
    ?g <- (ModActivo HacerPreguntas)
      =>
    (retract ?f)
    (retract ?g)
    (focus MCalcularRama)
    (assert (ModActivo CalcularRama))
  )

  ; ---------------------------------------------------------------------------
  ;                                NOTA_MEDIA
  ; ---------------------------------------------------------------------------

  ; Regla que se encarga de hacer la pregunta sobre la NotaMedia del estudiante
  ; Se representa por (Calificacion_media Alta|Media|Baja|NS)
  (defrule Preguntar_NotaMedia
    (ModActivo HacerPreguntas)
    ?f <- (PreguntaNotaMedia)
      =>
    (retract ?f)
    (printout t "Cual es tu nota media? (numero, Baja|Media|Alta o NS)" crlf)
    (bind ?calif (read))
    (assert (NotaMedia_check ?calif))
  )

  ; Si el usuario nos dice una nota media numerica comprobamos que
  ; esta entre los limites [0.0, 10.0], si no pregunta de nuevo
  (defrule Chequear_NotaMedia_Numero
    (declare (salience 1))
    (ModActivo HacerPreguntas)
    ?f <- (NotaMedia_check ?calif)
    (test (or (eq (type ?calif) FLOAT) (eq (type ?calif) INTEGER)))
    (test (or (> ?calif 10.0) (< ?calif 0.0)))
      =>
    (retract ?f)
    (printout t "Perdon, pero esa nota media no es valida." crlf)
    (assert (PreguntaNotaMedia))
  )

  ; Comprobamos si la nota media no numerica esta en alguna de las
  ; opciones (BAJO | MEDIO | ALTO | NS | STOP), si no pregunta de nuevo
  (defrule Chequear_NotaMedia_Symbol
    (declare (salience 1))
    (ModActivo HacerPreguntas)
    ?f <- (NotaMedia_check ?calif)
    (test (eq (type ?calif) SYMBOL))
    (test (and (neq (upcase ?calif) BAJA) (neq (upcase ?calif) MEDIA) (neq (upcase ?calif) ALTA) (neq (upcase ?calif) NS) (neq (upcase ?calif) STOP)))
      =>
    (retract ?f)
    (printout t "Perdon, pero no he entenido la nota media que me has dicho." crlf)
    (assert (PreguntaNotaMedia))
  )

  (defrule Converitr_NotaMedia_Caps
    (ModActivo HacerPreguntas)
    ?f <- (NotaMedia_check ?calif)
    (test (eq (type ?calif) SYMBOL))
      =>
    (retract ?f)
    (assert (NotaMedia (upcase ?calif)))
  )

  ; Convertimos la nota media [0.0, 6.0] a Baja
  (defrule Convertir_NotaMedia_Numerica_Baja
    (ModActivo HacerPreguntas)
    ?f <- (NotaMedia_check ?calif)
    (test (or (eq (type ?calif) FLOAT) (eq (type ?calif) INTEGER)))
    (test (<= ?calif 6.0))
      =>
    (retract ?f)
    (assert (NotaMedia BAJA))
  )

  ; Convertimos la nota media (6.0, 7.5] a Media
  (defrule Convertir_NotaMedia_Numerica_Media
    (ModActivo HacerPreguntas)
    ?f <- (NotaMedia_check ?calif)
    (test (or (eq (type ?calif) FLOAT) (eq (type ?calif) INTEGER)))
    (test (and (> ?calif 6.0) (<= ?calif 7.5)))
      =>
    (retract ?f)
    (assert (NotaMedia MEDIA))
  )

  ; Convertimos la nota media (7.5, 10.0] a Alta
  (defrule Convertir_NotaMedia_Numerica_Alta
    (ModActivo HacerPreguntas)
    ?f <- (NotaMedia_check ?calif)
    (test (or (eq (type ?calif) FLOAT) (eq (type ?calif) INTEGER)))
    (test (>= ?calif 7.5))
      =>
    (retract ?f)
    (assert (NotaMedia ALTA))
  )

  ; Si el usuario hace STOP
  (defrule Acabar_NotaMedia
    ?f <- (NotaMedia STOP)
    ?g <- (ModActivo HacerPreguntas)
      =>
    (retract ?f)
    (retract ?g)
    (focus MCalcularRama)
    (assert (ModActivo CalcularRama))
  )

  ; ---------------------------------------------------------------------------
  ;                                Sin preguntas
  ; ---------------------------------------------------------------------------

  ; Si hemos hecho todas las preguntas pasamos a calcular la rama
  (defrule SinPreguntas
    (not (exists (PreguntaSINO $?)))
    (not (exists (PreguntaNotaMedia $?)))
    ?g <- (ModActivo HacerPreguntas)
      =>
    (focus MCalcularRama)
    (retract ?g)
    (assert (ModActivo CalcularRama))
  )

; ---------------------------------------------------------------------------
; Modulo correspondiente a la parte de tomar en consideracion las respuestas
; del usuario y aconsejar sobre la rama que deberia coger
; ---------------------------------------------------------------------------

(defmodule MCalcularRama (export ?ALL) (import MHacerPreguntas ?ALL))

  ; Si alguien le gusta el Hardware, indiferente de lo demas, deberia tomar IC
  (defrule GustaHardware
    (ModActivo CalcularRama)
    (Gusta Hardware SI)
      =>
    (assert (Consejo "IC" "Te recomiendo IC ya que hardware no le suele encantar a nadie, y puedes meterte mas en profundidad de lo poco que se ve en la carrera." "Mike"))
    (assert (Aviso "IC"))
  )

  ; Si a alguien le gusta las Matematicas y no el Hardware recomiendo que tome CSI
  (defrule GustaMatematicas
    (ModActivo CalcularRama)
    (Gusta Matematicas SI)
    (not (exists (Gusta Hardware SI)))
      =>
    (assert (Consejo "CSI" "Te aconsejo CSI porque no a mucha gente le gustan las matematicas y en esta rama es donde se usan mas, tienes muchisimas aplicaciones y salidas laborales." "Mike"))
    (assert (Aviso "CSI"))
  )

  ; Si le gusta Bigdata (y no mates / hardware) y t recomiendo SI
  (defrule GustaBigdata
    (ModActivo CalcularRama)
    (Gusta BigData SI)
    (not (exists (Gusta Matematicas SI)))
    (not (exists (Gusta Hardware SI)))
      =>
    (assert (Consejo "SI" "La rama SI es una muy buena opcion para ti, ya que tienes mucho analisis de datos que no se ven en las ramas troncales y actualmente con muchas salidas." "Mike"))
  )

  ; Si le gusta Software (y no mates / hardware /bigdata) recomiendo IS
  (defrule GustaSoftware
    (ModActivo CalcularRama)
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
    (ModActivo CalcularRama)
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
    (ModActivo CalcularRama)
    (exists (Gusta ? NO))
    (not (exists (Gusta ? SI)))
    (not (exists (NotaMedia $?)))
      =>
    (assert (Consejo "IS" "Con lo que me has dicho te tengo que recomendar IS, que es la rama generica de informatica, aunque no te guste programar, por defecto te puede valer luego para cualquier trabajo de informatico." "Mike"))
  )

  ; Basamos la decision solo con la nota (baja)
  (defrule SoloNotas_Baja
    (ModActivo CalcularRama)
    (not (exists (Gusta ? SI)))
    (NotaMedia ?calif & BAJA)
      =>
    (assert (Consejo "TI" "Tienes la nota baja por lo que una rama como TI, que tiene cosas faciles con paginas web que no requieren mucha complicacion te puede ir bien." "Mike"))
    (assert (Consejo "SI" "Tambian te vale SI si le pones requiera un poco mas de esfuerzo, ya que en cuestion de analisis de datos es un poco mas dura." "Mike"))
  )

  ; Basamos la decision solo con la nota (media)
  (defrule SoloNotas_Media
    (ModActivo CalcularRama)
    (not (exists (Gusta ? SI)))
    (NotaMedia ?calif & MEDIA)
      =>
    (assert (Consejo "IS" "Por tu nota media creo que te puede valer una rama de dificultad media como lo es IS, donde se tienen asignaturas mas de programar software." "Mike"))
    (assert (Consejo "SI" "Tambien te vale SI por tener la ciencia de datos, que requiere algo de esfuerzo pero relativamente." "Mike"))
    (assert (Consejo "IC" "Finalmente, si te interesa algo el hardware puedes intentar hacer IC tambien, aunque solo si tienes algo de interes." "Mike"))
  )

  ; Basamos la decision solo con la nota (alta)
  (defrule SoloNotas_Alta
    (ModActivo CalcularRama)
    (not (exists (Gusta ? SI)))
    (NotaMedia ?calif & ALTA)
      =>
    (assert (Consejo "CSI" "Debido a tu gran media te aconsejo que vayas a por CSI, ya que es una rama que requiere mucho trabajo y entendimiento con temas dificiles donde hay matematicas." "Mike"))
  )

  ; Añade un aviso si se tiene la nota media baja
  (defrule Aviso
    (ModActivo CalcularRama)
    ?f <- (Aviso ?rama)
    ?g <- (Consejo ?rama ?motivo ?autor)
    (NotaMedia ?calif & BAJA)
      =>
    (retract ?f)
    (retract ?g)
    (assert (Consejo ?rama (str-cat ?motivo " Aunque te advierto que igual tienes que esforzarte un poco mas dada tu nota media baja." ) ?autor))
  )

  ; Si el usuario no ha respondido nada, recomendamos IS ya que es un tema que gusta en general
  (defrule SinRespuestas
    (declare (salience -2))
    (ModActivo CalcularRama)
    (not (exists (Consejo)))
      =>
    (assert (Consejo "IS" "No puedo decirte mucho puesto que no me has respondido a nada, te recomiendo IS por ejemplo puesto que programar software va con la linea general del grado y por lo que suelen hacer el grado los estudiantes, pero realmente puedes escoger cualquiera." "Mike"))
  )

  ; Una vez se hayan calculado las ramas, se coge el nombre del experto y se cambia al
  ; modulo de dar los consejos calculados
  (defrule RamaCalculada
    (declare (salience -1))
    ?f <- (ModActivo CalcularRama)
    (Consejo ? ? ?experto)
      =>
    (focus MRespuestaRama)
    (retract ?f)
    (assert (Experto ?experto))
    (assert (ModActivo RespuestaRama))
  )

; ---------------------------------------------------------------------------
; Modulo correspondiente a la parte de tomar en consideracion las respuestas
; del usuario y aconsejar sobre la rama que deberia coger
; ---------------------------------------------------------------------------

(defmodule MRespuestaRama (import MCalcularRama ?ALL))

  ; Mensaje inicial para dar respuesta
  (defrule RespuestaExperto
    (declare (salience 9999))
    (ModActivo RespuestaRama)
    (Experto ?experto)
      =>
    (printout t "" crlf)
    (printout t "Segun las recomendaciones del experto " ?experto ", te aconsejamos lo siguiente: " crlf)
  )

  ; Imprime consejo
  (defrule ImprimeConsejo
    (ModActivo RespuestaRama)
    (Consejo ?rama ?motivo ?)
      =>
    (printout t " -" ?rama ": " ?motivo  crlf)
  )
