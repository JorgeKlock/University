/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Descifrador.h"



bool ComienzaPalabra(char v[], int tam, int pos)
{
    bool comienza=false;
    if (tam>=0 && tam<=VAL_MAX && pos>=0 && pos<=tam)//Comprobamos que la entrada es correcta
    {
        if(v[pos]!=' ' && pos==0) //Si es el primer elemento y no es un espacio comienza palabra
            comienza=true;
        else if (v[pos]!=' ' && v[pos-1]==' ') //Si no es un espacio y antes hay un espacio
            comienza=true;       
    }
    //Si la entrada no es correcta
    else
        cout << endl << "Entrada incorrecta, la operacion no se realizara";
    
    return comienza;
}
bool TerminaPalabra(char v[], int tam, int pos)
{
    bool comienza=false;
    if (tam>=0 && tam<=VAL_MAX && pos>=0 && pos<=tam)//Comprobamos que la entrada es correcta
    {
        if (v[pos]!=' ' && v[pos+1]==' ') //Si no es un espacio y despues hay un espacio
            comienza=true;  
    }
    
    //Si la entrada no es correcta
    else
    {
        cout << endl << "Entrada incorrecta, la operacion no se realizara";
    }
    return comienza;
}

void descifra(char v[], int tam, char rta[], int &tams)
{
    if(tam>0 && tam<=VAL_MAX){ //Comprobamos que la entrada es correcta
        
    int contador=0;
    /*Dar Valor a n_rta e ir rellenanodo rta*/
    
    for(int i=0; i<tam; i++)
    {
        if(ComienzaPalabra(v, tam, i)||TerminaPalabra(v, tam, i))
        {
            rta[contador]=v[i];
            contador++;
        }
    }
    tams=contador;
    }
    //Si la entrada no es correcta
    else
        cout << endl << "Entrada incorrecta, la operacion no se realizara";
}


string toString(char v[], int tam)
{
    string s;
    if(tam>0 && tam<=VAL_MAX)
    { //Comprobamos que la entrada es correcta
    for(int i=0; i<tam;i++)
    {
        s+= v[i];
    }
    }
    else 
        s="Entrada incorrecta, la operacion no se realizara";
    return s;
}