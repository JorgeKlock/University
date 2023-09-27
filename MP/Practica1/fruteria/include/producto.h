#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <string>
using namespace std;

struct Producto
{
    string nombre;
    int peso; // en gramos
    float precio_kg;
};


    string productoToString(Producto a);
    Producto creaProducto(string nombre, int peso, float precio);

#endif
