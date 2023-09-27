#include <iostream>
using namespace std;


struct tiempo
{
	int horas=0;
	int minutos=0;
	int segundos=0;
};
void ordenar(tiempo &at)
{
	while (at.segundos >= 60)
	{
		at.minutos++;
		at.segundos -= 60;
	}
	while (at.minutos >= 60)
	{
		at.horas++;
		at.minutos -= 60;
	}
}
int convertirASegundos(tiempo at)
{
	return (at.horas * 3600 + at.minutos * 60 + at.segundos);
}
bool esPosterior(tiempo primero, tiempo segundo)
{
	bool ordenados = false;
	if (convertirASegundos(segundo) > convertirASegundos(primero))
		ordenados = true;
	return ordenados;
}
tiempo obtenerNuevoTiempo(tiempo at, int S)
{
	int nuevotiempo = convertirASegundos(at) + S;
	tiempo retornado;
	retornado.segundos = nuevotiempo;
	ordenar(retornado);
	return retornado;
}
int main()
{
	tiempo t1;
	t1.horas = 5, t1.minutos = 80, t1.segundos = 151;
	tiempo t2;
	t2 = obtenerNuevoTiempo(t1, 150);
	ordenar(t1);
	ordenar(t2);
	cout << "t1: " << t1.horas << " horas" << t1.minutos << " minutos" << t1.segundos << " segundos" << endl;
	cout << "t2: " << t2.horas << " horas" << t2.minutos << " minutos" << t2.segundos << " segundos" << endl;
	cout << "t2: " << convertirASegundos(t2) << " segundos" << endl;
	cout << "Es t2 posterior a t1?";
	if (esPosterior(t1, t2)==1)
		cout << " Si" << endl;
	else
		cout << " No" << endl;
	return 0;
}
