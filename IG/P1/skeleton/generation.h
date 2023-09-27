#ifndef GENERATION_H
#define GENERATION_H

//#include "object3d.h"
#include "piramidedoble.h"

class generation:public _object3D
{
public:
    generation();
    void GenerarVertices(_object3D &base, vector<_vertex3f> generatriz, int n_rotaciones);
    void GenerarTriangulos(_object3D &base, int n_vertices, int niveles, int caras, int p_nivel, int p_eje);
};

#endif // GENERATION_H
