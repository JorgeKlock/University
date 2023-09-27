/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particula.cpp
 * Author: jorgeklock
 * 
 * Created on 10 de abril de 2019, 18:29
 */

#include "Particula.h"
#include <math.h>
using namespace std;
Particula::Particula() {
    this->dx=rand()%MAX_VEL;
    this->dy=rand()%MAX_VEL;
    c=Disponibles[rand()%N];
    this->x=((float) rand() / RAND_MAX) * MIN_X;
    this->y=((float) rand() / RAND_MAX) * MIN_Y;
}
Particula::Particula(int nx, int ny)
{
    this->x=nx;
    this->y=ny;
    this->dx=1.0;
    this->dy=1.0;
    c=ROJO;
}
void Particula::mueve_particula(int vancho, int valto) {
   const float factor = 0.95;
   this->x += this->dx;
   this->y += this->dy;
   if (this->x > vancho - RADIO) {
      this->dx = -this->dx * factor;
      this->x = vancho - RADIO;
   }
    else if (this->x < RADIO) {
      this->dx = -this->dx * factor;
      this->x = RADIO;
   }
    else if (this->y > valto - RADIO) {
      this->dy = -this->dy * factor;
      this->y = valto- RADIO;
   }
    else if (this->y < RADIO) {
      this->dy = -this->dy * factor;
      this->y = RADIO;
   }
   //Para añadir gravedad:     this->dy += 0.1;
}
float Particula::distancia (const Particula& P) const
{
    return sqrt(pow(P.getx()-this->getx(),2)+pow(P.gety()-this->gety(),2)); /*raiz de los cuadrados de las diferencias*/ 
}
bool Particula::colision (const Particula& P) const
{
    bool colisiona = false;
    if(this->distancia(P) <= UMBRAL)
    {
         colisiona = true;
    }
    return colisiona;
}
void Particula::rebota(Particula &otra)
{
    float tempdx=this->dx;
    float tempdy=this->dy;
    this->setdx(otra.getdx());
    this->setdy(otra.getdy());
    otra.setdx(tempdx);
    otra.setdy(tempdy);
}
ostream& operator<<(std::ostream &flujo, const Particula &p)
{
    flujo << "Posicion X: " << p.getx() << "\t Posicion Y: " << p.gety();
    flujo << "Velocidad X: " << p.getdx() << "\t Velocidad Y: " << p.getdy();
    flujo << "Color: " << p.getcolor();
    return flujo;
}