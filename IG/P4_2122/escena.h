#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzPosicional.h"
#include "luzDireccional.h"
#include "material.h"
#include "Persona.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELILUMINACION,SELMOVIMIENTO,SELANIMACION} menu;
typedef enum {NINGUNA, CUBO, TETRAEDRO, PLY, REVOLUCION, CILINDRO, CONO, ESFERA} figuras;
typedef enum {INMEDIATO, DIFERIDO, SUAVIZADO, PLANO} modos;
typedef enum {TRIANGULOS, LINEAS, PUNTOS, AJEDREZ, TAPAS} dibujados;
class Escena
{
   private:
 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;
   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;
    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

   void clear_window();

   menu modoMenu=NADA;
   modos modo_activo=INMEDIATO;
   bool d_activo[5]={1,0,0,0,1};
   bool f_activo[8]={1,1,1,1,1,1,1,1};
   int m_activo = 0;
   int incremento[5]={0,0,0,0,0};
   bool luz_activa[2]={0,0};
   bool angulo_alpha = 1;
   
   bool animacion = false;
   float velocidad[10] = {0.05,0.05,0.05,0.25,0.25,0.25,0.25,0.25,0.25,0};
   
   
   float cambio[10] = {0,0,0,0,0,0,0,0,0,0};
   float limite[10] = {30,30,30,120,120,120,90,90,90,0};
   
   
   
   
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; 
   Tetraedro * tetraedro= nullptr ;
   ObjPLY * objply = nullptr;
   ObjRevolucion * revolucion = nullptr;
   ObjRevolucion * revolucion2 = nullptr;
   Cilindro * cilindro = nullptr;
   Cono * cono = nullptr;
   Esfera * esfera = nullptr;
   luzPosicional * luz1 = nullptr;
   luzDireccional * luz2 = nullptr;
   Persona * persona = nullptr; 
   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
	void animarModeloJerarquico();

};
#endif
