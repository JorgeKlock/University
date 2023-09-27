#ifndef COMPRA_H
#define COMPRA_H
#include "producto.h"


struct Compra
{
    static const int MAX = 10;
    Producto lista[MAX];

};

    void incrementarPrecios(Compra & c, int k);
    void listarCompra(const Compra & c);
    void obtenerImporteYPeso(const Compra & c, float & precio, float & peso);
    void mostrarTicketCompra(const Compra & c);



#endif
