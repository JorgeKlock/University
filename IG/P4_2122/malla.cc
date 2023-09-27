#include "aux.h"
#include "malla.h"
// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

 void Malla3D::calcular_normales()
 {
 int p,q,r;
 Tupla3f v1,v2,v3,a,b,m,n;
   this->nc.resize(0);
   this->nv.resize(this->v.size());
   //Si las normales quedan al reves se puede invertir el orden del producto vectorial
   for (int i=0; i<this->f.size(); i++)
   {
      p = f[i][0]; //Indice del vertice p
      q = f[i][1]; //Indice del vertice q
      r = f[i][2]; //Indice del vertice r
      v1 = this->v[p];  //Coordenadas del vertice p
      v2 = this->v[q];  //Coordenadas del vertice q
      v3 = this->v[r];  //Coordenadas del vertice r
      a = v2-v1;
      b = v3-v1;
      //Producto Vectorial: vector1.cross(vector2)
      m = a.cross(b);
      double modulo = sqrt(pow(m[0],2)+pow(m[1],2)+pow(m[2],2));
      n = m/modulo; 
      this->nc.push_back(n);
     //Sumar el resultado a las normales de los vértices implicados
     
     this->nv[p] = nv[p]+n;
     this->nv[q] = nv[q]+n;
     this->nv[r] = nv[r]+n;
   }
   
 }

void Malla3D::draw_ModoInmediato(bool dibujado[5])
{
   glDisable(GL_LIGHTING);
  
  	// habilitar uso de un array de vértices
	glEnableClientState(GL_VERTEX_ARRAY);
	// indicar el formato y la dirección de memoria del array de vértices
	// (son tuplas de 3 valores float, sin espacio entre ellas)
	glVertexPointer(3, GL_FLOAT, 0, v.data()) ;
	// visualizar, indicando: tipo de primitiva, número de índices,
	// tipo de los índices, y dirección de la tabla de índices
	glEnableClientState(GL_COLOR_ARRAY);
	
	int sobrantes;
	if(dibujado[4]) sobrantes = 0;
	if(!dibujado[4]) sobrantes = sin_dibujar;
	
	
   if(!dibujado[3])
   {
      if(dibujado[0])
      {
            glPolygonMode(GL_FRONT, GL_FILL);
            glColorPointer(4, GL_FLOAT, 0, c_solido.data() );
            glDrawElements( GL_TRIANGLES , 3*f.size()-sobrantes, GL_UNSIGNED_INT , f.data());
      }
      if(dibujado[1])
      {
            glPolygonMode(GL_FRONT, GL_LINE);
            glColorPointer(4, GL_FLOAT, 0, c_linea.data() );
            glDrawElements( GL_TRIANGLES , 3*f.size()-sobrantes, GL_UNSIGNED_INT , f.data());
      }
      if(dibujado[2])
      {
            glPolygonMode(GL_FRONT, GL_POINT);
            glColorPointer(4, GL_FLOAT, 0, c_punto.data() );
            glDrawElements( GL_TRIANGLES , 3*f.size()-sobrantes, GL_UNSIGNED_INT , f.data());
      }   
   }
   else
   {
   
         //Modificar colores y dibujar
         glPolygonMode(GL_FRONT, GL_FILL);
         
         //Color de las caras pares
	      glColorPointer(4, GL_FLOAT, 0, c_chess1.data() );
	      //Dubujar las caras pares
         glDrawElements( GL_TRIANGLES , 3*f1.size()-int(sobrantes/2), GL_UNSIGNED_INT , f1.data());
         //Color de las caras impares
	      glColorPointer(4, GL_FLOAT, 0, c_chess2.data() );
	      //Dibujar las caras impares
         glDrawElements( GL_TRIANGLES , 3*f2.size()-int(sobrantes/2), GL_UNSIGNED_INT , f2.data());
   }

	// deshabilitar array de vértices
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY);
    glEnable(GL_LIGHTING);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

