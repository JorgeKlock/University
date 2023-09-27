#include "luz.h"
void Luz::activar()
{
    //Encender la luz
    switch (this->id)
    {
    case 0:
        glEnable(GL_LIGHT0);
        break;
    case 1:
        glEnable(GL_LIGHT1);
        break;
    case 2:
        glEnable(GL_LIGHT2);
        break;
    case 3:
        glEnable(GL_LIGHT3);
        break;
    case 4:
        glEnable(GL_LIGHT4);
        break;
    case 5:
        glEnable(GL_LIGHT5);
        break;
    case 6:
        glEnable(GL_LIGHT6);
        break;
    case 7:
        glEnable(GL_LIGHT7);
        break;
    }
   //Definir Colores
   glLightfv(id,GL_DIFFUSE,this->colorDifuso);
   glLightfv(id,GL_SPECULAR,this->colorEspecular);
   glLightfv(id,GL_AMBIENT,this->colorAmbiente);
   //Definir Posicion
   glLightfv(id,GL_POSITION,posicion);

   
}
