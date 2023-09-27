/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConjuntoParticulas.cpp
 * Author: jorgeklock
 * 
 * Created on 3 de mayo de 2019, 18:36
 */

#include "ConjuntoParticulas.h"
using namespace std;
const int TAM_BLOQUE = 5;

ConjuntoParticulas::ConjuntoParticulas(int capacity) 
{
    //this->capacidad=capacity;
   
    set=new Particula[capacity];
    for(int i=0; i<capacity; i++)
    {
        Particula a;
        set[i]= a;
    }
     //this->utiles=capacity;
}

ConjuntoParticulas::ConjuntoParticulas(const ConjuntoParticulas& orig) {
    this->capacidad=orig.getcapacidad();
    this->utiles=orig.getutiles();
    this->set=new Particula[this->getcapacidad()];
    for(int i=0; i<orig.getutiles(); i++)
    {
        set[i]=orig.ObtieneParticula(i);
    }
}

ConjuntoParticulas::~ConjuntoParticulas() {
    delete [] set;
}
 void ConjuntoParticulas::redimensionar(int capacidadnueva)
 {
     if(capacidadnueva<0) capacidadnueva=0;
     this->capacidad=capacidadnueva;
     Particula* aux= new Particula[capacidadnueva];
     for(int i=0; i<this->getutiles(); i++)
     {
         aux[i]=this->set[i];
     }
     if(this->set != 0){
     delete [] this->set;}
     
     set=aux;
 }
 
void ConjuntoParticulas::AgregaParticula(Particula p)
{
    if(this->utiles == this->capacidad)
        this->redimensionar(this->capacidad+TAM_BLOQUE);
    
    this->set[this->utiles]=p;
    this->utiles++;
}
void ConjuntoParticulas::BorraParticula(int posicion)
{
    if(posicion>=0 && posicion<utiles)
    for(int i=posicion; i<utiles-1; i++)
    {
        this->set[i]=this->set[i+1];//cuidado con esto!!!
    }
    this->utiles--;
    if((this->capacidad-this->utiles)>TAM_BLOQUE)
        redimensionar(this->capacidad-TAM_BLOQUE);
}
void ConjuntoParticulas::ReemplazaParticula(int suplantada, Particula p)
{
    if(suplantada>=0 && suplantada<utiles && suplantada>=0 && suplantada<utiles)
    {
        this->set[suplantada]=p;
    }
}
void ConjuntoParticulas::Mover(int vancho, int valto)
{
    for(int i=0; i<utiles; i++)
    {
        this->set[i].mueve_particula(vancho, valto);
    }
}
void ConjuntoParticulas::GestionarColisiones()
{
    for(int i=0; i<(this->getutiles()-1); i++)
    {
        bool chocado=false;
        for(int j=i+1; j<this->getutiles() && !chocado; j++)
        {
            if(this->set[i].colision(this->set[j])==true)
            {
                 this->set[i].rebota(this->set[j]);
                 chocado=true;
            }
                       
        }
    }
     
}
void ConjuntoParticulas::operator =(const ConjuntoParticulas& c2)
{
    this->capacidad=c2.getcapacidad();
    this->redimensionar(this->capacidad);
    this->utiles=c2.getutiles();
    for(int i=0; i<this->utiles; i++)
    {
        this->set[i]=c2.ObtieneParticula(i);
    }
    
}