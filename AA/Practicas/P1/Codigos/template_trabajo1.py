# -*- coding: utf-8 -*-
"""
TRABAJO 1. 
Nombre Estudiante: Jorge Gangoso Klock 49398653N
"""

import numpy as np
import matplotlib.pyplot as plt

np.random.seed(1)

print('EJERCICIO SOBRE LA BUSQUEDA ITERATIVA DE OPTIMOS\n')
print('Ejercicio 1\n')

#Función E
def E(u,v):
    return np.power(( (np.power(u,3)*np.exp(v-2)) - (2*np.power(v,2)*np.exp(-u)) ),2)

#Función F
def F(x,y):
    return np.power(x+2,2)+(2*np.power(y-2,2))+2*np.sin(2*np.pi*x)*np.sin(2*np.pi*y)

#Derivada parcial de E con respecto a u
def dEu(u,v):
    return 2 * ( (np.power(u,3)*np.exp(v-2)) - (2*np.exp(-u)*np.power(v,2)) ) * ( (3*np.power(u,2)*np.exp(v-2)) + (2*np.exp(-u)*np.power(v,2)) )
    
#Derivada parcial de E con respecto a v
def dEv(u,v):
    return 2 * ( (np.power(u,3)*np.exp(v-2)) - (2*np.exp(-u)*np.power(v,2)) ) * ( (np.power(u,3)*np.exp(v-2)) - (4*v*np.exp(-u)) )

#Derivada parcial de F con respecto a x
def dEx(x,y):
    return 2*(x+2) + 4*np.pi*np.cos(2*np.pi*x)*np.sin(2*np.pi*y)
#Derivada parcial de F con respecto a y
def dEy(x,y):
    return 4*(y-2) + 4*np.pi*np.sin(2*np.pi*x)*np.cos(2*np.pi*y)

#Gradiente de E
def gradE(u,v):
    return np.array([dEu(u,v), dEv(u,v)])

#Gradiente de F
def gradF(x,y):
    return np.array([dEx(x,y), dEy(x,y)])

#Gradiente descendente
def gradient_descent(tasa, it_parada, err_parada, inicio, gradiente_usado, funcion_usada, parada):
    W = np.array(inicio)
    w = inicio
    for k in range(it_parada+1):
        if(parada):
            if(funcion_usada(w[0],w[1]) < err_parada):
                break
        w = w -tasa*gradiente_usado(w[0], w[1])
        W = np.append(W, w)
    return w, k, W  


eta = 0.01 
maxIter = 10000000000
error2get = 1e-14
initial_point = np.array([1.0,1.0])
w, it, W = gradient_descent(eta, maxIter, error2get, initial_point, gradE, E, 1)


print ('Numero de iteraciones: ', it)
print ('Coordenadas obtenidas: (', w[0], ', ', w[1],')')


# DISPLAY FIGURE
from mpl_toolkits.mplot3d import Axes3D
x = np.linspace(-30, 30, 50)
y = np.linspace(-30, 30, 50)
X, Y = np.meshgrid(x, y)
Z = E(X, Y) #E_w([X, Y])
#Z = F(X, Y)
fig = plt.figure()
ax = Axes3D(fig)
surf = ax.plot_surface(X, Y, Z, edgecolor='none', rstride=1, cstride=1, cmap='jet')
min_point = np.array([w[0],w[1]])
min_point_ = min_point[:, np.newaxis]
ax.plot(min_point_[0], min_point_[1], E(min_point_[0], min_point_[1]), 'r*', markersize=10)
ax.set(title='Ejercicio 1.2. Función sobre la que se calcula el descenso de gradiente')
ax.set_xlabel('u')
ax.set_ylabel('v')
ax.set_zlabel('E(u,v)')

input("\n--- Pulsar tecla para continuar ---\n")
####Ejercicio 3 (F(x,y))

#Calculamos el gradiente descendiente de F: 50 iteraciones, 0.01 aprendizaje
initial_point = np.array([-1.0,1.0])
maxIter = 50
w, it1, W1 = gradient_descent(eta, maxIter, error2get, initial_point, gradF, F, 0)
print ('Numero de iteraciones: ', it1)
print ('Coordenadas obtenidas: (', w[0], ', ', w[1],')')
    #Guardamos todos los valores de F para los W obtenidos durante el gradiente
