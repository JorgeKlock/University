/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Simulador.cpp
 * Author: jorgeklock
 * 
 * Created on 15 de mayo de 2019, 18:33
 */

#include "Simulador.h"

Simulador::Simulador(ConjuntoParticulas mov, ConjuntoParticulas fij, int anch, int alt): moviles(mov), fijas(fij), ancho(anch), alto(alt)
{
    miniwin::vredimensiona(this->ancho, this->alto);
}

Simulador::Simulador(const Simulador& orig) {
}

Simulador::~Simulador() {
    miniwin::vcierra();
}
void Simulador::Pintar(int milisegundos) const
{
    miniwin::borra();
    this->PintaMoviles();
    this->PintaFijas();
    miniwin::refresca();
    miniwin::espera(milisegundos);
}
void Simulador::PintaMoviles() const
{
    int cantidad=this->moviles.getutiles();
    Particula p;
    for(int i=0; i<cantidad; i++)
    {
        p=this->moviles.ObtieneParticula(i);
        miniwin::color(p.getcolor());
        miniwin::circulo_lleno(p.getx(), p.gety(), RADIO);
    }
}
void Simulador::PintaFijas() const
{
    int cantidad=this->fijas.getutiles();
    Particula p;
    for(int i=0; i<cantidad; i++)
    {
        p=this->fijas.ObtieneParticula(i);
        miniwin::color(p.getcolor());
        miniwin::rectangulo_lleno(p.getx()-RADIO/2, p.gety()-RADIO/2, p.getx()+RADIO/2, p.gety()+RADIO/2);
    }
}
void Simulador::Rebotes()
{
    for(int i=0; i<this->moviles.getutiles(); i++)
    {
        for(int j=0; j<this->fijas.getutiles(); j++)
        {
            if(this->moviles.ObtieneParticula(i).colision(this->fijas.ObtieneParticula(j)))
            {
                
                //HACER QUE DE LA VUELTA
                 float ratiocambio=-1;
                 this->moviles.ObtieneParticulaReal(i)->setdx(this->moviles.ObtieneParticula(i).getdx()*ratiocambio);
                 this->moviles.ObtieneParticulaReal(i)->setdy(this->moviles.ObtieneParticula(i).getdy()*ratiocambio);
                //APARECER Y DESAPARECER SEGUN COLOR
                 //SI MISMO COLOR COPIAR
                 if(this->moviles.ObtieneParticula(i).getcolor()==this->fijas.ObtieneParticula(j).getcolor())
                 {
                    Particula medionueva;
                    medionueva.setcolor(this->moviles.ObtieneParticula(i).getcolor());
                    medionueva.setdx(this->moviles.ObtieneParticula(i).getdx());
                    medionueva.setdy(this->moviles.ObtieneParticula(i).getdy());
                    this->moviles.AgregaParticula(medionueva);
                 }
                 //SI DISTINTO COLOR ELIMINAR
                  else
                 {
                  this->moviles.BorraParticula(i);   
                 }
            }
        }
    }
}
void Simulador::Step()
{
    this->Rebotes();
    this->moviles.Mover(this->ancho, this->alto);
    this->moviles.GestionarColisiones();
}