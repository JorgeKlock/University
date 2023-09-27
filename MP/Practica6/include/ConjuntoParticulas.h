/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConjuntoParticulas.h
 * Author: jorgeklock
 *
 * Created on 3 de mayo de 2019, 18:36
 */

#ifndef CONJUNTOPARTICULAS_H
#define CONJUNTOPARTICULAS_H

#include "Particula.h"



class ConjuntoParticulas {
    private:
        Particula *set;
        int capacidad;
        int utiles;
        void redimensionar(int capacidadnueva);
public:
    ConjuntoParticulas(int capacity);
    ConjuntoParticulas(const ConjuntoParticulas& orig);
    virtual ~ConjuntoParticulas();
    
    //gets
    int getcapacidad() const {return capacidad;};
    int getutiles() const {return utiles;};
    Particula ObtieneParticula(int posicion) const {return set[posicion];};
    
    //sets

    //Otros
    void AgregaParticula(Particula p);
    void BorraParticula(int posicion);
    void ReemplazaParticula(int suplantada, Particula p);
    void Mover(int vancho, int valto);
    //gestionarcolisiones usando el metodo de particula
    void GestionarColisiones();
    //sobrecarga de operadores
    void operator=(const ConjuntoParticulas &c2);
};
std::ostream& operator<<(std::ostream &flujo, const ConjuntoParticulas &c)
{
    
    flujo << "El conjunto tiene: " << c.getutiles()<< "Particulas." << std::endl;
    flujo << "Hay espacio para un total de: " << c.getcapacidad() << "Particulas" << std::endl;
    
    
     for(int i=0; i<c.getutiles(); i++)
     {
        flujo << "Particula numero " << i << ": ";
        flujo << c.ObtieneParticula(i) << std::endl;
     }
     
    
}
#endif /* CONJUNTOPARTICULAS_H */

