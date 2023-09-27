---
  title: Tema Y
---

Tema Y (67 preguntas)
=====================

1.  Empareje el tipo de dependencia con la característica que la define.
    -   Una dependencia es reversible si -\> cuando se retracta el
        antecedente debe retractarse el consecuente
    -   Una dependencia es irreversible si -\> al retractar el
        antecedente no puede retractarse el consecuente
2.  Marque las opciones correctas: El encadenamiento hacia adelante:
    -   [x] Es más específico que el encadenamiento hacia atrás.
    -   [ ] Suele solicitar al usuario la afirmación que no ha podido
        deducir.
    -   [x] Utiliza sólo los datos disponibles.
    -   [ ] Es menos específico que el encadenamiento hacia atrás.
3.  En los sistemas basados en reglas, ¿se puede sustituir una Base de
    Conocimiento por otra sin modificar el motor de inferencias?
    -   [ ] Si, en todos los casos
    -   [x] Si, solo es necesario que ambas Bases de Conocimiento tengan
        la misma sintaxi
    -   [ ] No, en ningún caso
4.  En el esquema de los componentes básicos de los sistemas basados en
    reglas la flecha que une la base de conocimiento con el motor de
    inferencia cuando es bidireccional indica que:
    -   [x] El sistema puede aprender
    -   [x] El motor de inferencia utiliza la base de conocimiento.
    -   [ ] Nunca es bidireccional
5.  ¿Cuáles de las siguientes afirmaciones sobre el encadenamiento hacia
    adelante y el encadenamiento hacia atrás son ciertas?
    -   [ ] El encadenamiento hacia atrás también se conoce como basado
        en datos.
    -   [x] El encadenamiento hacia adelante aparece cuando al
        introducir información en el sistema y ejecutarse una regla
        acorde a dicha información se produce la ejecución de otras
        reglas.
    -   [ ] El encadenamiento hacia atrás nunca solicita información al
        usuario.
    -   [x] El encadenamiento hacia atrás es más eficiente que el
        encadenamiento hacia adelante porque es más específico (busca
        las reglas que permite establecer una conclusión y no ejecuta
        todas las reglas relacionadas con la información introducida).
    -   [ ] El encadenamiento hacia adelante también se conoce como
        basado en objetivos.
    -   [x] El encadenamiento hacia adelante utiliza únicamente los
        datos disponibles en el sistema.
6.  En la base de conocimientos de un SBR el orden de la reglas no es
    relevante.
    -   [ ] Es verdad, el conocimiento de la base de conocimiento no
        cambia al cambiar el orden de las reglas
    -   [ ] Si es relevante pues las primeras reglas son mas importantes
        que las últimas
    -   [x] Depende de la estrategia de control que se vaya a usar, si
        esta considera ese orden es totalmente relevante, pero si no
        considera ese orden es irrelevante
7.  Normalmente el encadenamiento hacia adelante suele solicitar al
    usuario la información que no ha podido deducir.
    -   [ ] Verdadero
    -   [x] Falso
8.  En las dependencias reversibles cuando se retracta el antecedente se
    tiene que retractar el consecuente.
    -   [x] Verdadero
    -   [ ] Falso
9.  Seleccione las afirmaciones correctas:
    -   [x] Decimos que nuestro sistema tiene capacidad de aprendizaje
        si la fecha entre la base de conocimiento y el motor de
        inferencia es bidireccional en el diagrama visto en clase de los
        componentes de un sistema basado en reglas.
    -   [ ] hielo\_en\_la\_carretera y nivel\_de\_gasolina\<8 son
        ejemplos de hipótesis.
    -   [x] averia\_electrica y temperatura\_interior\<18 podrían ser
        clausulas.
    -   [ ] En interpretación declarativa, los consecuentes son acciones
        que debe de realizar el sistema, mientras que en la imperativa,
        son conclusiones deducidas de los antecedentes.
    -   [ ] El entender como falsas aquellas afirmaciones que no se
        encuentran en la base de afirmaciones ni se pueden deducir, se
        llama lógica por defecto.
