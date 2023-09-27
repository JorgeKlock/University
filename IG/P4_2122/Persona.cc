#include "Persona.h"

Persona::Persona()
{
	cabeza = new Cabeza();
	torso = new Torso();
	brazo_Izq = new Brazo();
	brazo_Der = new Brazo();
	pierna_Izq = new Pierna();
	pierna_Der = new Pierna();
}

void Persona::draw(int modo, bool dibujado[5])
{
   glPushMatrix();
   
      glTranslatef(inc_x, inc_y, inc_z);
	      //Pintar Torso
	      glPushMatrix();
		      torso->draw(modo, dibujado);
	      glPopMatrix();
	      
	      //Trasladar Cabeza y Pintar
	      glPushMatrix();
		      glTranslatef(0, 6+0.75, 0);
		      cabeza->draw(modo, dibujado);
	      glPopMatrix();
	      
	      //Trasladar Brazos y Pintar
	      glPushMatrix();
		      glTranslatef((1.5+0.5), 5, 0);
		      glRotatef(this->h_i_z,0,0,1);
		      glRotatef(this->h_i_x,1,0,0);
		      brazo_Izq->draw(modo, dibujado);
	      glPopMatrix();
	      
	      glPushMatrix();
		      glTranslatef(-(1.5+0.5), 5, 0);
		      glRotatef(this->h_d_z,0,0,1);
		      glRotatef(this->h_d_x,1,0,0);
		      brazo_Der->draw(modo, dibujado);
	      glPopMatrix();
	      //Trasladar Piernas y Pintar
	      
	      glPushMatrix();
		      glTranslatef(0.75, -4, 0);
		      pierna_Izq->draw(modo, dibujado);
	      glPopMatrix();
	      
	      
	      glPushMatrix();
		      glTranslatef(-0.75, -4, 0);
		      pierna_Der->draw(modo, dibujado);
	      glPopMatrix();
	glPopMatrix();
}

void Persona::setMaterial (Material m)
{
   cabeza->setMaterial(m);
   torso->setMaterial(m);
   brazo_Der->setMaterial(m);
   brazo_Izq->setMaterial(m);
   pierna_Der->setMaterial(m);
   pierna_Izq->setMaterial(m);
   
}
