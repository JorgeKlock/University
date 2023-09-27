// QAP3.cpp: define el punto de entrada de la aplicación.
//

#include "QAP3.h"
#include "random.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string> // Necesario para stof
//#include <sstream>
#include <algorithm>
#include <chrono>
#include <climits>


using namespace std;
using Random = effolkronium::random_static;

enum Cruces { Posicion = 0, PMX = 1 };

struct Solucion
{
	vector<int> Genes;
	float Valoracion = FLT_MAX;
};

bool operator==(const Solucion& s1, const Solucion& s2)
{
	return (s1.Genes == s2.Genes);
}

bool compararSolucion(const Solucion& s1, const Solucion& s2)
{
	return s1.Valoracion < s2.Valoracion;
}

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
			temporal += elementos[(i * size) + j];
		}
		Potenciales[i] = temporal;
	}

	return Potenciales;
}


int permutar_BL_QAP(vector<int>& Solucion, int i, int j, int coste, int mejora)
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
		if ((k != i) && (k != j))
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


Solucion TorneoBinario(Solucion p1, Solucion p2)
{
	if (p1.Valoracion < p2.Valoracion)
	{
		return p1;
	}
	else
	{
		return p2;
	}
}

vector<Solucion> TorneoBinario4(Solucion p1, Solucion p2, Solucion p3, Solucion p4)
{
	vector<Solucion> Ganadores;
	vector<Solucion> Competidores;
	Competidores.push_back(p1);
	Competidores.push_back(p2);
	Competidores.push_back(p3);
	Competidores.push_back(p4);
	//Calculamos el mejor
	int idx_mejor;
	float valoracion_mejor = FLT_MAX;
	for (int i = 0; i < 4; i++)
	{
		if (Competidores[i].Valoracion < valoracion_mejor)
		{
			valoracion_mejor = Competidores[i].Valoracion;
			idx_mejor = i;
		}
	}
	// Lo guardamos y calculamos el siguiente
	Ganadores.push_back(Competidores[idx_mejor]);
	Competidores.erase(Competidores.begin() + idx_mejor);

	//Calculamos el mejor
	valoracion_mejor = FLT_MAX;
	for (int i = 0; i < 3; i++)
	{
		if (Competidores[i].Valoracion < valoracion_mejor)
		{
			valoracion_mejor = Competidores[i].Valoracion;
			idx_mejor = i;
		}
	}
	// Lo guardamos y calculamos el siguiente
	Ganadores.push_back(Competidores[idx_mejor]);
	return Ganadores;
}

void Mutacion(Solucion& individuo, vector<int> genes)
{
	int temp = individuo.Genes[genes[0]];
	individuo.Genes[genes[0]] = individuo.Genes[genes[1]];
	individuo.Genes[genes[1]] = temp;
}

void CrucePosicion(Solucion& padre1, Solucion& padre2)
{
	vector<int> Restos;
	vector<int> Posiciones;
	for (int i = 0; i < padre1.Genes.size(); i++)
	{
		if (padre1.Genes[i] != padre2.Genes[i])
		{
			Restos.push_back(padre1.Genes[i]);
			Posiciones.push_back(i);
		}
	}

	Random::shuffle(Restos);
	// Asignar en los huecos del padre 1
	for (int i = 0; i < Posiciones.size(); i++)
	{
		padre1.Genes[Posiciones[i]] = Restos[i];
	}


	Random::shuffle(Restos);
	//Asignar en los huecos del padre 2
	for (int i = 0; i < Posiciones.size(); i++)
	{
		padre2.Genes[Posiciones[i]] = Restos[i];
	}
}

void CrucePMX(Solucion& padre1, Solucion& padre2)
{
	// Elegir aleatoriamente la subcadena central
	int tamano_solucion = padre1.Genes.size();
	vector<int> numbers;
	for (int i = 0; i < tamano_solucion; i++)
	{
		numbers.push_back(i);
	}
	Random::shuffle(numbers);
	vector<int> limites;
	limites.push_back(numbers[0]);
	limites.push_back(numbers[1]);

	if (limites[0] > limites[1])
	{
		int temp = limites[0];
		limites[0] = limites[1];
		limites[1] = temp;
	}

	// Inicializamos los hijos a -1 para saber que posiciones aun no hemos almacenado porque no pueden aparecer en los padres
	vector<int> hijo1(padre1.Genes.size(), -1);
	vector<int> hijo2(padre2.Genes.size(), -1);

	// Limites[0] inicio subcadena   Limites[1] fin subcadena
	// Generamos el vector de correspondencias
	vector<vector<int>> Correspondencias;
	for (int i = limites[0]; i <= limites[1]; i++)
	{
		vector<int> correspondencia = { padre1.Genes[i], padre2.Genes[i] };
		Correspondencias.push_back(correspondencia);
		hijo1[i] = padre2.Genes[i];
		hijo2[i] = padre1.Genes[i];
	}

	// Hacemos el cruce y la correspondencia del segmento inferior
	for (int i = 0; i < limites[0]; i++)
	{
		// Actualizamos hijo 1 e hijo 2
		int elemento_a_introducir1 = padre1.Genes[i];
		int elemento_a_introducir2 = padre2.Genes[i];
		int k1 = 1;
		int k2 = 0;
		// Comprobamos si el elemento a introducir ya esta en los respectivos vectores
		while (find(hijo1.begin(), hijo1.end(), elemento_a_introducir1) != hijo1.end())
		{
			// Establecemos la correspondencia
			for (int j = 0; j < Correspondencias.size(); j++)
			{
				if (Correspondencias[j][k1] == elemento_a_introducir1)
				{
					// Sumamos 1 módulo 2 para cambiar de elemento en la correspondencia
					elemento_a_introducir1 = Correspondencias[j][(k1 + 1) % 2];
				}
			}
		}
		while (find(hijo2.begin(), hijo2.end(), elemento_a_introducir2) != hijo2.end())
		{
			// Establecemos la correspondencia
			for (int j = 0; j < Correspondencias.size(); j++)
			{
				if (Correspondencias[j][k2] == elemento_a_introducir2)
				{
					// Sumamos 1 módulo 2 para cambiar de elemento en la correspondencia
					elemento_a_introducir2 = Correspondencias[j][(k2 + 1) % 2];

				}
			}
		}

		// Una vez finalizadas las correspondencias podemos añadir el elemento en el vector
		hijo1[i] = elemento_a_introducir1;
		hijo2[i] = elemento_a_introducir2;
	}

	// Hacemos el cruce y la correspondencia del segmento superior si es no nulo
	if (tamano_solucion != limites[1] + 1)
	{
		for (int i = limites[1] + 1; i < tamano_solucion; i++)
		{
			// Actualizamos hijo 1 e hijo 2
			int elemento_a_introducir1 = padre1.Genes[i];
			int elemento_a_introducir2 = padre2.Genes[i];
			int k1 = 1;
			int k2 = 0;
			// Comprobamos si el elemento a introducir ya esta en los respectivos vectores
			while (find(hijo1.begin(), hijo1.end(), elemento_a_introducir1) != hijo1.end())
			{
				// Establecemos la correspondencia
				for (int j = 0; j < Correspondencias.size(); j++)
				{
					if (Correspondencias[j][k1] == elemento_a_introducir1)
					{
						// Sumamos 1 módulo 2 para cambiar de elemento en la correspondencia
						elemento_a_introducir1 = Correspondencias[j][(k1 + 1) % 2];
					}
				}
			}
			while (find(hijo2.begin(), hijo2.end(), elemento_a_introducir2) != hijo2.end())
			{
				// Establecemos la correspondencia
				for (int j = 0; j < Correspondencias.size(); j++)
				{
					if (Correspondencias[j][k2] == elemento_a_introducir2)
					{
						// Sumamos 1 módulo 2 para cambiar de elemento en la correspondencia
						elemento_a_introducir2 = Correspondencias[j][(k2 + 1) % 2];

					}
				}
			}

			// Una vez finalizadas las correspondencias podemos añadir el elemento en el vector
			hijo1[i] = elemento_a_introducir1;
			hijo2[i] = elemento_a_introducir2;
		}
	}
	// Los hijos ya pueden sustituir a los padres
	padre1.Genes = hijo1;
	padre2.Genes = hijo2;
}

// ----------------- ALGORITMOS ----------------------------
// Greedy - Algoritmo Greedy
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

