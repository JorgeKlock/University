/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tirador.h
 * Author: jorgeklock
 *
 * Created on 13 de marzo de 2019, 19:11
 */

#ifndef TIRADOR_H
#define TIRADOR_H

#include <string>
#include <iostream>
const int TAM_MAX=100;
using namespace std;
void apagaTodo(bool v[], int tam);
void enciendeTodo(bool v[], int tam);
void apagarLed(bool v[], int tam, int pos);
void encenderLed(bool v[], int tam, int pos);
string toString (bool v[], int tam);

#endif /* TIRADOR_H */