Fxy1 = np.array(F(W1[0],W1[1]))
for _ in range(2,(2*it1)-1,2):
    Fxy1 = np.append(Fxy1, F(W1[_],W1[_+1]))
    
#Calculamos el gradiente descendiente de F: 50 iteraciones, 0.1 aprendizaje
eta = 0.1
w, it2, W2 = gradient_descent(eta, maxIter, error2get, initial_point, gradF, F, 0)
print ('Numero de iteraciones: ', it2)
print ('Coordenadas obtenidas: (', w[0], ', ', w[1],')')
    #Guardamos todos los valores de F para los W obtenidos durante el gradiente
Fxy2 = np.array(F(W2[0],W2[1]))
for _ in range(2,(2*it2)-1,2):
    Fxy2 = np.append(Fxy2, F(W2[_],W2[_+1]))
    
fig, ax=plt.subplots()
ax.plot(np.arange(0,it1),Fxy1, label="eta 0.01")  
ax.plot(np.arange(0,it2),Fxy2, label="eta 0.1")    

legend = ax.legend(loc="upper left", shadow=True, fontsize="x-large")
plt.xlabel("Iteraciones")
plt.ylabel("F(x,y)")
plt.title("Evolución de F(w) frente a Iteraciones")
plt.show()
print("Gráfica en la figura 2")


input("\n--- Pulsar tecla para continuar ---\n")
#Apartado C
    #Preparamos los puntos iniciales para el gradiente
initial_points = [(-0.5,-0.5), (1,1),(2.1,-2.1),(-3,3),(-2,2)]
    #Realizamos el gradiente sobre cada punto inicial
w_tabla = np.empty((5,2))
for _ in range(0,5):
    w_tabla[_], it2, W2 = gradient_descent(eta, maxIter, error2get, initial_points[_], gradF, F, 1)
    #Almacenamos los valores de la función en los puntos devueltos por los gradientes
f_tabla = np.empty((5,1))
for _ in range(0, 5):
    f_tabla[_] = F(w_tabla[_][0], w_tabla[_][1])

string_tabla =np.empty((4,6))

#Preparamos los datos para implementarlos en una tabla de matplotlib
rows = ("Initial_Values","F(w) min", "x values", "y values")
columns = ("1","2","3","4","5")

data = [[initial_points[0],initial_points[1],initial_points[2],initial_points[3],initial_points[4]],
        [f_tabla[0],f_tabla[1],f_tabla[2],f_tabla[3],f_tabla[4]],
        [w_tabla.T[0][0],w_tabla.T[0][1],w_tabla.T[0][2],w_tabla.T[0][3],w_tabla.T[0][4]],
        [w_tabla.T[1][0],w_tabla.T[1][1],w_tabla.T[1][2],w_tabla.T[1][3],w_tabla.T[1][4]]       
        ]

#Se recomienda poner la gráfica a pantalla completa para visualizarla bien, ya que he ampliado
#el tamaño de fuente para que sea bien legible
fig, ax=plt.subplots()
ax.axis('tight')
ax.axis('off')

table = ax.table(cellText=data, rowLabels=rows, colLabels=columns, loc="center")
table.auto_set_font_size(False)
table.set_fontsize(9)
print("Tabla en la figura 3")

###############################################################################
###############################################################################
###############################################################################
###############################################################################
print('EJERCICIO SOBRE REGRESION LINEAL\n')
print('Ejercicio 1\n')

label5 = 1
label1 = -1

# Funcion para leer los datos
def readData(file_x, file_y):
	# Leemos los ficheros	
	datax = np.load(file_x)
	datay = np.load(file_y)
	y = []
	x = []	
	# Solo guardamos los datos cuya clase sea la 1 o la 5
	for i in range(0,datay.size):
		if datay[i] == 5 or datay[i] == 1:
			if datay[i] == 5:
				y.append(label5)
			else:
				y.append(label1)
			x.append(np.array([1, datax[i][0], datax[i][1]]))
			
	x = np.array(x, np.float64)
	y = np.array(y, np.float64)
	return x, y