// BL - Algoritmo Búsqueda local (vector<int>)
vector<int> busqueda_local_QAP(vector<int> distancias, vector<int> flujos, int size, bool depuration_data)
{
	vector<int> S = generaSolucionAleatoria_QAP(size);
	vector<bool> DontLookBits(size, 0); //Inicialmente todos los bits están a 0
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

// BL - Algoritmo Búsqueda local (solucion)
Solucion busqueda_local_QAP_P(vector<int> distancias, vector<int> flujos, int size, bool depuration_data, int max_eval, Solucion sol_ini, int& evaluaciones_retornadas)
{
	vector<int> S = sol_ini.Genes;
	vector<bool> DontLookBits(size, 0); //Inicialmente todos los bits están a 0
	int evaluaciones = 0;
	int MAX_EVALUACIONES = max_eval;
	bool mejora = true;

	int coste = sol_ini.Valoracion;
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
	Solucion mejor_vecino;
	mejor_vecino.Genes = S;
	mejor_vecino.Valoracion = coste;
	evaluaciones_retornadas = evaluaciones;
	return mejor_vecino;
}

// AGG - Algoritmo Generacional con Elitismo
Solucion AGG(vector<int> distancias, vector<int> flujos, int n_Poblacion, int problem_size, Cruces cruce, float p_cruce, float p_mutacion, unsigned int MAX_EVALUACIONES)
{
	float mejor = FLT_MAX;
	Solucion mejor_individuo;
	// 1 - Inicializar la poblacion
	vector<Solucion> Poblacion;
	for (int i = 0; i < n_Poblacion; i++)
	{
		// 2 - Relación entre genotipo y fenotipo
			// El genotipo de cada individuo se representa mediante un vector de N valores naturales [0,N-1]
			// El fenotipo es la secuencia de esos valores, cada inviduo único se representa mediante una permutación de elementos
		Solucion individuo;
		individuo.Genes = generaSolucionAleatoria_QAP(problem_size);
		// 3 - Evaluación de individuos
			// Inicialmente contamos con las funciones:
			// - funcion_objetivo_QAP
			// - diferencia_coste_BL_QAP (Probablemente no aplicable)
		individuo.Valoracion = funcion_objetivo_QAP(distancias, flujos, individuo.Genes);
		Poblacion.push_back(individuo);
	}
	// 4 - Bucle Principal
	unsigned int evaluaciones = 0;

	while (evaluaciones < MAX_EVALUACIONES)
	{
		// 5.0 - Guardar al mejor miembro de P(t) para incorporarlo al final del proceso de cruce y reemplazamiento
		mejor = FLT_MAX;
		for (int i = 0; i < n_Poblacion; i++)
		{
			if (Poblacion[i].Valoracion < mejor)
			{
				mejor_individuo = Poblacion[i];
				mejor = Poblacion[i].Valoracion;
			}
		}
		// 5 - Seleccionar Padres aleatorios mediante torneo (Tantos como miembros haya en P, por parejas)
		vector<Solucion> Poblacion_Nueva;
		for (int i = 0; i < n_Poblacion; i++)
		{
			vector<int> id_padres = Random::get<vector>(0, n_Poblacion - 1, 2);
			Solucion padre = TorneoBinario(Poblacion[id_padres[0]], Poblacion[id_padres[1]]);
			Poblacion_Nueva.push_back(padre);
		}

		Poblacion = Poblacion_Nueva;
		// Se estima el número de emparejamientos
		int n_cruces = p_cruce * (n_Poblacion / 2);
		// Hacemos la cantidad estimada de emparejamientos
		for (int i = 0; i < n_cruces; i++)
		{
			int id_padre1 = i * 2;
			int id_padre2 = (i * 2) + 1;
			Solucion padre1 = Poblacion[id_padre1];
			Solucion padre2 = Poblacion[id_padre2];

			// 6 - Cruzar
			if (cruce == Posicion)
			{
				// Los hijos se generan en los propios objetos de los padres ya que no importa que estos sean destruidos en el proceso
				CrucePosicion(padre1, padre2);
				padre1.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre1.Genes);
				padre2.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre2.Genes);
				// Cada vez que se cruzan los padres, se actualizan sus valoraciones en los hijos, por tanto se hace una evaluacion de la función objetivo por hijo
				evaluaciones += 2;
			}
			else if (cruce == PMX)
			{
				CrucePMX(padre1, padre2);
				padre1.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre1.Genes);
				padre2.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre2.Genes);
				// Cada vez que se cruzan los padres, se actualizan sus valoraciones en los hijos, por tanto se hace una evaluacion de la función objetivo por hijo
				evaluaciones += 2;
			}
			// Sustituimos los padres por los hijos ya actualizados
			Poblacion[i * 2] = padre1;
			Poblacion[(i * 2) + 1] = padre2;
		}
		// 7 - Mutar
			// Calculamos el número esperado de mutaciones
		int  n_mutaciones = p_mutacion * n_Poblacion;
		for (int i = 0; i < n_mutaciones; i++)
		{
			int Individuo_a_mutar = Random::get(0, n_Poblacion - 1);
			vector<int> Genes_a_mutar = Random::get<std::vector>(0, problem_size - 1, 2);
			Poblacion[Individuo_a_mutar].Valoracion += diferencia_coste_BL_QAP(Poblacion[Individuo_a_mutar].Genes, distancias, flujos, Genes_a_mutar[0], Genes_a_mutar[1]);
			// Cada vez que muta, se actualiza su valoracion, por tanto se hace una evaluacion de la función objetivo
			evaluaciones++;
			Mutacion(Poblacion[Individuo_a_mutar], Genes_a_mutar);
		}

		// 8 - Reemplazar
			// La poblacion nueva se convierte automáticamente en la actual
			// Comprobar si la mejor solucion anterior ha sobrevivido
		//Si ha sobrevivido no hacemos nada
			// Si no ha sobrevivido, sustituir la peor actual
		if (find(Poblacion.begin(), Poblacion.end(), mejor_individuo) == Poblacion.end())
		{
			// Buscar al peor actual
			int idx_peor;
			float valoracion_peor = 0;
			for (int i = 0; i < n_Poblacion; i++)
			{
				if (Poblacion[i].Valoracion > valoracion_peor)
				{
					valoracion_peor = Poblacion[i].Valoracion;
					idx_peor = i;
				}
			}
			// Sustituir el mejor por el peor si este es más favorable
			if (mejor_individuo.Valoracion < valoracion_peor)
			{
				Poblacion[idx_peor] = mejor_individuo;
			}

		}
		// 9 - Evaluar poblacion
	}


	// Devolver el mejor individuo
	mejor = FLT_MAX;
	for (int i = 0; i < n_Poblacion; i++)
	{
		if (Poblacion[i].Valoracion < mejor)
		{
			mejor_individuo = Poblacion[i];
			mejor = Poblacion[i].Valoracion;
		}
	}
	return mejor_individuo;
}

