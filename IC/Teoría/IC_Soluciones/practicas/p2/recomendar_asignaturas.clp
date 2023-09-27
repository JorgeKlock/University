; Archivo: recomendar_asignaturas.clp
; Autor: Miguel Lentisco Ballesteros
; Implementa el sistema que se encarga de recomendar asignaturas

; ---------------------------------------------------------------------------------------------
;                                          Módulo MMenuRA
; ---------------------------------------------------------------------------------------------
; Módulo para el menú de recomendar asignaturas
; Funciones básicas para el menú y los hechos con la información relevante

; Clase que representa una Asignatura
(deftemplate Asignatura
  ; ID de la asignatura: generalmente tomamos la abreviatura
  (slot ID
    (type SYMBOL))
  ; Nombre de la asignatura
  (slot Nombre
    (type STRING))
  ; Curso de la asignatura: de 1 a 4
  (slot Curso
    (type INTEGER)
    (range 1 4))
  ; Cuatrimestre de la asignatura: 1 o 2
  (slot Cuatrimestre
    (type INTEGER)
    (range 1 2))
  ; Nº de creditos de la asignatura: la mayoría dan 6, asi que se pone por defecto
  ; Además restringimos al nº máximo de créditos posible (18) y mínimo (1)
  (slot Creditos
    (type INTEGER)
    (range 1 18)
    (default 6))
  ; La rama de la asignatura: si es para todos se toma Comun
  ; Por defecto se toma Comun
  (slot Rama
    (type SYMBOL)
    (allowed-values CSI IC IS SI TI Comun)
    (default Comun))
  ; Dificultad de la asignatura: 1 (facil), 2 (media), 3 (dificil), por defecto 2
  (slot Dificultad
    (type INTEGER)
    (range 1 3)
    (default 2))
  ; Carga de trabajo de la asignatura: 1 (poco), 2 (medio), 3 (mucho), por defecto 2
  (slot Carga
    (type INTEGER)
    (range 1 3)
    (default 2))
  ; Tipo de asignatura: obligatoria u optativa, por defecto es obligatoria
  (slot Tipo
    (type SYMBOL)
    (allowed-values Obligatoria Optativa)
    (default Obligatoria))
  ; Temas principales dados en la asignatura: Software (S), Hardware (H), Web (W), Bases de Datos (BD),
  ; Redes (R), Ciencia de Datos (CD), Inteligencia Artifical (IA), Gráficos (G), Empresa (E)
  (multislot Temas
    (type SYMBOL)
    (allowed-values S H W BD R CD IA G E))
)

