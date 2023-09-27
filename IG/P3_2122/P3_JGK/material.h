// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: material.h

//
// #############################################################################

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"


class Material
{
   public:
       Material();
       Material(Tupla4f n_ambiente, Tupla4f n_especular, Tupla4f n_difuso, float n_brillo);
       void Aplicar();
   protected:
   private:
      Tupla4f ambiente;   //Color ambiente
      Tupla4f especular;   //Color especular
      Tupla4f difuso;   //Color difuso
      float brillo;   
} ;




#endif
