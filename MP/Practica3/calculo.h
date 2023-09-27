/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Calculo.h
 * Author: Jorge Gangoso Klock
	DNI: 49398653N
	Grupo: Miercoles
 *
 * Created on 20 de marzo de 2019, 18:24
 */

#ifndef CALCULO_H
#define CALCULO_H

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int FIL = 12;	
const int COL = 31;

void RellenarMatriz(int min, int max, int M[FIL][COL]);
double MediaMensualAjustada(int mes, int M[FIL][COL]);
void ResumenMaximasMinimas(int maximas[FIL], int minimas[FIL], int M[FIL][COL]);
bool secuenciaDiasCalidos(int temp, int dias, int mes, int M[FIL][COL]);
void mostrarMatriz(int M[FIL][COL]);

#endif /* CALCULO_H */