; Lista de asignaturas de la BBDD
(deffacts ListaAsignaturas
  ; 1º Primer cuatri
  (Asignatura (ID FP)
    (Nombre "Fundamentos de la Programacion")
    (Curso 1)
    (Cuatrimestre 1)
    (Temas S)
    (Dificultad 2)
    (Carga 2))

  (Asignatura (ID FFT)
    (Nombre "Fundamentos Fisicos y Tecnologicos")
    (Curso 1)
    (Cuatrimestre 1)
    (Temas H)
    (Dificultad 3)
    (Carga 3))

  ; 1ª Segundo cuatri
  (Asignatura (ID TOC)
    (Nombre "Tecnologia y Organizacion de Computadores")
    (Curso 1)
    (Cuatrimestre 2)
    (Temas H)
    (Dificultad 1)
    (Carga 2))

  (Asignatura (ID IES)
    (Nombre "Ingenieria, Empresa y Sociedad")
    (Curso 1)
    (Cuatrimestre 2)
    (Temas E)
    (Dificultad 1)
    (Carga 1))

  ; 2º Primer cuatri
  (Asignatura (ID SCD)
    (Nombre "Sistemas Concurrentes y Distribuidos")
    (Curso 2)
    (Cuatrimestre 1)
    (Temas S)
    (Dificultad 1)
    (Carga 2))

  (Asignatura (ID ED)
    (Nombre "Estructura de Datos")
    (Curso 2)
    (Cuatrimestre 1)
    (Temas S)
    (Dificultad 3)
    (Carga 2))

  ; 2º Segundo cuatri
  (Asignatura (ID FBD)
    (Nombre "Fundamentos de Bases de Datos")
    (Curso 2)
    (Cuatrimestre 2)
    (Temas BD)
    (Dificultad 2)
    (Carga 2))

  (Asignatura (ID IA)
    (Nombre "Inteligencia Artificial")
    (Curso 2)
    (Cuatrimestre 2)
    (Temas IA)
    (Dificultad 2)
    (Carga 3))

  ; 3º Primer cuatri
  (Asignatura (ID IG)
    (Nombre "Informatica Grafica")
    (Curso 3)
    (Cuatrimestre 1)
    (Temas G)
    (Dificultad 3)
    (Carga 3))

  (Asignatura (ID FR)
    (Nombre "Fundamentos de Redes")
    (Curso 3)
    (Cuatrimestre 1)
    (Temas R)
    (Dificultad 3)
    (Carga 2))

  ; 3º Segundo cuatri - CSI
  (Asignatura (ID TSI)
    (Nombre "Tecnicas de los Sistemas Inteligentes")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama CSI)
    (Temas IA S)
    (Dificultad 2)
    (Carga 3))

  (Asignatura
    (ID AA)
    (Nombre "Aprendizaje Automatico")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama CSI)
    (Temas IA CD)
    (Dificultad 3)
    (Carga 3))

  (Asignatura
    (ID IC)
    (Nombre "Ingenieria del Conocimiento")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama CSI)
    (Temas IA S)
    (Dificultad 2)
    (Carga 2))

  (Asignatura
    (ID MH)
    (Nombre "MetaHeuristicas")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama CSI)
    (Temas IA CD)
    (Dificultad 1)
    (Carga 3))

  (Asignatura
    (ID MAC)
    (Nombre "Modelos Avanzados de Computacion")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama CSI)
    (Temas IA)
    (Dificultad 3)
    (Carga 2))

  ; 3º Segundo cuatri - IS
  (Asignatura
    (ID DSD)
    (Nombre "Desarollo de Sistemas Distribuidos")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama IS)
    (Temas S H))

  (Asignatura
    (ID DS)
    (Nombre "Desarollo de Software")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama IS)
    (Temas S))

  (Asignatura
    (ID DIU)
    (Nombre "Disenio de Interfaces de Usuario")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama IS)
    (Temas S G))

  (Asignatura
    (ID SIBW)
    (Nombre "Sistemas de Informacion Basados en Web")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama IS)
    (Temas BD W))

  (Asignatura
    (ID SG)
    (Nombre "Sistemas Graficos")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama IS)
    (Temas S G))

  ; 3º Segundo cuatri - IC
  (Asignatura
    (ID AS)
    (Nombre "Arquitectura de Sistemas")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama IC)
    (Temas H))

  (Asignatura
    (ID ACAP)
    (Nombre "Arquitectura y Computacion de Altas Prestaciones")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama IC)
    (Temas H))

  (Asignatura
    (ID DHD)
    (Nombre "Desarrollo de Hardware Digital")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama IC)
    (Temas H S))

  (Asignatura
    (ID DSE)
    (Nombre "Disenio de Sistemas Electronicos")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama IC)
    (Temas H))

  (Asignatura
    (ID SMP)
    (Nombre "Sistemas con MicroProcesadores")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama IC)
    (Temas H))

  ; 3º Segundo cuatri - SI
  (Asignatura
    (ID ABD)
    (Nombre "Administracion de Bases de Datos")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama SI)
    (Temas BD S))

  (Asignatura
    (ID ISI)
    (Nombre "Ingenieria de Sistemas de Informacion")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama SI)
    (Temas S BD))

  (Asignatura
    (ID PW)
    (Nombre "Programacion Web")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama SI)
    (Temas W S)
    (Dificultad 1)
    (Carga 2))

  (Asignatura
    (ID SIE)
    (Nombre "Sistemas de Informacion para Empresas")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama SI)
    (Temas BD E))

  (Asignatura
    (ID SMD)
    (Nombre "Sistemas MultiDimensionales")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama SI)
    (Temas S H))

  ; 3º Segundo cuatri - TI
  (Asignatura
    (ID TDRC)
    (Nombre "Transmision de Datos y Redes de Computadores")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama TI)
    (Temas R H))

  (Asignatura
    (ID SWAP)
    (Nombre "Servidores Web de Altas Prestaciones")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama TI)
    (Temas R W))

  (Asignatura
    (ID TW)
    (Nombre "Tecnologias Web")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama TI)
    (Temas W))

  (Asignatura
    (ID SMM)
    (Nombre "Sistemas MultiMedia")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama TI)
    (Temas G S))

  (Asignatura
    (ID CUIA)
    (Nombre "Computacion Ubicua e Inteligencia Ambiental")
    (Curso 3)
    (Cuatrimestre 2)
    (Rama TI)
    (Temas S H IA))

  ; 4º Primer cuatri - CSI
  (Asignatura
    (ID VC)
    (Nombre "Vision por Computador")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama CSI)
    (Temas CD IA)
    (Dificultad 3)
    (Carga 3))

  (Asignatura
    (ID NPI)
    (Nombre "Nuevos Paradigmas de Interaccion")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama CSI)
    (Temas S G)
    (Dificultad 1)
    (Carga 3))

  (Asignatura
    (ID PL)
    (Nombre "Procesadores de Lenguajes")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama CSI)
    (Temas IA S)
    (Dificultad 1)
    (Carga 2))

  (Asignatura
    (ID TIC)
    (Nombre "Teoria de la Informacion y la Codificacion")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama CSI)
    (Temas IA))

  (Asignatura
    (ID SS)
    (Nombre "Simulacion de Sistemas")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama CSI)
    (Temas IA S))

  (Asignatura
    (ID PTC)
    (Nombre "Programacion Tecnica y Cientifica")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama CSI)
    (Temas IA S))

  ; 4º Primer cuatri - IS
  (Asignatura
    (ID MDA)
    (Nombre "Metodologias de Desarrollo Agil")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama IS))

  (Asignatura
    (ID DBA)
    (Nombre "Desarrollo Basado en Agentes")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama IS))

  (Asignatura
    (ID DGP)
    (Nombre "Direccion y Gestion de Proyectos")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama IS)
    (Temas E))

  (Asignatura
    (ID PGV)
    (Nombre "Programacion Grafica de Videojuegos")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama IS)
    (Temas G))

  (Asignatura
    (ID SSO)
    (Nombre "Seguridad en Sistemas Operativos")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama IS)
    (Temas S))

  (Asignatura
    (ID LP)
    (Nombre "Logica y Programacion")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama IS)
    (Temas S))

  ; 4º Primer cuatri - IC
  (Asignatura
    (ID SE)
    (Nombre "Sistemas Empotrados")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama IC)
    (Temas H))

  (Asignatura
    (ID TR)
    (Nombre "Tecnologias de Red")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama IC)
    (Temas R))

  (Asignatura
    (ID CPD)
    (Nombre "Centros de Procesamiento de Datos")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama IC)
    (Temas BD))

  (Asignatura
    (ID II)
    (Nombre "Informatica Industrial")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama IC)
    (Temas H))

  (Asignatura
    (ID TE)
    (Nombre "Tecnologias Emergentes")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama IC)
    (Temas H))

  ; 4º Primer cuatri - SI
  (Asignatura
    (ID IN)
    (Nombre "Inteligencia del Negocio")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama SI)
    (Temas CD))

  (Asignatura
    (ID BDD)
    (Nombre "Bases de Datos Distribuidas")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama SI)
    (Temas BD))

  (Asignatura
    (ID RI)
    (Nombre "Recuperacion de Informacion")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama SI)
    (Temas S))

  (Asignatura
    (ID SIG)
    (Nombre "Sistemas de Informacion Geograficos")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama SI)
    (Temas S))

  (Asignatura
    (ID GRD)
    (Nombre "Gestion de Recursos Digitales")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama SI)
    (Temas G))

  (Asignatura
    (ID RSC)
    (Nombre "Redes y Sistemas Complejos")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama SI)
    (Temas R))

  ; 4º Primer cuatri - TI
  (Asignatura
    (ID DAI)
    (Nombre "Desarrollo de Aplicaciones para Internet")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama TI)
    (Temas W))

  (Asignatura
    (ID IV)
    (Nombre "Infraestructura Virtual")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama TI)
    (Temas W G))

  (Asignatura
    (ID SPSI)
    (Nombre "Seguridad y Proteccion de Sistemas Informaticos")
    (Curso 4)
    (Cuatrimestre 1)
    (Rama TI)
    (Temas S IA))

  (Asignatura
    (ID TID)
    (Nombre "Tratamiento de Imagenes Digitales")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama TI)
    (Temas G))

  (Asignatura
    (ID CRIM)
    (Nombre "Compresion y Recuperacion de Informacion Multimedia")
    (Curso 4)
    (Cuatrimestre 1)
    (Tipo Optativa)
    (Rama TI)
    (Temas G))

  ; 4º Segundo cuatri - Común
  (Asignatura
    (ID EISI)
    (Nombre "Etica, Informatica y Sociedad de la Informacion")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Temas E))

  (Asignatura
    (ID CEGE)
    (Nombre "Creacion de Empresas y Gestion Emprendedora")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Temas E))

  (Asignatura
    (ID DI)
    (Nombre "Derecho Informatico")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Temas E))

  ; 4º Segundo cuatri - CSI
  (Asignatura
    (ID PLD)
    (Nombre "Programacion Ludica")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama CSI)
    (Temas S G))

  (Asignatura
    (ID CRIP)
    (Nombre "CRIPtografia y computacion")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama CSI)
    (Temas IA H))

  (Asignatura
    (ID RI)
    (Nombre "Robotica Industrial")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama CSI)
    (Temas IA H))

  ; 4º Segundo cuatri - IS
  (Asignatura
    (ID AO)
    (Nombre "Animacion por Ordenador")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama IS)
    (Temas G))

  (Asignatura
    (ID PPR)
    (Nombre "Programaciones PaRalelas")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama IS)
    (Temas S))

  (Asignatura
    (ID NTP)
    (Nombre "Nuevas Tecnologias de la Programacion")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama IS)
    (Temas S))

  ; 4º Segundo cuatri - IC
  (Asignatura
    (ID CII)
    (Nombre "Circuitos Integrados e Impresos")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama IC)
    (Temas H))

  (Asignatura
    (ID MEI)
    (Nombre "Mantenimiento de Equipos Informaticos")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama IC)
    (Temas H))

  ; 4º Segundo cuatri - SI
  (Asignatura
    (ID SCGC)
    (Nombre "Sistemas Cooperativos y Gestion de Contenidos")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama SI)
    (Temas H BD))

  (Asignatura
    (ID PDIH)
    (Nombre "Perifericos y Dispositivos de Interfaz Humana")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama SI)
    (Temas S G))

  ; 4º Segundo cuatri - TI
  (Asignatura
    (ID PDM)
    (Nombre "Programacion de Dispositivos Moviles")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama TI)
    (Temas S G))

  (Asignatura
    (ID PDS)
    (Nombre "Procesamiento Digital de Seniales")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama TI)
    (Temas R H))

  (Asignatura
    (ID RMS)
    (Nombre "Redes MultiServicio")
    (Curso 4)
    (Cuatrimestre 2)
    (Tipo Optativa)
    (Rama TI)
    (Temas R))
)

