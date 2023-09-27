# P1 - IC
## Miguel Lentisco Ballesteros

## Sistema de razonamiento con sistemas basado en reglas
El sistema que he cogido es el 3 en raya, y he desarrollado las reglas que se plantean para que la IA actúe de manera inteligente, está en el archivo "tres_en_raya.clp"

A considerar las nuevas reglas:

  - En el apartado INICIALIZAR ESTADO:
    - Regla `Crear_EnLinea` que crea los hechos `EnLinea` para saber si dos casillas están conectadas por la misma linea.
  - En el apartado ACTUALIZAR ESTADO TRAS JUGADA DE CLISP:
    - Regla `Crear_2_en_linea` para crear el hecho`2_en_linea` cuando un jugador tenga 2 fichas en la misma linea (usando `EnLinea`).
    - Regla `Comprobar_Puede_ganar_poniendo` que crea el hecho `Puede_ganar` cuando un jugador esté a un movimiento de ganar poniendo una ficha en la posición indicada (usando `2_en_raya`).
    - Regla `Comprobar_Puede_ganar_moviendo` lo mismo pero si se puede ganar moviendo una ficha de una posición adyacente a la que forma 3 en raya.
  - En el apartado CLISP JUEGA CON CRITERIO:
    - Regla `clisp_juega_con_criterio_fichas_sin_colocar_mov_ganador` que hace que la maquina gane si tiene un movimiento ganador poniendo fichas(usando `Puede_ganar`).
    - Regla `clisp_juega_con_criterio_fichas_sin_colocar_evitar_mov_ganador` que hace que la maquina evite que la persona gane (y la maquina no puede ganar en este turno) poniendo fichas.
    - Regla `clisp_juega_con_criterio_fichas_sin_colocar` si no se puede ganar o evitar perder, por defecto se intenta poner la ficha en el medio (mejor posición posible).
    - Regla `clisp_juega_con_criterio_mov_ganador` que gana si se puede moviendo fichas.
    - Regla `clisp_juega_con_criterio_evitar_mov_ganador` que evita perder si no se puede ganar moviendo fichas.
    - Regla `clisp_juega_con_criterio` que juega evitando movimientos que le den la partida al jugador.

## Sistema experto para aconsejar elección de rama
El sistema para aconsejar ramas se incluye en "recomendar_rama.clp", viene dividido por modulos para que se haga más facil la lectura.

La adquisición de conocimientos viene de dos tareas anteriores (árbol y entrevista), juntando esta información con el criterio y experiencia del experto (en este caso yo), que ha valorado la flexibilidad del sistema (respuestas parciales, información incompleta), las mejores maneras de dilucidar que rama es mejor (preguntas de temas, nota media) y ha creado un sistema sencillo pero eficaz a la hora de recomendar las asignaturas.

Se tiene 3 módulos fáciles de entender:

  - `MHacerPreguntas`: que se encarga de hacer las preguntas y recoger la información.
  - `MCalcularRama`: en base a la información obtenida realiza sugerencias de rama.
  - `MRespuestaRama`: se encarga de responder al usuario con los consejos obtenidos.
