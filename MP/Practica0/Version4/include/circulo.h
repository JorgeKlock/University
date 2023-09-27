#ifndef CIRCULO_H
#define CIRCULO_H
#include "punto.h" 
class Circulo {
private:
    Punto centro; // Centro del círculo
    double radio; // radio del círculo

public:

	const double PI = 3.14159265;
    Circulo(); // Constructor: Pone a 0 el punto y el radio
    Circulo(Punto centro, double rradio); // Constructor: Inicializa el círculo con un centro y un radio
    void set(Punto centro, double rradio); // Asigna el centro y el radio a un circulo
    Punto getCentro(); 
    double getRadio(); 
    string toString(); // devuelve el contenido del circulo como un string
    double area(); // Devuelve el �rea de un círculo
    double distancia (Circulo c2);
    bool interior (Punto p); // true si p est� contenido en el círculo
};

#endif 