; Hechos para el menu
(deffacts HechosMenu
  (OpcionesRA a b c d)
  (ActivarRA a MListarRA ListarAsignaturas)
  (ActivarRA b MPreguntarRA HacerPreguntasAsignaturas)
  (ActivarRA c MMenu MostrarMenu)
)

; Mostramos el menú inicial
(defrule MostrarMenu
  (MActual MMenuRA)
  ?f <- (Comando MostrarMenu)
    =>
  ; Mostramos menú
  (printout t crlf "Recomendador Asignaturas 2000: " crlf)
  (printout t " [a] Listar las asignaturas cargadas en la BBDD." crlf)
  (printout t " [b] Iniciar el recomendador." crlf)
  (printout t " [c] Volver atras." crlf)
  (printout t " [d] Salir." crlf)
  (printout t "Opcion: " )
  ; Cogemos salida y transformamos a simbolo
  (assert (OpcionRA (lowcase (sym-cat (readline)))))
  (retract ?f)
)

; Comprueba que la opción sea correcta
(defrule ChequearOpcion
  (declare (salience 1))
  (MActual MMenuRA)
  ?f <- (OpcionRA ?opt)
  ; Si la opción no está entre las válidas
  (not (OpcionesRA $? ?opt $?))
    =>
  (retract ?f)
  (printout t "Opcion invalida." crlf)
  (assert (Comando MostrarMenu))
)

; Según la opción escogida se ejecuta el modulo correspondiente
(defrule EjecutarOpcion
  ?f1 <- (MActual MMenuRA)
  ; Opción y módulo
  ?f2 <- (OpcionRA ?opt)
  (ActivarRA ?opt ?modulo ?comando)
    =>
  ; Quitamos el modulo actual y pasamos al siguiente
  (retract ?f1 ?f2)
  (assert (MActual ?modulo))
  (assert (Comando ?comando))
)

; Salir del programa
(defrule Salir
  ?f1 <- (MActual MMenuRA)
  ?f2 <- (OpcionRA d)
    =>
  (retract ?f1 ?f2)
)

; Cuando de una opción volvemos al menú
(defrule VolverMenu
  ?f1 <- (Comando VolverMenu)
  ?f2 <- (MActual ?)
    =>
  (retract ?f1 ?f2)
  (assert (MActual MMenuRA))
  (assert (Comando MostrarMenu))
)

; ---------------------------------------------------------------------------------------------
;                                           Módulo MListarRA
; ---------------------------------------------------------------------------------------------
; Módulo correspondiente para listar las asignaturas en la BBDD

; Clase auxiliar para listar
(deftemplate Rama
  (slot ID
    (type SYMBOL)
    (allowed-values CSI IC IS SI TI Comun))
)

; Clase auxiliar para listar
(deftemplate Tipo
  (slot ID
    (type SYMBOL)
    (allowed-values Obligatoria Optativa))
)

; Hechos auxiliares para listar
(deffacts HechosAuxiliaresListar
  ; Ramas
  (Rama (ID Comun))
  (Rama (ID CSI))
  (Rama (ID IC))
  (Rama (ID IS))
  (Rama (ID SI))
  (Rama (ID TI))
  ; Tipo asignatura
  (Tipo (ID Obligatoria))
  (Tipo (ID Optativa))
)

; Lista todas las asignaturas que tenemos en la base de datos
(defrule ListarAsignaturas
  (MActual MListarRA)
  ?f <- (Comando ListarAsignaturas)
    =>
  (printout t "Lista de asignaturas: " crlf)
  ; Listamos 1º/2º sin ramas
  (loop-for-count (?curso 1 2) do
    (printout t "--Curso " ?curso "--" crlf)
    (loop-for-count (?cuatri 1 2) do
      (printout t " --Cuatrimestre " ?cuatri "--" crlf)
      (do-for-all-facts ((?asig Asignatura))
        (and (eq ?asig:Curso ?curso)
             (eq ?asig:Cuatrimestre ?cuatri)
        )
        (printout t " - " ?asig:ID ": " ?asig:Nombre crlf)
      )
      (printout t "Pulse ENTER para continuar." crlf)
      (readline)
    )
  )

  ; Listamos Primer Cuatrimestre de 3º sin ramas
  (printout t "--Curso 3--" crlf)
  (printout t " --Cuatrimestre 1--" crlf)
  (do-for-all-facts ((?asig Asignatura))
    (and (eq ?asig:Curso 3)
         (eq ?asig:Cuatrimestre 1)
    )
    (printout t " - " ?asig:ID ": " ?asig:Nombre crlf)
  )
  (printout t "Pulse ENTER para continuar." crlf)
  (readline)

  ; Listamos Segundo Cuatrimestre de 3º con ramas/tipo
  (printout t " --Cuatrimestre 2--" crlf)
  (do-for-all-facts ((?rama Rama))
    (printout t "  --" ?rama:ID "--" crlf)
    (do-for-all-facts ((?tipo Tipo))
      (printout t "  " ?tipo:ID ": " crlf)
      (do-for-all-facts ((?asig Asignatura))
        (and (eq ?asig:Rama ?rama:ID)
             (eq ?asig:Curso 3)
             (eq ?asig:Cuatrimestre 2)
             (eq ?asig:Tipo ?tipo:ID)
        )
        (printout t  "   - " ?asig:ID ": " ?asig:Nombre crlf)
      )
    )
  )
  (printout t "Pulse ENTER para continuar." crlf)
  (readline)

  ; Listamos 4º entero con ramas/tipo
  (printout t "--Curso 4--" crlf)
  (loop-for-count (?cuatri 1 2) do
    (printout t " --Cuatrimestre " ?cuatri "--" crlf)
    (do-for-all-facts ((?rama Rama))
      (printout t "  --" ?rama:ID "--" crlf)
      (do-for-all-facts ((?tipo Tipo))
        (printout t "  " ?tipo:ID ": " crlf)
        (do-for-all-facts ((?asig Asignatura))
          (and (eq ?asig:Rama ?rama:ID)
               (eq ?asig:Curso 4)
               (eq ?asig:Cuatrimestre ?cuatri)
               (eq ?asig:Tipo ?tipo:ID)
          )
          (printout t  "   - " ?asig:ID ": " ?asig:Nombre crlf)
        )
      )
    )
    (printout t "Pulse ENTER para continuar." crlf)
    (readline)
  )

  ; Volvemos al modulo menú
  (assert (Comando VolverMenu))
  (retract ?f)
)

