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
	//Pintar Torso
	glPushMatrix();
		torso.draw(modo, dibujado);
	glPopMatrix();
	//Trasladar Cabeza y Pintar
	glPushMatrix();
		glTranslatef(0, (1 + 0.75), 0);
		cabeza.draw(modo, dibujado);
	glPopMatrix();
	//Trasladar Brazos y Pintar
	glPushMatrix();
		glTranslatef(1, 1, 0);
		brazo_Izq.draw(modo, dibujado);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1, 1, 0);
		brazo_Der.draw(modo, dibujado);
	glPopMatrix();
	//Trasladar Piernas y Pintar
	glPushMatrix();
		glTranslatef(0.75, -1, 0);
		pierna_Izq.draw(modo, dibujado);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.75, -1, 0);
		pierna_Der.draw(modo, dibujado);
	glPopMatrix();
}