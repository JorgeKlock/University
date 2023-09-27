#include "Mano.h"

Mano::Mano()
{
	palma = new Palma();
	d1 = new Dedo();
	d2 = new Dedo();
	d3 = new Dedo();
	d4 = new Dedo();
	d5 = new Dedo();
}
void Mano::draw(int modo, bool dibujado[5])
{
	//Pintar Palma
	glPushMatrix();
		palma->draw(modo, dibujado);
	glPopMatrix();
	//Trasladar dedos y pintar
	glPushMatrix();
		glTranslatef(-0.5, -(0.5+0.6), 0);
		d1->draw(modo, dibujado);
		glTranslatef(0.25, 0, 0);
		d2->draw(modo, dibujado);
		glTranslatef(0.25, 0, 0);
		d3->draw(modo, dibujado);
		glTranslatef(0.25, 0, 0);
		d4->draw(modo, dibujado);
	glPopMatrix();
	glPushMatrix();
		glTranslatef((0.5+0.05), -0.5, 0);
		d5->draw(modo, dibujado);
	glPopMatrix();
}
void Mano::setMaterial(Material m)
{
   palma->setMaterial(m);
   d1->setMaterial(m);
   d2->setMaterial(m);
   d3->setMaterial(m);
   d4->setMaterial(m);
   d5->setMaterial(m);
}
