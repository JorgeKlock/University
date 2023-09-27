# -*- coding: utf-8 -*-
"""
Created on Sun Mar  7 15:29:11 2021

@author: Jorge Gangoso Klock
"""
import numpy as np
from sklearn import datasets
import matplotlib.pyplot as plt

    #Cargamos los datos de iris en x e y
iris = datasets.load_iris()
x = iris.data
y = iris.target

#Parte 1
    #Contamos cuantas filas de X pertenecen a las clases 1,2 y 3
n1=np.count_nonzero(y==0)
n2=n1+np.count_nonzero(y==1)
n3=n2+np.count_nonzero(y==2)
    #Dibujamos las categorías 1 y 3 enfrentadas, separadas en subplots por clases
fig, ax=plt.subplots()
ax.scatter(x[0:n1,0],x[0:n1,2], color="orange", label="clase1")   
ax.scatter(x[n1:n2,0],x[n1:n2,2], color="black", label="clase2")   
ax.scatter(x[n2:n3,0],x[n2:n3,2], color="green", label="clase3")   

legend = ax.legend(loc="lower right", shadow=True, fontsize="x-large")
plt.xlabel("Característica 1")
plt.ylabel("Característica 3")
plt.title("Values of X")
plt.show()

#Parte 2

#Usar la random seed para mantener resultados iguales y realizar comprobaciones
#np.random.seed(20)

#ordenar cada segmento de X (segun las clases 0,1,2) de forma aleatoria
x_random = x.copy()
np.random.shuffle(x_random[0:n1])
np.random.shuffle(x_random[n1:n2])
np.random.shuffle(x_random[n2:n3])

#coger un 75% de cada uno de los intervalos 0,1 y 2
training = np.concatenate((x_random[0:int(0.75*n1)], x_random[n1:n1+int(0.75*(n2-n1))], x_random[n2:n2+int(0.75*(n3-n2))]))
#coger el 25% restante de cada uno de los intervalos
test = np.concatenate((x_random[int(0.75*n1):n1], x_random[n1+int(0.75*(n2-n1)):n2], x_random[n2+int(0.75*(n3-n2)):n3,:]))
#crear un vector de clase con la cantidad y orden adecuados de 0,1,2
y_training = np.concatenate((np.zeros((1, int(n1*0.75)), int),np.ones((1, int((n2-n1)*0.75)), int),np.full((1,int((n3-n2)*0.75)), 2, int)), axis=1)
y_test = np.concatenate((np.zeros((1, n1-int(n1*0.75)), int),np.ones((1, (n2-n1)-int((n2-n1)*0.75)), int),np.full((1,(n3-n2)-int((n3-n2)*0.75)), 2, int)), axis=1)
#comprobamos que cada matriz tiene el tamaño correcto
#training deberia ser de (3*(75% de 50), 4) y test (3*(25% de 50), 4)
    #la suma de filas en training y test debe ser 150
print(training.shape)
print(test.shape)
#training_y y test_y deberian ser de 75% de 150 y 25% de 150 respectivamente
    #la suma de columnas en y_training e y_test debe ser 150
print(y_training.shape)
print(y_test.shape)

#Parte 3
    #Crear un vector ordenado de 100 elementos equitativamente distribuidos de 0 a 4pi
vector_eq = np.arange(0, 4*np.pi, (4*np.pi)/100)
    #Aplicamos seno, coseno y tanh(seno+coseno) y almacenamos en un vector cada uno para mostrarlos despues
sins = np.sin(vector_eq)
coss = np.cos(vector_eq)
tanhs = np.tanh(sins+coss)
    #Mostramos cada función en un subplot con distintos colores
fig2, ax2 = plt.subplots()
ax2.plot(sins, c="green", label="sin(x)")
ax2.plot(coss, c="black", label="cos(x)")
ax2.plot(tanhs, c="red", label="tanh(x)")
legend = ax2.legend(loc="lower right", shadow=True, fontsize="x-large")
plt.show()