; ---------------------------------------------------------------------------------------------
;                                 Módulo MPreguntarRA
; ---------------------------------------------------------------------------------------------
; Módulo que se encarga de recopilar información del usuario para recomendar las asignaturas

; Clase para encapsular la información introducida por el usuaruio
(deftemplate Usuario
  ; Lista de asignaturas que necesita recomendación
  (multislot Asignaturas
    (type SYMBOL)
  )

  ; Nº de créditos para matricularse
  (slot Creditos
    (type INTEGER)
  )

  ; Mención del usuario (si es Comun se interpreta que no tiene)
  ; Por defecto tomamos Comun
  (multislot Mencion
    (type SYMBOL)
    (default Comun defecto)
  )

  ; Nota media del usuario, tomamos 1 (Baja), 2 (Media), 3 (Alta), por defecto es 2
  (multislot NotaMedia
    (default 2 defecto)
  )

  ; Ganas de trabajar del usuario, tomamos 1 (Baja), 2 (Media), 3 (Alta), por defecto es 2
  (multislot CargaTrabajo
    (default 2 defecto)
  )

  ; Intereses del usuario: Software (S), Hardware (H), Web (W), Bases de Datos (BD),
  ; Redes (R), Ciencia de Datos (CD), Inteligencia Artifical (IA), Gráficos (G). Empresa (E)
  ; Por defecto vendrá dado según la mención que se tenga.
  (multislot Intereses)
)

; Hechos auxuliares para el módulo
(deffacts HechosAuxiliaresPreguntar
  ; Intereses temáticos
  (Interes S H W BD R CD IA G E)
  ; Intereses por defecto según mención
  (InteresesDefecto Comun S G IA)
  (InteresesDefecto CSI CD IA S)
  (InteresesDefecto IS S G IA)
  (InteresesDefecto IC H R)
  (InteresesDefecto SI CD BD W)
  (InteresesDefecto TI W R BD)
  ; Nota media / carga categorica a discreta
  (VarCategorica BAJA 1)
  (VarCategorica MEDIA 2)
  (VarCategorica ALTA 3)
  ; Nota media continua a discreta
  (VarNumerica NotaMedia 0 6 1)
  (VarNumerica NotaMedia 6 7.5 2)
  (VarNumerica NotaMedia 7.5 10.1 3)
  ; Ganas trabajar a discreta
  (VarNumerica CargaTrabajo 0 2.5 1)
  (VarNumerica CargaTrabajo 2.5 3.5 2)
  (VarNumerica CargaTrabajo 3.5 5.1 3)
)

; Mensaje de inicio
(defrule RecomendadorAsignaturas
  (MActual MPreguntarRA)
  ?f <- (Comando HacerPreguntasAsignaturas)
    =>
  (printout t crlf "Muy buenas, soy un sistema programado con el proposito de ayudarte a decidirte por esas asignaturas que no tienes claro que hacer. No te preocupes, que estoy aqui para eso!" crlf "Para ello, te voy a hacer una serie de cuestiones para obtener informacion para un buena recomendacion." crlf)
  (retract ?f)
  ; Lista de preguntas
  (assert (Preguntar ListaAsignaturas))
  (assert (Preguntar Creditos))
  (assert (Preguntar NotaMedia))
  (assert (Preguntar CargaTrabajo))
  (assert (Preguntar Mencion))
  ; Información sobre el usuario
  (assert (Usuario))
)

; Cuando salimos del recomendador, limpiamos todas los inicios de pregunta
(defrule SalidaRecomendadorPreguntas
  (declare (salience 1))
  (MActual MPreguntarRA)
  (Comando VolverMenu)
  ?f <- (Preguntar ?)
    =>
  (retract ?f)
)

; Cuando salimos del recomendador, borramos toda la información del usuario
(defrule SalidaRecomendadorUsuario
  (declare (salience 1))
  (MActual MPreguntarRA)
  (Comando VolverMenu)
  ?f <- (Usuario)
    =>
  (retract ?f)
)

; Pedimos la lista de asignaturas que el usuario duda
(defrule PreguntaListaAsignaturas
  (MActual MPreguntarRA)
  ?f <- (Preguntar ListaAsignaturas)
    =>
  (printout t crlf "Escribeme, separados por espacios, las siglas de las asignaturas. Puedes volver escribiendo STOP, y consultar la lista de mi BBDD." crlf)
  (printout t crlf "Asignaturas: ")
  ; Leemos la lista
  (bind ?asigs (explode$ (upcase (readline))))
  (retract ?f)
  (assert (Asignaturas ?asigs))
)

; Si tiene STOP paramos y volvemos al menú anterior
(defrule ParadaListaAsignaturas
  (declare (salience 2))
  (MActual MPreguntarRA)
  ; Tiene STOP en alguna
  ?f <- (Asignaturas $? STOP $?)
    =>
  (printout t "Volviendo al menu..." crlf)
  (assert (Comando VolverMenu))
  (retract ?f)
)

; Si alguna asignatura no está en la BBDD avisamos y paramos
(defrule ChequearAsignaturas
  (declare (salience 1))
  (MActual MPreguntarRA)
  ?f <- (Asignaturas $? ?asig $?)
  ; Si no existe ninguna asignatura con esas siglas
  (not (Asignatura (ID ?asig)))
    =>
  (printout t "Error: Asignatura " ?asig " no reconocida." crlf)
  (assert (Comando VolverMenu))
  (retract ?f)
)

; Eliminar asignaturas repetidas
(defrule EliminarAsignaturasRepetidas
  (declare (salience 1))
  (MActual MPreguntarRA)
  ; Asignatura repetida
  ?f <- (Asignaturas $?aux1 ?asig $?aux2 ?asig $?aux3)
    =>
  (retract ?f)
  (assert (Asignaturas $?aux1 ?asig $?aux2 $?aux3))
)

; Si la lista de asignaturas es vacía, paramos dando error
(defrule AsignaturasVacias
  (declare (salience 1))
  (MActual MPreguntarRA)
  ?f <- (Asignaturas)
    =>
  (printout t "Error: Lista de asignaturas vacia." crlf)
  (assert (Comando VolverMenu))
  (retract ?f)
)

; Si la lista de asignaturas es correcta se añade a la información
(defrule AsignaturasCorrecto
  (MActual MPreguntarRA)
  ?f1 <- (Asignaturas $?asigs)
  ?f2 <- (Usuario)
    =>
  (modify ?f2 (Asignaturas ?asigs))
  (retract ?f1)
)

