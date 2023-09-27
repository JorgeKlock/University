// CMakeProject1.cpp: define el punto de entrada de la aplicación.
//

#include "CMakeProject1.h"
#include "random.hpp"
#include <vector>
#include <iostream>
#include <fstream>
//#include <sstream>
#include <algorithm>
#include <chrono>


using namespace std;
//using namespace std::chrono;
using Random = effolkronium::random_static;

float funcion_objetivo_QAP(vector<int> distancias, vector<int> flujos, vector<int> solucion)
{
	float valoracion = 0;
	//Cálculo del valor de Función Objetivo para el QAP
	for (int i = 0; i < solucion.size(); i++)
	{
		for (int j = 0; j < solucion.size(); j++)
		{
			valoracion = valoracion + (flujos[(i * solucion.size()) + j] * distancias[(solucion[i] * solucion.size()) + solucion[j]]);
		}
	}

	return valoracion;
}

double funcion_fitness_QAP(double coste, double mejor_coste)
{
	return (coste - mejor_coste) / mejor_coste;
}

int lectura_QAP(vector<int>& distancias, vector<int>& flujos, string fichero)
{
	ifstream fichero_lectura;
	cout << "Nombre del Fichero: " << fichero << endl;
	fichero_lectura.open(fichero);
	if (!fichero_lectura)	cout << "El fichero seleccionado no existe";
	else
	{
		int tamano_problema = -1;
		//El primero elemento del fichero es el tamaño del problema.
		fichero_lectura >> tamano_problema;

		int valor;
		//A continuacion tenemos tamaño*tamaño elementos en flujo
		for (int i = 0; i < tamano_problema * tamano_problema; i++)
		{
			fichero_lectura >> valor;
			flujos.push_back(valor);
		}
		for (int i = 0; i < tamano_problema * tamano_problema; i++)
		{
			fichero_lectura >> valor;
			distancias.push_back(valor);
		}

		fichero_lectura.close();
		return tamano_problema;
	}
	return -1;
}

vector<int> Calcular_Potencial(vector<int> elementos, int size)
{
	vector<int> Potenciales(size);
	for (int i = 0; i < size; i++)
	{
		int temporal = 0;
		for (int j = 0; j < size; j++)
		{
			temporal += elementos[(i*size) + j];
		}
		Potenciales[i] = temporal;
	}

	return Potenciales;
}

vector<int> greedy_QAP(vector<int> distancias, vector<int> flujos, int size, bool depuration_data)
{
	vector<int> S(size);
	vector<int> potencial_flujo(size);
	vector<int> potencial_distancia(size);

	potencial_flujo = Calcular_Potencial(flujos, size);
	potencial_distancia = Calcular_Potencial(distancias, size);

	if (depuration_data)
	{
		cout << "Potenciales de flujo: " << potencial_flujo.size() << endl;
		for (int i = 0; i < potencial_flujo.size(); i++)
			cout << potencial_flujo[i] << " ";
		cout << endl;
		cout << "Potenciales de distancias: " << potencial_distancia.size() << endl;
		for (int i = 0; i < potencial_distancia.size(); i++)
			cout << potencial_distancia[i] << " ";
		cout << endl;
	}
	
	for (int i = 0; i < S.size(); i++)
	{
		// Este código podría llegar a dar error si hubiera potenciales iguales a INT_MAX lo cual se presupone no factible (ya que si pueden llegar a INT_MAX podrían llegar a INT_MAX + 1 produciendo desbordamiento
		vector<int>::iterator pos_flujo = max_element(potencial_flujo.begin(), potencial_flujo.end());
		vector<int>::iterator pos_distancia = min_element(potencial_distancia.begin(), potencial_distancia.end());


		S[distance(begin(potencial_flujo), pos_flujo)] = distance(begin(potencial_distancia), pos_distancia);

		potencial_flujo[distance(begin(potencial_flujo), pos_flujo)] = -1;
		potencial_distancia[distance(begin(potencial_distancia), pos_distancia)] = INT_MAX;

	}

	return S;
}

int permutar_BL_QAP(vector<int> & Solucion, int i, int j, int coste, int mejora)
{
	int temp = Solucion[i];
	Solucion[i] = Solucion[j];
	Solucion[j] = temp;

	return coste + mejora;
}

int diferencia_coste_BL_QAP(vector<int> solucion, vector<int> distancias, vector<int> flujos, int i, int j)
{
	int sumatoria = 0;
	for (int k = 0; k < solucion.size(); k++)
	{
		if ( (k != i) && (k != j) )
		{
			int f1 = flujos[(i * solucion.size() + k)] * ((distancias[(solucion[j] * solucion.size() + solucion[k])]) - (distancias[(solucion[i] * solucion.size() + solucion[k])]));
			int f2 = flujos[(j * solucion.size() + k)] * ((distancias[(solucion[i] * solucion.size() + solucion[k])]) - (distancias[(solucion[j] * solucion.size() + solucion[k])]));
			int f3 = flujos[(k * solucion.size() + i)] * ((distancias[(solucion[k] * solucion.size() + solucion[j])]) - (distancias[(solucion[k] * solucion.size() + solucion[i])]));
			int f4 = flujos[(k * solucion.size() + j)] * ((distancias[(solucion[k] * solucion.size() + solucion[i])]) - (distancias[(solucion[k] * solucion.size() + solucion[j])]));
			sumatoria = sumatoria + f1 + f2 + f3 + f4;
		}
	}
	return sumatoria;
}

vector<int> generaSolucionAleatoria_QAP(int size)
{
	vector<int> random_solution(size);
	for (int i = 0; i < size; i++)
	{
		random_solution[i] = i;
	}
	Random::shuffle(random_solution);
	return random_solution;
}

