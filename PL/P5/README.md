# Objetivo 
Generación de código intermedio elemental. No hace falta generar código para subprogramas ni para listas. 

# Ficheros 

ejemplos: carpeta con ejemplos de código en nuestro lenguaje (extensión pl) para probar que todo funciona bien


makefile: crea pl5.exe 

README.md: este mismo fichero 


dec_fun.c : Declaración y traducción de todos los subprogramas del texto fuente (No se va a usar).

dec_dat.h: Fichero para la gestión del tipo estructurado (listas) (no se va a usar). 

tablaSimbolos.h: 

tablaTokens: 


## Ficheros necesarios para crear el compilador 
pl5.c: Main para crear el compilador. Se encarga de leer el fichero con el código fuente. 

sintactico.y: Es el mismo que en la p4   

lexico.l: Es el mismo que en la p4  

generador.c: 
- Incluye las librerías necesarias 
- Funciónes que buscan espacio en memoria
    · char * temporal(void)
    · char * etiqueta(void)


semantica.c: 

## Ficheros generados al hacer make 
y.tab.c, lex.yy.c: Analizadores en c  

y.tab.h: Contiene la tabla de símbolos que usa el analizador léxico 

pl5.exe: Compilador. Ejecutable que recibe como entrada un programa en nuestro lenguaje de programación y lo traduce a c en el fichero salida.c 

salida.c: Código intermedio generado por pl.exe 