; Pregunta por el nº de créditos
(defrule PreguntarCreditos
  (MActual MPreguntarRA)
  ?f <- (Preguntar Creditos)
    =>
  (printout t crlf "Dime cuantos creditos quieres matricularte: ")
  (assert (Creditos (string-to-field (readline))))
  (retract ?f)
)

; Comprueba que el nº de creditos es entero
(defrule ComprobarCreditosEntero
  (MActual MPreguntarRA)
  ?f <- (Creditos ?cred)
  (not (test (integerp ?cred)))
    =>
  (printout t crlf "Error: " ?cred " no es un numero entero." crlf)
  (retract ?f)
  (assert (Comando VolverMenu))
)

; Comprueba que el nº de creditos es positivo
(defrule ComprobarCreditosValido
  (MActual MPreguntarRA)
  ?f1 <- (Creditos ?cred)
  (test (integerp ?cred))
  ?f2 <- (Usuario)
    =>
  (retract ?f1)
  (if (<= ?cred 0) then
      (printout t crlf "Error: " ?cred "no es un entero positivo." crlf)
      (assert (Comando VolverMenu))
    else (modify ?f2 (Creditos ?cred))
  )
)

; Pregunta la mención del usuario, se puede no responder
(defrule PreguntarMencion
  (MActual MPreguntarRA)
  ?f <- (Preguntar Mencion)
    =>
  (printout t crlf "Dime cual es tu mencion (si no tienes o no quieres responder pulsa ENTER), por ej CSI: ")
  (bind ?mencion (explode$ (upcase (readline))))
  (assert (Mencion ?mencion))
  (retract ?f)
)

; Saltamos mención si no se introduce nada (sin mencion por defecto)
(defrule MencionVacia
  (declare (salience 2))
  (MActual MPreguntarRA)
  ?f <- (Mencion)
    =>
  (retract ?f)
  ; Informamos de la lógica por defecto
  (printout t "Tomamos la mencion Comun (sin mencion) por defecto, ya que la mayoria de estudiantes no tienen mencion." crlf)
  ; Ya podemos preguntar por los intereses
  (assert (Preguntar Intereses))
)

; Comprueba que la mención introducida es correcta
(defrule ComprobarMencion
  (declare (salience 1))
  (MActual MPreguntarRA)
  ?f <- (Mencion ?mencion)
  ; No existe esa mencion
  (not (Rama (ID ?mencion)))
    =>
  (printout t crlf "Error: Mencion " ?mencion " no reconocida." crlf)
  (retract ?f)
  (assert (Comando VolverMenu))
)

; Mención correcta
(defrule MencionCorrecta
  (MActual MPreguntarRA)
  ?f1 <- (Mencion ?mencion)
  ?f2 <- (Usuario)
    =>
  ; Actualizamos mención (defecto a seguro)
  (retract ?f1)
  (modify ?f2 (Mencion ?mencion seguro))
  ; Informamos de que estamos seguros
  (printout t "Retractamos la mencion Comun (sin mencion) por defecto, ya que el usuario tiene mencion en " ?mencion "." crlf)
  ; Ya podemos preguntar por los intereses
  (assert (Preguntar Intereses))
)

; Preguntar por la nota media del usuario
(defrule PreguntarNotaMedia
  (MActual MPreguntarRA)
  ?f <- (Preguntar NotaMedia)
    =>
  (printout t crlf "Dime tu nota media, numerica (1 a 10), o BAJA, MEDIA, ALTA (ENTER para saltar): ")
  (bind ?nota (string-to-field (implode$ (explode$ (upcase (readline))))))
  (assert (NotaMedia ?nota))
  (retract ?f)
)

; Si saltamos la pregunta de nota media (por defecto media)
(defrule NotaVacia
  (declare (salience 2))
  (MActual MPreguntarRA)
  ?f <- (NotaMedia EOF)
    =>
  (retract ?f)
  ; Informamos de la lógica por defecto
  (printout t "Tomamos la nota media MEDIA (2) por defecto, ya que la mayoria de estudiantes tienen esta media." crlf)
)

; Comprobamos que la nota media numerica está en [0, 10]
(defrule ComprobarNotaNumerica
  (declare (salience 1))
  (MActual MPreguntarRA)
  ?f <- (NotaMedia ?nota)
  (test (numberp ?nota))
  (or (test (> ?nota 10))
      (test (< ?nota 0))
  )
    =>
  (printout t crlf "Error: nota media (numerica) " ?nota " no valida." crlf)
  (retract ?f)
  (assert (Comando VolverMenu))
)

; Comprobamos que la nota media categórica es una de las válidas
(defrule ComprobarNotaCategorica
  (declare (salience 1))
  (MActual MPreguntarRA)
  ?f <- (NotaMedia ?nota)
  (not (test (numberp ?nota)))
  (not (VarCategorica ?nota ?))
    =>
  (printout t crlf "Error: nota media (categorica) " ?nota " no valida." crlf)
  (retract ?f)
  (assert (Comando VolverMenu))
)

; Transformación nota categorica a numerica
(defrule TransformarNotaCategorica
  (MActual MPreguntarRA)
  ?f1 <- (NotaMedia ?nota)
  ?f2 <- (Usuario)
  (VarCategorica ?nota ?nueva_nota)
    =>
  (retract ?f1)
  (modify ?f2 (NotaMedia ?nueva_nota seguro))
  ; Informamos de que estamos seguros
  (printout t "Retractamos la nota media MEDIA por defecto, ya que el usuario tiene una nota " ?nota "." crlf)
)

; Transformación nota continua a discreta
(defrule TransformarNotaDecimal
  (MActual MPreguntarRA)
  ?f1 <- (NotaMedia ?nota)
  ?f2 <- (Usuario)
  (test (numberp ?nota))
  (VarNumerica NotaMedia ?lim_inf ?lim_sup ?nueva_nota)
  (and (test (>= ?nota ?lim_inf))
       (test (< ?nota ?lim_sup))
  )
    =>
  (retract ?f1)
  ; Informamos de que estamos seguros
  (printout t "Retractamos la nota media MEDIA por defecto, ya que el usuario tiene una nota de " ?nota "." crlf)
  (modify ?f2 (NotaMedia ?nueva_nota seguro))
)

; Preguntar por la carga de trabajo
(defrule PreguntarCargaTrabajo
  (MActual MPreguntarRA)
  ?f <- (Preguntar CargaTrabajo)
    =>
  (printout t crlf "Dime que carga de trabajo prefieres, numerica (de 1 a 5) o BAJA, MEDIA, ALTA (ENTER para saltar): ")
  (bind ?carga (string-to-field (implode$ (explode$ (upcase (readline))))))
  (assert (CargaTrabajo ?carga))
  (retract ?f)
)

; Si saltamos la pregunta de carga de trabajo (por defecto media)
(defrule CargaVacia
  (declare (salience 2))
  (MActual MPreguntarRA)
  ?f <- (CargaTrabajo EOF)
    =>
  ; Informamos de la lógica por defecto
  (printout t "Tomamos la ganas de trabajar como MEDIA (2) por defecto, ya que la mayoria de estudiantes tienen unas ganas intermedias de dedicar a una asignatura." crlf)
  (retract ?f)
)

