// CSA.cpp: define el punto de entrada de la aplicación.
//



#include "CSA.h"
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "random.hpp"

using namespace std;
using Random = effolkronium::random_static;

// Metaheurística CSA : Crow Swarch Algorithm
// El algoritmo CSA tiene por objetivo encontrar soluciones cercanas al óptimo simulando el comportamiento inteligente de 
// los cuervos a la hora de esconder y recuperar alimento.


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

double funcion_fitness_QAP(unsigned int coste, unsigned int mejor_coste)
{
	return ((double)coste - (double)mejor_coste) / (double)mejor_coste;
}

struct Solucion_QAP
{
	vector<int> Genes;
	unsigned int Valoracion = 0;
};

struct Crow
{
	vector<float> Next_Position;
	vector<float> Position;
	vector<float> Memory_Position;
	Solucion_QAP Position_Solution;
	Solucion_QAP Memory_Solution;
};

// Cálculo del valor de Función Objetivo para el QAP
unsigned int f_QAP(vector<int> distancias, vector<int> flujos, vector<int> permutacion)
{
	unsigned int valoracion = 0;
	for (int i = 0; i < permutacion.size(); i++)
	{
		for (int j = 0; j < permutacion.size(); j++)
		{
			valoracion = valoracion + (flujos[(i * permutacion.size()) + j] * distancias[(permutacion[i] * permutacion.size()) + permutacion[j]]);
		}
	}
	return valoracion;
}


vector<float> Random_Position(unsigned int Problem_size)
{
	const float random_min_value = -100.0;
	const float random_max_value = 100.0;
	vector<float> positions = Random::get<vector>(random_min_value, random_max_value, Problem_size);
	Random::shuffle(positions);

	return positions;
}


vector<int> Position_to_Solution(vector<float> position_values)
{
	vector<int> indices(position_values.size());
	iota(indices.begin(), indices.end(), 0);
	sort(indices.begin(), indices.end(), [&](int a, int b) {return position_values[a] < position_values[b]; });

	return indices;
}

vector<float> operator- (const vector<float>& v1, const vector<float>& v2)
{
	vector<float> resultado;
	for (int i = 0; i < v1.size(); i++)
	{
		resultado.push_back(v1[i] - v2[i]);
	}
	return resultado;
}

vector<float> operator+ (const vector<float>& v1, const vector<float>& v2)
{
	vector<float> resultado;
	for (int i = 0; i < v1.size(); i++)
	{
		resultado.push_back(v1[i] + v2[i]);
	}
	return resultado;
}

vector<float> operator* (const vector<float>& v1, const float& element)
{
	vector<float> resultado;
	for (int i = 0; i < v1.size(); i++)
	{
		resultado.push_back(v1[i] * element);
	}
	return resultado;
}

vector<float> operator* (const float& element, const vector<float>& v1)
{
	vector<float> resultado;
	for (int i = 0; i < v1.size(); i++)
	{
		resultado.push_back(v1[i] * element);
	}
	return resultado;
}

// El algoritmo CSA para hayar trayectorias que conecten soluciones, ya que nuestro espacio de soluciones para el problema QAP es una permutación de un vector
// de N elementos enteros, los cuervos implementarán sus posiciones como un vector de floats donde cada elemento se corresponde con una de las posiciones del vector Solucion.
// Posteriormente estos elementos float serán ordenados, y el orden nos proporcionará el valor de la permutación

