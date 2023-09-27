/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   problema1.h
 * Author: jorgeklock
 *
 * Created on 3 de abril de 2019, 18:14
 */

#ifndef PROBLEMA1_H
#define PROBLEMA1_H

#include <cstdlib>
#include <iostream>

using namespace std;

void Mostrarvector(int* p, int cap);
void Redimensiona(int* &p, int tipo, int &cap);
void Anadirdato(int* &p, int dato, int llenos, int &cap);
void obtenerSegmento(int* &v, int cap, int* &sol, int &tam);


#endif /* PROBLEMA1_H */

