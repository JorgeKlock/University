#include "aux.h"
#include "esfera.h"
#include <cmath>
Esfera::Esfera     (const int num_vert_perfil = 2, 
                    const int num_instancias_perf = 20, 
                    const float radio = 1.0)
{
   std::vector<Tupla3f> perfil;
   this->radio = radio;
   Tupla3f puntoInicial = {0, radio, 0};
   
   float pi = M_PI;
   float alfa = pi/(num_vert_perfil-1);
   float rotacionZ[3][3] = {{cos(alfa), sin(alfa), 0},
                           {-sin(alfa), cos(alfa), 0},
                           {0         , 0        , 0}};
   
   for(int i=0; i<=num_vert_perfil; i++)
   {
    float alfa = i*pi/num_vert_perfil;
    float x = sin(alfa)*radio;
    float y = cos(alfa)*radio;
    float z = 0;
    perfil.push_back({x,y,z});
      
   }
   perfil[perfil.size()-1](X) = 0;

   this->crearMalla(perfil, num_instancias_perf, true, true);
}
