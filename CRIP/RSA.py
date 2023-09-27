from random import randint
from math import sqrt, floor
import time



def potenciamodular(a,b,m):
    p = 1
    while b > 0:
        if (b%2 == 1):
            p = (p*a)%m
        b = b>>1
        a = (a*a)%m
    return p

def mcd_ex(a,b):
    (u0,u1)=(1,0)
    (v0,v1)=(0,1)
    while b > 0:
        (c,r) = (a//b, a%b)
        (u0,u1) = (u1,u0-c*u1)
        (v0,v1) = (v1,v0-c*v1)
        (a,b) = (b, a%b)
    return [a,u0,v0]

def inverso(a,p):
    x = mcd_ex(a,p)
    if x[0] == 1:
        return(x[1]%p)
    print('No existe el inverso')
    return 0


def textotonumero(tex):
    sol = 0
    pos = 1
    for s in tex:
        x = ord(s)
        if (x>64 and x < 91): 
            sol = sol + pos*(x-64)
            pos*=28
        elif x == 209:
            sol = sol + pos*27
            pos*=28
        elif x == 32:
            pos*=28
    return sol

def numerototexto(num):
    texto = ''
    while num > 0:
       aux = num%28
       if aux==0:
           texto = texto + ' '
       elif aux == 27:
           texto = texto + 'Ñ'
       else:
           texto = texto + chr(aux+64)
       num = num//28
    return texto


def menu():
    print('1. Cifrar un mensaje ')
    print('2. Descifrar un mensaje ')
    print('3. Salir ')
    op = input("Introduce una opción: ")
    if op == '1':
        print('Vamos a introducir los parámetros (n,e) de la clave pública')
        n = int(input("Módulo. n = "))
        e = int(input("Exponente de cifrado. e = "))
        mensaje = input("Introduce el mensaje (sólo admite letras mayúsculas y espacios): ")
        mensaje_numero = textotonumero(mensaje)
        cif = potenciamodular(mensaje_numero,e,n)
        men_cif = numerototexto(cif)
        print('El mensaje cifrado es:')
        print(men_cif)
        menu()
    elif op == '2':
        print('Vamos a introducir los parámetros (n,d) de la clave privada')
        n = int(input("Módulo. n = "))
        d = int(input("Exponente de descifrado. d = "))
        mensaje_cif = input("Introduce el mensaje cifrado (sólo admite letras mayúsculas y espacios): ")
        mensaje_cif_numero = textotonumero(mensaje_cif)
        descif = potenciamodular(mensaje_cif_numero,d,n)
        mensaje_descifrado = numerototexto(descif)
        print('El mensaje descifrado es:')
        print(mensaje_descifrado)
        menu()
    elif op == '3':
        print('FIN')
    else:
        print('La opción que has introducido no es válida.')
        print(' ')
        menu()
        

menu()
