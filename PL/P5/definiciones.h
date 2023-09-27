
#ifndef DEFINICIONES
    #define DEFINICIONES

typedef enum {
	entero,
	real,
	caracter,
	booleano,
	lista,
	noasignado
} dtipo ;



typedef struct {
	int atrib ;
	char *lexema ;
	dtipo tipo ;
	int cantidad;	
	int dim;
	dtipo subt;
	char *traduccion;
	char *varTemporal;
} atributo ;


typedef struct {
	char *EtiquetaEntrada ;
	char *EtiquetaSalida ;
	char *EtiquetaElse ;
	char *NombreVarControl ;
} DescriptorDeInstrControl ;

#endif
