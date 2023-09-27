/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Descifrador.h
 * Author: jorgeklock
 *
 * Created on 13 de marzo de 2019, 17:50
 */

#ifndef DESCIFRADOR_H
#define DESCIFRADOR_H

#include <string>
#include <iostream>

using namespace std;

const int VAL_MAX=100;

bool ComienzaPalabra(char v[], int tam, int pos);
bool TerminaPalabra(char v[], int tam, int pos);
void descifra(char v[], int tam, char rta[], int &tams);
string toString(char v[], int tam);


#endif /* DESCIFRADOR_H */

