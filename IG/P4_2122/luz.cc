#include "luz.h"
void Luz::activar()
{
   //Encender la luz
   glEnable(GL_LIGHT0+id);
    
   //Definir Colores
   glLightfv(GL_LIGHT0+id,GL_DIFFUSE,this->colorDifuso);
   glLightfv(GL_LIGHT0+id,GL_SPECULAR,this->colorEspecular);
   glLightfv(GL_LIGHT0+id,GL_AMBIENT,this->colorAmbiente);
   //Definir Posicion
   glLightfv(GL_LIGHT0+id,GL_POSITION,posicion);

   
}
void Luz::apagar()
{
   glDisable(GL_LIGHT0+id);
}
