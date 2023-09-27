// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   void draw_ModoInmediato(bool dibujado[5]);
   void draw_ModoDiferido(bool dibujado[5]);
   void draw_ModoSuavizado(bool dibujado[5]);
   void draw_ModoPlano(bool dibujado[5]);

   void draw(int modo=0, bool dibujado[5]=nullptr) ;
   
   void setMaterial (Material mat) {this->m = mat;}

   protected:
   
   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f1; //Caras pares e impares
   std::vector<Tupla3i> f2;
   
   std::vector<Tupla4f> c_linea;   //Tupla de 4 floats (R,G,B,alpha) como reales
   std::vector<Tupla4f> c_punto;   //Tupla de 4 floats (R,G,B,alpha) como reales
   std::vector<Tupla4f> c_solido;   //Tupla de 4 floats (R,G,B,alpha) como reales
   std::vector<Tupla4f> c_chess1;   //Tupla de 4 floats (R,G,B,alpha) como reales
   std::vector<Tupla4f> c_chess2;   //Tupla de 4 floats (R,G,B,alpha) como reales
   
   std::vector<Tupla3f> nv;   // Normales de los vértices
   std::vector<Tupla3f> nc;   // Normales de las caras
      
   int sin_dibujar = 0;
   // completar: tabla de colores, tabla de normales de vértices
   
   unsigned id_vbo_ver = 0;
   unsigned id_vbo_tri = 0;
   unsigned id_vbo_tri2 = 0;
   unsigned id_vbo_tri1 = 0;
   unsigned id_vbo_cS = 0;
   unsigned id_vbo_cL = 0;
   unsigned id_vbo_cP = 0;
   unsigned id_vbo_cC1 = 0;
   unsigned id_vbo_cC2 = 0;
   
   private:
       Material m;
} ;


#endif
