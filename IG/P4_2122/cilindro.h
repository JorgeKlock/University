
#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"


class Cilindro : public ObjRevolucion
{
private:
    float altura;
    float radio;
public:
    Cilindro   (const int num_vert_perfil = 20, 
                    const int num_instancias_perf = 20, 
                    const float altura = 1, 
                    const float radio = 1);
                    
};



#endif
