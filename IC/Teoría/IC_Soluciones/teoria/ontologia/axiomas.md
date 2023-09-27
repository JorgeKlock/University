---
  title: Expresiones OWL
  author: Miguel Lentisco Ballesteros
---

# Ejercicio 1
Traducir a palabras el siguiente axioma:

$$\exists \text{Nº Articulos}.\{n\} \equiv \leq n.\text{P-author}^{-1} \cap \geq n.\text{P-author}^{-1}$$

Veamoslo por partes:

  - $n.\text{P-author}^{-1}$ es la clase de Autores que tienen n o menos Presentaciones.
  - $\geq n.\text{P-author}^{-1}$ es la clase de Autores que tienen n o más Presentaciones.
  - $\leq n.\text{P-author}^{-1} \cap \geq n.\text{P-author}^{-1}$ es la clase de Autores que tienen n Presentaciones.
  - $\exists \text{Nº Articulos}.\{n\}$ es la clase de Autores que tienen al menos un valor de Nº articulos que vale n (como Nº Articulos es funcional, quedaría en la clase de los Autores con Nº articulos igual a n).

Por tanto la expresión completa nos dice que la clase de Autores que tienen Nº articulos igual a n es la misma que la clase de Autores que tienen n Presentaciones; o lo que es lo mismo: \textbf{La propiedad Nº Articulos de Autor debe ser el número de presentaciones con ese Autor}.

\newpage

## Ejercicio 2
Crear una axioma para la siguiente afirmación: \emph{Todas las presentaciones deben tener al menos uno de sus autores inscritos}.

Vayamos por partes:

  - $\exists \text{NombreIns}^{-1}.\text{Inscrito}$ es la clase de Strings que son el NombreIns de al menos un Inscrito.
  - $\exists \text{NombreAut}.(\exists \text{NombreIns}^{-1}.\text{Inscrito})$ es la clase de Autores cuyo NombreAut es el NombreIns de un Inscrito; de otra manera, la clase de Autores que son Inscritos.
  - $\exists \text{P-autor}.(\exists \text{NombreAut}.(\exists \text{NombreIns}^{-1}.\text{Inscrito}))$ es la clase de Presentaciones que tienen al menos un Autor que es Inscrito.
  - $\text{Presentacion} \equiv \exists \text{P-autor}.(\exists \text{NombreAut}.(\exists \text{NombreIns}^{-1}.\text{Inscrito}))$ nos dice que la clase de Presentaciones debe ser la misma que la clase de Presentaciones que tienen al menos un Autor que es Inscrito.

Es decir: \textbf{Todas las presentaciones deben tener al menos un autor inscrito}.

Aquí la expresión completa en grande:

$$\text{Presentacion}\equiv \exists \text{P-autor}.(\exists \text{NombreAut}.(\exists \text{NombreIns}^{-1}.\text{Inscrito}))$$
