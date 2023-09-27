#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" 
#include "luz.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena....
    
    cubo = new Cubo(1);
    tetraedro = new Tetraedro(1);
    objply = new ObjPLY("beethoven.ply");
    revolucion = new ObjRevolucion("peon.ply", 50, 1, 1, 0); //EJE CAMBIADO
    revolucion2 = new ObjRevolucion("peon.ply", 50, 1, 1, 1);
    cilindro = new Cilindro(20, 20, 1, 1);
    cono = new Cono(20, 30, 1, 1);
    esfera = new Esfera(20, 20, 1);
    
    Tupla4f blanco = {1,1,1,1};
    Tupla4f negro = {0,0,0,1};
    
    Tupla4f ambiente = {0,0,0,1.0};
    Tupla4f difuso = {0.3,1,0.3,1.0};
    Tupla4f especular = {1,0.7,0.7,1.0};

    Tupla4f rojo = {1,0,0,1};
    Tupla4f verde = {0,1,0,1};
    Tupla4f azul = {0,0,1,1};
    
    Tupla3f posicion = {0,0,0};
    luz1 = new luzPosicional(posicion, 1, ambiente, difuso, difuso);

    Tupla2f direccion = {5,-5};
    luz2 = new luzDireccional(direccion, 0, ambiente, blanco, blanco);
      
    //Ambiente - Especular - Difuso
    Material m_rojo(rojo, blanco, rojo, 64);
    Material m_verde(verde, blanco, verde, 64);
    Material m_azul(azul, blanco, azul, 64);
    Material m_blanco(ambiente, blanco, blanco, 64);
    Material m_negro(ambiente, negro, negro, 64);


    cubo->setMaterial(m_rojo);
    objply->setMaterial(m_verde);
    tetraedro->setMaterial(m_azul);
    revolucion->setMaterial(m_blanco);
    revolucion2->setMaterial(m_negro);
    cilindro->setMaterial(m_verde);
    cono->setMaterial(m_rojo);
    esfera->setMaterial(m_verde);
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
	glEnable( GL_CULL_FACE); //Habilitar cull-face (Rubrica)
	glEnable( GL_NORMALIZE); //Para normalizar las normales tras hacer transformaciones
	
	glPointSize(2);

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

    change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
    change_observer();
    glDisable(GL_LIGHTING);
     ejes.draw();
    glEnable(GL_LIGHTING);

    luz1->activar();
    std::cout << "Componente Difusa de la Luz 1: " << luz1->getD() << std::endl;
    luz2->activar();
   
    if(f_activo[CUBO])
    {
      glPushMatrix();
         glTranslatef(-100, 0, 0);
         glScalef(10,10,10);
         cubo->draw(modo_activo, d_activo);         
      glPopMatrix();
    }
    if(f_activo[TETRAEDRO])
    {
      glPushMatrix();
         glTranslatef(-50, 0, 0);
         glScalef(10,10,10);
         tetraedro->draw(modo_activo, d_activo);
      glPopMatrix();
    }
    if(f_activo[PLY])
    {
      glPushMatrix();
         glScalef(10,10,10);
         objply->draw(modo_activo, d_activo);
      glPopMatrix();
    }
    if(f_activo[REVOLUCION])
    {
      glPushMatrix();
         glTranslatef(100, 0, 0);
         glScalef(10,10,10);
         revolucion->draw(modo_activo, d_activo);
      glPopMatrix();
      glPushMatrix();
         glTranslatef(150, 0, 0);
         glScalef(10,10,10);
         revolucion2->draw(modo_activo, d_activo);
      glPopMatrix();
    }
    if(f_activo[CILINDRO])
    {
      glPushMatrix();
         glTranslatef(50, 0, 0);
         glScalef(10,10,10);
         cilindro->draw(modo_activo, d_activo);
      glPopMatrix();
    }
    if(f_activo[CONO])
    {
      glPushMatrix();
         glTranslatef(0, 100, 0);
         glScalef(10,10,10);
         cono->draw(modo_activo, d_activo);
      glPopMatrix();
    }
    if(f_activo[ESFERA])
    {
      glPushMatrix();
         glTranslatef(0, -100, 0);
         glScalef(10,10,10);
         esfera->draw(modo_activo, d_activo);
      glPopMatrix();
    }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir = false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
         {
            modoMenu=NADA;  
            cout << "Saliendo del menu" << endl;      
         }    
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         cout << "Se encuentra en selección de objeto. Escoja CUBO (C), TETRAEDRO (T), OBJETO PLY (Y) u OBJETO REVOLUCION (R), CILINDRO(I), CONO(U), ESFERA(E)" << endl;
         modoMenu=SELOBJETO; 
         break ;
        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         cout << "Se encuentra en selección de visualización. Pulse '1' para cambiar a modo Inmediato" <<
         " o '2' para cambiar a modo Diferido" << endl;
         modoMenu=SELVISUALIZACION;
         break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         cout << "Se encuentra en seleccion de dibujado. Escoja P(puntos), L(lineas), S(solido) o A(ajedrez) o W(con/sin tapas)" << endl;
         modoMenu=SELDIBUJADO;
         break ;
         // COMPLETAR con los diferentes opciones de teclado
       case 'C' :
         if(modoMenu==SELOBJETO)
         {
            f_activo[CUBO] = !f_activo[CUBO];
            modoMenu = NADA;
            cout << "Ha seleccionado el cubo, saliendo del menu" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
         break;
       case 'T' :
         if(modoMenu==SELOBJETO)
         {
            f_activo[TETRAEDRO] = !f_activo[TETRAEDRO];
            modoMenu = NADA;
            cout << "Ha seleccionado el tetraedro, saliendo del menu" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
       case 'Y' :
         if(modoMenu==SELOBJETO)
         {
            f_activo[PLY] = !f_activo[PLY];
            modoMenu = NADA;
            cout << "Ha seleccionado el objetoPLY, saliendo del menu" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
      case 'I' :
         if(modoMenu==SELOBJETO)
         {
            f_activo[CILINDRO] = !f_activo[CILINDRO];
            modoMenu = NADA;
            cout << "Ha seleccionado el Cilindro, saliendo del menu" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
      case 'U' :
         if(modoMenu==SELOBJETO)
         {
            f_activo[CONO] = !f_activo[CONO];
            modoMenu = NADA;
            cout << "Ha seleccionado el Cono, saliendo del menu" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
      case 'E' :
         if(modoMenu==SELOBJETO)
         {
            f_activo[ESFERA] = !f_activo[ESFERA];
            modoMenu = NADA;
            cout << "Ha seleccionado la Esfera, saliendo del menu" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
         case 'R' :
      if(modoMenu==SELOBJETO)
      {
         f_activo[REVOLUCION] = !f_activo[REVOLUCION];
         modoMenu = NADA;
         cout << "Ha seleccionado el objeto revolucion, saliendo del menu" << endl;
      }
      else
         cout << "Opcion incorrecta" << endl;
         break;
       case '1' :
         if(modoMenu==SELVISUALIZACION)
         {
            modo_activo = INMEDIATO;
            modoMenu = NADA;
            cout << "Ha seleccionado el modo inmediato, saliendo del menu" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
       case '2' :
         if(modoMenu==SELVISUALIZACION)
         {
            modo_activo = DIFERIDO;
            modoMenu = NADA;
            cout << "Ha seleccionado el modo diferido, saliendo del menu" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
       case '3' :
         if(modoMenu==SELVISUALIZACION)
         {
            modo_activo = SUAVIZADO;
            modoMenu = NADA;
            cout << "Ha seleccionado el modo suavizado, saliendo del menu" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
       case '4' :
         if(modoMenu==SELVISUALIZACION)
         {
            modo_activo = PLANO;
            modoMenu = NADA;
            cout << "Ha seleccionado el modo plano, saliendo del menu" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
       case 'P':
         if(modoMenu==SELDIBUJADO)
         {
            d_activo[PUNTOS]=!d_activo[PUNTOS];
            cout << "Ha seleccionado activar/desactivar puntos, continúa en el menu de dibujado (P-puntos,L-lineas,S-solido,A-ajedrez)" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
       case 'L':
         if(modoMenu==SELDIBUJADO)
         {
            d_activo[LINEAS]=!d_activo[LINEAS];
            cout << "Ha seleccionado activar/desactivar lineas, continúa en el menu de dibujado (P-puntos,L-lineas,S-solido,A-ajedrez)" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
       case 'S':
         if(modoMenu==SELDIBUJADO)
         {
            d_activo[TRIANGULOS]=!d_activo[TRIANGULOS];
            cout << "Ha seleccionado activar/desactivar triangulos, continua en el menu de dibujado (P-puntos,L-lineas,S-solido,A-ajedrez)" 
            << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
       case 'W':
         if(modoMenu==SELDIBUJADO)
         {
            d_activo[TAPAS]=!d_activo[TAPAS];
            cout << "Ha seleccionado activar/desactivar tapaderas, continua en el menu de dibujado (P-puntos,L-lineas,S-solido,A-ajedrez, W-tapas)" 
            << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
       case 'A':
         if(modoMenu==SELDIBUJADO)
         {
            d_activo[AJEDREZ]=!d_activo[AJEDREZ];
            cout << "Ha seleccionado activar/desactivar ajedrez, continúa en el menu de dibujado (P-puntos,L-lineas,S-solido,A-ajedrez)" << endl;
         }
         else
            cout << "Opcion incorrecta" << endl;
            break;
       default:
         cout << "Tecla no Disponible" << endl;
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
