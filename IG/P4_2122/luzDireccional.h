#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"

class luzDireccional : public Luz
{
   public:
      luzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
      void variarAnguloAlpha (float incremento);
      void variarAnguloBeta (float incremento);
   protected:
      float alpha;
      float beta;
   private:
      void actualizarPosicion();
} ;




#endif
