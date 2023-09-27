/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mainLed.cpp
 * Author: jorgeklock
 *
 * Created on 13 de marzo de 2019, 19:10
 */

#include <cstdlib>
#include "tirador.h"

/*
 * 
 */
int main(int argc, char** argv) {
    int tamano=20;
    bool tira[tamano]={0,1,0,1,0,1,1,0,1,0,1,1,1,0,0,1,0,0,1,1};
    apagaTodo(tira, tamano);
    cout << toString(tira, tamano)<< endl;
    for (int i=0; i<tamano; i+=2)
    {
        encenderLed(tira, tamano, i);
    }
    cout << toString(tira, tamano)<< endl;
    for (int i=0; i<tamano; i+=2)
    {
        apagarLed(tira, tamano, i);
        encenderLed(tira, tamano, i+1);
    }
    cout << toString(tira, tamano)<< endl;
    return 0;
}

