
#include "TestOtros.h"
#include "ConjuntoInt.h"
#include "Graficas.h"
#include "Mtime.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "Constantes.h"
using namespace std;

///* Constantes simbólicas para indicar el metodo de ordenacion*/
//enum algoritmos { BURBUJA, INSERCION, SELECCION};
///* Constantes para indicar el Orden del metodo de ordenacion*/
//enum ordenes { CUADRADO, NlogN};
///* Constantes para indicar el Numero de repeticiones para el caso medio de cada método de búsqueda */
//static const int NUMREPETICIONES=10;
///* Constantes para indicar la variacion de las tallas del vector */
//enum valoresTallas { tallaIni = 100,tallaFin = 1000,incTalla = 100}; 

static int const MAX_LONG = 10;
/*1!!! -Añadir el push back para que se sume a la cantidad de algoritmos en uso*/
TestOtros::TestOtros()
{
	nombreAlgoritmo.push_back("Floyd");
	nombreAlgoritmo.push_back("Fibonacci");
	nombreAlgoritmo.push_back("Hanoi");
}
TestOtros::~TestOtros() {}

int ** ReservaMatriz(int dim)
{
	int **M;
	if (dim <= 0)
	{
		cerr << "\n ERROR: Dimension de la matriz debe ser mayor que 0" << endl;
		exit(1);
	}
	M = new int *[dim];
	if (M == NULL)
	{
		cerr << "\n ERROR: No puedo reservar memoria para un matriz de "
			<< dim << " x " << dim << "elementos" << endl;
		exit(1);
	}
	for (int i = 0; i < dim; i++)
	{
		M[i] = new int[dim];
		if (M[i] == NULL)
		{
			cerr << "ERROR: No puedo reservar memoria para un matriz de "
				<< dim << " x " << dim << endl;
			for (int j = 0; j < i; j++)
				delete[] M[i];
			delete[] M;
			exit(1);
		}
	}
	return M;
}


/**********************************************************************/

void LiberaMatriz(int ** & M, int dim)
{
	for (int i = 0; i < dim; i++)
		delete[] M[i];
	delete[] M;
	M = NULL;
}


/**********************************************************************/
void RellenaMatriz(int **M, int dim)
{
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			if (i != j)
				M[i][j] = (rand() % MAX_LONG);
}


/**********************************************************************/
void Floyd(int **M, int dim)
{
	for (int k = 0; k < dim; k++)
		for (int i = 0; i < dim; i++)
			for (int j = 0; j < dim; j++)
			{
				int sum = M[i][k] + M[k][j];
				M[i][j] = (M[i][j] > sum) ? sum : M[i][j];
			}
}

int fibo(int n)
{
	if (n < 2)
		return 1;
	else
		return fibo(n - 1) + fibo(n - 2);
}

void hanoi(int M, int i, int j)
{
	if (M > 0)
	{
		hanoi(M - 1, i, 6 - i - j);
		//cout << i << " -> " << j << endl;
		hanoi(M - 1, 6 - i - j, j);
	}
}

void TestOtros::casoMedio(int metodo)
{
	switch (metodo)
	{
	case 0:
	{
		cout << "Metodo de Floyd" << endl;
		ofstream casomedio_floyd;
		casomedio_floyd.open("floyd.dat");

		for (int dim = 50; dim < 700; dim+=25)
		{
			int ** M = ReservaMatriz(dim);
			RellenaMatriz(M, dim);

				Mtime t;
				LARGE_INTEGER t_inicial, t_final;
				QueryPerformanceCounter(&t_inicial);

				Floyd(M, dim);

				QueryPerformanceCounter(&t_final);

				double secs = t.performancecounter_diff(&t_final, &t_inicial);

			cout << endl << dim << "\t" << secs;
			casomedio_floyd << dim << "\t" << secs << "\n";
			LiberaMatriz(M, dim);
		}
		casomedio_floyd.close();
		cout << endl;
		break;
	}
	case 1:
	{
		cout << "Metodo de Fibonacci" << endl;
		ofstream casomedio_fibonacci;
		casomedio_fibonacci.open("fibonacci.dat");
		for(int i=MAX_LONG*3; i<MAX_LONG*4; i++)
		{
		int f;
		Mtime t;
		LARGE_INTEGER t_inicial, t_final;
		QueryPerformanceCounter(&t_inicial);

		f = fibo(i);

		QueryPerformanceCounter(&t_final);
		double secs = t.performancecounter_diff(&t_final, &t_inicial);
		cout << endl << i << "\t" << secs;
		casomedio_fibonacci << i << "\t" << secs << "\n";
		}
		
		cout << endl;
		break;
	}
	case 2:
	{
		cout << "Metodo de Hanoi" << endl;
		ofstream casomedio_hanoi;
		casomedio_hanoi.open("hanoi.dat");

		for (int i = 5; i <= 30; i++)
		{
			int discos = i;
			Mtime t;
			LARGE_INTEGER t_inicial, t_final;
			QueryPerformanceCounter(&t_inicial);

			hanoi(discos, 1, 2);

			QueryPerformanceCounter(&t_final);
			double secs = t.performancecounter_diff(&t_final, &t_inicial);
			cout << endl << i << "\t" << secs;
			casomedio_hanoi << i << "\t" << secs << "\n";
		}
		cout << endl;
		break;
	}
	}
}
