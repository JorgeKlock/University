#include "aux.h"
#include "luz.h"
#include "luzPosicional.h"

luzPosicional::luzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso)
{
   this->colorDifuso = colorDifuso;
   this->colorEspecular = colorEspecular;
   this->colorAmbiente = colorAmbiente;
   this->id = idLuzOpenGL;
   this->posicion = posicion;
}