// AGE - Algoritmo Generacional estacionario
Solucion AGE(vector<int> distancias, vector<int> flujos, int n_Poblacion, int problem_size, Cruces cruce, float p_cruce, float p_mutacion, unsigned int MAX_EVALUACIONES)
{
	// 1 - Inicializar la poblacion
	vector<Solucion> Poblacion;
	for (int i = 0; i < n_Poblacion; i++)
	{
		// 2 - Relación entre genotipo y fenotipo
			// El genotipo de cada individuo se representa mediante un vector de N valores naturales [0,N-1]
			// El fenotipo es la secuencia de esos valores, cada inviduo único se representa mediante una permutación de elementos
		Solucion individuo;
		individuo.Genes = generaSolucionAleatoria_QAP(problem_size);
		// 3 - Evaluación de individuos
			// Inicialmente contamos con las funciones:
			// - funcion_objetivo_QAP
			// - diferencia_coste_BL_QAP (Probablemente no aplicable)
		individuo.Valoracion = funcion_objetivo_QAP(distancias, flujos, individuo.Genes);
		Poblacion.push_back(individuo);
	}
	// 4 - Bucle Principal
	unsigned int evaluaciones = 0;
	while (evaluaciones < MAX_EVALUACIONES)
	{
		// 5 - Seleccionar Padres aleatorios (Sólo dos en el estacionario)
		vector<int> id_padres = Random::get<vector>(0, n_Poblacion - 1, 2);
		Solucion hijo1 = TorneoBinario(Poblacion[id_padres[0]], Poblacion[id_padres[1]]);
		id_padres = Random::get<vector>(0, n_Poblacion - 1, 2);
		Solucion hijo2 = TorneoBinario(Poblacion[id_padres[0]], Poblacion[id_padres[1]]);
		// 6 - Cruzar
		float cruce_check = Random::get(0.0, 1.0);
		if (cruce_check <= p_cruce)
		{
			if (cruce == Posicion)
			{
				// Los hijos se generan en los propios objetos de los padres ya que no importa que estos sean destruidos en el proceso
				CrucePosicion(hijo1, hijo2);
				hijo1.Valoracion = funcion_objetivo_QAP(distancias, flujos, hijo1.Genes);
				hijo2.Valoracion = funcion_objetivo_QAP(distancias, flujos, hijo2.Genes);
				// Cada vez que se cruzan los padres, se actualizan sus valoraciones en los hijos, por tanto se hace una evaluacion de la función objetivo por hijo
				evaluaciones += 2;
			}
			else if (cruce == PMX)
			{
				CrucePMX(hijo1, hijo2);
				hijo1.Valoracion = funcion_objetivo_QAP(distancias, flujos, hijo1.Genes);
				hijo2.Valoracion = funcion_objetivo_QAP(distancias, flujos, hijo1.Genes);
				// Cada vez que se cruzan los padres, se actualizan sus valoraciones en los hijos, por tanto se hace una evaluacion de la función objetivo por hijo
				evaluaciones += 2;
			}
		}
		// 7 - Mutar
		int check_mutacion = Random::get(0.0, 1.0);
		if (check_mutacion <= p_mutacion)
		{
			vector<int> Genes_a_mutar = Random::get<std::vector>(0, problem_size - 1, 2);
			hijo1.Valoracion += diferencia_coste_BL_QAP(hijo1.Genes, distancias, flujos, Genes_a_mutar[0], Genes_a_mutar[1]);
			//hijo1.Valoracion = funcion_objetivo_QAP(distancias, flujos, hijo1.Genes);

			// Cada vez que muta, se actualiza su valoracion, por tanto se hace una evaluacion de la función objetivo
			evaluaciones++;
			Mutacion(hijo1, Genes_a_mutar);
		}
		check_mutacion = Random::get(0.0, 1.0);
		if (check_mutacion <= p_mutacion)
		{
			vector<int> Genes_a_mutar = Random::get<std::vector>(0, problem_size - 1, 2);
			hijo2.Valoracion += diferencia_coste_BL_QAP(hijo2.Genes, distancias, flujos, Genes_a_mutar[0], Genes_a_mutar[1]);
			//hijo2.Valoracion = funcion_objetivo_QAP(distancias, flujos, hijo2.Genes);
			// Cada vez que muta, se actualiza su valoracion, por tanto se hace una evaluacion de la función objetivo
			evaluaciones++;
			Mutacion(hijo2, Genes_a_mutar);
		}
		// 8 - Reemplazar
			// Las dos peores soluciones de la generacion anterior compiten con los dos hijos nuevos para ver quien se mantiene, como baremo se utiliza el fitness
				// Buscar las dos peores soluciones
					// Buscar la primera
		int idx_peor = 0;
		float valoracion_peor = 0;
		for (int i = 0; i < Poblacion.size(); i++)
		{
			if (Poblacion[i].Valoracion > valoracion_peor)
			{
				//cout << "Indice peor de momento" << i << endl;
				valoracion_peor = Poblacion[i].Valoracion;
				idx_peor = i;
			}
		}

		// Almacenarlo y quitarlo de la poblacion
		Solucion peor1 = Poblacion[idx_peor];
		Poblacion.erase(Poblacion.begin() + idx_peor);
		// Buscar la segunda
		valoracion_peor = 0;
		for (int i = 0; i < Poblacion.size(); i++)
		{
			if (Poblacion[i].Valoracion > valoracion_peor)
			{
				valoracion_peor = Poblacion[i].Valoracion;
				idx_peor = i;
			}
		}
		// Almacenarlo y quitarlo de la poblacion
		Solucion peor2 = Poblacion[idx_peor];
		Poblacion.erase(Poblacion.begin() + idx_peor);
		// Competir
		vector<Solucion> ganadores = TorneoBinario4(peor1, peor2, hijo1, hijo2);
		// Insertar
		Poblacion.push_back(ganadores[0]);
		Poblacion.push_back(ganadores[1]);
		// 9 - Evaluar poblacion
			// No hay que realizar ninguna acción en el modelo estacionario
	}

	Solucion mejor_individuo;
	float mejor = FLT_MAX;
	for (int i = 0; i < n_Poblacion; i++)
	{
		// Almacenar el mejor individuo, para mantenerlo
		if (Poblacion[i].Valoracion < mejor)
		{
			mejor_individuo = Poblacion[i];
		}
	}
	return mejor_individuo;
}

// Hibridacion - All:Total Rand:Parcial Best:Parcial_Elitista
// AM - Algoritmo Memético -------------------
Solucion AM_All(vector<int> distancias, vector<int> flujos, int n_Poblacion, int problem_size, Cruces cruce, float p_cruce, float p_mutacion, unsigned int MAX_EVALUACIONES)
{
	float mejor = FLT_MAX;
	Solucion mejor_individuo;
	// 1 - Inicializar la poblacion
	vector<Solucion> Poblacion;
	unsigned int contador_generacion = 0;
	for (int i = 0; i < n_Poblacion; i++)
	{
		// 2 - Relación entre genotipo y fenotipo
			// El genotipo de cada individuo se representa mediante un vector de N valores naturales [0,N-1]
			// El fenotipo es la secuencia de esos valores, cada inviduo único se representa mediante una permutación de elementos
		Solucion individuo;
		individuo.Genes = generaSolucionAleatoria_QAP(problem_size);
		// 3 - Evaluación de individuos
			// Inicialmente contamos con las funciones:
			// - funcion_objetivo_QAP
			// - diferencia_coste_BL_QAP (Probablemente no aplicable)
		individuo.Valoracion = funcion_objetivo_QAP(distancias, flujos, individuo.Genes);
		Poblacion.push_back(individuo);
		// Almacenar el mejor individuo, para mantenerlo
		if (individuo.Valoracion < mejor)
		{
			mejor_individuo = individuo;
		}
	}
	// 4 - Bucle Principal
	unsigned int evaluaciones = 0;

	while (evaluaciones < MAX_EVALUACIONES)
	{
		// 5.0 - Guardar al mejor miembro de P(t) para incorporarlo al final del proceso de cruce y reemplazamiento
		mejor = FLT_MAX;
		for (int i = 0; i < n_Poblacion; i++)
		{
			if (Poblacion[i].Valoracion < mejor)
			{
				mejor_individuo = Poblacion[i];
				mejor = Poblacion[i].Valoracion;
			}
		}
		// 5 - Seleccionar Padres aleatorios mediante torneo (Todos en el generacional, por parejas)
		vector<Solucion> Poblacion_Nueva;
		for (int i = 0; i < n_Poblacion; i++)
		{
			vector<int> id_padres = Random::get<vector>(0, n_Poblacion - 1, 2);
			Solucion padre = TorneoBinario(Poblacion[id_padres[0]], Poblacion[id_padres[1]]);
			Poblacion_Nueva.push_back(padre);
		}
		Poblacion = Poblacion_Nueva;
		// Se estima el número de emparejamientos
		int n_cruces = p_cruce * (n_Poblacion / 2);
		// Hacemos la cantidad estimada de emparejamientos
		for (int i = 0; i < n_cruces; i++)
		{
			int id_padre1 = i * 2;
			int id_padre2 = (i * 2) + 1;
			Solucion padre1 = Poblacion[id_padre1];
			Solucion padre2 = Poblacion[id_padre2];

			// 6 - Cruzar
			if (cruce == Posicion)
			{
				// Los hijos se generan en los propios objetos de los padres ya que no importa que estos sean destruidos en el proceso
				CrucePosicion(padre1, padre2);
				padre1.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre1.Genes);
				padre2.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre2.Genes);
				// Cada vez que se cruzan los padres, se actualizan sus valoraciones en los hijos, por tanto se hace una evaluacion de la función objetivo por hijo
				evaluaciones += 2;
			}
			else if (cruce == PMX)
			{
				CrucePMX(padre1, padre2);
				padre1.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre1.Genes);
				padre2.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre2.Genes);
				// Cada vez que se cruzan los padres, se actualizan sus valoraciones en los hijos, por tanto se hace una evaluacion de la función objetivo por hijo
				evaluaciones += 2;
			}
			// Sustituimos los padres por los hijos ya actualizados
			Poblacion[i + i] = padre1;
			Poblacion[(i + i) + 1] = padre2;
		}
		// 7 - Mutar
			// Calculamos el número esperado de mutaciones
		int  n_mutaciones = p_mutacion * n_Poblacion;
		for (int i = 0; i < n_mutaciones; i++)
		{
			int Individuo_a_mutar = Random::get(0, n_Poblacion - 1);
			vector<int> Genes_a_mutar = Random::get<std::vector>(0, problem_size - 1, 2);
			Poblacion[Individuo_a_mutar].Valoracion += diferencia_coste_BL_QAP(Poblacion[Individuo_a_mutar].Genes, distancias, flujos, Genes_a_mutar[0], Genes_a_mutar[1]);
			// Cada vez que muta, se actualiza su valoracion, por tanto se hace una evaluacion de la función objetivo
			evaluaciones++;
			Mutacion(Poblacion[Individuo_a_mutar], Genes_a_mutar);
		}

		// 8.0 - Cada 10 generaciones, aplicar la BL sobre todos los cromosomas
			// Se evaluan 400 vecinos
		contador_generacion++;
		if (contador_generacion % 10 == 0)
		{
			for (int i = 0; i < Poblacion.size(); i++)
			{
				int eval_ret = 0;
				Poblacion[i] = busqueda_local_QAP_P(distancias, flujos, problem_size, false, 400, Poblacion[i], eval_ret /*La solucion que toque explorar*/);
				evaluaciones += eval_ret;
			}

		}
		// 8 - Reemplazar
			// La poblacion nueva se convierte automáticamente en la actual
			// Comprobar si la mejor solucion anterior ha sobrevivido
		//Si ha sobrevivido no hacemos nada
			// Si no ha sobrevivido, sustituir la peor actual
		if (find(Poblacion.begin(), Poblacion.end(), mejor_individuo) == Poblacion.end())
		{
			// Buscar al peor actual
			int idx_peor;
			float valoracion_peor = 0;
			for (int i = 0; i < n_Poblacion; i++)
			{
				if (Poblacion[i].Valoracion > valoracion_peor)
				{
					valoracion_peor = Poblacion[i].Valoracion;
					idx_peor = i;
				}
			}
			// Sustituir el mejor por el peor si este es más favorable
			if (mejor_individuo.Valoracion < valoracion_peor)
			{
				Poblacion[idx_peor] = mejor_individuo;
			}

		}


	}
	// Devolver el mejor individuo
	mejor = FLT_MAX;
	for (int i = 0; i < n_Poblacion; i++)
	{
		if (Poblacion[i].Valoracion < mejor)
		{
			mejor_individuo = Poblacion[i];
			mejor = Poblacion[i].Valoracion;
		}
	}
	return mejor_individuo;
}


