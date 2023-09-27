#include "Torso.h"

Torso::Torso()
{
	cubo = new Cubo();
}
void Torso::draw(int modo, bool dibujado[5])
{
	//Deformar el cubo y pintar
	glPushMatrix();
		glScalef(2, 2, 1);
		cubo.draw(modo, dibujado);
	glPopMatrix();
}