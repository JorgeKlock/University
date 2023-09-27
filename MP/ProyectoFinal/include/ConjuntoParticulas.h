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
    ConjuntoParticulas();
    ConjuntoParticulas(int capacity);
    ConjuntoParticulas(const ConjuntoParticulas& orig);
    virtual ~ConjuntoParticulas();
    
    //gets
    int getcapacidad() const {return capacidad;};
    int getutiles() const {return utiles;};
    Particula ObtieneParticula(int posicion)const {return set[posicion];};
    Particula* ObtieneParticulaReal(int posicion) {return set[posicion].getparticula();};
    //Otros
    void AgregaParticula(Particula p);
    void BorraParticula(int posicion);
    void ReemplazaParticula(int suplantada, Particula p);
    void Mover(int vancho, int valto);
    void GestionarColisiones();
    //sobrecarga de operadores
    void operator=(const ConjuntoParticulas &c2);
    ConjuntoParticulas operator+(const ConjuntoParticulas &cd) const;
};

ostream& operator<<(ostream &flujo, const ConjuntoParticulas &c);
#endif /* CONJUNTOPARTICULAS_H */

