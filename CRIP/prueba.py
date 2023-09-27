def comprobacionmatematica (b):
	r1 = (b-b%2)/2
	r2 = b>>1
	return (r1 == r2)

print('introduce un numero cualquiera')
a = int(input('numero: '))
print('es cierto? ', comprobacionmatematica(a))