10. Los objetivos se encuentran en el motor de inferencia al ser donde
    se va a obtener su resultado.
    -   [ ] Verdadero
    -   [x] Falso
11. NOTA: (ampersand) denota el simbolo y (igual) también. Por sintaxis
    de las cuestiones GIFT no pueden ponerse.
    -   [ ] ?defrule es-alto ?cliente\_parque\_atracciones
        ?identificación ?numero? ?altura ?altura(ampersand):?\>?altura
        1'60??(igual)\> ?printout t "Cliente" ?numero \" puede
        pasar\"??.
    -   [x] ?defrule muestra-edad ?matriculado ?nombre ?nombre
        ?apellido? ?edad ? ?(igual)\>?printout t \" El alumno \" ?nombre
        ?apellido \" tiene \" ? "años" ??
    -   [ ] ?assert ?tiempo soleado??.
12. Posibles acciones en el consecuente de una regla:
    \_\_\_\_\_\_\_\_\_\_\_\_
    -   [ ] a)Afirmar:enviar una orden a los actuadores con los que está
        conectado el sistema.Retractar:modificar una afirmación anterior
        y Actuar:ejecutar el programa.
    -   [ ] b)Afirmar:establecer algún tipo de afirmación y Actuar:
        ejecutar dicha afirmación.
    -   [ ] c)Afirmar:establecer algún tipo de afirmación y
        Retractar:modificar alguna afirmación.
    -   [x] d) Afirmar: establecer algún tipo de afirmación,
        retractar:modificar alguna afirmación y actuar:se envía una
        orden a los actuadores con los que está conectado el sistema.
13. ¿Cuál de estos elementos pueden intervenir en una regla?
    -   [x] Dato
    -   [ ] Relación de cercanía
    -   [x] Hipótesis
    -   [x] Relación de pertenencia
14. El considerar falsa toda proposición que no se encuentre en la Base
    de Afirmaciones ni pueda deducirse de la información disponible, se
    conoce como
    -   [ ] Axioma de la Verdad Absoluta
    -   [ ] Axioma del Mundo Abierto
    -   [ ] Axioma de la Deducción
    -   [x] Axioma del Mundo Cerrado
15. Las principales desventajas de los lenguajes basados en reglas son:
    -   [x] La ejecución del proceso de reconocimiento de patrones los
        vuelve ineficientes.
    -   [ ] Falta de naturalidad, las reglas no son una forma natural de
        expresar el conocimiento.
    -   [x] Existe uan dificultad para cubrir todo el conocimiento (el
        número de reglas necesarias podría no ser manejable)
    -   [x] No podemos predecir qué acciones ocurrirán cuando observamos
        una base de conocimiento.
16. Relaciona términos con su definición
    -   Cláusula -\> hipótesis, relación. O bien negación, conjunción y
        disyunción de otras cláusulas.
    -   Motor de inferencia -\> Coordina la información de todo el
        Sistema, trabaja sobre la Base de Conocimiento y envía
        resultados a la interfaz de usuario, a la Base de Afirmaciones,
        a la Base de Datos y, en ocasiones, a la Base de Conocimiento
    -   faceta -\> Propiedad asociada a un atributo
    -   Red semántica -\> Sistema de representación estructurada del
        conocimiento
    -   CLIPS -\> Lenguaje basado en reglas
    -   Control de razonamiento -\> Permite seleccionar qué regla
        ejecutar en primer lugar.
