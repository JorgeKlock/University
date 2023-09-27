/*ES:   Asignatura: Algoritmica
        Trabajo: Practica 3 - Greedy
        Descripcion: TSP con método de Cercanía */ 

// LIBRERIAS
//      Entrada/Salida
#include <iostream>
//      Vectores
#include <vector>
#include <list>
//      Abrir archivos
#include <fstream>
//      Procesado de Cadenas
#include <string>
#include <sstream>
//      Hacer operaciones matematicas
#include <cmath>
//      Obtener el MAX_INT
#include <climits>
#include <cstring>
#include <ctime>

#include <bitset>

using namespace std;

const int BITMAX=32;

//  FUNCIONES
//      Funcion auxiliar para calcular distancia euclidea entre dos puntos.
int calcularDistancia(double x2, double x1, double y2, double y1)
{
    return  (int)round( ( sqrt( pow(x2 - x1, 2) + pow(y2 - y1, 2) ) ) ) ;
}

void rellenarMatAdj(int** &adyacencia, float** &entrada, int dim)
{
    for (auto i = 0; i < dim; i++)
    {
        for (auto j = 0; j < dim; j++)
        {
            if (i != j)
            {
                adyacencia[i][j] = calcularDistancia(entrada[i][1], entrada[j][1], entrada[i][2], entrada[j][2]);
            }
            else
            {
                adyacencia[i][j] = 0;
            }
            
        }
    }
}


struct nodo
{
    int indice;
    double x;
    double y;
};

