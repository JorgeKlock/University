extern "C" {
#include "cec17.h"
}
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

bool Feasible(vector<double> solution)
{
    for (int i = 0; i < solution.size(); i++)
    {
        if (solution[i] < -100.0 || solution[i] > 100.0) return false;
    }
    return true;
}

double BL(vector<double> &sol_ini, int Max_eval, int problem_size, std::mt19937 gen)
{
    int eval = 0;
    std::uniform_real_distribution<> unitdis(-1.0, 1.0);
    double best_fitness = cec17_fitness(&sol_ini[0]);

    while (eval < Max_eval)
    {
        vector<double> sol_actual(problem_size);
        for (int i = 0; i < problem_size; i++)
        {
            double r_k = unitdis(gen);
            sol_actual[i] = sol_ini[i] + (r_k);
        }
        if (Feasible(sol_actual))
        {
            double fitness = cec17_fitness(&sol_actual[0]);
            eval += 1;
            if (fitness < best_fitness)
            {
                best_fitness = fitness;
                sol_ini = sol_actual;
            }
        }
    }
    return best_fitness;
}


int main() {
    vector<double> sol;
    int dim = 30;
    int seed = 42;
    int flock_size = 50;
    double awareness_probability = 0.1;
    double flight_lenght = 2;
    vector<vector<double>> Flock(flock_size, vector<double>(dim));
    vector<vector<double>> Memories(flock_size, vector<double>(dim));
    vector<double> Memories_fitness(flock_size);
    vector<vector<double>> Future(flock_size, vector<double>(dim));
    std::uniform_real_distribution<> dis(-100.0, 100.0);
    std::uniform_int_distribution<> intdis(0, flock_size-2);
    std::uniform_real_distribution<> unitdis(0.0, 1.0);

    int Max_evals_BL = 100*dim;

    for (int funcid = 1; funcid <= 30; funcid++) {
        vector<double> sol(dim);
        vector<double> bestsol(dim);
        double fitness;
        double best = -1;

        cec17_init("CSAbl", funcid, dim);

        //cerr << "Warning: output by console, if you want to create the output file you have to comment cec17_print_output()" << endl;
        //cec17_print_output(); // Comment to generate the output file

        std::mt19937 gen(seed); // Inicio semilla
        int evals = 0;

        // Inicializamos la bandada de cuervos
        for (int i = 0; i < flock_size; i++)
        {
            // Para cada cuervo crear [Problem_size] componentes aleatorias
            for (int j = 0; j < dim; j++)
            {
                sol[j] = dis(gen);
            }
            Flock[i] = sol;
            // Evaluar su fitness
            fitness = cec17_fitness(&sol[0]);
            evals += 1;
            // Almacenar en memoria
            Memories[i] = sol;
            Memories_fitness[i] = fitness;
        }

        while (evals < 10000 * dim)
        {
            // Para cada cuervo hacer
            for (int i = 0; i < flock_size; i++)
            {
                // Elegir un cuervo aleatorio distinto de si mismo
                int crow_followed = intdis(gen);
                if (crow_followed >= i) crow_followed++;

                // Determinar si se da cuenta
                double r_j = unitdis(gen);
                // Si no se da cuenta le guía hacia su comida
                if (r_j >= awareness_probability)
                {
                    double r_i = unitdis(gen);
                    vector<double> temp_sol(dim);
                    //future[i] = Flock[i] + r_i x flight_lenght x (Memories[crow_followed] - Flock[i]);
                    transform(Memories[crow_followed].begin(), Memories[crow_followed].end(), Flock[i].begin(), temp_sol.begin(), minus<double>());
                    double escalar = r_i * flight_lenght;
                    transform(temp_sol.begin(), temp_sol.end(), temp_sol.begin(), [escalar](double componente) { return escalar * componente; });
                    transform(Flock[i].begin(), Flock[i].end(), temp_sol.begin(), Future[i].begin(), plus<double>());
                }
                // Si se da cuenta le guía en dirección aleatoria
                else
                {
                    for (int k = 0; k < dim; k++)
                    {
                        sol[k] = dis(gen);
                    }
                    Future[i] = sol;
                }
            }
            // Actualizamos las soluciones actuales por las futuras mientras sean plausibles 
            for (int i = 0; i < flock_size; i++)
            {
                if (Feasible(Future[i]))
                {
                    fitness = cec17_fitness(&Future[i][0]);
                    evals += 1;
                    if (fitness < Memories_fitness[i])
                    {
                        Memories_fitness[i] = fitness;
                        Memories[i] = Future[i];
                    }
                    Flock[i] = Future[i];
                }
            }
            // Al 10% les aplicamos una búsqueda local
            int cuantos = flock_size / 10;
            // Tenemos en indices ordenados de mejor a peor fitness
            for (int i = 0; i < cuantos; i++)
            {
                //Hacemos búsqueda local a los mejores
                Memories_fitness[i] = BL(Memories[i], Max_evals_BL, dim, gen);
                evals += Max_evals_BL + 1;
            }
                
            
        }
        // Una vez se acaban las evaluaciones, devolvemos la mejor solucion
        best = Memories_fitness[0];
        bestsol = Memories[0];
        for (int i = 1; i < flock_size; i++)
        {
            if (Memories_fitness[i] < best)
            {
                best = Memories_fitness[i];
                bestsol = Memories[i];
            }
        }
        cout << "Best CSAbl[F" << funcid << "]: " << scientific << cec17_error(best) << endl;
    }

}
