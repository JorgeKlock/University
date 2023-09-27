#include "aux.h"
#include "luz.h"
#include "luzPosicional.h"

luzPosicional::luzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso)
{
   this->colorDifuso = colorDifuso;
   this->colorEspecular = colorEspecular;
   this->colorAmbiente = colorAmbiente;
   this->id = idLuzOpenGL;
   Tupla4f pos;
      pos[0] = posicion[0];
      pos[1] = posicion[1];
      pos[2] = posicion[2];
      pos[3] = 1;
   this->posicion = pos;
}
