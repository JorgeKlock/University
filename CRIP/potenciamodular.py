def potenciamodular(a,b,m):
	p=1
	while b>0:
		if (b%2 == 1):
			p = (p*a)%m
		b = (b//2)
		a = (a**2)%m
	return p
	
base = 3
modulo = 561
exponente = modulo-1
print(potenciamodular(base,exponente,modulo))
