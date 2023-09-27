/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jorgeklock
 *
 * Created on 13 de marzo de 2019, 17:47
 */

#include <cstdlib>
#include "Descifrador.h"

/*
 * 
 */
int main(int argc, char** argv) {

    int tamano=10;
    char v[tamano]={'H','i','u','o',' ',' ','l','i','a',' '};
    int tamanosalida;
    char v2[tamano];
    cout << toString (v, tamano)<<endl;
    descifra(v, tamano, v2, tamanosalida);
    cout << toString(v2, tamanosalida)<<endl;
    
    
    
    
    
    
    return 0;
}

