#include "aux.h"
#include "objrevolucion.h"


/*
ObjRevolucion::ObjRevolucion(int t_i, int t_s)
{
   this->Tapa_Inferior = t_i;
	this->Tapa_Superior = t_s;
}
 */
 
// *****************************************************************************
// A partir de un archivo (PLY)

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf, unsigned eje) {
   
   //Leemos el perfil del objeto en un vector
   std::vector<Tupla3f> perfil;
   ply::read_vertices(archivo, perfil);
   
   //Creamos la malla 
   crearMalla(perfil, num_instancias, tapa_sup, tapa_inf, eje);
}

// *****************************************************************************
// A partir de un perfil (vector de puntos)

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup, bool tapa_inf, unsigned eje) {
   //Creamos la malla 
   crearMalla(perfil, num_instancias, tapa_sup, tapa_inf, eje);
}

// *****************************************************************************
// Crear la malla (Vértices y Caras)

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf, unsigned eje) {

   int Tapa_Inferior = 0;
   int Tapa_Superior = 0;
   unsigned ejealt1, ejealt2;
   if(eje == 0)
   {
      ejealt1 = 1;
      ejealt2 = 2;
   }
   else if(eje == 1)
   {
      ejealt1 = 0;
      ejealt2 = 2;
   }
   else if(eje == 2)
   {
      ejealt1 = 0;
      ejealt2 = 1;
   }

   bool abajo = false;
   if(perfil_original[0](eje) < perfil_original[1](eje))
      abajo = true;
      
   //Comprobamos si tiene polos superiores o inferiores
   bool norte, sur = false;
   Tupla3f polo_norte;
   Tupla3f polo_sur;
   
    if(perfil_original[0](ejealt1) == 0 && perfil_original[0](ejealt2) == 0)
    {
        polo_sur = perfil_original[0];
        perfil_original.erase(perfil_original.begin());
        sur = true;
    }
    if(perfil_original[perfil_original.size()-1](ejealt1) == 0 && perfil_original[perfil_original.size()-1](ejealt2) == 0)
    {
        polo_norte = perfil_original[perfil_original.size()-1];
        perfil_original.pop_back();
        norte = true;
    }
   
   //Establecemos los parámetros para la creación de la malla
   int tam = perfil_original.size();
   float pi = atan(1)*4;
   float alfa = 2*pi/num_instancias;
   float matmul[3][3];
   float RotacionX[3][3] = {{1,               0,                0},
                           {0,        cos(alfa),        sin(alfa)},
                           {0,       -sin(alfa),       cos(alfa)}};
   
   float RotacionY[3][3] = {{cos(alfa),       0,        -sin(alfa)},
                           {0,                1,                 0},
                           {sin(alfa),        0,        cos(alfa)}};
                           
   float RotacionZ[3][3] = {{cos(alfa),        sin(alfa),          0},
                           {-sin(alfa),        cos(alfa),          0},
                           {0,                         0,          1}};
                           
   switch (eje)
   {
      case 0:
         {
            for(int i=0; i<3; i++)
            {
               for(int j=0; j<3; j++)
               {
                  matmul[i][j] = RotacionX[i][j];
               }
            }
         }
         break;
      case 1:
         {
            for(int i=0; i<3; i++)
            {
               for(int j=0; j<3; j++)
               {
                  matmul[i][j] = RotacionY[i][j];
               }
            }
         }
         break;
      case 2:
         {
            for(int i=0; i<3; i++)
            {
               for(int j=0; j<3; j++)
               {
                  matmul[i][j] = RotacionZ[i][j];
               }
            }
         }
         break;
      default:
         break;
   }
   
   
   for(int i = 0; i<tam; i++)
   {
      v.push_back(perfil_original[i]);
   }
   
   //Creamos los vertices girando el perfil original
   for(int i = 1; i < num_instancias; i++)
   {
      for(int j = 0; j < tam; j++)
      {
         Tupla3f elemento = v[(i-1)*tam+j];
         float x = elemento(X)*matmul[0][0]+elemento(Y)*matmul[1][0]+elemento(Z)*matmul[2][0];
         float y = elemento(X)*matmul[0][1]+elemento(Y)*matmul[1][1]+elemento(Z)*matmul[2][1];
         float z = elemento(X)*matmul[0][2]+elemento(Y)*matmul[1][2]+elemento(Z)*matmul[2][2];
         v.push_back({x,y,z});
      }
   }
   
   //Creamos las caras según como venga dado el perfil
   
   if(abajo)
   {
      //De abajo arriba
      for(int i=0; i < num_instancias; i++)
      {
         for(int j=0; j < tam-1; j++)
         {
            int a = tam*i+j;
            int b = tam*((i+1)%num_instancias)+j;
            f.push_back({a,b,b+1});
            f.push_back({a,b+1,a+1});
         }
      }
   }
   else
   {
      //De arriba a abajo
      for(int i=0; i < num_instancias; i++)
      {
         for(int j=0; j < tam-1; j++)
         {
            int a = tam*i+j;
            int b = tam*((i+1)%num_instancias)+j;
            f.push_back({a,b+1,b});
            f.push_back({a,a+1,b+1});
         }
      }
   }
   
   if(tapa_inf)
   {
      if (sur) //Usamos la tapa del perfil
        v.push_back(polo_sur);
      else  //Creamos una proyectando sobre el eje Y
        v.push_back({0, v[0](eje), 0});
   }
   if(tapa_sup)
   {
      if(norte)   //Usamos la tapa del perfil
         v.push_back(polo_norte);
      else  //Creamos una proyectando sobre el eje Y
         v.push_back({0, v[tam-1](eje), 0});
   }
   
   if(abajo)
   {
      //tapa inferior
      for(int i=0; i < num_instancias; i++)
      {
         f.push_back({tam*num_instancias, (tam*(i+1))%(tam*num_instancias), tam*i});
         Tapa_Inferior += 1;
      }
      
      //Tapa superior
      for(int i=0; i < num_instancias; i++)
      {
         f.push_back({tam*num_instancias+1, tam*(i+1)-1, (tam*(i+2)-1)%(tam*num_instancias)});
         Tapa_Superior += 1;
      }
   }
   else
   {
      //tapa inferior
      for(int i=0; i < num_instancias; i++)
      {
         f.push_back({tam*num_instancias+1, (tam*(i+2)-1)%(tam*num_instancias), tam*(i+1)-1});
         Tapa_Inferior += 1;
      }
      //Tapa superior
      for(int i=0; i < num_instancias; i++)
      {
         f.push_back({tam*num_instancias, tam*i, (tam*(i+1))%(tam*num_instancias)});
         Tapa_Superior += 1;
      }
   }
   
   
   //Colores y caras
   tam = v.size();
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
         
   sin_dibujar = 3*Tapa_Inferior+3*Tapa_Superior;   
   this->calcular_normales();
}