GLuint CrearVBO( GLuint tipo_vbo , GLuint tamanio_bytes ,GLvoid * puntero_ram )
{
   GLuint id_vbo; // resultado: identificador de VBO
   glGenBuffers( 1, & id_vbo ); // crear nuevo VBO, obtener identificador (nunca 0)
   glBindBuffer( tipo_vbo , id_vbo ); // activar el VBO usando su identificador
   // esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData( tipo_vbo , tamanio_bytes , puntero_ram , GL_STATIC_DRAW );
   glBindBuffer( tipo_vbo , 0 ); // desactivación del VBO (activar 0)
   return id_vbo ; // devolver el identificador resultado
}
void Malla3D::draw_ModoDiferido(bool dibujado[5])
{
    glDisable(GL_LIGHTING);
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   if(id_vbo_ver == 0)
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(float), v.data());
   if(id_vbo_tri == 0)
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*3*sizeof(int), f.data());
   if(id_vbo_cS == 0)
      id_vbo_cS = CrearVBO(GL_ARRAY_BUFFER, c_solido.size()*4*sizeof(float), c_solido.data());
   if(id_vbo_cL == 0)
      id_vbo_cL = CrearVBO(GL_ARRAY_BUFFER, c_linea.size()*4*sizeof(float), c_linea.data());
   if(id_vbo_cP == 0)
      id_vbo_cP = CrearVBO(GL_ARRAY_BUFFER, c_punto.size()*4*sizeof(float), c_punto.data());
   if(id_vbo_cC1 == 0)
      id_vbo_cC1 = CrearVBO(GL_ARRAY_BUFFER, c_chess1.size()*4*sizeof(float), c_chess1.data());
   if(id_vbo_cC2 == 0)
      id_vbo_cC2 = CrearVBO(GL_ARRAY_BUFFER, c_chess2.size()*4*sizeof(float), c_chess2.data());
   
   glBindBuffer( GL_ARRAY_BUFFER , id_vbo_ver ); // activar VBO de vértices
   glVertexPointer( 3, GL_FLOAT , 0, 0 ); 
   glBindBuffer( GL_ARRAY_BUFFER , 0 ); // desactivar VBO de vértices.
   glEnableClientState( GL_VERTEX_ARRAY ); // habilitar tabla de vértices
   glEnableClientState(GL_COLOR_ARRAY);   //Habilitar tabla de colores
   
   int sobrantes;
   if(dibujado[4]) sobrantes = 0;
   if(!dibujado[4]) sobrantes = sin_dibujar;
	
	
   if(!dibujado[3])
   {
	   if(dibujado[0]) //Modo Relleno
	   {
	        glPolygonMode(GL_FRONT, GL_FILL);
                        
            glBindBuffer( GL_ARRAY_BUFFER , id_vbo_cS );// activar VBO de colores
            glColorPointer(4, GL_FLOAT, 0, 0);
            
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri );// activar VBO de triángulos
            glDrawElements( GL_TRIANGLES , 3*f.size()-sobrantes, GL_UNSIGNED_INT , 0 ) ; //Dibujar triangulos
            
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
            glBindBuffer( GL_ARRAY_BUFFER , 0 );// desactivar VBO de colores
      }
      if(dibujado[1]) //Modo Lineas
      {
	         glPolygonMode(GL_FRONT, GL_LINE);
	         
	        glBindBuffer( GL_ARRAY_BUFFER , id_vbo_cL );// activar VBO de colores
            glColorPointer(4, GL_FLOAT, 0, 0);
            
	        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri );// activar VBO de triángulos
            glDrawElements( GL_TRIANGLES , 3*f.size()-sobrantes, GL_UNSIGNED_INT , 0 ) ;
            
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
            glBindBuffer( GL_ARRAY_BUFFER , 0 );// desactivar VBO de colores
      }
      if(dibujado[2]) //Modo Puntos
      {
            
            glPolygonMode(GL_FRONT, GL_POINT);
            
            glBindBuffer( GL_ARRAY_BUFFER , id_vbo_cP );// activar VBO de colores
            glColorPointer(4, GL_FLOAT, 0, 0);
            
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri );// activar VBO de triángulos
            glDrawElements( GL_TRIANGLES , 3*f.size()-sobrantes, GL_UNSIGNED_INT , 0 ) ;
            
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
            glBindBuffer( GL_ARRAY_BUFFER , 0 );// desactivar VBO de colores
      }   
   }
   else
   {
         //Modificar colores y dibujar
         glPolygonMode(GL_FRONT, GL_FILL);
         
         if(id_vbo_tri1 == 0)
            id_vbo_tri1 = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f1.size()*3*sizeof(int), f1.data());
         if(id_vbo_tri2 == 0)
            id_vbo_tri2 = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f2.size()*3*sizeof(int), f2.data());        
            
         //Color de las caras pares
         glBindBuffer( GL_ARRAY_BUFFER , id_vbo_cC1 );// activar VBO de colores
         glColorPointer(4, GL_FLOAT, 0, 0);
            
	     //Dubujar las caras pares
	     glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri1 );// activar VBO de triángulos
         glDrawElements( GL_TRIANGLES , 3*f1.size()-int(sobrantes/2), GL_UNSIGNED_INT , 0 ) ;
         glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
         glBindBuffer( GL_ARRAY_BUFFER , 0 );// desactivar VBO de colores
         
	      
         //Color de las caras impares
         glBindBuffer( GL_ARRAY_BUFFER , id_vbo_cC2 );// activar VBO de colores
         glColorPointer(4, GL_FLOAT, 0, 0);
            
	     //Dibujar las caras impares
	     glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri2 );// activar VBO de triángulos
         glDrawElements( GL_TRIANGLES , 3*f2.size()-int(sobrantes/2), GL_UNSIGNED_INT , 0 ) ;
         glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 ); // desactivar VBO de triángulos
         glBindBuffer( GL_ARRAY_BUFFER , 0 );// desactivar VBO de colores
	      
   }

   // desactivar uso de array de vértices
   glDisableClientState( GL_VERTEX_ARRAY );
   glDisableClientState(GL_COLOR_ARRAY);
   glEnable(GL_LIGHTING);
}

