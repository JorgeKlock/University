#include "circulo.h"
Circulo::Circulo():centro(0,0), radio(0) {
}

Circulo::Circulo(Punto p, double rradio):centro(p),radio(rradio) {
}

void Circulo::set(Punto p, double rradio) {
	radio = rradio;
	centro = p;
}


Punto Circulo::getCentro()  {
	return centro;
}

double Circulo::getRadio()  {
	return radio;
}

string Circulo::toString() {
    // // devuelve un string con el formato (x,y) radio-(x,y)
    
 string rta = to_string(radio) + "-" + centro.toString();
 return rta;
}

double Circulo::Circulo::area() {
    return PI * radio * radio;
}

double Circulo::distancia (Circulo c2){
    // calcula la distancia entre los dos centros
    double dist = centro.distancia(c2.getCentro());
    return dist;
}

//Comprueba si un punto es interior al círculo
bool Circulo::interior (Punto p){
	bool rta = p.distancia(centro) <= getRadio();
	return rta;
}


