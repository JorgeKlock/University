#include "punto.h"

Punto::Punto():x(0),y(0) {
}

Punto::Punto(double px, double py):x(px),y(py) {
}

double Punto::getX() {
	return x;
}

double Punto::getY() {
	return y;
}

void Punto::setX(double px) {
	x = px;
}

void Punto::setY(double py) {
	y = py;
}

string Punto::toString() {
 // devuelve un string con el formato (x,y)
 string rta = "(" + to_string(x) + "," + to_string(y) + ")";
 return rta;
}

double Punto::distancia(Punto p2){
    double dx = p2.getX() - getX();
    double dy = p2.getY() - getY();
    return sqrt(dx * dx + dy * dy);
}


Punto Punto::puntoMedio(Punto p2){
    Punto pMedio;
    pMedio.setX((getX() + p2.getX()) / 2.0);
    pMedio.setY((getY() + p2.getY()) / 2.0);
    return pMedio;	
}
