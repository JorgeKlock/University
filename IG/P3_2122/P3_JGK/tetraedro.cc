#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float l)
{

   // inicializar la tabla de vértices
   float unidad = l/2;
   float r3 = sqrt(3);
   float r6 = sqrt(6);
	
   // inicializar la tabla de vértices
   v.resize(4);
   
   v.at(0) = {-l/2,-l*r6/6,-l*r3/4};
   v.at(1) = {l/2,-l*r6/6,-l*r3/4};
   v.at(2) = {0,-l*r6/6, l*r3/4};
   v.at(3) = {0,l*r6/6, 0};
   
   c_solido.resize(4);
   c_linea.resize(4);
   c_punto.resize(4);
   c_chess1.resize(4);
   c_chess2.resize(4);
   
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
   
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   f.resize(4);
   f.at(0) = {0,1,2};
   f.at(1) = {0,3,1};
   f.at(2) = {0,2,3};
   f.at(3) = {1,3,2};
   
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

