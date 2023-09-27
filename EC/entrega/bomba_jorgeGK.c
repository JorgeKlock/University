// gcc -Og bomba_jorgeGK.c -o bomba_jorgeGK -no-pie -fno-guess-branch-probability

#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE 100
#define TLIM 5

char password[]="pbvdxf\n";	// contrasenia original: patata
int  passcode  = 5625;			// pin original: 1125

void boom(void){
    printf(	"\n"
               "***************\n"
               "*** BOOM!!! ***\n"
               "***************\n"
               "\n");
    exit(-1);
}

void defused(void){
    printf(	"\n"
               "Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·\n"
               "Â·Â·Â· bomba desactivada Â·Â·Â·\n"
               "Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·Â·\n"
               "\n");
    exit(0);
}

int main(){
    char pw[SIZE];
    int  pc, n;

    struct timeval tv1,tv2;	// gettimeofday() secs-usecs
    gettimeofday(&tv1,NULL);

    do	printf("\nIntroduce la contraseÃ±a: ");
    while (	fgets(pw, SIZE, stdin) == NULL );


    //Transformacion, sumarle i al iesimo elemento de la cadena (avanzar tanto en el abecedario ascii)
    for(int i=0; i<strlen(pw)-1; i++)
    {
        pw[i] = (char)((int)pw[i]+i);
    }

    if    (	strncmp(pw,password,sizeof(password)) )
        boom();

    gettimeofday(&tv2,NULL);
    if    ( tv2.tv_sec - tv1.tv_sec > TLIM )
        boom();

    do  {	printf("\nIntroduce el pin: ");
        if ((n=scanf("%i",&pc))==0)
            scanf("%*s")    ==1;         }
    while (	n!=1 );

    //Transformacion (Multiplicar el pin por 5)

    pc = pc*5;

    if    (	pc != passcode )
        boom();

    gettimeofday(&tv1,NULL);
    if    ( tv1.tv_sec - tv2.tv_sec > TLIM )
        boom();

    defused();
}