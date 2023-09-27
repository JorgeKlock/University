# Ejercicio 1
	#Calcula el MCD de a y b mediante el algoritmo extendido de Euclides
def MCD(a,b):
	(u0,u1) = (1,0)
	(v0,v1) = (0,1)
	while(b > 0):
		(c, r) = (a//b, a%b)
		(u0, u1) = (u1, u0-c*u1)
		(v0, v1) = (v1, v0-c*v1)
		a = b
		b = r
	return [a, u0, v0]
	
# Ejercicio 2
	#Calcula el inverso de a modulo b
def InversoModular(a, b):
	[a, bz1, bz2] = MCD(a,b)
	return bz1%b
# Ejercicio 3
	#Calcula la potencia de a elevado a b en mod n
def PotenciaModular(a, b, n):
	p = 1
	while(b > 0):
		b = b>>1 #Es lo mismo que (b-b%2)/2
		a = (a*a)%n
		if(b%2 == 1):
			p = (p*a)%n
	return p
#Ejercicio 4

	

## Main ##
	#Ejercicio 1
print('Introduce a y b para hacer el MCD:')
a = int(input('a: '))
b = int(input('b: '))
[mcd, bz1, bz2] = MCD(a,b)
print('El MCD es ', mcd, 'Los coeficientes de bezout son: ', bz1, ' y ', bz2)
	#Ejercicio 2
print('Introduce a y modulo para hacer el inverso:')
a = int(input('a: '))
b = int(input('modulo: '))
inverso = InversoModular(a,b)
print('El inverso de ', a, ' es ', inverso, ' modulo ', b)
	#Ejercicio 3
print('Introduce a, b y modulo para hacer la potencia modular:')
a = int(input('a: '))
b = int(input('b: '))
modulo = int(input('modulo: '))
print('La potencia ', a, ' ^ ', b, ' modulo ', modulo, ' es: ', PotenciaModular(a, b, modulo))