bool estaCalculado(int i, list<int> S,int** &memo)
{
    bitset<BITMAX> bitS;

    for (int j : S )
    {
        bitS.set(j);
    }
    bitS.set(i);
    if(memo[(int)bitS.to_ulong()][i] >= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int calcularCoord(list<int> S, int i)
{
    bitset<BITMAX> bitS;

    for (int j : S )
    {
        bitS.set(j);
    }
    bitS.set(i);
    return (int)bitS.to_ulong();
}

void print(list<int> S)
{
    for(int j: S)
    {
        cout<<j<<" ";
    }
}

void printMemo(int** &memo)
{
    int dim=4;
    cout<<"----START-----"<<endl;
    for (auto i = 0; i <  (1<<dim); i++)
    {
        for (auto j = 0; j < dim; j++)
        {
            if (memo[i][j]==-1)
            {
                cout<<"0 ";
            }
            else
            {
                cout<<memo[i][j]<<" ";                
            }
        }
        cout<<endl;
    }
    cout<<"----END-----"<<endl;

}


int g(int ciuIni, list<int> &listCiu, list<int> &caminoCiu, int** dist, int** &memo)
{
    if(listCiu.empty())
    {   
     //   cout<<"g("<<ciuIni<<",0) caso base, devuelvo "<< dist[ciuIni][0]<<endl;
        return memo[calcularCoord(listCiu,ciuIni)][ciuIni] = dist[ciuIni][0];
    }
    else if(estaCalculado(ciuIni,listCiu,memo))
    {
      //  cout<<"g("<<ciuIni<<",{";print(listCiu);cout<<"}) en tabla="<<memo[calcularCoord(listCiu,ciuIni)][ciuIni]<<endl;
        return memo[calcularCoord(listCiu,ciuIni)][ciuIni];
    }
    else
    {
        int costoMini = INT_MAX, costoAct;
        int sigCiu;
        int S = listCiu.size();
        for (int i = 0; i < S; i++)
        {
            sigCiu = listCiu.front();
            listCiu.pop_front();

        //    cout<<"g("<<ciuIni<<",{";print(listCiu);cout<<"}) entro en recursion."<<endl;

            costoAct = dist[ciuIni][sigCiu] + g(sigCiu,listCiu,caminoCiu,dist,memo);
            listCiu.push_front(sigCiu);

         //   cout<<"g("<<ciuIni<<",{";print(listCiu);cout<<"}) de vuelta de recursión, costo: "<<costoAct<<endl;

            if(costoAct < costoMini)
            {
                costoMini = costoAct;
                memo[calcularCoord(listCiu,ciuIni)][ciuIni] = costoMini;
           //     cout<<"g("<<ciuIni<<",{";print(listCiu);cout<<"}) costo actualizado="<<costoMini<<endl;
            }
            listCiu.pop_front();
            listCiu.push_back(sigCiu);
        }
        return costoMini;
    }
}

void tsp(int** matrizAdy, list<int> &listaCiudades, list<int> &caminoCiudades, int &caminoCosto, int** &memo)
{
    int ciudadInicio = listaCiudades.front();
    listaCiudades.pop_front();
    caminoCosto = g(ciudadInicio, listaCiudades, caminoCiudades, matrizAdy, memo);
    cout <<"Costo min:"<<caminoCosto<<endl;
}
//      Funcion Main
int main(int argc, char * argv[])
{

    if (argc != 2)
    {
      cerr << "Formato: ./" << argv[0] << " <rutaArchivo.tsp>" << endl;
      return -1;
    }

    float **entrada,**matrizOUT;
    int dim;
    string linea = "";
    istringstream aux2;
    ifstream archivo (argv[1]);
    list<int> listaCiudades, caminoCiudades;
    if (archivo.is_open())
    {
        int aux;
        while (linea.compare("NODE_COORD_SECTION") != 0)
        {
            getline(archivo,linea);
            aux = linea.find("DIMENSION");
            if(aux != -1)
            {
                aux = linea.find(":");
                aux2.str(linea.substr(aux+1,-1));
                aux2 >> dim;
            }
        }

        entrada = new float*[dim];
        matrizOUT = new float*[dim+1];

        float a,b,c;
        for(int i=0; i<dim; i++)
        {
            archivo >> a >> b >> c;
            entrada[i] = new float[3];
            entrada[i][0] = a;
            entrada[i][1] = b;
            entrada[i][2] = c;

            matrizOUT[i] = new float[3];
            matrizOUT[i][0] = 0;
            matrizOUT[i][1] = 0;
            matrizOUT[i][2] = 0;
            
            listaCiudades.push_back(a-1);
        }
        matrizOUT[dim] = new float[3];
        archivo.close();
    }
    else cout << "No se puede abrir el archivo."; 

    int **matrizAdy = new int*[dim];
    for (auto i = 0; i < dim; i++)
    {
        matrizAdy[i] = new int[dim];
    }
    
    rellenarMatAdj(matrizAdy, entrada, dim);

    int **memo = new int*[(1 << dim)];
    for (auto i = 0; i < (1 << dim); i++)
    {
        memo[i] = new int[dim];
    }   
    for (auto i = 0; i < (1<< dim); i++)
    {
        for (auto j = 0; j < dim; j++)
        {
            memo[i][j] = -1;
        }
    }

    for (int i: listaCiudades)
    {
        cout << i <<" "<<endl;
    }

    int caminoCosto = 0;

     
    clock_t t_antes = clock();
    tsp(matrizAdy, listaCiudades, caminoCiudades, caminoCosto, memo);
    clock_t t_despues = clock();

  cout <<"Tiempo: " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << endl;

/*  for (auto i = 0; i <  (1<<dim); i++)
    {
        for (auto j = 0; j < dim; j++)
        {
            if (memo[i][j]==-1)
            {
                cout<<"-";
            }
            else
            {
                cout<<memo[i][j]<<" ";                
            }
        }
        cout<<endl;
    }*/

  /*  //  Imprimir resultado del Greedy
    cout <<"CAMINO: "<< camino << endl
            <<"INICIO_CAMINO_CERCANIA"<< endl;

    for (int i = 0; i < (int)tour.size(); i++)
    {
        cout <<tour[i].indice<<"\t" <<tour[i].x<<"\t"<<tour[i].y<<endl;
    }
*/

for (int i = 0; i < dim; i++)
{
    delete [] memo[i];
    delete [] matrizAdy[i];
}

  delete [] memo;
  delete [] matrizAdy;

  return 0;
}