17. De las siguientes afirmaciones, señale las correctas:
    -   [ ] En un sistema basado en reglas, el Motor de inferencia
        recibe información de la Base de Datos, pero nunca puede enviar
        nueva información a la base de datos.
    -   [ ] En el caso de tener que representar la información de un
        dominio tan complejo como lo es el de las armaduras de combate
        empleadas en todos los países del mundo entre los siglos V y XV
        d.c., lo mejor es emplear una red semántica.
    -   [x] En una taxonomía de frames se pueden dar sólo relaciones de
        instancia-de o subclase-de.
    -   [x] Una base de datos puede cambiarse por otra con la misma
        sintaxis sin necesidad de alterar el motor de inferencia.
    -   [ ] Los tipos de acciones que pueden aparecer en el antecedente
        de un regla son Afirmar y Retractar.
18. En CLIPS, una regla...
    -   [ ] debe depender de un solo hecho
    -   [x] puede depender de varios hechos
    -   [x] puede crear tantos hechos como uno necesite
    -   [ ] siempre debe crear un solo hecho nuevo
    -   [x] puede no crear ningún hecho nuevo
    -   [x] puede eliminar hechos ya existentes
19. El control de razonamiento es el mecanismo que evita que las reglas
    se contradigan.
    -   [ ] Verdadero
    -   [x] Falso
20. En CLIPS, las relaciones entre las reglas y los hechos se determinan
    al compilar.
    -   [ ] Verdadero
    -   [x] Falso
21. Si un problema no se puede resolver de forma algorítmica, tampoco se
    podrá resolver con un sistema basado en reglas.
    -   [ ] Verdadero
    -   [x] Falso
22. Selecciona Tipos de Sistemas de Producción \_\_\_\_\_\_\_\_\_\_\_\_
    .
    -   [ ] Hechos
    -   [ ] Reglas
    -   [x] Red de Inferencia
23. ¿Son las metarreglas un mecanismo de control del razonamiento?
    -   [x] Verdadero
    -   [ ] Falso
24. Marque cuales son las ventajas de los sistemas LBR.
    -   [ ] Eficiencia
    -   [ ] Se observan las acciones que pueden ocurrir
    -   [x] Modularidad
    -   [ ] Necesitan pocas reglas
    -   [x] Se observa el proceso de razonamiento
25. En referencia a los sistemas basados en reglas, enlace cada
    definición con su concepto correspondiente:
    -   Contiene las reglas específicas del dominio y puede que algunas
        afirmaciones iniciales. -\> Base de conocimiento.
    -   Almacena información sobre casos anteriores, así como variables
        que puedan caracterizar al objeto. -\> Base de datos.
    -   Se encarga de solicitar y mostrar la información pertinente al
        usuario. -\> Interfaz de usuario.
    -   Contiene las afirmaciones iniciales almacenadas en el sistema,
        así como las extraídas de casos anteriores o aportadas por el
        usuario, además de las que hayan sido inferidas. -\> Base de
        afirmaciones.
    -   Coordina y procesa la información de los demás componentes,
        enviando los resultados al lugar del sistema adecuado. -\> Motor
        de inferencia.
26. En cuanto a la estructura de una regla...
    -   [x] El antecedente es aquél que contiene las cláusulas que deben
        hacerse ciertas para que se ejecute la regla.
    -   [ ] La parte derecha de la regla corresponde a la hipótesis.
    -   [ ] Una regla de interpretación declarativa es aquélla que
        realiza una acción cuando se ejecuta la regla.
    -   [x] En el consecuente de la regla se pueden afirmar hechos,
        retractarlos o actuar de algún modo sobre ellos.
    -   [ ] El antecedente sólo puede contener cláusulas que estén
        formadas por una relación (de comparación o pertenencia).
27. Señala sólo las opciones correctas:
    -   [ ] Generalmente, las estrategias de control son tan complejas y
        costosas que para ciertos problemas más duros no son
        aconsejables.
    -   [x] Las estrategias de control son independientes del problema y
        no son modificables, aunque localmente el programador puede
        incluir algunas.
    -   [x] Si no fuera por las estrategias de control, programas como
        el ejemplo del mundo de bloques (página 56, tema 4-1) se
        desbordarían en tiempo de ejecución.
