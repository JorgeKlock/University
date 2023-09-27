#include "aux.h"
#include "luz.h"
#include "luzDireccional.h"

luzDireccional::luzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso)
{
   this->colorDifuso = colorDifuso;
   this->colorEspecular = colorEspecular;
   this->colorAmbiente = colorAmbiente;
   this->id = idLuzOpenGL;
   Tupla3f pos;
       pos[0] = direccion[0];
       pos[1] = direccion[1];
       pos[2] = 0;
   this->posicion = pos;
}
