#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

class ObjRevolucion : public Malla3D
{
   public:
   ObjRevolucion() {;}
	   //Ejes: X=0 Y=1 Z=2
	   ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, unsigned eje = 1) ; // Construir a partir de archivo
	   ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, unsigned eje = 1) ; // Construir a partir de un perfil
   protected:
	   void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, unsigned eje = 1);
	   
   private:
   /*
      int Tapa_Inferior = 0;
	   int Tapa_Superior = 0;
	   */
	   
} ;

#endif