; Comprobamos que la carga de trabajo numerica está en [0, 10]
(defrule ComprobarCargaNumerica
  (declare (salience 1))
  (MActual MPreguntarRA)
  ?f <- (CargaTrabajo ?carga)
  (test (numberp ?carga))
  (or (test (> ?carga 5))
      (test (< ?carga 0))
  )
    =>
  (printout t crlf "Error: carga de trabajo (numerica) " ?carga " no valida." crlf)
  (retract ?f)
  (assert (Comando VolverMenu))
)

; Comprobamos que la carga de trabajo categórica es una de las válidas
(defrule ComprobarCargaCategorica
  (declare (salience 1))
  (MActual MPreguntarRA)
  ?f <- (NotaMedia ?carga)
  (not (test (numberp ?carga)))
  (not (VarCategorica ?carga ?))
    =>
  (printout t crlf "Error: nota media (categorica) " ?carga " no valida." crlf)
  (retract ?f)
  (assert (Comando VolverMenu))
)

; Transformación carga de trabajo categorica a numerica
(defrule TransformarCargaCategorica
  (MActual MPreguntarRA)
  ?f1 <- (CargaTrabajo ?carga)
  ?f2 <- (Usuario)
  (VarCategorica ?carga ?nueva_carga)
    =>
  (retract ?f1)
  ; Informamos de que estamos seguros
  (printout t "Retractamos las ganas de trabajar MEDIA por defecto, ya que el usuario tiene unas ganas de trabajar " ?carga "." crlf)
  (modify ?f2 (CargaTrabajo ?nueva_carga seguro))
)

; Transformación carga de trabajo continua a discreta
(defrule TransformarCargaDecimal
  (MActual MPreguntarRA)
  ?f1 <- (CargaTrabajo ?carga)
  ?f2 <- (Usuario)
  (test (numberp ?carga))
  (VarNumerica CargaTrabajo ?lim_inf ?lim_sup ?carga_nueva)
  (and (test (>= ?carga ?lim_inf))
       (test (< ?carga ?lim_sup))
  )
    =>
  (retract ?f1)
  ; Informamos de que estamos seguros
  (printout t "Retractamos las ganas de trabajar MEDIA por defecto, ya que el usuario tiene unas ganas de trabajar de " ?carga "." crlf)
  (modify ?f2 (CargaTrabajo ?carga_nueva seguro))
)

; Preguntamos los intereses principales del usuario (por defecto se asignaran según la mención)
(defrule PreguntarIntereses
  (MActual MPreguntarRA)
  ?f <- (Preguntar Intereses)
    =>
  (printout t crlf "Escribeme, separados por espacios, las siglas de los intereses principales que mas te gusten. La lista es la siguiente:" crlf)
  (printout t " - [S] Software" crlf)
  (printout t " - [H] Hardware" crlf)
  (printout t " - [W] Web" crlf)
  (printout t " - [BD] Bases de Datos" crlf)
  (printout t " - [R] Redes" crlf)
  (printout t " - [CD] Ciencia de Datos" crlf)
  (printout t " - [IA] Inteligencia Artificial" crlf)
  (printout t " - [G] Graficos" crlf)
  (printout t " - [E] Empresa" crlf)
  (printout t crlf "Intereses (ENTER para omitir): ")
  ; Leemos la lista
  (bind ?intereses (explode$ (upcase (readline))))
  (retract ?f)
  (assert (Intereses ?intereses))
)

; Si algún interés no está en la BBDD avisamos y paramos
(defrule ChequearIntereses
  (declare (salience 1))
  (MActual MPreguntarRA)
  ?f <- (Intereses $? ?interes $?)
  ; Si no existe ninguna asignatura con esas siglas
  (not (Interes $? ?interes $?))
    =>
  (printout t "Error: Interes " ?interes " no reconocido." crlf)
  (assert (Comando VolverMenu))
  (retract ?f)
)

; Eliminamos intereses repetiods
(defrule EliminarInteresesRepetidos
  (declare (salience 1))
  (MActual MPreguntarRA)
  ?f <- (Intereses $?aux1 ?interes $?aux2 ?interes $?aux3)
    =>
  (retract ?f)
  (assert (Intereses $?aux1 ?interes $?aux2 $?aux3))
)

; Si la lista de asignaturas es vacia, inferimos por defecto según la mención
(defrule InteresesVacios
  (declare (salience 1))
  (MActual MPreguntarRA)
  ?f <- (Intereses)
    =>
  (assert (Comando InferirIntereses))
  (retract ?f)
)

; Inferimos los intereses según la mención del usuario (por defecto)
(defrule InferirIntereses
  (MActual MPreguntarRA)
  ?f1 <- (Comando InferirIntereses)
  ?f2 <- (Usuario (Mencion ?mencion ?))
  (InteresesDefecto ?mencion $?intereses)
    =>
  (retract ?f1)
  ; Informamos de la lógica por defecto
  (printout t "Tomamos los intereses " $?intereses " por defecto ya que la mayoria de estudiantes con mencion " ?mencion " tienen unos intereses afines a esta." crlf)
  (modify ?f2 (Intereses $?intereses defecto))
)

; Añadimos los interses del usuario (que son seguros)
(defrule InteresesCorrectos
  (MActual MPreguntarRA)
  ?f1 <- (Intereses $?intereses)
  ?f2 <- (Usuario (Mencion ?mencion ?))
  (InteresesDefecto ?mencion $?intereses2)
    =>
  (retract ?f1)
  ; Retractamos la logica
  (printout t "Retractamos los intereses por defecto " $?intereses2 " ya que a este estudiante le interesa " $?intereses "." crlf)
  (modify ?f2 (Intereses $?intereses seguro))
)

; Cuando acabamos todas la preguntas pasamos a calcular las asignaturas para recomendar
(defrule FinInformacion
  (declare (salience -1))
  ?f <- (MActual MPreguntarRA)
  ; Sin preguntas que hacer
  (not (Preguntar ?))
  (Usuario (Creditos ?cred))
    =>
  (retract ?f)
  ; Cambiamos de módulo y nº creditos a coger
  (assert (MActual MCalcularRA))
  (assert (CreditosActuales ?cred))
  ; Hechos aux
  (assert (HayOptativas NO))
  (assert (NAsignatura 1))
  (assert (CursoMaxMin 0 0))
)

; ---------------------------------------------------------------------------------------------
;                                 Módulo MCalcularRA
; ---------------------------------------------------------------------------------------------
; Módulo que se encarga de obtener las asignaturas recomendadas, calculando puntuaciones
; en cada apartado


; Añadimos para cada asignatura la puntuación 0
(defrule IniciarPuntuaciones
  (MActual MCalcularRA)
  ; Mientras aun no se hayan recomendado asignaturas
  (NAsignatura 1)
  (Usuario (Asignaturas $? ?asig $?))
  (not (Puntuacion ?asig $?))
    =>
  (assert (Puntuacion ?asig 0.0 "te recomiendo esta asignatura por los siguientes motivos: "))

  (assert (Puntuar Mencion ?asig))
  (assert (Puntuar Dificultad ?asig))
  (assert (Puntuar CargaTrabajo ?asig))
  (assert (Puntuar Curso ?asig))
  (assert (Puntuar Intereses ?asig))
  (assert (Puntuar Tipo ?asig))
)