Solucion_QAP CSA_QAP(unsigned int N_crows, unsigned int Max_iter, float flight_lenght, float awareness_probability, vector<int> distancias, vector<int> flujos, unsigned int Problem_size)
{
	// 1 - Se inicializan aleatoriamente los valores de posición y memoria de los N_crows cuervos. 
	// + Ya que los cuervos aun no han tenido experiencia el valor inicial de la memoria coincide con la posicion inicial
	vector<Crow> Flock;
	for (unsigned int i = 0; i < N_crows; i++)
	{
		Crow nuevo_cuervo;
		nuevo_cuervo.Position = Random_Position(Problem_size);														 // La posición del cuervo en valores float
		nuevo_cuervo.Position_Solution.Genes = Position_to_Solution(nuevo_cuervo.Position);							 // La posición del cuervo en valor permutación
		nuevo_cuervo.Position_Solution.Valoracion = f_QAP(distancias, flujos, nuevo_cuervo.Position_Solution.Genes); // La valoración de la posición

		nuevo_cuervo.Memory_Position = nuevo_cuervo.Position;
		nuevo_cuervo.Memory_Solution = nuevo_cuervo.Position_Solution;											  	 // La solución en memoria del cuervo
		Flock.push_back(nuevo_cuervo);
	}
	// 2 - Actualizamos los valores de los cuervos durante "Max_iter" iteraciones
	for (unsigned int iteracion = 0; iteracion < Max_iter; iteracion++)
	{
		// 3 - Para cada cuervo hacer lo necesario para obtener lo que será la futura posición del cuervo
		for (unsigned int i = 0; i < N_crows; i++)
		{
			// 3.1 - Elegir un cuervo al que seguir
			unsigned int cuervo_j = Random::get<unsigned int>(0, N_crows - 2);
			// 3.1.1 - Seleccionar correctamente un cuervo distinto de sí mismo, para ello, si es un valor menor al índice del cuervo se mantiene y  
			// si es igual o superior sumamos 1, para ignorar el cuervo actual
			if (cuervo_j >= i) cuervo_j++;

			// 3.2 - Comprobar si el cuervo_j percibe al cuervo_i
			float perception_check = Random::get<float>(0.0, 1.0);
				// 3.2.1 - Si no lo percibe lo guiará en dirección hacia su posición memorizada
			if (perception_check >= awareness_probability)
			{
				float flight_amount = Random::get<float>(0.0, 1.0);
				Flock[i].Next_Position = Flock[i].Position + (flight_amount * flight_lenght * (Flock[cuervo_j].Memory_Position - Flock[i].Position));
			}
				// 3.2.2 - Si lo percibe lo guiará hacia una posición aleatoria del espacio de soluciones
			else
			{
				Flock[i].Next_Position = Random_Position(Problem_size);
			}

		}
		// 4 - Actualizar todos los cuervos
		for (unsigned int i = 0; i < N_crows; i++)
		{
			// 4.1 - Convertir la futura posición en actual
			Flock[i].Position = Flock[i].Next_Position;
			// 4.2 - Convertir la nueva posición a formato solución (Permutación, Valoración)
			Flock[i].Position_Solution.Genes = Position_to_Solution(Flock[i].Position);
			Flock[i].Position_Solution.Valoracion = f_QAP(distancias, flujos, Flock[i].Position_Solution.Genes);
			// 4.3 - Comprobar si la nueva posición es mejor que la recordada y si lo es actualizar la posición y Solucion en memoria
			if (Flock[i].Position_Solution.Valoracion < Flock[i].Memory_Solution.Valoracion)
			{
				Flock[i].Memory_Position = Flock[i].Position;
				Flock[i].Memory_Solution = Flock[i].Position_Solution;
			}
		}
	}

	// 5 - Devolver la mejor solución recordada de un cuervo
	Solucion_QAP mejor_solucion = Flock[0].Memory_Solution;
	for (unsigned int i = 1; i < N_crows; i++)
	{
		if (Flock[i].Memory_Solution.Valoracion < mejor_solucion.Valoracion)
		{
			mejor_solucion = Flock[i].Memory_Solution;
		}
	}
	return mejor_solucion; 
}


int main()
{
	long int seed = 42;

	
	bool QAP = true;

	// Evaluación del Crow Search Algorithm para el cálculo del problema QAP
	if (QAP)
	{
		const string Nombre_Caso[20] = { "chr22a.dat", "chr22b.dat", "chr25a.dat", "esc128.dat", "had20.dat", "lipa60b.dat", "lipa80b.dat", "nug28.dat", "sko81.dat", "sko90.dat", "sko100a.dat", "sko100f.dat", "tai100a.dat", "tai100b.dat", "tai150b.dat", "tai256c.dat", "tho40.dat", "tho150.dat", "wil50.dat", "wil100.dat" };
		const unsigned int Mejor_Caso[20] = { 6156, 6194, 3796, 64, 6922, 2520135, 7763962, 5166, 90998, 115534, 152002, 149036, 21052466, 1185996137, 498896643, 44759294, 240516, 8133398, 48816, 273038 };
		int N;

		ofstream salida_CSA("salida_CSA.txt");
		int coste_medio = 0;
		double fitness_medio = 0.0;
		double tiempo_medio = 0.0;
		for (int i = 0; i < 20; i++)
		{


			vector<int> distancias;
			vector<int> flujos;

			string nombre_fichero = Nombre_Caso[i];
			N = lectura_QAP(distancias, flujos, nombre_fichero);
			
			if (N != -1)
			{
				Solucion_QAP solucion;
				const unsigned int n_crows = 50;
				const unsigned int max_iter = 1000;
				const float flight_lenght = 2;
				const float awareness_probability = (float)0.1;


				auto momentoInicio = std::chrono::high_resolution_clock::now();
				solucion = CSA_QAP(n_crows, max_iter, flight_lenght, awareness_probability, distancias, flujos, N);
				auto momentoFin = std::chrono::high_resolution_clock::now();


				cout << "Coste: " << solucion.Valoracion << endl;
				double fitness = funcion_fitness_QAP(solucion.Valoracion, Mejor_Caso[i]);
				cout << "Fitness: " << fitness << endl;
				std::chrono::milliseconds tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
				cout << "Tiempo Pasado: " << tiempo.count() << "ms" << endl;
				coste_medio += solucion.Valoracion / 20;
				fitness_medio += fitness / 20;
				tiempo_medio += tiempo.count() / 20;
				salida_CSA << nombre_fichero << " & " << solucion.Valoracion << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;
			}

		}
		salida_CSA << "Promedio" << " & " << coste_medio << " & " << fitness_medio << " & " << tiempo_medio << " ms" << " \\\\" << endl;
			
	}



	return 0;
}
