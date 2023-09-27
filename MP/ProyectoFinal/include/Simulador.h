/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Simulador.h
 * Author: jorgeklock
 *
 * Created on 15 de mayo de 2019, 18:33
 */

#ifndef SIMULADOR_H
#define SIMULADOR_H
#include "ConjuntoParticulas.h"


class Simulador {
private:
    ConjuntoParticulas moviles;
    ConjuntoParticulas fijas;
    //Tamano ventana
    int ancho, alto;
    //Metodos privados
    void PintaMoviles() const;
    void PintaFijas() const;
    
public:
    Simulador(ConjuntoParticulas mov, ConjuntoParticulas fij, int anch, int alt);
    Simulador(const Simulador& orig);
    virtual ~Simulador();
    
    //Get
    ConjuntoParticulas getMoviles() const {return this->moviles;};
    ConjuntoParticulas getFijas() const {return this->fijas;};
    //Set
    void setMoviles(ConjuntoParticulas mov) {this->moviles=mov;};
    void setFijas(ConjuntoParticulas fij) {this->fijas=fij;};
    //Otros
    void Pintar(int milisegundos) const;
    void Step();
    void Rebotes();
};

#endif /* SIMULADOR_H */

