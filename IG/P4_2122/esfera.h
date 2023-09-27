#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"


class Esfera : public ObjRevolucion
{
private:
    float radio;
public:
    Esfera (const int num_vert_perfil = 10, 
           const int num_instancias_perf = 20, 
           const float radio = 1.0);
           
};



#endif