#Funcion H
def H(x,w):
    matrix = np.matrix(x*w)
    return matrix.sum(axis=1)

# Funcion para calcular el error
def Err(x,y,w):
    return ((np.power(H(x,w).T-y,2)).sum())/x.shape[0]

#Gradiente Descendente Estocástico
def sgd(n_batches, it, eta, error2get, x, y):
    w = np.zeros(x.shape[1])
    #Juntamos x e y en una misma matriz
    xy = np.c_[x,y]
    for _ in range (it):
        #Barajamos aleatoriamente
        np.random.shuffle(xy)
        #Separamos en trozos según la cantidad de batches
        split_xy = np.array_split(xy, n_batches)       
        for b in range (0, n_batches):
            #Separamos x e y ahora que están mezclados y cortados
            mini_x, mini_y = split_xy[b][:,0:x.shape[1]], split_xy[b][:,x.shape[1]]
            #Calculamos el gradiente como H(x,w)-y
            grad = np.array(H(mini_x,w).T-mini_y)
            mini_x = np.array(mini_x)
            #Calculamos la sumatoria del gradiente
            sumatorio = (mini_x*grad.T).sum(axis=0)
            #Actualizamos w
            w = w-eta*sumatorio
            if(Err(x,y,w)<error2get):
                print("Hemos conseguido un error inferior!")
                break      
    #Devolvemos w
    return w

# Pseudoinversa	
def pseudoinverse(x, y):
    w = np.matmul(np.linalg.pinv(x), y)
    return w


# Lectura de los datos de entrenamiento
x, y = readData('datos/X_train.npy', 'datos/y_train.npy')
# Lectura de los datos para el test
x_test, y_test = readData('datos/X_test.npy', 'datos/y_test.npy')

N_BATCHES = 200
ETA = 0.01
N_ITERACIONES = 1
GOAL_ERROR = 1e-5

w = sgd(N_BATCHES, N_ITERACIONES, ETA, GOAL_ERROR, x, y)
print ('Bondad del resultado para grad. descendente estocastico:\n')
print ("Ein: ", Err(x,y,w))
print ("Eout: ", Err(x_test, y_test, w))
print ("Ajuste obtenido: ", w)

input("\n--- Pulsar tecla para continuar ---\n")

w_psi = pseudoinverse(x,y)
print ('Bondad del resultado para pseudoinversa:\n')
print ("Ein: ", Err(x,y,w_psi))
print ("Eout: ", Err(x_test, y_test, w_psi))

#Graficamos el resultado del sgd
unos = np.where(y==label1)
cincos = np.where(y==label5)

fig, ax = plt.subplots()
ax.scatter(x[unos,1], x[unos,2], color = "green", label = "unos")
ax.scatter(x[cincos,1], x[cincos,2], color = "red", label = "cincos")
ax.plot([0, 1], [-w[0]/w[2], -w[0]/w[2]-w[1]/w[2]]) 
legend = ax.legend(loc="lower right", shadow=True, fontsize="x-large")
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

print('Ejercicio 2\n')
# Simula datos en un cuadrado [-size,size]x[-size,size]
def simula_unif(N, d, size):
	return np.random.uniform(-size,size,(N,d))

#Funcion sign(), devuelve si el signo de X es positivo o negativo
def sign(x):
	if x >= 0:
		return 1
	return -1

#Funcion f
def f(x1, x2):
    return sign(((x1-0.2)**2)+(x2**2)-0.6) 

#Funcion opuesto(), devuelve la etiqueta opuesta
def opuesto(numero):
    if numero == 1:
        return -1
    return 1

#Funcion ruido(), modifica las etiquetas añadiendo ruido
def ruido(x):
    valores_a_modificar = round(0.1*len(x))
    #Elegir v_a_m posiciones aleatorias del vector
    indexes = np.random.choice(np.arange(len(x)), valores_a_modificar, replace = False)
    for i in indexes:
        x[i] = opuesto(x[i])
    return x

