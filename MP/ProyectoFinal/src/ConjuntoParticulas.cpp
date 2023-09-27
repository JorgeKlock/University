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
const int TAM_BLOQUE = 5;

ConjuntoParticulas::ConjuntoParticulas()
{
    this->capacidad=0;
    this->utiles=0;
    set=0;
}
ConjuntoParticulas::ConjuntoParticulas(int capacity) 
{
    this->capacidad=capacity;
   
    set=new Particula[capacity];
    this->utiles=capacity;
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
     if(this->set != 0)
        delete [] this->set;
     
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
    {
        for(int i=posicion; i<utiles-1; i++)
        {
            this->set[i]=this->set[i+1];//cuidado con esto!!!
        }
        this->utiles--;
        if((this->capacidad-this->utiles)>TAM_BLOQUE)
            redimensionar(this->capacidad-TAM_BLOQUE);
    }
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
    for(int i=this->getutiles()-1; i>=0; i--)
    {
        this->BorraParticula(i);
    }
    
    this->redimensionar(c2.getcapacidad());
    
    for(int i=0; i<c2.getutiles(); i++)
    {
        this->AgregaParticula(c2.ObtieneParticula(i));
    }
}
ostream& operator<<(ostream &flujo, const ConjuntoParticulas &c)
{
    
    flujo << "El conjunto tiene: " << c.getutiles()<< " Particulas." << endl;
    flujo << "Hay espacio para un total de: " << c.getcapacidad() << " Particulas" << endl;
    
    
     for(int i=0; i<c.getutiles(); i++)
     {
        flujo << "Particula numero " << i << ": ";
        flujo << c.ObtieneParticula(i) << endl;
     }
 return flujo;
}
ConjuntoParticulas ConjuntoParticulas::operator+(const ConjuntoParticulas &cd) const
{
    ConjuntoParticulas concatenado(this->getutiles()+cd.getutiles());
    for(int i=0; i<this->getutiles(); i++)
    {
        concatenado.ReemplazaParticula(i, this->ObtieneParticula(i));
    }
    for(int i=0; i<cd.getutiles(); i++)
    {
        concatenado.ReemplazaParticula((i+this->getutiles()), cd.ObtieneParticula(i));
    }
    return concatenado;
}