28. ¿Cuales de las siguientes afirmaciones son correctas?
    -   [ ] El encadenamiento hacia adelante y hacia atrás sólo se
        pueden usar por separado, nunca se fusionan ya que son demasiado
        diferentes entre sí.
    -   [x] El encadenamiento hacia adelante se suele utilizar cuando
        tenemos pocos datos iniciales y podemos permitirnos lanzar
        muchas inferencias.
    -   [ ] Si usamos encadenamiento hacia atrás estaremos perjudicando
        la eficiencia y especificidad del sistema.
    -   [x] Este trabajo lo lleva a cabo el motor de inferencia del
        sistema.
29. ¿Cuál de las siguientes afirmaciones son ciertas?
    -   [x] La dependencia reversible se usa cuando tenemos varios
        caminos hacia un consecuente y la irreversible la usaremos
        cuando sólo tenemos un camino hacia un consecuente.
    -   [ ] La dependencia irreversible se puede usar cuando hay pocos
        caminos hacia un mismo consecuente.
    -   [ ] Por lo general, todas las interfaces de creación de sistemas
        basados en reglas permiten que sea el diseñador el que fije esta
        dependencia.
30. Los hechos estructurados tienen mayor control sobre los datos, pero
    precisan de una declaración previa.
    -   [x] Verdadero
    -   [ ] Falso
31. ¿Cuál de estos mecanismos forma parte de las estrategias de
    resolución de conflictos LEX Y MEA?
    -   [ ] Recursividad
    -   [x] Novedad
    -   [ ] Comparación
    -   [x] Refracción
32. Suponemos que al retractar el antecedente de una cierta regla no se
    puede retractar el consecuente. La dependencia de esta regla sería
    -   [ ] reversible
    -   [x] irreversible
33. Seleccione las afirmaciones correctas:
    -   [x] Si los datos del sistema basado en reglas son univaluados,
        las contradicciones en los valores de las variables no serán un
        problema.
    -   [ ] Una base de conocimiento puede cambiarse con otra puesto que
        el motor de inferencias es independiente.
    -   [x] Hablamos de dependencia reversible si al retractar un
        antecedente, también debe hacerlo el consecuente.
    -   [ ] El consecuente de una regla nos dice cuando se disparará.
34. ¿Cuál de estos de acciones no puede aparecer en el consecuente de
    una regla?
    -   [ ] Afirmar
    -   [x] Decidir
    -   [ ] Actuar
    -   [x] Pensar
    -   [ ] Retractar
35. ¿Que proceso de razonamiento comienza con todos los datos conocidos
    y procesa hasta la conclusión?
    -   [x] Razonamiento dirigido por los datos
    -   [ ] Razonamiento dirigido por los objetos
36. Marca cada propiedad como ventaja o desventaja del LBR
    -   Opacidad -\> desventaja
    -   Modularidad -\> ventaja
    -   Uniformidad -\> ventaja
    -   Naturalidad -\> ventaja
    -   Cobertura del conocimiento -\> desventaja
    -   Explicación -\> ventaja
    -   Ineficiencia -\> desventaja
37. ¿Cuáles de las siguientes afirmaciones sobre reglas son ciertas?.
    -   [ ] La base de conocimiento es el componente central de un
        sistema basado en reglas.
    -   [ ] El motor de inferencias es elemento que contiene las reglas
        del sistema basado en reglas.
    -   [ ] La base de afirmaciones sirve solamente para almacenar las
        afirmaciones que el motor de inferencia obtiene a partir del
        razonamiento.
    -   [x] Un sistema con capacidad de aprendizaje tendría una relación
        bidireccional con el motor de inferencias.
    -   [ ] Una regla consta de dos partes: antecedente, indica las
        conclusiones y acciones que se realizarán si la regla se ejecuta
        y el consecuente, contiene las condiciones para que la regla se
        cumpla.
    -   [x] El objetivo de introducir variables en las reglas es poder
        utilizar las reglas para representar afirmaciones tal y como
        hace la lógica de predicados.
    -   [ ] Los sistemas basados en reglas al igual que la lógica
        clásica no permiten retractar afirmaciones ya que en tal caso,
        el sistema no sabría cómo actuar.