Solucion AM_Rand(vector<int> distancias, vector<int> flujos, int n_Poblacion, int problem_size, Cruces cruce, float p_cruce, float p_mutacion, unsigned int MAX_EVALUACIONES)
{
	float mejor = FLT_MAX;
	Solucion mejor_individuo;
	// 1 - Inicializar la poblacion
	vector<Solucion> Poblacion;
	unsigned int contador_generacion = 0;
	for (int i = 0; i < n_Poblacion; i++)
	{
		// 2 - Relación entre genotipo y fenotipo
			// El genotipo de cada individuo se representa mediante un vector de N valores naturales [0,N-1]
			// El fenotipo es la secuencia de esos valores, cada inviduo único se representa mediante una permutación de elementos
		Solucion individuo;
		individuo.Genes = generaSolucionAleatoria_QAP(problem_size);
		// 3 - Evaluación de individuos
			// Inicialmente contamos con las funciones:
			// - funcion_objetivo_QAP
			// - diferencia_coste_BL_QAP (Probablemente no aplicable)
		individuo.Valoracion = funcion_objetivo_QAP(distancias, flujos, individuo.Genes);
		Poblacion.push_back(individuo);
		// Almacenar el mejor individuo, para mantenerlo
		if (individuo.Valoracion < mejor)
		{
			mejor_individuo = individuo;
		}
	}
	// 4 - Bucle Principal
	unsigned int evaluaciones = 0;

	while (evaluaciones < MAX_EVALUACIONES)
	{
		// 5.0 - Guardar al mejor miembro de P(t) para incorporarlo al final del proceso de cruce y reemplazamiento
		mejor = FLT_MAX;
		for (int i = 0; i < n_Poblacion; i++)
		{
			if (Poblacion[i].Valoracion < mejor)
			{
				mejor_individuo = Poblacion[i];
				mejor = Poblacion[i].Valoracion;
			}
		}
		// 5 - Seleccionar Padres aleatorios mediante torneo (Todos en el generacional, por parejas)
		vector<Solucion> Poblacion_Nueva;
		for (int i = 0; i < n_Poblacion; i++)
		{
			vector<int> id_padres = Random::get<vector>(0, n_Poblacion - 1, 2);
			Solucion padre = TorneoBinario(Poblacion[id_padres[0]], Poblacion[id_padres[1]]);
			Poblacion_Nueva.push_back(padre);
		}
		Poblacion = Poblacion_Nueva;
		// Se estima el número de emparejamientos
		int n_cruces = p_cruce * (n_Poblacion / 2);
		// Hacemos la cantidad estimada de emparejamientos
		for (int i = 0; i < n_cruces; i++)
		{
			int id_padre1 = i * 2;
			int id_padre2 = (i * 2) + 1;
			Solucion padre1 = Poblacion[id_padre1];
			Solucion padre2 = Poblacion[id_padre2];

			// 6 - Cruzar
			if (cruce == Posicion)
			{
				// Los hijos se generan en los propios objetos de los padres ya que no importa que estos sean destruidos en el proceso
				CrucePosicion(padre1, padre2);
				padre1.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre1.Genes);
				padre2.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre2.Genes);
				// Cada vez que se cruzan los padres, se actualizan sus valoraciones en los hijos, por tanto se hace una evaluacion de la función objetivo por hijo
				evaluaciones += 2;
			}
			else if (cruce == PMX)
			{
				CrucePMX(padre1, padre2);
				padre1.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre1.Genes);
				padre2.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre2.Genes);
				// Cada vez que se cruzan los padres, se actualizan sus valoraciones en los hijos, por tanto se hace una evaluacion de la función objetivo por hijo
				evaluaciones += 2;
			}
			// Sustituimos los padres por los hijos ya actualizados
			Poblacion[i * 2] = padre1;
			Poblacion[(i * 2) + 1] = padre2;
		}
		// 7 - Mutar
			// Calculamos el número esperado de mutaciones
		int  n_mutaciones = p_mutacion * n_Poblacion;
		for (int i = 0; i < n_mutaciones; i++)
		{
			int Individuo_a_mutar = Random::get(0, n_Poblacion - 1);
			vector<int> Genes_a_mutar = Random::get<std::vector>(0, problem_size - 1, 2);
			Poblacion[Individuo_a_mutar].Valoracion += diferencia_coste_BL_QAP(Poblacion[Individuo_a_mutar].Genes, distancias, flujos, Genes_a_mutar[0], Genes_a_mutar[1]);
			// Cada vez que muta, se actualiza su valoracion, por tanto se hace una evaluacion de la función objetivo
			evaluaciones++;
			Mutacion(Poblacion[Individuo_a_mutar], Genes_a_mutar);
		}

		// 8.0 - Cada 10 generaciones, aplicar la BL sobre cromosomas aleatorios cada uno con probabilidad 0.1
			// Se evaluan 400 vecinos
			// Se puede hacer una consideración para la optimización en tiempo y sería realizar siempre 0.1*n_Poblacion búsquedas locales, en cuyo caso sólo habría que calcular 
			// 0.1*n_poblacion números aleatorios para determinar qué cromosomas se exploran en lugar de calcular n_Poblacion números aleatorios.
		contador_generacion++;
		if (contador_generacion % 10 == 0)
		{
			for (int i = 0; i < Poblacion.size(); i++)
			{
				float LS = Random::get(0.0, 1.0);

				if (LS <= 0.1)
				{
					int eval_ret = 0;
					Poblacion[i] = busqueda_local_QAP_P(distancias, flujos, problem_size, false, 400, Poblacion[i], eval_ret);
					evaluaciones += eval_ret;
				}
			}
		}
		// 8 - Reemplazar
			// La poblacion nueva se convierte automáticamente en la actual
			// Comprobar si la mejor solucion anterior ha sobrevivido
		//Si ha sobrevivido no hacemos nada
			// Si no ha sobrevivido, sustituir la peor actual
		if (find(Poblacion.begin(), Poblacion.end(), mejor_individuo) == Poblacion.end())
		{
			// Buscar al peor actual
			int idx_peor;
			float valoracion_peor = 0;
			for (int i = 0; i < n_Poblacion; i++)
			{
				if (Poblacion[i].Valoracion > valoracion_peor)
				{
					valoracion_peor = Poblacion[i].Valoracion;
					idx_peor = i;
				}
			}
			// Sustituir el mejor por el peor si este es más favorable
			if (mejor_individuo.Valoracion < valoracion_peor)
			{
				Poblacion[idx_peor] = mejor_individuo;
			}

		}


		// 9 - Evaluar poblacion

	}
	// Devolver el mejor individuo
	mejor = FLT_MAX;
	for (int i = 0; i < n_Poblacion; i++)
	{
		if (Poblacion[i].Valoracion < mejor)
		{
			mejor_individuo = Poblacion[i];
			mejor = Poblacion[i].Valoracion;
		}
	}
	return mejor_individuo;
}