; Añade puntuación si la asignatura coincide con la mención (y se tiene una)
(defrule PuntuacionMencion
  (MActual MCalcularRA)
  ?f1 <- (Puntuar Mencion ?asig)
  ?f2 <- (Puntuacion ?asig ?punt $?exp)
  (Usuario (Mencion ?mencion ?))
  (Asignatura (ID ?asig) (Rama ?rama))
    =>
  (retract ?f1)
  ; Añadimos 1 si se tiene mención y coincide con la asignatura
  (if (and (neq ?mencion Comun)
           (eq ?mencion ?rama)
      ) then
    (retract ?f2)
    ; Explicación
    (bind ?exp_mencion "Escoger asignaturas de tu mencion suele ser una buena opcion, ya que te prioriza una plaza y tiene temario que probablemente te guste.")
    ; Actualizamos
    (assert (Puntuacion ?asig (+ ?punt 1.0) $?exp ?exp_mencion))
  )
)

; Añade puntuación si la dificultad de la asignatura se adecua a las notas del estudiante
(defrule PuntuacionDificultad
  (MActual MCalcularRA)
  ?f1 <- (Puntuar Dificultad ?asig)
  ?f2 <- (Puntuacion ?asig ?punt $?exp)
  (Usuario (NotaMedia ?nota ?))
  (Asignatura (ID ?asig) (Dificultad ?dif))
    =>
  (retract ?f1)
  ; Añadimos 1 si la nota media es mayor o igual que la dificultad
  (if (>= ?nota ?dif)
    then
    (retract ?f2)
    ; Explicación
    (bind ?exp_dif"La dificultad de la asignatura se adecua a tus notas.")
    ; Actualizamos
    (assert (Puntuacion ?asig (+ ?punt 1.0) $?exp ?exp_dif))
  )
)

; Añade puntuación si la carga de trabajo de la asignatura se adecua a las gansa de trabajar del estudiante
(defrule PuntuacionCarga
  (MActual MCalcularRA)
  ?f1 <- (Puntuar CargaTrabajo ?asig)
  ?f2 <- (Puntuacion ?asig ?punt $?exp)
  (Usuario (CargaTrabajo ?ganas ?))
  (Asignatura (ID ?asig) (Carga ?carga))
    =>
  (retract ?f1)
  ; Añadimos 1 si las ganas de trabajar son mayores o iguales que la carga
  (if (>= ?ganas ?carga) then
    (retract ?f2)
    ; Explicación
    (bind ?exp_carga"La carga de trabajo de la asignatura esta bien para tus ganas de hacer cosas.")
    ; Actualizamos
    (assert (Puntuacion ?asig (+ ?punt 1.0) $?exp ?exp_carga))
  )
)

; Añade un hecho que nos dice si hay optativas o no en la lista de asignaturas
(defrule ComprobarOptativas
  (declare (salience 1))
  (MActual MCalcularRA)
  (Usuario (Asignaturas $? ?asig $?))
  (Asignatura (ID ?asig) (Tipo Optativa))
  ?f <- (HayOptativas NO)
    =>
  (retract ?f)
  (assert (HayOptativas SI))
)

; Añade puntuación a las obligatorias (si hay al menos una optativa)
(defrule PuntuacionTipo
  (MActual MCalcularRA)
  ?f1 <- (Puntuar Tipo ?asig)
  ?f2 <- (Puntuacion ?asig ?punt $?exp)
  (Asignatura (ID ?asig) (Tipo ?tipo))
  (HayOptativas ?res)
    =>
  (retract ?f1)
  ; Tiene que haber al menos una optativa, y que la asignatura sea obligatoria para sumar
  (if (and (eq ?res SI)
           (eq ?tipo Obligatoria)
      ) then
      (retract ?f2)
      ; Explicación
      (bind ?exp_tipo "Interesa coger las asignaturas obligatorias antes que las optativas, ya que tienen contenido mas fundamental que las optativas.")
      ; Actualizamos
      (assert (Puntuacion ?asig (+ ?punt 1.0) $?exp ?exp_tipo))
  )
)

; Obtenemos el curso mínimo de las asignaturas
(defrule ComprobarCursoMin
  (declare (salience 1))
  (MActual MCalcularRA)
  (Usuario (Asignaturas $? ?asig $?))
  (Asignatura (ID ?asig) (Curso ?curso))
  ; Que no haya otra asignatura con curso menor
  (not (and (Usuario (Asignaturas $? ?asig2 $?))
            (Asignatura (ID ?asig2) (Curso ?curso2))
            (test (< ?curso2 ?curso))
       )
  )
  ?f <- (CursoMaxMin ?max 0)
    =>
  (retract ?f)
  (assert (CursoMaxMin ?max ?curso))
)

; Obtenemos el curso máximo de las asignaturas
(defrule ComprobarCursoMax
  (declare (salience 1))
  (MActual MCalcularRA)
  (Usuario (Asignaturas $? ?asig $?))
  (Asignatura (ID ?asig) (Curso ?curso))
  ; Que no haya otra asignatura con curso mayor
  (not (and (Usuario (Asignaturas $? ?asig2 $?))
            (Asignatura (ID ?asig2) (Curso ?curso2))
            (test (> ?curso2 ?curso))
       )
  )
  ?f <- (CursoMaxMin 0 ?min)
    =>
  (retract ?f)
  (assert (CursoMaxMin ?curso ?min))
)

; Añadimos puntuación a las asignaturas de menor curso (si hubiera de dos cursos distintos)
(defrule PuntuacionCurso
  (MActual MCalcularRA)
  ?f1 <- (Puntuar Curso ?asig)
  ?f2 <- (Puntuacion ?asig ?punt $?exp)
  (Asignatura (ID ?asig) (Curso ?curso))
  (CursoMaxMin ?max ?min)
    =>
  (retract ?f1)
  ; Debe haber dos asignaturas en cursos distinto, y se suma a las de curso inferior (mínimo)
  (if (and (neq ?max ?min)
           (eq ?min ?curso)
      ) then
      (retract ?f2)
      ; Explicación
      (bind ?exp_curso "Es mejor coger las asignaturas de cursos inferiores, puesto que se dan temas basicos para asignaturas mas complejas de cursos superiores.")
      ; Actualizamos
      (assert (Puntuacion ?asig (+ ?punt 2.0) $?exp ?exp_curso))
  )
)

; Añadimos puntuación a las asignaturas que compartan temas con los intereses preferidos del usuario
(defrule PuntuacionIntereses
  (MActual MCalcularRA)
  ?f <- (Puntuar Intereses ?asig)
  (Asignatura (ID ?asig) (Temas $?temas))
    =>
  (retract ?f)
  (assert (ComprobarIntereses ?asig $?temas))
)