#Apartado A-B-C, experimento individual de sgd sobre muestra uniforme
N_VALORES = 1000
muestra1 = simula_unif(N_VALORES,2,1)
etiquetas1 = [f(muestra1[indice,0], muestra1[indice,1]) for indice in np.arange(N_VALORES)]
ruido(etiquetas1)
etiquetas1 = np.array(etiquetas1)

unos = np.where(etiquetas1==label1)
cincos = np.where(etiquetas1==label5)
muestra1 = np.c_[np.ones_like(muestra1[:,0]), muestra1]
w = sgd(N_BATCHES, N_ITERACIONES, 0.0005, GOAL_ERROR, muestra1, etiquetas1)

print ('Bondad del resultado para grad. descendente estocastico sobre muestra uniforme:\n')
print ("Ein: ", Err(muestra1,etiquetas1,w))
print ("Ajuste obtenido: ", w)

fig, ax = plt.subplots()

ax.scatter(muestra1[unos,1], muestra1[unos,2], color = "green", label = "unos")
ax.scatter(muestra1[cincos,1], muestra1[cincos,2], color = "red", label = "cincos")
ax.plot([0, 1], [-w[0]/w[2], -w[0]/w[2]-w[1]/w[2]]) 
plt.ylim(top=1)
plt.ylim(bottom = -1)

legend = ax.legend(loc="lower right", shadow=True, fontsize="x-large")

plt.show()


input("\n--- Pulsar tecla para continuar ---\n")
    #Apartado D y versión NO_LINEAL aprovechando el bucle
Ein_total = 0
Eout_total = 0
Ein_fi_total = 0
Eout_fi_total = 0
N_BATCHES = 10
for _ in range(0,1000):
    muestra1 = simula_unif(N_VALORES,2,1)
    test1 = simula_unif(N_VALORES,2,1)
    etiquetas1 = [f(muestra1[indice,0], muestra1[indice,1]) for indice in np.arange(N_VALORES)]
    etiquetas_test1 = [f(test1[indice,0], test1[indice,1]) for indice in np.arange(N_VALORES)]
    ruido(etiquetas1)
    ruido(etiquetas_test1)
    etiquetas1 = np.array(etiquetas1)
    etiquetas_test1 = np.array(etiquetas_test1)
    
    muestra1 = np.c_[np.ones_like(muestra1[:,0]), muestra1]
    test1 = np.c_[np.ones_like(test1[:,0]), test1]
    
    muestra_FI = np.c_[muestra1[:,0], muestra1[:,1], muestra1[:,2], muestra1[:,1]*muestra1[:,2], muestra1[:,1]**2, muestra1[:,2]**2]
    test_FI = np.c_[test1[:,0], test1[:,1], test1[:,2], test1[:,1]*test1[:,2], test1[:,1]**2, test1[:,2]**2]
    w = sgd(N_BATCHES, N_ITERACIONES, ETA, GOAL_ERROR, muestra1, etiquetas1)
    w_fi = sgd(N_BATCHES, N_ITERACIONES, ETA, GOAL_ERROR, muestra_FI, etiquetas1)
    Ein_total += Err(muestra1, etiquetas1, w)
    Ein_fi_total += Err(muestra_FI, etiquetas1, w_fi)
    
    Eout_total += Err(test1, etiquetas_test1,w)
    Eout_fi_total += Err(test_FI, etiquetas_test1, w_fi)
    print(Eout_total, Eout_fi_total)
    
Ein_medio = Ein_total/1000
Eout_medio = Eout_total/1000
Ein_fi_medio = Ein_fi_total/1000
Eout_fi_medio = Eout_fi_total/1000
print("El Ein medio en las 1000 iteraciones es: ", Ein_medio)
print("El Eout medio en las 1000 iteraciones es: ", Eout_medio)
print("El Ein medio FI en las 1000 iteraciones es: ", Ein_fi_medio)
print("El Eout medio FI en las 1000 iteraciones es: ", Eout_fi_medio)