Solucion AM_Best(vector<int> distancias, vector<int> flujos, int n_Poblacion, int problem_size, Cruces cruce, float p_cruce, float p_mutacion, unsigned int MAX_EVALUACIONES)
{
	float mejor = FLT_MAX;
	Solucion mejor_individuo;
	// 1 - Inicializar la poblacion
	vector<Solucion> Poblacion;
	unsigned int contador_generacion = 0;
	for (int i = 0; i < n_Poblacion; i++)
	{
		// 2 - Relación entre genotipo y fenotipo
			// El genotipo de cada individuo se representa mediante un vector de N valores naturales [0,N-1]
			// El fenotipo es la secuencia de esos valores, cada inviduo único se representa mediante una permutación de elementos
		Solucion individuo;
		individuo.Genes = generaSolucionAleatoria_QAP(problem_size);
		// 3 - Evaluación de individuos
			// Inicialmente contamos con las funciones:
			// - funcion_objetivo_QAP
			// - diferencia_coste_BL_QAP (Probablemente no aplicable)
		individuo.Valoracion = funcion_objetivo_QAP(distancias, flujos, individuo.Genes);
		Poblacion.push_back(individuo);
		// Almacenar el mejor individuo, para mantenerlo
		if (individuo.Valoracion < mejor)
		{
			mejor_individuo = individuo;
		}
	}
	// 4 - Bucle Principal
	unsigned int evaluaciones = 0;

	while (evaluaciones < MAX_EVALUACIONES)
	{
		// 5.0 - Guardar al mejor miembro de P(t) para incorporarlo al final del proceso de cruce y reemplazamiento
		mejor = FLT_MAX;
		for (int i = 0; i < n_Poblacion; i++)
		{
			if (Poblacion[i].Valoracion < mejor)
			{
				mejor_individuo = Poblacion[i];
				mejor = Poblacion[i].Valoracion;
			}
		}
		// 5 - Seleccionar Padres aleatorios mediante torneo (Todos en el generacional, por parejas)
		vector<Solucion> Poblacion_Nueva;
		for (int i = 0; i < n_Poblacion; i++)
		{
			vector<int> id_padres = Random::get<vector>(0, n_Poblacion - 1, 2);
			Solucion padre = TorneoBinario(Poblacion[id_padres[0]], Poblacion[id_padres[1]]);
			Poblacion_Nueva.push_back(padre);
		}
		Poblacion = Poblacion_Nueva;
		// Se estima el número de emparejamientos
		int n_cruces = p_cruce * (n_Poblacion / 2);
		// Hacemos la cantidad estimada de emparejamientos
		for (int i = 0; i < n_cruces; i++)
		{
			int id_padre1 = i * 2;
			int id_padre2 = (i * 2) + 1;
			Solucion padre1 = Poblacion[id_padre1];
			Solucion padre2 = Poblacion[id_padre2];

			// 6 - Cruzar
			if (cruce == Posicion)
			{
				// Los hijos se generan en los propios objetos de los padres ya que no importa que estos sean destruidos en el proceso
				CrucePosicion(padre1, padre2);
				padre1.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre1.Genes);
				padre2.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre2.Genes);
				// Cada vez que se cruzan los padres, se actualizan sus valoraciones en los hijos, por tanto se hace una evaluacion de la función objetivo por hijo
				evaluaciones += 2;
			}
			else if (cruce == PMX)
			{
				CrucePMX(padre1, padre2);
				padre1.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre1.Genes);
				padre2.Valoracion = funcion_objetivo_QAP(distancias, flujos, padre2.Genes);
				// Cada vez que se cruzan los padres, se actualizan sus valoraciones en los hijos, por tanto se hace una evaluacion de la función objetivo por hijo
				evaluaciones += 2;
			}
			// Sustituimos los padres por los hijos ya actualizados
			Poblacion[i + i] = padre1;
			Poblacion[(i + i) + 1] = padre2;
		}
		// 7 - Mutar
			// Calculamos el número esperado de mutaciones
		int  n_mutaciones = p_mutacion * n_Poblacion;
		for (int i = 0; i < n_mutaciones; i++)
		{
			int Individuo_a_mutar = Random::get(0, n_Poblacion - 1);
			vector<int> Genes_a_mutar = Random::get<std::vector>(0, problem_size - 1, 2);
			Poblacion[Individuo_a_mutar].Valoracion += diferencia_coste_BL_QAP(Poblacion[Individuo_a_mutar].Genes, distancias, flujos, Genes_a_mutar[0], Genes_a_mutar[1]);
			// Cada vez que muta, se actualiza su valoracion, por tanto se hace una evaluacion de la función objetivo
			evaluaciones++;
			Mutacion(Poblacion[Individuo_a_mutar], Genes_a_mutar);
		}
		// 8.0 - Cada 10 generaciones, aplicar la BL sobre los 0.1*n_Poblacion mejores cromosomas
			// Se evaluan 400 vecinos
		contador_generacion++;
		if (contador_generacion % 10 == 0)
		{
			// Lo mas eficiente sería ordenar la poblacion por Valoración, poniendo en las primeras posiciones aquellos con un valor menor (Mejores)
			sort(Poblacion.begin(), Poblacion.end(), compararSolucion);

			for (int i = 0; i < 0.1 * Poblacion.size(); i++)
			{
				int eval_ret = 0;
				Poblacion[i] = busqueda_local_QAP_P(distancias, flujos, problem_size, false, 400, Poblacion[i], eval_ret);
				evaluaciones += eval_ret;
			}

		}
		// 8 - Reemplazar
			// La poblacion nueva se convierte automáticamente en la actual
			// Comprobar si la mejor solucion anterior ha sobrevivido
		//Si ha sobrevivido no hacemos nada
			// Si no ha sobrevivido, sustituir la peor actual
		if (find(Poblacion.begin(), Poblacion.end(), mejor_individuo) == Poblacion.end())
		{
			// Buscar al peor actual
			int idx_peor;
			float valoracion_peor = 0;
			for (int i = 0; i < n_Poblacion; i++)
			{
				if (Poblacion[i].Valoracion > valoracion_peor)
				{
					valoracion_peor = Poblacion[i].Valoracion;
					idx_peor = i;
				}
			}
			// Sustituir el mejor por el peor si este es más favorable
			if (mejor_individuo.Valoracion < valoracion_peor)
			{
				Poblacion[idx_peor] = mejor_individuo;
			}

		}


		// 9 - Evaluar poblacion
	}
	// Devolver el mejor individuo
	mejor = FLT_MAX;
	for (int i = 0; i < n_Poblacion; i++)
	{
		if (Poblacion[i].Valoracion < mejor)
		{
			mejor_individuo = Poblacion[i];
			mejor = Poblacion[i].Valoracion;
		}
	}
	return mejor_individuo;
}
// FIN ALGORITMOS MEMÉTICOS ------------------
// INICIO ALGORITMOS TRAYECTORIAS ------------
// ES - Algoritmo Enfiramiento Simulado
Solucion ES(vector<int> distancias, vector<int> flujos, int problem_size, unsigned int MAX_EVALUACIONES, unsigned int max_vecinos, unsigned int max_exitos, Solucion s_ini)
{
	Solucion s = s_ini;

	float mu = 0.3;
	float phi = 0.2;

	Solucion mejor_solucion = s;
	float temperatura_inicial = (s.Valoracion * mu) / (-1 * log(phi));
	float temperatura_final = 0.0001;
	int max_enfriamientos = (int)ceil(MAX_EVALUACIONES / max_vecinos);

	float temperatura = temperatura_inicial;
	if (temperatura_inicial < temperatura_final)
	{
		temperatura_final = temperatura_final * temperatura_inicial;
	}

	// Parámetro para el enfriamiento (Esquema de cauchy modificado)
	float B = (temperatura_inicial - temperatura_final) / (max_enfriamientos * temperatura_inicial * temperatura_final);

	unsigned int exitos = 0;
	unsigned int vecinos_explorados = 0;
	unsigned int enfriamientos = 0;
	do
	{
		vecinos_explorados = 0;
		exitos = 0;

		// Enfriamiento actual
		// Bucle interno: L(T)
		while (vecinos_explorados < max_vecinos && exitos < max_exitos)
		{
			vector<int> Posiciones = Random::get<std::vector>(0, problem_size - 1, 2);
			int diferencia_coste = diferencia_coste_BL_QAP(s.Genes, distancias, flujos, Posiciones[0], Posiciones[1]);
			vecinos_explorados++;

			float U = Random::get(0.0, 0.1);
			if (diferencia_coste < 0 || (U <= exp(-diferencia_coste / temperatura)))
			{
				exitos++; 
				s.Valoracion = permutar_BL_QAP(s.Genes, Posiciones[0], Posiciones[1], s.Valoracion, diferencia_coste); //Se actualiza la valoracion y se permutan los genes

				if (s.Valoracion < mejor_solucion.Valoracion)
				{
					mejor_solucion = s;
				}
			}
		}

		// Enfriamiento (Esquema de cauchy modificado)
		temperatura = temperatura / (1 + B * temperatura);
		enfriamientos++;

	// Si en este enfriamiento se ha tenido algun éxito procedemos al siguiente hasta MAX_EVALUACIONES
	} while (enfriamientos < max_enfriamientos && exitos > 0);

	return mejor_solucion;
}

// BLP3 - Algoritmo Búsqueda Local modificada en la P3 - Versión sin comprobación de vecindario explorado

