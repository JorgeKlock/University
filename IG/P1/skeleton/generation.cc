#include "generation.h"


_vertex3f Transformar(_vertex3f coor_original, int n_rotaciones, int k)
{
    _vertex3f solucion;
    solucion._0 = coor_original._0*cos(2*(M_PI/n_rotaciones)*k);
    solucion._2 = coor_original._0*sin(2*(M_PI/n_rotaciones)*k);
    return solucion;
}

generation::generation()
{

}
void generation::GenerarVertices(_object3D &base, vector<_vertex3f> generatriz, int n_rotaciones)
{
        //Comprobar cantidad de puntos al eje

    vector<int> index_eje;

    bool primer_eje = false;
    int contador = 0;
    for(int e=0; e<(int)generatriz.size(); e++)
    {
        if(generatriz[e]._0==0)
            index_eje.push_back(e);
    }

    //tambien se podria crear una mascara de bool para comprobar cuales de los elementos de la generatriz son eje

    //Reservar memoria para Los puntos de eje + puntos generados*n_notaciones
    if(index_eje.size()>2) {printf ("error 001: demasiados puntos en el eje\n");}

    base.Vertices.resize(index_eje.size()+(generatriz.size()-index_eje.size())*n_rotaciones);
    (base.Vertices.size());


    for(int i=0; i<(int)generatriz.size(); i++)
    {
        bool punto_de_eje = false;
        for(int j=0; j<(int)index_eje.size(); j++)
        {
            if(index_eje[j] == i) //Si estamos en la posicion de generatriz donde hay un p_eje
            {
                punto_de_eje = true;
                if(!primer_eje){
                base.Vertices[base.Vertices.size()-1] = generatriz[i];
                primer_eje = true;
                }
                else
                {
                base.Vertices[base.Vertices.size()-2] = generatriz[i];
                }

            }
        }
        if(!punto_de_eje){
        for(int k=0; k<n_rotaciones; k++)
        {
            base.Vertices[contador] = Transformar(generatriz[i], n_rotaciones, k);
            contador++;
        }
        }
    }
    GenerarTriangulos(base, base.Vertices.size(), 0, 4, 0, 2);

}

void generation::GenerarTriangulos(_object3D &base, int n_vertices, int niveles, int caras, int p_nivel, int p_eje)
{
    base.Triangles.resize(niveles*caras + p_eje*caras);

    if(p_eje == 2)
    {
        //Las caras de los p_eje
        for(int i=0; i<caras; i++)
        {
        base.Triangles[i] = _vertex3ui(n_vertices-2, (1+i)%4, (0+i)%4);
        base.Triangles[caras+i] = _vertex3ui(n_vertices-1, (0+i)%4, (1+i)%4);
        }
    }


}
