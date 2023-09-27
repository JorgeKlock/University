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
#include "Constantes.h"

using namespace std;

class Particula {
private:
   float x, y;
   float dx, dy;
   Color c;

public:
    //Constructores y destructores
    Particula();
    Particula(int nx, int ny);
    virtual ~Particula() {};
    //Gets
    float getx() const {return x;};
    float getdx() const {return dx;};
    float gety() const {return y;};
    float getdy() const {return dy;};
    Color getcolor() const {return c;}; 
    //Get objeto
    Particula* getparticula() {return this;};
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
ostream& operator<<(std::ostream &flujo, const Particula &p);

#endif /* PARTICULA_H */