Solucion BLP3_VNS(vector<int> distancias, vector<int> flujos, int problem_size, unsigned int MAX_EVALUACIONES, Solucion sol_ini, unsigned int K)
{
	Solucion S = sol_ini;
	int evaluaciones = 0;
	bool mejora = true;
	
	while (evaluaciones < MAX_EVALUACIONES)
	{
		vector<int> Posiciones = Random::get<std::vector>(0, problem_size - 1, 2*K);
		Solucion S_original = S;
		for (int i = 0; i < K; i++)
		{
			float diferencia_coste = diferencia_coste_BL_QAP(S.Genes, distancias, flujos, Posiciones[i * 2], Posiciones[(i * 2) + 1]);
			S.Valoracion = permutar_BL_QAP(S.Genes, Posiciones[i * 2], Posiciones[(i * 2) + 1], S.Valoracion, diferencia_coste);
			evaluaciones++;
		}
		if (S.Valoracion > S_original.Valoracion)
		{
			S = S_original;
		}
	}
	return S;
}

// BLP3 - Algoritmo Búsqueda Local modificada en la P3 - Versión con comprobación de vecindario explorado
Solucion BLP3(vector<int> distancias, vector<int> flujos, int problem_size, unsigned int MAX_EVALUACIONES, Solucion sol_ini)
{
	Solucion S = sol_ini;
	int evaluaciones = 0;
	bool mejora = false;

	vector<vector<int>> Vecinos;
	for (int i = 0; i < problem_size - 1; i++)
	{
		for (int j = i + 1; j < problem_size; j++)
		{
			Vecinos.push_back({ i, j });
		}
	}

	int vecinos_explorados = 0;

	while (evaluaciones < MAX_EVALUACIONES && vecinos_explorados < Vecinos.size())
	{
		// Aleatorizamos el vecindario de la solución actual
		Random::shuffle(Vecinos);

		vecinos_explorados = 0;
		mejora = false;

		// Mientras no hayamos explorado el vecindario entero, o finalizado las evaluaciones o encontrado una mejora
		while(vecinos_explorados < Vecinos.size() && evaluaciones < MAX_EVALUACIONES && !mejora)
		{
			vector<int> Posiciones = Vecinos[vecinos_explorados];
			int diferencia_coste = diferencia_coste_BL_QAP(S.Genes, distancias, flujos, Posiciones[0], Posiciones[1]);
			evaluaciones++;
			vecinos_explorados++;

			if (diferencia_coste < 0)
			{
				// Si encontramos una mejora sustituimos la solucion S y volvemos a generar el vecindario
				S.Valoracion = permutar_BL_QAP(S.Genes, Posiciones[0], Posiciones[1], S.Valoracion, diferencia_coste);
				mejora = true;
			}
		}
	}
	return S;
}

// BMB - Algoritmo Búsqueda Multiarranque Básica
Solucion BMB(vector<int> distancias, vector<int> flujos, int problem_size, unsigned int MAX_EVALUACIONES_BL, unsigned int iteraciones)
{
	Solucion mejor_solucion;
	mejor_solucion.Valoracion = FLT_MAX;

	for (int i = 0; i < iteraciones; i++)
	{
		Solucion s_ini;
		s_ini.Genes = generaSolucionAleatoria_QAP(problem_size);
		s_ini.Valoracion = funcion_objetivo_QAP(distancias, flujos, s_ini.Genes);

		Solucion s_nueva = BLP3(distancias, flujos, problem_size, MAX_EVALUACIONES_BL, s_ini);
		if (s_nueva.Valoracion < mejor_solucion.Valoracion)
		{
			mejor_solucion = s_nueva;
		}
	}
	return mejor_solucion;
}

Solucion MutacionILS(vector<int> distancias, vector<int> flujos, int problem_size, Solucion s_ini)
{
	Solucion s_fin = s_ini;
	int t = (int)ceil(problem_size / 3);
	int inicio = Random::get(0, problem_size);

	vector<int> sublist;
	for (int i = inicio; i < inicio+t; i++)
	{
		sublist.push_back(s_ini.Genes[i%problem_size]);
	}
	Random::shuffle(sublist);
	
	for (int i = inicio; i < inicio + t; i++)
	{
		s_fin.Genes[i%problem_size] = sublist[i - inicio];
	}

	return s_fin;
}
// ILS - Algoritmo Búsqueda Local Reiterada
Solucion ILS(vector<int> distancias, vector<int> flujos, int problem_size, unsigned int MAX_EVALUACIONES_BL, unsigned int iteraciones)
{
	Solucion solucion;
	solucion.Genes = generaSolucionAleatoria_QAP(problem_size);
	solucion.Valoracion = funcion_objetivo_QAP(distancias, flujos, solucion.Genes);
	Solucion mejor_solucion = solucion;

	for (int i = 0; i < iteraciones; i++)
	{
		Solucion n_solucion = BLP3(distancias, flujos, problem_size, MAX_EVALUACIONES_BL, solucion);

		if (n_solucion.Valoracion < mejor_solucion.Valoracion)
		{
			mejor_solucion = n_solucion;
			// Mutar la solucion
			solucion = MutacionILS(distancias, flujos, problem_size, n_solucion);
			solucion.Valoracion = funcion_objetivo_QAP(distancias, flujos, solucion.Genes);
						
		}
		else
		{
			solucion = mejor_solucion;
			// Mutar la solucion
			solucion = MutacionILS(distancias, flujos, problem_size, solucion);
			solucion.Valoracion = funcion_objetivo_QAP(distancias, flujos, solucion.Genes);
		}
		// Si tras la mutación alguna es mejor que la mejor la preservamos ya que va a ser destruída en la siguiente búsqueda local
		if (solucion.Valoracion < mejor_solucion.Valoracion)
		{
			mejor_solucion = solucion;
		}
	}
	return mejor_solucion;
}

// ILS_ES - Algoritmo Híbrido [Búsqueda local reiterada] + [Enfriamiento simulado]
Solucion ILS_ES(vector<int> distancias, vector<int> flujos, int problem_size, unsigned int MAX_EVALUACIONES_BL, unsigned int iteraciones, unsigned int max_vecinos, unsigned int max_exitos)
{
	Solucion solucion;
	solucion.Genes = generaSolucionAleatoria_QAP(problem_size);
	solucion.Valoracion = funcion_objetivo_QAP(distancias, flujos, solucion.Genes);
	Solucion mejor_solucion = solucion;

	for (int i = 0; i < iteraciones; i++)
	{
		Solucion n_solucion = ES(distancias, flujos, problem_size, MAX_EVALUACIONES_BL, max_vecinos, max_exitos, solucion);

		if (n_solucion.Valoracion < mejor_solucion.Valoracion)
		{
			mejor_solucion = n_solucion;
			// Mutar la solucion
			solucion = MutacionILS(distancias, flujos, problem_size, n_solucion);
			solucion.Valoracion = funcion_objetivo_QAP(distancias, flujos, solucion.Genes);

		}
		else
		{
			solucion = mejor_solucion;
			// Mutar la solucion
			solucion = MutacionILS(distancias, flujos, problem_size, solucion);
			solucion.Valoracion = funcion_objetivo_QAP(distancias, flujos, solucion.Genes);
		}
		// Si tras la mutación alguna es mejor que la mejor la preservamos ya que va a ser destruída en la siguiente búsqueda local
		if (solucion.Valoracion < mejor_solucion.Valoracion)
		{
			mejor_solucion = solucion;
		}
	}
	return mejor_solucion;
}

// VNS - Algoritmo Búsqueda con Vecindario Variable
Solucion VNS(vector<int> distancias, vector<int> flujos, int problem_size, unsigned int MAX_EVALUACIONES_BL, unsigned int iteraciones)
{
	Solucion solucion;
	solucion.Genes = generaSolucionAleatoria_QAP(problem_size);
	solucion.Valoracion = funcion_objetivo_QAP(distancias, flujos, solucion.Genes);
	Solucion mejor_solucion = solucion;
	unsigned int K = 1;
	unsigned int kmax = (int)floor(problem_size / 2);

	for (int i = 0; i < iteraciones; i++)
	{
		Solucion n_solucion = BLP3_VNS(distancias, flujos, problem_size, MAX_EVALUACIONES_BL, solucion, K);

		if (n_solucion.Valoracion < mejor_solucion.Valoracion)
		{
			K = 1;

			mejor_solucion = n_solucion;
			// Mutar la solucion
			solucion = MutacionILS(distancias, flujos, problem_size, n_solucion);
			solucion.Valoracion = funcion_objetivo_QAP(distancias, flujos, solucion.Genes);

		}
		else
		{
			K = K + 1;
			if (K > kmax)	K = 1;

			solucion = mejor_solucion;
			// Mutar la solucion
			solucion = MutacionILS(distancias, flujos, problem_size, solucion);
			solucion.Valoracion = funcion_objetivo_QAP(distancias, flujos, solucion.Genes);
		}
		// Si tras la mutación alguna es mejor que la mejor la preservamos ya que va a ser destruída en la siguiente búsqueda local
		if (solucion.Valoracion < mejor_solucion.Valoracion)
		{
			mejor_solucion = solucion;
		}
	}


	return mejor_solucion;
}
// FIN ALGORITMOS TRAYECTORIAS ---------------


// ------------- FIN DE ALGORITMOS ----------------------------


