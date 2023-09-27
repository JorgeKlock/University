#include "aux.h"
#include "luz.h"
#include "luzDireccional.h"

luzDireccional::luzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso)
{
   this->colorDifuso = colorDifuso;
   this->colorEspecular = colorEspecular;
   this->colorAmbiente = colorAmbiente;
   this->id = idLuzOpenGL;
   
   //calcular las coordenadas (x,y,z) a partir de (1, alpha, beta)
   this->alpha = direccion[0];
   this->beta = direccion[1];
   
   this->actualizarPosicion();
}


void luzDireccional::actualizarPosicion()
{
   float z = cos(beta);
   float x = sin(beta)*cos(alpha);
   float y = sin(beta)*sin(alpha);
   
   Tupla4f pos;
       pos[0] = x;
       pos[1] = y;
       pos[2] = z;
       pos[3] = 0;
   this->posicion = pos;
}
void luzDireccional::variarAnguloAlpha (float incremento)
{
   this->alpha += incremento;
   actualizarPosicion();
}
void luzDireccional::variarAnguloBeta (float incremento)
{
   this->beta += incremento;
   actualizarPosicion();
}

