# IC: Ejercicio Frames
## Miguel Lentisco Ballesteros

Ejercicio Frames sobre el Congreso.

**Nota**: si no se indica lo contrario, los atributos son heredables.

```
Tipo: Clase
Nombre: Descriptor
Padre:
Atributos:
  - Etiqueta:
    - Demonio si-añado comprobar_etiq:
        Comprueba que la etiqueta sea única en las instancias de Descriptor
  - Descripción:

Tipo: Clase
Nombre: Presentación
Padre:
Atributos:
  - Tipo:
    - Tipo: Artículo, Conferencia o Poster
  - Título:
  - Nº de referencia:
    - Demonio si-añado comprobar_ref:
        Comprueba que la referencia sea única en las instancias de Presentción
  - Autor/es:
    - Multivaluado
    - Demonio si-añado comprobar_autor:
        Comprueba que los autores existen en una instancia de Autor
  - Lista descriptores:
    - Multivaluado
    - Demonio si-añado comprobar_descrip:
        Comprueba que los descriptores existen en una instancia de Descriptor
  - Confirmado:
    - Tipo: Sí o No

Tipo: Clase
Nombre: Autor
Padre:
Atributos:
  - Nombre:
  - Apellidos:
  - Universidad/centro trabajo:
  - Nº articulos presentados:

Tipo: Clase
Nombre: Persona inscrita
Padre:
Atributos:
  - Nombre:
  - Cantidad abonada:
  - Nº tarjeta credito:
  - Estudiante: No

Tipo: Clase
Nombre: Estudiante inscrito
Padre: Persona inscrita
Atributos:
  - Universidad:
  - Estudiante: Sí

Tipo: Clase
Nombre: Sesión
Padre:
Atributos:
  - Día:
    - Tipo: Miércoles, Jueves o Viernes
  - Turno:
    - Tipo: Mañana1, Mañana2 o Tarde1

Tipo: Clase
Nombre: Sesión articulos
Padre: Sesión
Atributos:
  - Referencia artículo 1:
    - Demonio si-añado comprobar_ref_art:
        Comprueba que la referencia exista con una instancia
        de Presentación de tipo Artículo
  - Referencia artículo 2:
    - Demonio si-añado comprobar_ref_art:
        Comprueba que la referencia exista con una instancia
        de Presentación de tipo Artículo
  - Referencia artículo 3:
    - Demonio si-añado comprobar_ref_art:
        Comprueba que la referencia exista con una instancia
        de Presentación de tipo Artículo

Tipo: Clase
Nombre: Sesión conferencia
Padre: Sesión
Atributos:
  - Referencia conferencia:
    - Demonio si-añado comprobar_ref_conf:
      Comprueba que la referencia exista con una instancia
      de Presentación de tipo Conferencia

Tipo: Clase
Nombre: Sesión poster
Padre: Sesión
Atributos:
  - Lista referencia presentación:
    - Multivaluado
    - Demonio si-añado comprobar_ref_poster:
      Comprueba que las referencias existan con una instancia
      de Presentación de tipo Poster
```