; Si el primer tema de la lista está en los intereses del usuario sumamos a la puntuación
(defrule InteresesEsta
  (MActual MCalcularRA)
  ?f1 <- (ComprobarIntereses ?asig ?tema $?res)
  ?f2 <- (Puntuacion ?asig ?punt $?exp)
  (Usuario (Intereses $? ?tema $? ?))
    =>
  ; Actualizamos lista
  (retract ?f1 ?f2)
  (assert (ComprobarIntereses ?asig $?res))
  ; Explicación
  (bind ?exp_interes (str-cat "La asignatura tiene el tema " ?tema ", que te gusta."))
  (assert (Puntuacion ?asig (+ ?punt 2.0) $?exp ?exp_interes))
)

; Si el primer tema de la lista no está en los intereses del usuario lo quitamos
(defrule InteresesNoEsta
  (MActual MCalcularRA)
  ?f <- (ComprobarIntereses ?asig ?tema $?res)
  (not (Usuario (Intereses $? ?tema $? ?)))
    =>
  ; Actualizamos lista
  (retract ?f)
  (assert (ComprobarIntereses ?asig $?res))
)

; Cuando ya no hay más intereses, borramos
(defrule FinInteresesLista
  (declare (salience 1))
  (MActual MCalcularRA)
  ?f <- (ComprobarIntereses ?asig)
    =>
  (retract ?f)
)

; Cuando acaban los cálculos, y queden creditos por asignar, tomamos asignaturas
(defrule CalcularAsignaturasRecomendadas
  (declare (salience -1))
  (MActual MCalcularRA)
  (CreditosActuales ?cred)
  (test (> ?cred 0))
    =>
  (assert (Comando AsignaturaMax))
)

; Obtiene la asignatura con el máximo de puntuación (que puedan encajar en el
; nº de créditos restantes)
(defrule ObtenerAsignaturaMax
  (MActual MCalcularRA)
  ?f1 <- (Comando AsignaturaMax)
  ?f2 <- (Puntuacion ?asig ?punt $?exp)
  (Asignatura (ID ?asig) (Creditos ?cred1))
  ?f3 <- (CreditosActuales ?cred2)
  ; Que la asignatura no deje creditos negativos
  (test (>= (- ?cred2 ?cred1) 0))
  ; La asignatura es el máximo respecto las asignaturas que se pueden tomar
  (not (and (Puntuacion ?asig2 ?punt2 $?)
            (Asignatura (ID ?asig) (Creditos ?cred3))
            (test (>= (- ?cred2 ?cred3) 0))
            (test (> ?punt2 ?punt))
       )
  )
  ; Nº de asignatura escogida
  ?f4 <- (NAsignatura ?num)
    =>
  ; Eliminamos las asignaturas
  (retract ?f1 ?f2 ?f3 ?f4)
  ; Actualizamos créditos
  (assert (CreditosActuales (- ?cred2 ?cred1)))
  ; Añadimos recomendación
  (assert (AsignaturaRecomendada ?num ?asig $?exp))
  ; Actualizamos nº de asignaturas
  (assert (NAsignatura (+ ?num 1)))
)

; Cuando ya no se pueden asignar más asignaturas
(defrule FinCreditos
  (declare (salience -2))
  (MActual MCalcularRA)
  ?f <- (CreditosActuales ?cred)
    =>
  (assert (Comando LimpiarHechos))
  (retract ?f)
  ; Avisa si sobran créditos
  (if (> ?cred 0) then
    (printout t crlf "AVISO: han quedado " ?cred " por asignar." crlf)
  )
)

; Limpiamos los hechos de puntuaciones
(defrule LimpiarHechosPuntuacion
  (MActual MCalcularRA)
  (Comando LimpiarHechos)
  ?f <- (Puntuacion $?)
    =>
  (retract ?f)
)

; Limpiamos hechos auxiliares
(defrule LimpiarHechosExtra
  (MActual MCalcularRA)
  (Comando LimpiarHechos)
  ?f1 <- (HayOptativas ?)
  ?f2 <- (CursoMaxMin $?)
    =>
  (retract ?f1 ?f2)
)

; Terminamos de limpiar y pasamos a enseñar los resultados
(defrule LimpiarHechosFin
  (declare (salience -1))
  ?f1 <- (MActual MCalcularRA)
  ?f2 <- (Comando LimpiarHechos)
    =>
  (retract ?f1 ?f2)
  (assert (MActual MResultadosRA))
  ; Hechos base
  (assert (Comando MostrarAsignaturasInicio))
  (assert (MostrarAsignatura 1))
)

; ---------------------------------------------------------------------------------------------
;                                 Módulo MResultadosRA
; ---------------------------------------------------------------------------------------------
; Módulo que enseña al usuario las recomendaciones de las asignaturas dando una explicación al
; por qué de estas elecciones.

; Mensaje inicial al mostrar las asignaturas
(defrule MostrarAsignaturasInicial
  (MActual MResultadosRA)
  ?f <- (Comando MostrarAsignaturasInicio)
    =>
  (retract ?f)
  (printout t crlf "Vale, te voy a decir de que asignaturas deberias matricularte: " crlf)
  (assert (Comando MostrarAsignaturas))
)

; Si por alguna razón no tenemos razones para dar esa asignatura lo advertirmos
(defrule MostrarAsignaturaSinMotivos
  (declare (salience 1))
  (MActual MResultadosRA)
  (Comando MostrarAsignaturas)
  ?f <- (MostrarAsignatura ?num)
  (AsignaturaRecomendada ?num ?asig ?exp_ini)
    =>
  (retract ?f)
  (printout t crlf ?num ". " ?asig ", aunque no tengo motivos para recomendarte esta asignatura, te la doy por descarte" crlf)
  (assert (MostrarAsignatura (+ ?num 1)))
)

; Mostramos la recomendación (ordenada por puntos) explicando por qué
(defrule MostrarAsignatura
  (MActual MResultadosRA)
  (Comando MostrarAsignaturas)
  (MostrarAsignatura ?num)
  (AsignaturaRecomendada ?num ?asig ?exp_ini $?exp)
    =>
  (printout t crlf ?num ". " ?asig ", " ?exp_ini crlf)
  (assert (Razones $?exp))
)

; Imprime como una cola cada razón
(defrule ImprimirRazones
  (MActual MResultadosRA)
  ?f <- (Razones ?razon $?res)
    =>
  (printout t " - " ?razon crlf)
  (retract ?f)
  (assert (Razones $?res))
)

; Acabamos de imprimir las razones y pasamos a la siguiente asignatura
(defrule RazonesFin
  (MActual MResultadosRA)
  ?f1 <- (MostrarAsignatura ?num)
  ?f2 <- (Razones)
    =>
  (retract ?f1 ?f2)
  (assert (MostrarAsignatura (+ ?num 1)))
)

; Caundo imprimimos todas las asignaturas acabamos, eliminando hechos
(defrule FinRecomendar
  (MActual MResultadosRA)
  ?f1 <- (Comando MostrarAsignaturas)
  ?f2 <- (MostrarAsignatura ?num)
  ?f3 <- (NAsignatura ?num)
  ?f4 <- (Usuario)
    =>
  (retract ?f1 ?f2 ?f3 ?f4)
  (assert (Comando VolverMenu))
)

; Limpiamos mas hechos
(defrule LimpiarRecomendaciones
  (declare (salience 1))
  (MActual MResultadosRA)
  (Comando VolverMenu)
  ?f <- (AsignaturaRecomendada $?)
    =>
  (retract ?f)
)
