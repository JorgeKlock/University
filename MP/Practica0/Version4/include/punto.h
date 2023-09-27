#ifndef PUNTO_H
#define PUNTO_H


#include <iostream>
#include <cmath> 
#include <string>

using namespace std;


class Punto {
private:
    double x; // coordenada x del punto
    double y; // coordenada y del punto

public:
    Punto(); //constructor. Pone a 0 las dos coordenadas
    Punto(double px, double py); // constructor. Inicializa un punto con dos valores x y
    double getX(); 
    double getY(); 
    void setX(double newXValue); 
    void setY(double newYValue); 
    string toString(); //  devuelve el contenido del punto como un string
    double distancia(Punto p2); // calcula la distancia a otro punto
    Punto puntoMedio(Punto p2); //devuelve el punto medio entre el objeto implicito y p2
};


#endif 
