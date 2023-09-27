---
  title: Ontología IC
  author: Miguel Lentisco Ballesteros
  header-includes: |
    \usepackage{graphicx}
    \usepackage{rotating}
    \usepackage{pdflscape}
---

# Ontología

La ontología obtenida se muestra en la Figura \ref{fig:ontologia}. Los axiomas se listan a continuación.

# Axiomas

  - La propiedad "Nº asignaturas" de Estudiante hace referencia al nº de asignaturas matriculadas actualmente, igual que con "Nº créditos" al nº de créditos superados.
  - Las propiedades "Inicio" y "Fin" de Horario son de tipo "Date" (tipo para expresar horas) y expresan la hora de inicio y finalización de un horario.
  - La propiedad "Trabajador" de Estudiante hace referencia al nivel de trabajo que tiene el estudiante. Se miden de la misma manera las propiedades "Carga Trabajo", "Dificultad" de Asignatura, "Nivel Gusto" de Gusto, "Exigente" de Profesor y "Dificultad" de Rama; todas hacen referencia al nivel de lo que se refiere.
  - La propiedad "Tema" de Gusto hace referencia la tema que puede gustar al estudiante, por ej: IA, Web, Procesadores...
  - La propiedad "Ramas relacionadas" de Gusto hace referencia a las ramas que tienen que ver con "Tema" de Gusto, por ej: IA con CSI, Juegos con CSI e IS...
  - Las asignaturas tendrán un horario respecto a la clase de teoria y varios de prácticas, donde no podrán solaparse entre ellas.
  - Las asignaturas de la misma rama y curso no pueden coincidir en los horarios de teoría.
  - Cada asignatura optativa como mucho puede pertenecer a una rama.
  - Cada asignatura debe pertenecer solo a un curso.
  - Cada asignatura/rama solo pueden como mucho un descriptor.
  - El nº de asignaturas matriculadas de un estudiante debe coincidir con el nº de asignaturas enlazadas con el estudiante.
  - Todas las propiedades de datos son funcionales.

\begin{landscape}
  \begin{figure}[!htb]
    \centering
    \includegraphics[width=22cm]{ontologia.png}
    \caption{Ontología}
    \label{fig:ontologia}
  \end{figure}
\end{landscape}
