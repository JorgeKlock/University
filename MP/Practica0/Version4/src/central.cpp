#include "punto.h"
#include "circulo.h"
#include "punto.h"

int main()
{
	// Crear los circulos
	Punto centro1(0,0), centro2(10,10);
    Circulo c1(centro1,10),c2(centro2,5); 
   
    
    // realizar los calculos

	Punto aux = c1.getCentro();
	Punto centroNuevo;
	double radioNuevo;
    
	centroNuevo = aux.puntoMedio(c2.getCentro());
	radioNuevo = aux.distancia(c2.getCentro()) / 2.0;
	Circulo c3(centroNuevo, radioNuevo);


	// mostrar resultados
    
    
    cout << "\nLos circulos son\n";
	cout << "Circulo 1 -> " << c1.toString() << ", area: " << c1.area() << endl;
	cout << "Circulo 2 -> " << c2.toString() << ", area: " << c2.area() << endl;
	cout << "Circulo 3 -> " << c3.toString() << ", area: " << c3.area() << endl;
    
    
    cout << endl;
int a;
cin >> a;
}