38. ¿Cuáles de las siguientes afirmaciones sobre lenguajes basados en
    reglas son ciertas?
    -   [ ] Los sistemas de producción para poder realizar búsquedas en
        un espacio de estados necesitan una representación del estado
        del sistema, un estado inicial y un estado final.
    -   [ ] Los sistemas basados en reglas tienen una base de hechos,
        una base de conocimiento y un motor de inferencias.
    -   [ ] Podemos distinguir dos partes en un sistema basado en
        reglas: una parte declarativa, formada por el motor de
        inferencias y una parte algorítmica constituida por hechos, las
        reglas y las meta-reglas.
    -   [ ] Para el proceso de reconocimiento existen dos estructuras
        básicas: las redes de inferencia y las redes semánticas.
    -   [ ] Las relaciones entre las reglas y los hechos en CLIPS se
        realizan en tiempo de compilación.
    -   [ ] Los sistemas de reconocimiento de patrones se caracterizan
        por su fácil implementación, su flexibilidad y por su eficiencia
        a la hora de buscar hechos que satisfagan las reglas.
    -   [ ] El razonamiento dirigido por los datos también es conocido
        por encadenamiento progresivo (hacia adelante o hacia atrás).
    -   [ ] En CLIPS sólo podemos hacer razonamiento regresivo.
    -   [x] Algunas de las principales ventajas de CLIPS son la
        modularidad, los lenguajes sistemas en reglas son muy modulares
        y la naturalidad para expresar conocimiento.
39. Algunos elementos que pueden aparecer en una regla (Respuesta
    simple):
    -   [ ] Datos, teoremas, relaciones de comparación.
    -   [x] Cláusulas, datos, hipótesis.
    -   [ ] Relaciones de pertenencia, relaciones de asignación, datos.
    -   [ ] Información y relaciones.
40. Para que una regla pueda ser ejecutada, ¿debe cumplirse su
    antecedente? (Respuesta simple)
    -   [ ] No es necesario, ya que las reglas son independientes unas a
        otras.
    -   [ ] Debe cumplirse, pero no necesariamente todas sus cláusulas.
    -   [ ] Si las cláusulas que forman la regla anterior no tienen
        variable, no es necesario.
    -   [ ] Ninguna de las anteriores es correcta.
41. ¿Qué parte de la arquitectura de los lenguajes basados en reglas
    aplica las reglas a los hechos?
    -   [ ] Base de hechos
    -   [x] Motor de inferencia
    -   [ ] Control global
    -   [ ] Base de Reglas
42. Emparejar cada uno de los siguientes conceptos con un tipo de
    elemento
    -   años\_antigüedad -\> Dato
    -   hombre es persona -\> Relación de Pertenencia
    -   persiana\_subida -\> Hipótesis
    -   velocidad \< 100 -\> Reclación de Comparación
    -   persiana\_subida AND demasiada\_luz -\> Cláusula
43. ¿Porque puede estar compuesta una ontología? (Multirespuesta)
    -   [x] Conceptos o clases
    -   [x] Instancias o individuos
    -   [ ] Hechos o reglas
    -   [x] Propiedades o relaciones
    -   [ ] Modelos
    -   [ ] Grados de verdad
    -   [x] Axiomas

44 ¿Cuáles de las siguientes son propiedades de un sistema experto de
calidad?
    -   [x] Disponibilidad completa.
    -   [ ] Gran extensión, se aplican a problemas muy amplios.
    -   [ ] Existencia de reglas redundantes para evitar errores.
    -   [x] Confiable, la solución aportada está justificada.
    -   [ ] Llega a conclusiones complejas.
    -   [ ] Tienen una buena presentación visual.
    -   [x] Las conclusiones son lógicas y congruentes.
    -   [x] La base de conocimiento está verificada y no contendrá
    -   incompletitudes ni errores.

