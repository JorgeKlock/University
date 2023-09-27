#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <sstream>
#include <math.h>
#include <fstream>
#include <iterator>

using namespace std;

class TSP {

  private:

    vector< vector<int> > distancias;
    map<string, int> gs;
    vector<int> solucion;

  public:

    // Calculo de la distancia enter dos puntos
    int calcular_distancia(float x1, float x2, float y1, float y2) {
      return (int) round((sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2))));
    }

    // Constructor de la clase TSP
    TSP (vector<float> x, vector<float> y) {

      int dimension = (int) x.size();
      distancias.resize(dimension);

      // Creacion de la matriz de distancias
      for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
          distancias[i].push_back(this -> calcular_distancia(x[i],x[j],y[i],y[j]));
        }
      }
    }

    int g(int nodo, vector<int> s) {

      int distancia_min, distancia_min_aux;
      string ss_aux;
      stringstream sss_aux;
      vector<int> s_aux;
      map<string, int>::iterator gsit;

      distancia_min = INT_MAX;
      distancia_min_aux = INT_MAX;

      // Si 's' no está vacío
      if (!s.empty()) {

        copy(s.begin(), s.end(), ostream_iterator<int>(sss_aux, " "));
        ss_aux = to_string(nodo) + ' ' + sss_aux.str();

        // Comprobamos que g(nodo, s) lo hayamos calculado previamente
        gsit = this -> gs.find(ss_aux);
        if (gsit != this -> gs.end()) {
          distancia_min = gsit -> second;
        }
        // No ha sido calculado g(nodo, s)
        else {
            for (int i = 0; i < (int) s.size(); i++) {
              s_aux = s;
              s_aux.erase(s_aux.begin()+i);

              distancia_min_aux = distancias[nodo][s[i]] + g(s[i], s_aux);

              if (distancia_min_aux < distancia_min) {
                distancia_min = distancia_min_aux;
              } // end if
            } // end for

            // Guardamso el valor de g(nodo, s)
            gs[ss_aux] = distancia_min;
        } // end else
      }
      // 's' está vacío
      else {
        distancia_min = distancias[nodo][0];
      }
      return distancia_min;
    }

    vector<int> camino(int nodo, vector<int> s) {

      int distancia_min, distancia_min_aux, indice_nodo_min;
      vector<int> solucion, sin_solucion, s_aux;

      sin_solucion = s;
      solucion.push_back(nodo);

      while (solucion.size() <= s.size()) {

        distancia_min = INT_MAX;
        indice_nodo_min = -1;

        for (int i = 0; i < (int) sin_solucion.size(); i++) {

          s_aux = sin_solucion;
          s_aux.erase(s_aux.begin()+i);

          distancia_min_aux = distancias[solucion.back()][sin_solucion[i]] + g(sin_solucion[i], s_aux);

          if (distancia_min_aux < distancia_min) {
            distancia_min = distancia_min_aux;
            indice_nodo_min = i;
          }
        }

        solucion.push_back(sin_solucion[indice_nodo_min]);
        sin_solucion.erase(sin_solucion.begin()+indice_nodo_min);
      }

      return solucion;
    }
};

int main(int argc, char ** argv) {

  // Lectura de los parametros de entrada
  if (argc != 2)
  {
    cout << "Parametros de entrada: " << endl << "1.- Nombre del fichero TSP" << endl << endl;
    return 1;
  }

  ifstream infile(argv[1]);
  istringstream aux_stringstream;
  string line, text;
  int aux, dimension;
  float var1, var2, var3;
  vector<int> n;
  vector<float> x, y;

  if (infile.is_open()) {
    while (line.compare("NODE_COORD_SECTION") != 0) {
      getline(infile, line);
      aux = line.find("DIMENSION");
      if (aux != -1) {
        aux = line.find(":");
        aux_stringstream.str(line.substr(aux+1,-1));
        aux_stringstream >> dimension;
      }
    }
  }
  else {
    cout << "Archivo no encontrado" << endl;
  }

  // Lectura del número del nodo, su posición x e y
  for (int i = 0; i < dimension; i++) {
    infile >> var1 >> var2 >> var3;
    n.push_back(var1);
    x.push_back(var2);
    y.push_back(var3);
  }

  infile.close();

  TSP tsp(x, y);

  n.erase(n.begin());
  for (int i = 0; i < (int) n.size(); i++) {
    n[i] = n[i] - 1;
  }

  cout << tsp.g(0, n) << endl;

  n = tsp.camino(0, n);

  for (int i = 0; i < (int) n.size(); i++) {
    std::cout << n[i] + 1<< ' ';
  }
}
