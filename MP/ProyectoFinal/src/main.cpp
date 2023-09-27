// PROYECTO FINAL DE JORGE GANGOSO KLÖCK
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Simulador.h"

void pintaNube(const ConjuntoParticulas & miConjunto) {
    int N = miConjunto.getutiles();
    Particula p;
    for (int i = 0; i < N; i++) {
        p = miConjunto.ObtieneParticula(i);
        color(p.getcolor());
        circulo_lleno(p.getx(), p.gety(), RADIO);
    }

}
 
int main() {
    srand(time(0));

    int ancho = 800;
    int alto = 600;
    int opcion;

    cout << "\n  Opcion a probar: ";
    cin >> opcion;

    switch (opcion) {

        case 1:
        {
            cout << "\n** Prueba sobrecarga de operadores **" << endl;
            //vredimensiona(100, 100);
            ConjuntoParticulas a1, b1(4);
            cout << b1 << endl;

            Particula x;
            a1.AgregaParticula(x);
            x.mueve_particula(ancho, alto);
            a1.AgregaParticula(x);
            cout << a1 << endl;

            b1.Mover(ancho, alto);
            
            a1 = a1 + b1;
            cout << a1 << endl;

            ConjuntoParticulas cc = a1 + b1;
            ConjuntoParticulas xx(cc);
            cout << xx << endl;
            cout << endl;
            vcierra();

            break;
        }

        case 2:
        {
            cout << "\n** Prueba Conjunto Particulas ** " << endl;
            int NRO = 20;
            vredimensiona(ancho, alto);
            ConjuntoParticulas rojas(NRO);
            ConjuntoParticulas verdes(NRO);
            ConjuntoParticulas blancas;
            Particula p;


            for (int i = 0; i < NRO; i++) {
                p = rojas.ObtieneParticula(i);
                p.setcolor(ROJO);
                rojas.ReemplazaParticula(i, p);

                p = verdes.ObtieneParticula(i);
                p.setcolor(VERDE);
                verdes.ReemplazaParticula(i, p);
            }

            ConjuntoParticulas aux;
            for (int i = 0; i < 200; i++) {
                rojas.Mover(ancho, alto);
                verdes.Mover(ancho, alto);
                blancas.Mover(ancho, alto);
                aux = rojas + verdes + blancas;

                borra();
                pintaNube(aux);

                if (i % 10 == 0) {
                    Particula p;
                    p.setcolor(BLANCO);
                    blancas.AgregaParticula(p);
                    rojas.BorraParticula(rand() % rojas.getutiles());
                    verdes.BorraParticula(rand() % verdes.getutiles());

                }

                refresca();
                espera(35);
            }
            vcierra();

            break;
        }
        case 3:
        {
            cout << "\n**************  Probando Simulador ****************\n";
            ConjuntoParticulas base(30);
            ConjuntoParticulas otro(10);
            ConjuntoParticulas aux;
            int contador = 0;

            Simulador game(base, otro, ancho, alto);

            while (contador < 500) {
                game.Step();
                game.Pintar(30);
                contador++;
            }
            break;
        }
        case 4:
        {
            int ancho = 600 , alto = 400;
            srand (time (0)) ;
                ConjuntoParticulas parts (15) ;
                ConjuntoParticulas obstaculos (5) ;
                ConjuntoParticulas aux ;

                // PONER VELOCIDADES OBSTACULOS A 0
                for(int i=0; i<5; i++)
                {
                    obstaculos.ObtieneParticulaReal(i)->setdx(0);
                    obstaculos.ObtieneParticulaReal(i)->setdy(0);
                }

                    Simulador mySim (parts ,obstaculos ,ancho ,alto ) ;
                    int t= tecla();
                        while (t != ESCAPE) 
                        {
                        mySim.Step () ;
                        mySim.Pintar (25) ;
                            if(mySim.getFijas().getutiles()<20)
                            {
                                aux = mySim.getFijas() ;
                                Particula p;
                                aux.AgregaParticula(p);
                                mySim.setFijas(aux);
                            }
                            if(t == ESPACIO)
                            {
                            mySim.setMoviles(parts);
                            mySim.setFijas(obstaculos);
                            }
                        t=tecla();
                         }
        }
    }
    return 0;
}