45. Un sistema experto es funcional si:
    -   [x] su comportamiento cubre las expectativas para las que fue
        construido.
    -   [x] presenta medios de explicación.
    -   [ ] tiene respuesta para cada combinación de los hechos de
        entrada.
46. Seleccione las afirmaciones correctas:
    -   [ ] La verificación se encarga de comprobar que el sistema es el
        correcto , es decir, hace lo que se dijo que haría, satisface
        las necesidades del usuario.
    -   [x] La verificación se encarga de comprobar que el sistema está
        correctamente construido, es decir, hace bien lo que se ha
        implementado.
    -   [x] La validación se encarga de comprobar que el sistema es el
        correcto , es decir, hace lo que se dijo que haría, satisface
        las necesidades del usuario.
    -   [ ] La validación se encarga de comprobar que el sistema está
        correctamente construido, es decir, hace bien lo que se ha
        implementado.
47. Une cada estándar con principal característica:
    -   UNICODE -\> Codifica textos en cualquier forma e idioma.
    -   XML -\> Estandariza formatos.
    -   RDF -\> Representa conceptos y relaciones usando tripletas.
    -   RDFS -\> Proporciona elementos básicos para crear ontologías.
48. Seleccione las características de un SE con calidad:
    -   [x] Obtiene conclusiones correctas.
    -   [x] Obtiene conclusiones completas.
    -   [x] Obtiene conclusiones congruentes.
    -   [x] Es confiable respecto a las conclusiones que se van
        produciendo.
    -   [x] Presenta mecanismos de seguridad.
    -   [x] El código es comprensible y está comentado.
    -   [x] Esta disponible para cualquier posible usuario.
    -   [x] La base de conocimiento esta verificada.
49. ¿Según Ontology Web Language, cuál sería la relación entre
    tieneMarido y tieneCónyuge?
    -   [ ] subClassOf
    -   [ ] disjointWith
    -   [ ] equivalentClass
    -   [ ] sameIndividualAs
    -   [ ] differentFrom
    -   [ ] InverseOf
    -   [x] subPropertyOf
    -   [ ] tansitiveProperty
    -   [ ] functionalProperty
    -   [ ] inverseFunctionalProperty
    -   [ ] equivalentPropertyOf
50. Asigne cada campo a su valor correspondiente. Los principales
    errores en el desarrollo de un sistema experto los podemos encontrar
    en:
    -   Experto -\> Errores en los que el conocimiento es incorrecto o
        incompleto.
    -   Base del Conocimiento -\> Errores de sintaxis (debido a un
        conocimiento incorrecto, incompleto e incertidumbre en las
        reglas).
    -   IC -\> Errores semánticos de significados entre el IC y el
        especialista.
    -   Motor de inferencia -\> Errores en la programación y errores de
        lógica.
51. Relacione los siguientes conceptos
    -   Conocimiento específico de dominio -\> Ontologías de dominio
    -   Generalización de tareas -\> Ontologías orientadas a tareas
    -   Útil para la reutilización -\> Ontologías genéricas
    -   Conceptos comunes de bajo nivel -\> Ontologías de aplicación
52. Para que un SE sea considerado efectivo debe siempre darnos la
    respuesta correcta lo más rápido posible
    -   [ ] Verdadero
    -   [x] Falso
53. Asocie los conceptos:
    -   Inconsistencia Semántica -\> Las variables toman valores no
        válidos o ilegales.
    -   Validación -\> Comprobar si el sistema satisface las necesidades
        de los usuarios.
    -   Verificación -\> Comprobación de la corrección del SBC
        (Descubrimiento y corrección de los errores).
54. El "Ontology Web Language" no es una extensión de "Resource
    Definition Format Schema".
    -   [ ] Verdadero
    -   [x] Falso
