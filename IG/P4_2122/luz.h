#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz
{
   public:
      void activar();
      void apagar();
      Tupla4f getD() {return this->colorDifuso;}
   protected:
      Tupla4f posicion;
      GLenum id;
      Tupla4f colorAmbiente;
      Tupla4f colorDifuso;
      Tupla4f colorEspecular;
   private:
};

#endif