vector<int> busqueda_local_QAP(vector<int> distancias, vector<int> flujos, int size, bool depuration_data)
{
	vector<int> S = generaSolucionAleatoria_QAP(size);
	vector<bool> DontLookBits(size,0); //Inicialmente todos los bits están a 0
	int evaluaciones = 0;
	int MAX_EVALUACIONES = 50000;
	bool mejora = true;

	int coste = funcion_objetivo_QAP(distancias, flujos, S);
	int movimiento_mejora;


	while (mejora && evaluaciones < MAX_EVALUACIONES)
	{
		for (int i = 0; i < size; i++)
		{
			if (DontLookBits[i] == 0)
			{
				mejora = false;
				for (int j = 0; j < size; j++)
				{
					movimiento_mejora = diferencia_coste_BL_QAP(S, distancias, flujos, i, j);
					evaluaciones++;
					if (movimiento_mejora < 0)
					{
						coste = permutar_BL_QAP(S, i, j, coste, movimiento_mejora);
						DontLookBits[i] = 0;
						DontLookBits[j] = 0;
						mejora = true;
					}
				}
				if (!mejora) DontLookBits[i] = 1;
			}
		}
	}
	return S;
}

int main()
{
	long int seed = 1;
	Random::seed(seed);
	
	
	const string Nombre_Caso[20] = { "chr22a.dat", "chr22b.dat", "chr25a.dat", "esc128.dat", "had20.dat", "lipa60b.dat", "lipa80b.dat", "nug28.dat", "sko81.dat", "sko90.dat", "sko100a.dat", "sko100f.dat", "tai100a.dat", "tai100b.dat", "tai150b.dat", "tai256c.dat", "tho40.dat", "tho150.dat", "wil50.dat", "wil100.dat" };
	const unsigned int Mejor_Caso[20] = { 6156, 6194, 3796, 64, 6922, 2520135, 7763962, 5166, 90998, 115534, 152002, 149036, 21052466, 1185996137, 498896643, 44759294, 240516, 8133398, 48816, 273038 };
	
	int N;
	string nombre_fichero = "chr22a.dat";
	bool Depuration_Data = true;


	cout << "Inicio del Programa para el cálculo de soluciones QAP" << endl;

	for (int i = 0; i < 20; i++)
	{
		
			
			vector<int> distancias;
			vector<int> flujos;

			nombre_fichero = Nombre_Caso[i];
			N = lectura_QAP(distancias, flujos, nombre_fichero);
			vector<int> solucion(N);

			if (N != -1)
			{
				cout << "Size of Problem: " << N << endl;

				Depuration_Data = false;
				if (Depuration_Data)
				{
					cout << "Flujos: ";
					for (int i = 0; i < flujos.size(); i++)
						cout << flujos[i] << " ";
					cout << endl << "Distancias: ";
					for (int i = 0; i < distancias.size(); i++)
						cout << distancias[i] << " ";
					cout << endl;
				}

				cout << "Calculo de la solucion Greedy: " << endl;

				auto momentoInicio = std::chrono::high_resolution_clock::now();
				solucion = greedy_QAP(distancias, flujos, N, Depuration_Data);
				auto momentoFin = std::chrono::high_resolution_clock::now();

				Depuration_Data = false;
				if (Depuration_Data)
				{
					cout << "Solucion: ";
					for (int i = 0; i < solucion.size(); i++)
					{
						if (i == solucion.size() - 1)
						{
							cout << solucion[i];
						}
						else cout << solucion[i] << ", ";
					}
					cout << endl;
				}
					int coste = funcion_objetivo_QAP(distancias, flujos, solucion);
					cout << "Coste: " << coste << endl;
					double fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "Fitness: " << fitness << endl;
					std::chrono::milliseconds tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "Tiempo Pasado: " << tiempo.count() << "ms" << endl;
				

				cout << "Calculo de la solucion BL: " << endl;

				int min_coste = INT_MAX;
				long unsigned int coste_medio = 0;
				int max_coste = 0;
				double fitness_medio = 0;
				std::chrono::milliseconds tiempo_medio = std::chrono::milliseconds::zero();

				for (int j = 0; j < 10; j++)
				{
					Random::seed(j);

					auto momentoInicio_BL = std::chrono::high_resolution_clock::now();
					solucion = busqueda_local_QAP(distancias, flujos, N, Depuration_Data);
					auto momentoFin_BL = std::chrono::high_resolution_clock::now();

					Depuration_Data = false;
					if (Depuration_Data)
					{
						cout << "Solucion: ";
						for (int i = 0; i < solucion.size(); i++)
						{
							if (i == solucion.size() - 1)
							{
								cout << solucion[i];
							}
							else cout << solucion[i] << ", ";
						}

						cout << endl;
					}

					int coste = funcion_objetivo_QAP(distancias, flujos, solucion);
					cout << "Coste: " << coste << endl;
					double fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "Fitness: " << fitness << endl;
					std::chrono::milliseconds tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin_BL - momentoInicio_BL);
					cout << "Tiempo Pasado: " << tiempo.count() << "ms" << endl;

					if (coste < min_coste)	min_coste = coste;
					if (coste > max_coste)	max_coste = coste;
					coste_medio += coste / 10;
					tiempo_medio += tiempo;
					fitness_medio += fitness;
				}
				fitness_medio = fitness_medio / 10;
				cout << "Coste Minimo: " << min_coste << endl;
				cout << "Coste Maximo: " << max_coste << endl;
				cout << "Coste Promedio: " << coste_medio << endl;
				cout << "Fitness Promedio: " << fitness_medio << endl;
				cout << "Tiempo Promedio: " << tiempo_medio.count() << endl;
			}
		cout << endl << endl;
	}

	
	return 0;
}
