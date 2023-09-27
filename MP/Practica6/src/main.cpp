// PROGRAMA DE PRUEBA PARA LA CLASE CONJUNTOPARTICULA
#include <cmath>
#include "miniwin.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Particula.h"
#include "Constantes.h"
#include "ConjuntoParticulas.h"

using namespace miniwin;
using namespace std;

void pintaNube(const ConjuntoParticulas & miConjunto) {
    int N = miConjunto.getutiles();
    Particula p;
    for (int i = 0; i < N; i++) {
        p = miConjunto.ObtieneParticula(i);
        color(p.getcolor());
        circulo_lleno(p.getx(), p.gety(), RADIO);
    }

}
void pinta_pelota(const Particula& P)
{
   color(P.getcolor());
   circulo_lleno(P.getx(), P.gety(), RADIO);
}

int main() {
    srand(time(0));

    int ancho = 500;
    int alto = 500;
    vredimensiona(ancho, alto);

    int contador = 0;
    int minParticulas = 2;
    int maxParticulas = 50;

    ConjuntoParticulas nube(minParticulas);
    cout << nube;
    bool AGREGA = true;
    int nroParticulas;
    
    while (tecla() != ESCAPE) {
        
        nube.Mover(ancho, alto);
        nube.GestionarColisiones();
        borra();
        
        pintaNube(nube);
        contador++;

        nroParticulas = nube.getutiles();
        color(BLANCO);
        texto(10,10, "particulas: " + to_string(nroParticulas));

        // se agregan particulas cada 10 iteraciones hasta llegar a 50 particulas
        // luego se borran hasta llegar a 10.
        if (contador % 10 == 0){
           if (AGREGA){
             Particula p;
             nube.AgregaParticula(p);
            }
           else
             // borro una particula al azar
              nube.BorraParticula(rand()%nroParticulas);
        }

        if (nroParticulas <= minParticulas)
            AGREGA = true;
        else if (nroParticulas >= maxParticulas)
            AGREGA = false;

        refresca();
        espera(25);
         
           }
     
    vcierra();
    
    return 0;
}
/*
void pintaNube(const ConjuntoParticulas & miConjunto) {
    int N = miConjunto.GetNroParticulas();
    Particula p;
    for (int i = 0; i < N; i++) {
        p = miConjunto.ObtieneParticula(i);
        color(p.getColor());
        circulo_lleno(p.getX(), p.getY(), RADIO);
    }

}
*/
/* "Color" es un tipo enumerado definido en Miniwin.h.
Una variable de tipo Color puede tomar los siguientes valores:
NEGRO, ROJO, VERDE, AZUL, AMARILLO, MAGENTA, CYAN, BLANCO

*/



