#include "producto.h"




// crea una variable de tipo Producto y la devuelve
Producto creaProducto(string nombre, int peso, float precio)
{
	Producto nuevo;
	nuevo.nombre= nombre;
	nuevo.peso=peso;
	nuevo.precio_kg=precio;
	return nuevo;
}
string productoToString(Producto a)
{
    string rta;
    rta = a.nombre + "\t\t" + to_string(a.peso) + "\t" + to_string(a.precio_kg);
    return rta;
}