void Malla3D::draw_ModoSuavizado(bool dibujado[5])
{
   glShadeModel(GL_SMOOTH);
	
   int sobrantes;
   if(dibujado[4]) sobrantes = 0;
   if(!dibujado[4]) sobrantes = sin_dibujar;
	   
   this->m.Aplicar(); 
   
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glVertexPointer(3, GL_FLOAT, 0, v.data()) ;
   glNormalPointer(GL_FLOAT, 0, nv.data());
   
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
   
      glDrawElements( GL_TRIANGLES , 3*f.size()-sobrantes, GL_UNSIGNED_INT , f.data());
   
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
}
void Malla3D::draw_ModoPlano(bool dibujado[5])
{
    glShadeModel(GL_FLAT);

    int sobrantes;
    if (dibujado[4]) sobrantes = 0;
    if (!dibujado[4]) sobrantes = sin_dibujar;

    this->m.Aplicar();

    
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
       glVertexPointer(3, GL_FLOAT, 0, v.data());
       glNormalPointer(GL_FLOAT, 0, nv.data());

       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       
         glDrawElements(GL_TRIANGLES, 3 * f.size() - sobrantes, GL_UNSIGNED_INT, f.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void Malla3D::draw(int modo, bool dibujado[5])
{
   switch(modo)
   {
      case 0:   
         draw_ModoInmediato(dibujado);
         break;
      case 1:
         draw_ModoDiferido(dibujado);
         break;
      case 2:
         draw_ModoSuavizado(dibujado);
         break;
      case 3:
         draw_ModoPlano(dibujado);
         break;
   }
}


