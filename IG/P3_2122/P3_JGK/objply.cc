#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );
   
   int tam = v.size();
   c_solido.resize(tam);
   c_linea.resize(tam);
   c_punto.resize(tam);
   c_chess1.resize(tam);
   c_chess2.resize(tam);
   
   for(int i=0; i<c_solido.size(); i++)
            {
               c_solido.at(i) = {1.0,0.0,0.0,1};
            }
   for(int i=0; i<c_linea.size(); i++)
            {
               c_linea.at(i) = {0.0,1.0,0.0,1};
            }
   for(int i=0; i<c_punto.size(); i++)
            {
               c_punto.at(i) = {0.0,0.0,1.0,1};
            }   
   for(int i=0; i<c_chess1.size(); i++)
	         {
	            c_chess1.at(i) = {0.0,0.0,1.0,1};
	         } 
   for(int i=0; i<c_chess2.size(); i++)
	         {
	            c_chess2.at(i) = {0.0,1.0,0.0,1};
	         }     
	         
	//Rellenar caras pares e impares
         for(int i=0; i<f.size(); i++)
         {
            if (i%2 == 0)
            f1.push_back(f[i]);
            else
            f2.push_back(f[i]);
         }
       this->calcular_normales();  
}


