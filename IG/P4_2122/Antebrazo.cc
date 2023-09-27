#include "Antebrazo.h"

Antebrazo::Antebrazo()
{
	codo = new Codo();
	parte_inferior = new ParteSI();
	mano = new Mano();
}
void Antebrazo::draw(int modo, bool dibujado[5])
{
	//Pintar el codo
	glPushMatrix();
		codo->draw(modo, dibujado);
	glPopMatrix();
	//Trasladar la parte inferior y pintar
	glPushMatrix();
		glTranslatef(0, -(3+0.5), 0);
		parte_inferior->draw(modo, dibujado);
	glPopMatrix();
	//Trasladar la mano y pintar
	glPushMatrix();
		glTranslatef(0, -(3+1), 0);
		mano->draw(modo, dibujado);
	glPopMatrix();
}
void Antebrazo::setMaterial(Material m)
{
   codo->setMaterial(m);
   parte_inferior->setMaterial(m);
   mano->setMaterial(m);
}
