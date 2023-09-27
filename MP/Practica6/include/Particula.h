/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particula.h
 * Author: jorgeklock
 *
 * Created on 10 de abril de 2019, 18:29
 */

#ifndef PARTICULA_H
#define PARTICULA_H
#include "miniwin.h"
#include "Constantes.h"

using namespace miniwin;


class Particula {
private:
   float x, y;
   float dx, dy;
   Color c;

public:
    //Constructores y destructores
    Particula();
    Particula(int nx, int ny);
    virtual ~Particula();
    
   
    //Gets
    float getx() const {return x;};
    float getdx() const {return dx;};
    float gety() const {return y;};
    float getdy() const {return dy;};
    Color getcolor() const {return c;}; 
    //Sets
    void setx(float x) {this->x=x;};
    void setdx(float dx) {this->dx=dx;};
    void sety(float y) {this->y=y;};
    void setdy(float dy) {this->dy=dy;};
    void setcolor(Color nc) {this->c=nc;};
    //Otros
    void mueve_particula(int vancho, int valto);
    float distancia (const Particula& P) const;
    bool colision (const Particula& P) const;
    void rebota(Particula &otra);


};

std::ostream& operator<<(std::ostream &flujo, const Particula &p)
{
    flujo << "Posicion X: " << p.getx() << "\t Posicion Y: " << p.gety();
    flujo << "Velocidad X: " << p.getdx() << "\t Velocidad Y: " << p.getdy();
    flujo << "Color: " << p.getcolor();
}

#endif /* PARTICULA_H */