55. Los axiomas en las ontologías:
    -   [ ] No forman parte de las ontologías.
    -   [x] Son las restricciones y meta-información sobre las
        relaciones.
    -   [ ] Describen las relaciones entre los conceptos.
    -   [ ] Son las propiedades de las ontologías.
    -   [x] Definen el significado y permiten razonar con la ontología.
56. Empareje cada componente de las ontologías con su definición.
    -   Conceptos -\> Ideas básicas que se intentan formalizar.
    -   Relaciones -\> Enlace entre conceptos del dominio.
    -   Funciones -\> Tipo concreto de relación.
    -   Instancias -\> Representan objetos determinados de un concepto.
    -   Axiomas -\> Teoremas sobre las relaciones que deben cumplir los
        elementos de la ontología.
57. Las ontologías solo se pueden usar en los sistemas expertos
    -   [ ] verdadero
    -   [x] falso
58. Algunos de los errores en el desarrollo de un sistema experto pueden
    ser causados por el experto.
    -   [x] verdadero
    -   [ ] falso
59. En una ontología, las propiedades ligan individuos de un rango a
    individuos de un dominio.
    -   [ ] Verdadero
    -   [x] Falso
60. La validación objetiva son las actividades encaminadas a eliminar
    los errores de tipo conceptual y de contexto.
    -   [ ] Verdadero
    -   [x] Falso
61. ¿Cuáles de las siguientes afirmaciones sobre lenguajes para la
    definición de ontologías son ciertas?
    -   [ ] URI es un meta-lenguaje que se caracteriza por el uso de
        etiquetas entendibles para los humanos.
    -   [ ] UNICODE es el estándar que permite codificar un texto a una
        forma e idioma concreto.
    -   [x] RDF representa conceptos y relaciones mediante tripletas.
        Cada tripleta contiene:, un recurso, una propiedad y un objeto.
    -   [ ] OWL permite: expresar clases, representar y restringir
        relaciones entre clases y restringir propiedades (cardinalidad).
    -   [x] Los tres sub-lenguajes de OWL, ordenados de mayor a menor
        potencia expresiva son OWL-full (Soporte completo), OWL-DL (sólo
        constructores decidibles) y OWL-lite (versión simplificada).
    -   [ ] Las propiedades ligan individuos de un rango a individuos de
        un dominio.
    -   [x] FaCT++, Pellet y Racer son razonadores para Ontologías.
    -   [x] Las ontologías permiten la extracción del conocimiento y que
        éste sea entendible por humanos y máquinas.
62. ¿Qué tipo de Ontología combina diversas subontologías para su
    aplicación.?
    -   [ ] Ontologías genéricas.
    -   [ ] Ontologías de dominio.
    -   [ ] Ontologías orientadas a tareas.
    -   [x] Ontologías de aplicación.
63. Las ontologías: (Respuesta múltiple)
    -   [x] Generan información comprensible para humanos y ordenadores.
    -   [x] Son un método de clasificación automática.
    -   [x] Ayudan a la comprensión común.
    -   [x] Permiten la deducción de conocimiento a través de métodos
        automáticos.
64. En las ontologías: Las instancias describen las relaciones entre los
    conceptos.
    -   [ ] Verdadero
    -   [x] Falso
65. Un sistema experto de calidad debe ser capaz de adquirir nuevo
    conocimiento, para lo que debe tener integrado en el sistema algún
    mecanismo para modificar los conocimientos anteriores.
    -   [x] Verdadero
    -   [ ] Falso
66. Señala la opción que no se realiza en el razonamiento con
    ontologías.
    -   [ ] Detección de redundancias.
    -   [ ] Clasificación de instancias
    -   [x] Clasificador de restricciones
    -   [ ] Chequeo de consistencia
67. La validación es un proceso opcional en la construcción de un SE, ya
    que una vez construido dicho SE, ya es funcional.
    -   [ ] Verdadero
    -   [x] Falso