// Las opciones son:
// QAP3.exe 
// QAP3.exe seed
// QAP3.exe seed, iteraciones_BMB, evaluacionesBL_BMB
// Cualquier otra cantidad de parámetros será considerada como QAP2.exe con los valores por defecto
int main(int argc, char* argv[])
{
	long int seed;

	unsigned int iteraciones_BMB;
	unsigned int evaluacionesBL_BMB;

	if (argc == 1)
	{
		seed = int(argv[0]);
		iteraciones_BMB = 25;
		evaluacionesBL_BMB = 2000;
	}
	else if (argc == 7)
	{
		seed = int(argv[0]);
		iteraciones_BMB = int(argv[1]);
		evaluacionesBL_BMB = int(argv[2]);
	}
	else
	{
		seed = 2;
		iteraciones_BMB = 25;
		evaluacionesBL_BMB = 2000;
	}
	Random::seed(seed);


	const string Nombre_Caso[20] = { "chr22a.dat", "chr22b.dat", "chr25a.dat", "esc128.dat", "had20.dat", "lipa60b.dat", "lipa80b.dat", "nug28.dat", "sko81.dat", "sko90.dat", "sko100a.dat", "sko100f.dat", "tai100a.dat", "tai100b.dat", "tai150b.dat", "tai256c.dat", "tho40.dat", "tho150.dat", "wil50.dat", "wil100.dat" };
	const unsigned int Mejor_Caso[20] = { 6156, 6194, 3796, 64, 6922, 2520135, 7763962, 5166, 90998, 115534, 152002, 149036, 21052466, 1185996137, 498896643, 44759294, 240516, 8133398, 48816, 273038 };

	int N;
	string nombre_fichero = "chr22a.dat";
	bool Depuration_Data = true;
	bool p1 = false;
	bool p2 = false;
	bool p3 = false;

	cout << "Inicio del Programa para el cálculo de soluciones QAP" << endl;
	// Bucle para Greedy y QAP
	if (p1)
	{
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
	}


	// Algoritmos poblaciones
	int poblacion = 50;
	float p_cruce_agg = 0.7;
	float p_cruce_age = 1;
	float p_cruce_am = 0.7;
	float p_mutacion = 0.1;
	unsigned int MAX_EVALUACIONES = 50000;

	if (p2)
	{
		// Bucle para AGG, AGE y AM
		ofstream salida_AGG_POS("salida_AGG_POS.txt");
		ofstream salida_AGG_PMX("salida_AGG_PMX.txt");
		ofstream salida_AGE_POS("salida_AGE_POS.txt");
		ofstream salida_AGE_PMX("salida_AGE_PMX.txt");
		ofstream salida_AM_1("salida_AM_1.txt");
		ofstream salida_AM_01("salida_AM_01.txt");
		ofstream salida_AM_01m("salida_AM_01m.txt");
		vector<int> coste_medio(7, 0);
		vector<float> fitness_medio(7, 0.0);
		vector<float> tiempo_medio(7, 0.0);


		if (salida_AGG_POS.is_open() && salida_AGG_PMX.is_open() && salida_AGE_POS.is_open() && salida_AGE_PMX.is_open() && salida_AM_1.is_open() && salida_AM_01.is_open() && salida_AM_01m.is_open())
		{
			
			for (int i = 0; i < 20; i++)
			{


				vector<int> distancias;
				vector<int> flujos;

				nombre_fichero = Nombre_Caso[i];
				N = lectura_QAP(distancias, flujos, nombre_fichero);
				vector<int> solucion(N);

				if (N != -1)
				{
					cout << "--------------------------------------------------------------------------------------------" << endl;
					//Algoritmos Generacionales
					cout << "*** AGG cruce Posicion ***: " << endl;
					Solucion solucion;

					auto momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = AGG(distancias, flujos, poblacion, N, Posicion, p_cruce_agg, p_mutacion, MAX_EVALUACIONES);
					//solucion = AGG(distancias, flujos, poblacion, N, Posicion, p_cruce_agg, p_mutacion, MAX_EVALUACIONES);
					auto momentoFin = std::chrono::high_resolution_clock::now();


					int coste = solucion.Valoracion;
					cout << "Coste: " << coste << endl;
					double fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "Fitness: " << fitness << endl;
					std::chrono::milliseconds tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "Tiempo Pasado: " << tiempo.count() << "ms" << endl;

					coste_medio[0] += coste / 20;
					fitness_medio[0] += fitness / 20;
					tiempo_medio[0] += tiempo.count() / 20;
					salida_AGG_POS << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;




					cout << "** AGG cruce PMX: " << endl;

					momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = AGG(distancias, flujos, poblacion, N, PMX, p_cruce_agg, p_mutacion, MAX_EVALUACIONES);
					momentoFin = std::chrono::high_resolution_clock::now();


					coste = solucion.Valoracion;
					cout << "Coste: " << coste << endl;
					fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "Fitness: " << fitness << endl;
					tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "Tiempo Pasado: " << tiempo.count() << "ms" << endl;
					coste_medio[1] += coste / 20;
					fitness_medio[1] += fitness / 20;
					tiempo_medio[1] += tiempo.count() / 20;
					salida_AGG_PMX << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;



					cout << "** AGE cruce Posicion: " << endl;

					momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = AGE(distancias, flujos, poblacion, N, Posicion, p_cruce_age, p_mutacion, MAX_EVALUACIONES);
					momentoFin = std::chrono::high_resolution_clock::now();


					coste = solucion.Valoracion;
					cout << "Coste: " << coste << endl;
					fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "Fitness: " << fitness << endl;
					tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "Tiempo Pasado: " << tiempo.count() << "ms" << endl;
					coste_medio[2] += coste / 20;
					fitness_medio[2] += fitness / 20;
					tiempo_medio[2] += tiempo.count() / 20;
					salida_AGE_POS << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;


					cout << "** AGE cruce PMX: " << endl;

					momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = AGE(distancias, flujos, poblacion, N, PMX, p_cruce_age, p_mutacion, MAX_EVALUACIONES);
					momentoFin = std::chrono::high_resolution_clock::now();


					coste = solucion.Valoracion;
					cout << "Coste: " << coste << endl;
					fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "Fitness: " << fitness << endl;
					tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "Tiempo Pasado: " << tiempo.count() << "ms" << endl;
					coste_medio[3] += coste / 20;
					fitness_medio[3] += fitness / 20;
					tiempo_medio[3] += tiempo.count() / 20;
					salida_AGE_PMX << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;




					// Algoritmos Meméticos
					cout << "** AM basado en [AGG cruce PMX] con hibridacion total: " << endl;

					momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = AM_All(distancias, flujos, poblacion, N, PMX, p_cruce_agg, p_mutacion, MAX_EVALUACIONES);
					momentoFin = std::chrono::high_resolution_clock::now();


					coste = solucion.Valoracion;
					cout << "Coste: " << coste << endl;
					fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "Fitness: " << fitness << endl;
					tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "Tiempo Pasado: " << tiempo.count() << "ms" << endl;
					coste_medio[4] += coste / 20;
					fitness_medio[4] += fitness / 20;
					tiempo_medio[4] += tiempo.count() / 20;
					salida_AM_1 << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;



					cout << "** AM basado en [AGG cruce PMX] con hibridacion parcial aleatoria: " << endl;

					momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = AM_Rand(distancias, flujos, poblacion, N, PMX, p_cruce_agg, p_mutacion, MAX_EVALUACIONES);
					momentoFin = std::chrono::high_resolution_clock::now();


					coste = solucion.Valoracion;
					cout << "Coste: " << coste << endl;
					fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "Fitness: " << fitness << endl;
					tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "Tiempo Pasado: " << tiempo.count() << "ms" << endl;
					coste_medio[5] += coste / 20;
					fitness_medio[5] += fitness / 20;
					tiempo_medio[5] += tiempo.count() / 20;
					salida_AM_01 << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;


					cout << "** AM basado en [AGG cruce PMX] con hibridacion parcial elitista: " << endl;

					momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = AM_Best(distancias, flujos, poblacion, N, PMX, p_cruce_agg, p_mutacion, MAX_EVALUACIONES);
					momentoFin = std::chrono::high_resolution_clock::now();


					coste = solucion.Valoracion;
					cout << "Coste: " << coste << endl;
					fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "Fitness: " << fitness << endl;
					tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "Tiempo Pasado: " << tiempo.count() << "ms" << endl;
					coste_medio[6] += coste / 20;
					fitness_medio[6] += fitness / 20;
					tiempo_medio[6] += tiempo.count() / 20;
					salida_AM_01m << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;


					cout << "--------------------------------------------------------------------------------------------" << endl;
				}
			}
			salida_AGG_POS << "Promedio" << " & " << coste_medio[0] << " & " << fitness_medio[0] << " & " << tiempo_medio[0] << " ms" << " \\\\" << endl;
			salida_AGG_PMX << "Promedio" << " & " << coste_medio[1] << " & " << fitness_medio[1] << " & " << tiempo_medio[1] << " ms" << " \\\\" << endl;
			salida_AGE_POS << "Promedio" << " & " << coste_medio[2] << " & " << fitness_medio[2] << " & " << tiempo_medio[2] << " ms" << " \\\\" << endl;
			salida_AGE_PMX << "Promedio" << " & " << coste_medio[3] << " & " << fitness_medio[3] << " & " << tiempo_medio[3] << " ms" << " \\\\" << endl;
			salida_AM_1 << "Promedio" << " & " << coste_medio[4] << " & " << fitness_medio[4] << " & " << tiempo_medio[4] << " ms" << " \\\\" << endl;
			salida_AM_01 << "Promedio" << " & " << coste_medio[5] << " & " << fitness_medio[5] << " & " << tiempo_medio[5] << " ms" << " \\\\" << endl;
			salida_AM_01m << "Promedio" << " & " << coste_medio[6] << " & " << fitness_medio[6] << " & " << tiempo_medio[6] << " ms" << " \\\\" << endl;
		}
	}
	
	p3 = true;
	if (p3)
	{
		// Bucle para ES, BLP3, BMB, ILS, ILS_ES y VNS
		ofstream salida_ES("salida_ES.txt");
		ofstream salida_BLP3("salida_BLP3.txt");
		ofstream salida_BMB("salida_BMB.txt");
		ofstream salida_ILS("salida_ILS.txt");
		ofstream salida_ILS_ES("salida_ILS_ES.txt");
		ofstream salida_VNS("salida_VNS.txt");
		vector<int> coste_medio(6, 0);
		vector<float> fitness_medio(6, 0.0);
		vector<float> tiempo_medio(6, 0.0);
		unsigned int max_vecinos;
		unsigned int max_exitos;

		

		if (salida_ES.is_open() && salida_BLP3.is_open() && salida_BMB.is_open() && salida_ILS.is_open() && salida_ILS_ES.is_open() && salida_VNS.is_open())
		{
			cout << "------------------ Algoritmos de Trayectorias --------------------" << endl;
			for (int i = 0; i < 20; i++)
			{
				vector<int> distancias;
				vector<int> flujos;

				nombre_fichero = Nombre_Caso[i];
				N = lectura_QAP(distancias, flujos, nombre_fichero);
				Solucion solucion;

				if (N != -1)
				{
					max_vecinos = 15 * N;
					max_exitos = 0.1 * max_vecinos;

					cout << "---------------------------------------------------" << endl;

					cout << "Algoritmo ES: " << endl;
					//---------------INICIO ALGORITMO-----------------------------//
					Solucion s_ini;
					s_ini.Genes = generaSolucionAleatoria_QAP(N);
					s_ini.Valoracion = funcion_objetivo_QAP(distancias, flujos, s_ini.Genes);

					auto momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = ES(distancias, flujos, N, MAX_EVALUACIONES, max_vecinos, max_exitos, s_ini);
					auto momentoFin = std::chrono::high_resolution_clock::now();


					float coste = solucion.Valoracion;
					cout << "++ Coste: " << coste << endl;
					double fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "++ Fitness: " << fitness << endl;
					auto tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "++ Tiempo Pasado: " << tiempo.count() << "ms" << endl;
					coste_medio[0] += coste / 20;
					fitness_medio[0] += fitness / 20;
					tiempo_medio[0] += tiempo.count() / 20;
					salida_ES << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;
					//-------------------FIN ALGORITMO-----------------------------//

					cout << "Algoritmo BP3: " << endl;
					//---------------INICIO ALGORITMO-----------------------------//
					
					s_ini.Genes = generaSolucionAleatoria_QAP(N);
					s_ini.Valoracion = funcion_objetivo_QAP(distancias, flujos, s_ini.Genes);
					momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = BLP3(distancias, flujos, N, MAX_EVALUACIONES, s_ini);
					momentoFin = std::chrono::high_resolution_clock::now();


					coste = solucion.Valoracion;
					cout << "++ Coste: " << coste << endl;
					fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "++ Fitness: " << fitness << endl;
					tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "++ Tiempo Pasado: " << tiempo.count() << "ms" << endl;
					coste_medio[1] += coste / 20;
					fitness_medio[1] += fitness / 20;
					tiempo_medio[1] += tiempo.count() / 20;
					salida_BLP3 << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;
					//-------------------FIN ALGORITMO-----------------------------//

					cout << "Algoritmo BMB: " << endl;
					//---------------INICIO ALGORITMO-----------------------------//
					momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = BMB(distancias, flujos, N, evaluacionesBL_BMB, iteraciones_BMB);
					momentoFin = std::chrono::high_resolution_clock::now();


					coste = solucion.Valoracion;
					cout << "++ Coste: " << coste << endl;
					fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "++ Fitness: " << fitness << endl;
					tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "++ Tiempo Pasado: " << tiempo.count() << "ms" << endl;
					coste_medio[2] += coste / 20;
					fitness_medio[2] += fitness / 20;
					tiempo_medio[2] += tiempo.count() / 20;
					salida_BMB << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;
					//-------------------FIN ALGORITMO-----------------------------//

					cout << "Algoritmo ILS: " << endl;
					//---------------INICIO ALGORITMO-----------------------------//
					momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = ILS(distancias, flujos, N, evaluacionesBL_BMB, iteraciones_BMB);
					momentoFin = std::chrono::high_resolution_clock::now();


					coste = solucion.Valoracion;
					cout << "++ Coste: " << coste << endl;
					fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "++ Fitness: " << fitness << endl;
					tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "++ Tiempo Pasado: " << tiempo.count() << "ms" << endl;
					coste_medio[3] += coste / 20;
					fitness_medio[3] += fitness / 20;
					tiempo_medio[3] += tiempo.count() / 20;
					salida_ILS << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;

					//-------------------FIN ALGORITMO-----------------------------//

					cout << "Algoritmo ILS_ES: " << endl;
					//---------------INICIO ALGORITMO-----------------------------//
					momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = ILS_ES(distancias, flujos, N, evaluacionesBL_BMB, iteraciones_BMB, max_vecinos, max_exitos);
					momentoFin = std::chrono::high_resolution_clock::now();


					coste = solucion.Valoracion;
					cout << "++ Coste: " << coste << endl;
					fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "++ Fitness: " << fitness << endl;
					tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "++ Tiempo Pasado: " << tiempo.count() << "ms" << endl;
					coste_medio[4] += coste / 20;
					fitness_medio[4] += fitness / 20;
					tiempo_medio[4] += tiempo.count() / 20;
					salida_ILS_ES << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;

					//-------------------FIN ALGORITMO-----------------------------//

					cout << "Algoritmo VNS: " << endl;
					//---------------INICIO ALGORITMO-----------------------------//
					momentoInicio = std::chrono::high_resolution_clock::now();
					solucion = VNS(distancias, flujos, N, evaluacionesBL_BMB, iteraciones_BMB);
					momentoFin = std::chrono::high_resolution_clock::now();


					coste = solucion.Valoracion;
					cout << "++ Coste: " << coste << endl;
					fitness = funcion_fitness_QAP(coste, Mejor_Caso[i]);
					cout << "++ Fitness: " << fitness << endl;
					tiempo = std::chrono::duration_cast<std::chrono::milliseconds>(momentoFin - momentoInicio);
					cout << "++ Tiempo Pasado: " << tiempo.count() << "ms" << endl;
					coste_medio[5] += coste / 20;
					fitness_medio[5] += fitness / 20;
					tiempo_medio[5] += tiempo.count() / 20;
					salida_VNS << nombre_fichero << " & " << coste << " & " << fitness << " & " << tiempo.count() << " ms" << " \\\\" << endl;

					//-------------------FIN ALGORITMO-----------------------------//
					



					cout << "------------------------------------------------------" << endl;
				}
			}
			salida_ES << "Promedio" << " & " << coste_medio[0] << " & " << fitness_medio[0] << " & " << tiempo_medio[0] << " ms" << " \\\\" << endl;
			salida_BLP3 << "Promedio" << " & " << coste_medio[1] << " & " << fitness_medio[1] << " & " << tiempo_medio[1] << " ms" << " \\\\" << endl;
			salida_BMB << "Promedio" << " & " << coste_medio[2] << " & " << fitness_medio[2] << " & " << tiempo_medio[2] << " ms" << " \\\\" << endl;
			salida_ILS << "Promedio" << " & " << coste_medio[3] << " & " << fitness_medio[3] << " & " << tiempo_medio[3] << " ms" << " \\\\" << endl;
			salida_ILS_ES << "Promedio" << " & " << coste_medio[4] << " & " << fitness_medio[4] << " & " << tiempo_medio[4] << " ms" << " \\\\" << endl;
			salida_VNS << "Promedio" << " & " << coste_medio[5] << " & " << fitness_medio[5] << " & " << tiempo_medio[5] << " ms" << " \\\\" << endl;
		}
	}

	return 0;
}
