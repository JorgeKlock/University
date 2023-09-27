/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jorgeklock
 *
 * Created on 27 de marzo de 2019, 18:56
 */

#include <cstdlib>
#include <iostream>
using namespace std;


int longitud_cadena (char* cad)
{
    char* aux=cad;
    int longitud=0;
    while(*aux!='\0')
    {
        longitud++;
        aux++;
    }
    return longitud;
}
bool palindromo (char* cad)
{
    bool palindromo=true;
    char* aux1=cad;
    char* aux2=cad+longitud_cadena(cad)-1;
    while(palindromo && aux1<aux2)
    {
        if(*aux1==*aux2)
        {
            aux1++;
            aux2--;
        }
        else
        {
            palindromo=false;
        }
    }
    return palindromo;
}
int comparar_cadenas(char* c1, char* c2)
{
    int tamano1=0;
    int tamano2=0;
    char* aux=c1;
    while(*aux!='\0')
    {
        tamano1+=*aux;
        aux++;
    }
    aux=c2;
    while(*aux!='\0')
    {
        tamano2+=*aux;
        aux++;
    }
    return tamano1-tamano2;
    
}
/*
 * 
 */
int main(int argc, char** argv)
{

    char* cadena= new char[10];
    for(int i=0; i<10;i++)
    {
        cadena[i]='w';
    }
    cadena[4]='a';
    cout << palindromo(cadena);
    return 0;
}

