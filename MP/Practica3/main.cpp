/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Jorge Gangoso Klock
 * DNI: 49398653N
 * Grupo: Miercoles
 * Created on 20 de marzo de 2019, 18:17
 */

#include <cstdlib>
#include "calculo.h"

/*
 * 
 */
#define sangria "\t"
#define linea "\n"
int main(int argc, char** argv) {
    
    int M[FIL][COL];
    int min;
    int max;
    char ver;
    int choice;
    cout << sangria << sangria << "Practica 3 - Temperaturas" << linea;
    cout << sangria << sangria << "Jorge Gangoso Klock 49398653N" << linea;
    cout << linea << linea <<"Antes de comenzar rellenaremos la matriz con valores aleatorios entre min y max." << linea;
    cout << linea << sangria << "Introduzca valor de min: ";
    cin >>min;
    cout << linea << sangria << "Introduzca valor de max: ";
    cin >>max;
    RellenarMatriz(min, max, M);
    cout << linea << "Desea ver la matriz?(s/n): ";
    cin >> ver;
	if (ver == 's')
	{
		mostrarMatriz(M);
		system("pause");
	}
    do{	
		system("cls");
		cout << sangria << "**** MENU PARA EL PROCESAMIENTO DE TEMPERATURAS ****" << linea;
		cout << "1.-VOLVER A RELLENAR LA MATRIZ" << linea;
		cout << "2.-CALCULAR LA MEDIA MENSUAL AJUSTADA" << linea;
		cout << "3.-OBTENER TEMPERATURAS MAXIMAS Y MINIMAS DE CADA MES" << linea;
		cout << "4.-BUSCAR SECUENCIA DE TEMPERATURAS SUPERIORES A UN VALOR" << linea;
		cout << "0.-SALIR" << linea;
		cout << linea << sangria << "Introduzca su seleccion: ";
		cin >> choice;

		switch (choice)
		{
		case 1: 
		{
			char ver;
			system("cls");
			cout << linea << sangria << "Introduzca valor de min: ";
			cin >> min;
			cout << linea << sangria << "Introduzca valor de max: ";
			cin >> max;
			RellenarMatriz(min, max, M);
			cout << linea << "Desea ver la matriz?(s/n): ";
			cin >> ver; 
			if (ver == 's')
				mostrarMatriz(M);
			
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			int mes;
			cout << "Indique el mes(1-12): ";
			cin >> mes;
			cout << "La media mensual ajustada es: " << MediaMensualAjustada(mes, M) << linea;
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			int maximas[FIL];
			int minimas[FIL];
			ResumenMaximasMinimas(maximas, minimas, M);
			cout << "las maximas son: ";
			for (int i = 0; i < FIL; i++)
				cout << maximas[i] << " ";
			cout << linea;
			cout << "las minimas son: ";
			for (int i = 0; i < FIL; i++)
				cout << minimas[i] << " ";
			cout << linea;
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			int messec;
			int diassec;
			int temperaturasec;
			cout << "Indique el mes para el que se buscara la secuencia(1-12): ";
			cin >> messec;
			cout << "Indique la cantidad de dias consecutivos: ";
			cin >> diassec;
			cout << "Indique la temperatura que debe superarse durante la secuencia: ";
			cin >> temperaturasec;
			if (secuenciaDiasCalidos(temperaturasec, diassec, messec, M))
				cout << "La secuencia se cumple" << linea;
			else
				cout << "La secuencia no se cumple" << linea;
			system("pause");
			break;
		}
		case 0:
		{
			system("cls");
			cout << "Gracias por usar el programa, a continuacion se detendra" << linea;
			system("pause");
			break;
		}
		default:
		{
			system("cls");
			cout << "Opcion incorrecta, intentelo de nuevo";
			system("pause");
		}
		}
        
        
    }while(choice!=0);
    
    return 0;
}

