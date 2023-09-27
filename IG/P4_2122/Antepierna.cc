#include "Antepierna.h"

Antepierna::Antepierna()
{
	codo = new Codo();
	parte_inferior = new ParteSI();
	pie = new Pie();
}
void Antepierna::draw(int modo, bool dibujado[5])
{
	//Pintar el codo
	glPushMatrix();
		codo->draw(modo, dibujado);
	glPopMatrix();
	//Trasladar la parte inferior y pintar
	glPushMatrix();
		glTranslatef(0, -(0.5+3), 0);
		parte_inferior->draw(modo, dibujado);
	glPopMatrix();
	//Trasladar el pie y pintar
	glPushMatrix();
		glTranslatef(0, -(0.5 + 3 + 0.5), 0);
		pie->draw(modo, dibujado);
	glPopMatrix();
}
void Antepierna::setMaterial(Material m)
{
   codo->setMaterial(m);
   parte_inferior->setMaterial(m);
   pie->setMaterial(m);
}
