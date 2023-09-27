#include "compra.h"


// incrementa el precio de cada producto en un k %
void incrementarPrecios(Compra & c, int k)
{
    float aumento = 1+((float)k/100);
    for(int i=0; i<c.MAX; i++)
    {
        c.lista[i].precio_kg*=aumento;
    }
}

// muestra el listado de productos comprados
void listarCompra(const Compra & c)
{
    for(int i=0; i<c.MAX; i++)
    {

        ///productoToString(c.lista[i]);
        cout << c.lista[i].nombre << "\t" << c.lista[i].peso << "\t\t" << c.lista[i].precio_kg << endl;
    }
}

// función que devuelve el importe total de la compra (sin IVA) y su peso (en kgs)
void obtenerImporteYPeso(const Compra & c, float & precio, float & peso)
{
    peso=0;
    precio=0;
    for(int i=0; i<c.MAX; i++)
    {
        peso+=(float)c.lista[i].peso/1000;
        precio+=c.lista[i].precio_kg*((float)c.lista[i].peso/1000);
    }
}

// función que muestra el "ticket" de compra según el formato sugerido
void mostrarTicketCompra(const Compra & c)
{
    float subtotal;
    float pesosym;
    obtenerImporteYPeso(c, subtotal, pesosym);
    float iva= subtotal*0.21;
    float total = subtotal+iva;
    listarCompra(c);
    cout << "Subtotal:\t\t " << subtotal << endl;
    cout << "IVA(21%):\t\t " << iva << endl;
    cout << "Total de la compra:\t " << total << endl;
}
