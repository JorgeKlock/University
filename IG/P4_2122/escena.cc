#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" 
#include "luz.h"


void MensajeMenuPrincipal()
{
    std::cout << "Menu Principal: O-Objetos/ V-Visualización / D-Dibujado / I-Iluminación / M-Movimiento Q-Salir";
    std::cout << std::endl;
}


//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************




const float pi = atan(4);
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
    persona = new Persona();
    
    Tupla4f blanco = {1,1,1,1};
    Tupla4f negro = {0,0,0,1};
    
    Tupla4f ambiente = {0,0,0,1.0};
    Tupla4f difuso = {0.3,1,0.3,1.0};
    Tupla4f especular = {1,0.7,0.7,1.0};

    Tupla4f rojo = {1,0,0,1};
    Tupla4f verde = {0,1,0,1};
    Tupla4f azul = {0,0,1,1};
    
    Tupla3f posicion_inicial = {0,0,50};
    luz1 = new luzPosicional(posicion_inicial, 0, ambiente, especular, difuso);

    Tupla2f direccion = {0,10};
    luz2 = new luzDireccional(direccion, 1, ambiente, blanco, blanco);
      
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
    
    persona->setMaterial(m_azul);
    
    system("clear");
    MensajeMenuPrincipal();
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
void Escena::animarModeloJerarquico()
{
if(animacion){


    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
    change_observer();
    glDisable(GL_LIGHTING);
     ejes.draw();
    glEnable(GL_LIGHTING);

   if(luz_activa[0] == 1) luz1->activar();
       else luz1->apagar();
       if(luz_activa[1] == 1) luz2->activar();
       else luz2->apagar();


    

    glPushMatrix();
      persona->TrasladarPersonaX(cambio[0]);
      persona->TrasladarPersonaY(cambio[1]);
      persona->TrasladarPersonaZ(-cambio[2]);
      
      persona->girarHombroDerechoZ(-cambio[3]);
      persona->girarCodoDerechoZ(-cambio[4]);
      persona->girarHombroDerechoX(-cambio[5]);
      
      persona->girarHombroIzquierdoZ(cambio[6]);
      persona->girarCodoIzquierdoZ(cambio[7]);
      persona->girarHombroIzquierdoX(-cambio[8]);
      
      glScalef(10,10,10);
      persona->draw(modo_activo, d_activo);
    glPopMatrix();
    
      for (int i=3; i<10; i++)
      {
         cambio[i] += velocidad[i];
         
         if(cambio[i] > limite[i]) 
         {
         cambio[i] = 0;
         }
         //else if(cambio[i] < 0) cambio[i] = limite[i];
      }
      for(int i=0; i<3; i++)
      {
      cambio[i] += velocidad[i];
         if(cambio[i] > limite[i])
         {
            cambio[0] = 0;
            cambio[1] = 0;
            cambio[2] = 0;
         }
      }
         //std::cout << cambio[0] << std::endl;
      
      }
}
void Escena::dibujar()
{
   if(!animacion){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
    change_observer();
    glDisable(GL_LIGHTING);
     ejes.draw();
    glEnable(GL_LIGHTING);

   if(luz_activa[0] == 1) luz1->activar();
       else luz1->apagar();
       if(luz_activa[1] == 1) luz2->activar();
       else luz2->apagar();
    
       switch (m_activo)
       {
         case 0:
         persona->girarHombroDerechoZ(incremento[m_activo]);
         break;
         case 1:
         persona->girarHombroIzquierdoZ(incremento[m_activo]);
         break;
         case 2:
         persona->girarCodoDerechoZ(incremento[m_activo]);
         break;
         case 3:
         persona->girarCodoIzquierdoZ(incremento[m_activo]);
         break;
         case 4:
         persona->TrasladarPersonaX(incremento[m_activo]);
         break;
       }
      
       glPushMatrix();
          glTranslatef(0,-50,0);
          glScalef(10,10,10);
          persona->draw(modo_activo, d_activo);
       glPopMatrix();
       
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
            glScalef(10,30,10);
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
   bool salir = false;
   
   
   if(modoMenu == NADA)
   {
      switch (toupper(tecla))
      {
         case 'O' :
            modoMenu = SELOBJETO; 
            cout << "Se encuentra en selección de objeto" << endl;
            cout << "CUBO (C), TETRAEDRO (T), PLY (P),";
            cout << " OBJETO REVOLUCION (R), CILINDRO(I), CONO(O), ESFERA(E), Salir(Q)" << endl;
            break ;
         case 'V' :
            modoMenu = SELVISUALIZACION;
            cout << "Se encuentra en selección de visualización." << endl;
            cout << "1- Modo Inmediato / 2- Modo Diferido / 3- Iluminación suave / 4- Iluminación Plana";
            cout << " / Q- Salir" << endl;
            break ;
         case 'D' :
            modoMenu = SELDIBUJADO;
            cout << "Se encuentra en seleccion de dibujado" << endl;
            cout << "P-puntos / L-lineas / S-solido / A-ajedrez / T(con/sin tapas) / Q-Salir" << endl;
            break ;
         case 'I' :
            modoMenu = SELILUMINACION;
            cout << "Se encuentra en seleccion de iluminación" << endl;
            cout << "0-Activar luz0 / 1-Activar luz1 / A-Modificar Alpha / B-Modificar Beta";
            cout << " / + aumentar ángulo / - reducir ángulo / Q-Salir" << endl;
            break ;
         case 'M' :
            modoMenu = SELMOVIMIENTO;
            cout << "Se encuentra en seleccion de movimiento" << endl;
            cout << "0-Hombro derecho / 1-Hombro Izquierdo / 2-Codo Derecho / 3-Codo Izquierdo / 4-Cuerpo";
            cout << " / + aumentar valor / - reducir valor / Q-Salir" << endl;
            break;
         case 'A' :
            modoMenu = SELANIMACION;
            animacion = true;
            cout << "Se está reproduciendo la animación" << endl;
            cout << "Pulse + para aumentar la velocidad o - para reducirla" << endl;
            break;
         case 'Q' :
            salir = true;
            break;
      }
   }
   
   else if(modoMenu == SELOBJETO)
   {
      switch (toupper(tecla))
      {
         case 'C' :
            f_activo[CUBO] = !f_activo[CUBO];
            cout << "Ha seleccionado el cubo. Continúa en el menu Selección de Objetos" << endl;
            break;
         case 'T' :
            f_activo[TETRAEDRO] = !f_activo[TETRAEDRO];
            cout << "Ha seleccionado el tetraedro. Continúa en el menu Selección de Objetos" << endl;
            break;
         case 'P' :
            f_activo[PLY] = !f_activo[PLY];
            cout << "Ha seleccionado el objetoPLY. Continúa en el menu Selección de Objetos" << endl;
            break;
         case 'R' :
            f_activo[REVOLUCION] = !f_activo[REVOLUCION];
            cout << "Ha seleccionado el objRevolución. Continúa en el menu Selección de Objetos" << endl;
            break;
         case 'I' :
            f_activo[CILINDRO] = !f_activo[CILINDRO];
            cout << "Ha seleccionado el Cilindro. Continúa en el menu Selección de Objetos" << endl;
            break;
         case 'O' :
            f_activo[CONO] = !f_activo[CONO];
            cout << "Ha seleccionado el Cono. Continúa en el menu Selección de Objetos" << endl;
            break;
         case 'E' :
            f_activo[ESFERA] = !f_activo[ESFERA];
            cout << "Ha seleccionado la Esfera. Continúa en el menu Selección de Objetos" << endl;
            break;
         case 'Q' :
            modoMenu = NADA;  
            system("clear");
            cout << "Volviendo al Menú Principal" << endl;  
            MensajeMenuPrincipal();
            break;
         default:
            cout << "Opción no disponible" << endl;     
         }    
   }
   
   else if(modoMenu == SELVISUALIZACION)
   {
      switch (toupper(tecla))
      {
         case '1' :
            modo_activo = INMEDIATO;
            cout << "Ha seleccionado el modo inmediato. Continúa en el menu Selección Visual" << endl;
            break;
         case '2' :
            modo_activo = DIFERIDO;
            cout << "Ha seleccionado el modo diferido. Continúa en el menu Selección Visual" << endl;
            break;
         case '3' :
            modo_activo = SUAVIZADO;
            cout << "Ha seleccionado el modo suavizado. Continúa en el menu Selección Visual" << endl;
            break;
         case '4' :
            modo_activo = PLANO;
            cout << "Ha seleccionado el modo plano, saliendo del menu" << endl;
            break;
         case 'Q' :
            modoMenu=NADA;  
            system("clear");
            cout << "Volviendo al Menú Principal" << endl;   
            MensajeMenuPrincipal(); 
            break;
         default:
            cout << "Opción no disponible" << endl;           
      }
   } 
   
   else if (modoMenu == SELDIBUJADO)
   {
      switch (toupper(tecla))
      {
         case 'P':
            d_activo[PUNTOS]=!d_activo[PUNTOS];
            modo_activo = DIFERIDO;
            cout << "Ha activado/desactivado Puntos. Continúa en el menu Dibujado" << endl;
            break;
         case 'L':
            d_activo[LINEAS]=!d_activo[LINEAS];
            modo_activo = DIFERIDO;
            cout << "Ha activado/desactivado Lineas. Continúa en el menu Dibujado" << endl;
            break;
         case 'S':
            d_activo[TRIANGULOS]=!d_activo[TRIANGULOS];
            modo_activo = DIFERIDO;
            cout << "Ha activado/desactivado Sólido. Continúa en el menu Dibujado" << endl;
            break;
         case 'A':
            d_activo[AJEDREZ]=!d_activo[AJEDREZ];
            modo_activo = DIFERIDO;
            cout << "Ha activado/desactivado Ajedrez. Continúa en el menu Dibujado" << endl;
            break;
         case 'T':
            d_activo[TAPAS]=!d_activo[TAPAS];
            cout << "Ha activado/desactivado Tapas. Continúa en el menu Dibujado" << endl;
            break;
         case 'Q' :
            modoMenu=NADA;  
            system("clear");
            cout << "Volviendo al Menú Principal" << endl;      
            MensajeMenuPrincipal();
            break;  
         default:
            cout << "Opción no disponible" << endl;                   
      }
   }
   else if (modoMenu == SELILUMINACION)
   {
      switch (toupper(tecla))
      {
         case '0':
            luz_activa[0]=!luz_activa[0];
            cout << "Ha activado/desactivado Luz0. Continúa en el menu Iluminacion" << endl;
            break;
         case '1':
            luz_activa[1]=!luz_activa[1];
            cout << "Ha activado/desactivado Luz1. Continúa en el menu Iluminacion" << endl;
            break;
         case 'A':
            angulo_alpha=true;
            cout << "El ángulo a modificar es Alpha. Continúa en el menu Iluminacion" << endl;
            break;
          case 'B':
            angulo_alpha=false;
            cout << "El ángulo a modificar es Beta. Continúa en el menu Iluminacion" << endl;
            break;
         case '+':
            if(angulo_alpha) luz2->variarAnguloAlpha(pi/4);
            if(!angulo_alpha) luz2->variarAnguloBeta(pi/4);
            break;
         case '-' :
            if(angulo_alpha) luz2->variarAnguloAlpha(-pi/4);
            if(!angulo_alpha) luz2->variarAnguloBeta(-pi/4);
            break;  
         case 'Q' :
            modoMenu=NADA;  
            system("clear");
            cout << "Volviendo al Menú Principal" << endl;      
            MensajeMenuPrincipal();
            break;  
         default:
            cout << "Opción no disponible" << endl;                   
      }
   }
   else if (modoMenu == SELMOVIMIENTO)
   {
      switch (toupper(tecla))
      {
         case '0':
            m_activo = 0;
            break;
         case '1':
            m_activo = 1;
            break;
         case '2':
            m_activo = 2;
            break;
         case '3':
            m_activo = 3;
            break;
         case '4':
            m_activo = 4;
            break;
         case '+':
            incremento[m_activo] += 1;
            break;
         case '-' :
            incremento[m_activo] -= 1;
            break;  
         case 'Q' :
            modoMenu=NADA;  
            system("clear");
            cout << "Volviendo al Menú Principal" << endl;      
            MensajeMenuPrincipal();
            break;  
         default:
            cout << "Opción no disponible" << endl;                   
      }
   }
   else if (modoMenu == SELANIMACION)
   {
      switch (toupper(tecla))
      {
         case '1':
            velocidad[0] += 0.01;
            break;
         case '2':
            velocidad[1] += 0.01;
            break;
         case '3':
            velocidad[3] += 0.01;
            velocidad[4] += 0.01;
            velocidad[5] += 0.01;
            break;
         case '+':
            for(int i=0; i<=10; i++)
            {
            velocidad[i] += 0.01;
            }
            break;
         case '-' :
            for(int i=0; i<=10; i++)
            {
            velocidad[i] -= 0.01;
            }
            break;  
         case 'Q' :
            modoMenu=NADA;  
            animacion = false;
            system("clear");
            cout << "Volviendo al Menú Principal" << endl;      
            MensajeMenuPrincipal();
            break;  
         default:
            cout << "Opción no disponible" << endl;                   
      }
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
