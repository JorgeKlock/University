#include "Torso.h"

Torso::Torso()
{
	cubo = new Cubo();
}
void Torso::draw(int modo, bool dibujado[5])
{
	//Deformar el cubo y pintar
	glPushMatrix();
	   glTranslatef(0, -1, 0);
		glScalef(3, 6, 1);
		glTranslatef(0, 0.5, 0);
		cubo->draw(modo, dibujado);
	glPopMatrix();
}
