
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
    Cilindro   (const int num_vert_perfil, 
                const int num_instancias_perf, 
                const float altura, 
                const float radio);
                    
};



#endif
