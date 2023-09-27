#include "cubo.h"

Cubo::Cubo(float l)
{
	float unidad = l/2;
	
   // inicializar la tabla de vértices
   v.resize(8);
   
   v.at(0) = {-unidad,unidad,unidad};
   v.at(1) = {unidad,unidad,unidad};
   v.at(2) = {-unidad,-unidad,unidad};
   v.at(3) = {unidad,-unidad,unidad};
   v.at(4) = {-unidad,unidad,-unidad};
   v.at(5) = {unidad,unidad,-unidad};
   v.at(6) = {-unidad,-unidad,-unidad};
   v.at(7) = {unidad,-unidad,-unidad};
   
   c_solido.resize(8);
   c_linea.resize(8);
   c_punto.resize(8);
   c_chess1.resize(8);
   c_chess2.resize(8);
   
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
   
   f.resize(12);
   f.at(0) = {0,2,1};
   f.at(1) = {1,2,3};
   f.at(2) = {1,3,5};
   f.at(3) = {3,7,5};
   f.at(4) = {5,7,4};
   f.at(5) = {4,7,6};
   f.at(6) = {0,4,6};
   f.at(7) = {0,6,2};
   f.at(8) = {0,5,4};
   f.at(9) = {0,1,5};
   f.at(10) = {2,7,3};
   f.at(11) = {2,6,7};
   
   //Rellenar caras pares e impares
         for(int i=0; i<f.size(); i++)
         {
            if (i%2 == 0)
            f1.push_back(f[i]);
            else
            f2.push_back(f[i]);
         }
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   this->calcular_normales();
}

