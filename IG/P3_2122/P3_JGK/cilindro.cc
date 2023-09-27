#include "aux.h"
#include "cilindro.h"

Cilindro::Cilindro (const int num_vert_perfil = 2, 
                    const int num_instancias_perf = 20, 
                    const float altura = 1.0, 
                    const float radio = 1.0)
{
   std::vector<Tupla3f> perfil;
   this->altura = altura;
   this->radio = radio;
   float desplazamiento_superior = altura/(num_vert_perfil-1);
   
   for(int i=0; i<num_vert_perfil; i++)
   {
      perfil.push_back({radio, i*desplazamiento_superior, 0});
   }
   this->crearMalla(perfil, num_instancias_perf, true, true);
}
