/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jorgeklock
 *
 * Created on 27 de marzo de 2019, 17:41
 */

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
const int TOPE=20;
const int INICIO=0;

using namespace std;

/* SE PUEDE CREAR UNA FUNCION INTERCAMBIAR
 * 
 */
void rellenarvector(int v[])
{
    for(int i=0; i<TOPE; i++)
    {
        v[i]=(rand()%40);
    }
    
}
void mostrarvector(int v[])
{
    for(int i=0; i<TOPE; i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main(int argc, char** argv) {
    
    int v[TOPE];
    rellenarvector(v);
    mostrarvector(v);
    int referencia=v[INICIO];
    int * p_ini=&v[INICIO+1];
    int * p_fin=&v[TOPE-1];
    while(p_ini<p_fin) //MIENTRAS NO SE CRUCEN
    {
        while(*p_ini<=referencia && p_ini<p_fin)
        {
            p_ini++;            
        }
        
        while(*p_fin>referencia && p_ini<p_fin)
        {
            p_fin--;
        }
        
        if(p_ini<p_fin)
        {
                //INTERCAMBIAR
                int temp=*p_ini;
                *p_ini=*p_fin;
                *p_fin=temp;  
          
        }
    }
    mostrarvector(v);
    //TERMINADO
    
    return 0;   
}

