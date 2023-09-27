/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "tirador.h"
void apagaTodo(bool v[], int tam)
{
    if(tam<=TAM_MAX){
    for(int i=0; i<tam; i++)
    {
        v[i]=false;
    }
    }
    else
        cout << "Valor incorrecto, la operacion no se realizara" << endl;
}

void enciendeTodo(bool v[], int tam)
{
    if(tam<=TAM_MAX){
    for(int i=0; i<tam; i++)
    {
        v[i]=true;
    }
    }
    else
        cout << "Valor incorrecto, la operacion no se realizara" << endl;
    
}

void apagarLed(bool v[], int tam, int pos)
{
    if(tam<=TAM_MAX && pos>=0 && pos<=TAM_MAX){
    v[pos]=false;
    }
    else
        cout << "Valor incorrecto, la operacion no se realizara" << endl;
}

void encenderLed(bool v[], int tam, int pos)
{
    if(tam<=TAM_MAX && pos>=0 && pos<=TAM_MAX){
    v[pos]=true;
    }
    else
        cout << "Valor incorrecto, la operacion no se realizara" << endl;
}

string toString (bool v[], int tam)
{
    if(tam<=TAM_MAX){
    string s;
    for(int i=0; i<tam; i++)
    {
        if(v[i])
            s+="encendido ";
        else
            s+="apagado ";
    }
    }
    else
        cout << "Valor incorrecto, la operacion no se realizara" << endl;
}
