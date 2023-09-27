# -*- coding: utf-8 -*-
"""
TRABAJO 2
Nombre Estudiante: Jorge Gangoso Klock 49398653N
"""
import numpy as np
import matlib.pyplot as plt


# Fijamos la semilla
#np.random.seed(1)


def simula_unif(N, dim, rango):
	return np.random.uniform(rango[0],rango[1],(N,dim))

def label_data(x1, x2):
    y = np.sign((x1-0.2)**2 + x2**2 - 0.6)
    idx = np.random.choice(range(y.shape[0]), size=(int(y.shape[0]*0.1)), replace=True)
    y[idx] *= -1
    return y


def simula_gaus(N, dim, sigma):
    media = 0    
    out = np.zeros((N,dim),np.float64)        
    for i in range(N):
        # Para cada columna dim se emplea un sigma determinado. Es decir, para 
        # la primera columna (eje X) se usará una N(0,sqrt(sigma[0])) 
        # y para la segunda (eje Y) N(0,sqrt(sigma[1]))
        out[i,:] = np.random.normal(loc=media, scale=np.sqrt(sigma), size=dim)
    
    return out


def simula_recta(intervalo):
    points = np.random.uniform(intervalo[0], intervalo[1], size=(2, 2))
    x1 = points[0,0]
    x2 = points[1,0]
    y1 = points[0,1]
    y2 = points[1,1]
    # y = a*x + b
    a = (y2-y1)/(x2-x1) # Calculo de la pendiente.
    b = y1 - a*x1       # Calculo del termino independiente.
    
    return a, b


# EJERCICIO 1.1: Dibujar una gráfica con la nube de puntos de salida correspondiente

x = simula_unif(50, 2, [-50,50])
#CODIGO DEL ESTUDIANTE
plt.figure(0)
plt.scatter(x[:, 0], x[:, 1])
plt.show()



x = simula_gaus(50, 2, np.array([5,7]))
#CODIGO DEL ESTUDIANTE
plt.figure(1)
plt.scatter(x[:, 0], x[:, 1])
plt.show()


input("\n--- Pulsar tecla para continuar ---\n")


###############################################################################
###############################################################################
###############################################################################


# EJERCICIO 1.2: Dibujar una gráfica con la nube de puntos de salida correspondiente

# La funcion np.sign(0) da 0, lo que nos puede dar problemas
def signo(x):
	if x >= 0:
		return 1
	return -1

def signo_cero(x):
	if x >= 0:
		return 1
	return 0

def f(x, y, a, b):
	return signo(y - a*x - b)

#CODIGO DEL ESTUDIANTE
def misclassification (y_original, y_obtenida):
    tmp = np.array(y_original-y_obtenida)
    ocurrencias = np.count_nonzero(tmp)
    porcentaje = (ocurrencias / y_original.size) *100
    return porcentaje


    #Crear la muestra y la recta (ax+b)
x = simula_unif(100, 2, [-50,50])
a,b = simula_recta([-50,50])
x2a = x
x2b = x

    #Crear las etiquetas y 
y = np.array([f(x[i,0], x[i,1], a, b) for i in range (0, x.shape[0])])
y2a = y
y_positivo = np.where(y==1)
y_negativo = np.where(y==-1)
    #Parametrizar la recta ideal para mostrarla en plots
n = np.linspace(-50,50,100)
y_n = a*n+b
    #Calcular la tasa de misclassification
misclassification_rate = misclassification(y, y)
print("Misclassification rate: ", misclassification_rate, " %")
    #Hacer el plot de los datos
fig, ax = plt.subplots()
ax.scatter(x[y_positivo, 0], x[y_positivo, 1], color = "green", label="positivos")
ax.scatter(x[y_negativo, 0], x[y_negativo, 1], color = "red", label="negativos")

ax.plot(n, y_n)
legend = ax.legend(loc="lower right", shadow=True, fontsize="x-large")
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

# 1.2.b. Dibujar una gráfica donde los puntos muestren el resultado de su etiqueta, junto con la recta usada para ello
# Array con 10% de indices aleatorios para introducir ruido
def ruido(y):
    idx = np.random.choice(range(y.shape[0]), size=(int(y.shape[0]*0.1)), replace=True)
    y[idx] *= -1
    return y
#CODIGO DEL ESTUDIANTE

y_ruido = np.array(ruido(y.copy()))
y2b = y_ruido
y_r_positivo = np.where(y_ruido == 1)
y_r_negativo = np.where(y_ruido == -1)

    #Calcular la tasa de misclassification
misclassification_rate = misclassification(y, y_ruido)
print("Misclassification rate: ", misclassification_rate, " %")
    #Hacer el plot de los datos
fig, ax = plt.subplots()
ax.scatter(x[y_r_positivo, 0], x[y_r_positivo, 1], color = "green", label="positivos")
ax.scatter(x[y_r_negativo, 0], x[y_r_negativo, 1], color = "red", label="negativos")

ax.plot(n, y_n)
legend = ax.legend(loc="lower right", shadow=True, fontsize="x-large")
plt.show()

input("\n--- Pulsar tecla para continuar ---\n")

###############################################################################
###############################################################################
###############################################################################

# EJERCICIO 1.3: Supongamos ahora que las siguientes funciones definen la frontera de clasificación de los puntos de la muestra en lugar de una recta

def plot_datos_cuad(X, y, fz, title='Point cloud plot', xaxis='x axis', yaxis='y axis'):
    #Preparar datos
    min_xy = X.min(axis=0)
    max_xy = X.max(axis=0)
    border_xy = (max_xy-min_xy)*0.01
    
    #Generar grid de predicciones
    xx, yy = np.mgrid[min_xy[0]-border_xy[0]:max_xy[0]+border_xy[0]+0.001:border_xy[0], 
                      min_xy[1]-border_xy[1]:max_xy[1]+border_xy[1]+0.001:border_xy[1]]
    grid = np.c_[xx.ravel(), yy.ravel(), np.ones_like(xx).ravel()]
    pred_y = fz(grid)
 
    # pred_y[(pred_y>-1) & (pred_y<1)]
    pred_y = np.clip(pred_y, -1, 1).reshape(xx.shape)
    
    #Plot
    f, ax = plt.subplots(figsize=(8, 6))
    contour = ax.contourf(xx, yy, pred_y, 50, cmap='RdBu',vmin=-1, vmax=1)
    ax_c = f.colorbar(contour)
    ax_c.set_label('$f(x, y)$')
    ax_c.set_ticks([-1, -0.75, -0.5, -0.25, 0, 0.25, 0.5, 0.75, 1])
    ax.scatter(X[:, 0], X[:, 1], c=y, s=50, linewidth=2, 
                cmap="RdYlBu", edgecolor='white')
    
    XX, YY = np.meshgrid(np.linspace(round(min(min_xy)), round(max(max_xy)),X.shape[0]),np.linspace(round(min(min_xy)), round(max(max_xy)),X.shape[0]))
    positions = np.vstack([XX.ravel(), YY.ravel()])
    
    ax.contour(XX,YY,fz(positions.T).reshape(X.shape[0],X.shape[0]),[0], colors='black')
    
    ax.set(
       xlim=(min_xy[0]-border_xy[0], max_xy[0]+border_xy[0]), 
       ylim=(min_xy[1]-border_xy[1], max_xy[1]+border_xy[1]),
       xlabel=xaxis, ylabel=yaxis)
    plt.title(title)
    plt.show()
    
    
#CODIGO DEL ESTUDIANTE
#Funcion 1
fz = lambda x: (x[:,0]-10)**2 + (x[:,1]-20)**2 - 400

y_fz = fz(x)
y_fz = np.array([signo(y_fz[i]) for i in range (0,y_fz.shape[0])])
misclassification_rate = misclassification(y, y_fz)
print("Misclassification rate: ", misclassification_rate, " %")
   
plot_datos_cuad(x, y_ruido, fz)
#Funcion 2
fz = lambda x: 0.5*(x[:,0]+10)**2 + (x[:,1]-20)**2 - 400

y_fz = fz(x)
y_fz = np.array([signo(y_fz[i]) for i in range (0,y_fz.shape[0])])
misclassification_rate = misclassification(y, y_fz)
print("Misclassification rate: ", misclassification_rate, " %")

plot_datos_cuad(x, y_ruido, fz)
#Funcion 3
fz = lambda x: 0.5*(x[:,0]-10)**2 - (x[:,1]+20)**2 - 400

y_fz = fz(x)
y_fz = np.array([signo(y_fz[i]) for i in range (0,y_fz.shape[0])])
misclassification_rate = misclassification(y, y_fz)
print("Misclassification rate: ", misclassification_rate, " %")

plot_datos_cuad(x, y_ruido, fz)
#Funcion 4
fz = lambda x: x[:,1] - 20*(x[:,0]**2) - 5*x[:,0] + 3

y_fz = fz(x)
y_fz = np.array([signo(y_fz[i]) for i in range (0,y_fz.shape[0])])
misclassification_rate = misclassification(y, y_fz)
print("Misclassification rate: ", misclassification_rate, " %")

plot_datos_cuad(x, y_ruido, fz)

input("\n--- Pulsar tecla para continuar ---\n")

###############################################################################
###############################################################################
###############################################################################

# EJERCICIO 2.1: ALGORITMO PERCEPTRON

def ajusta_PLA(datos, label, max_iter, vini):
    #CODIGO DEL ESTUDIANTE
    n = datos.shape[0]
    w = np.array(vini)
    iteraciones = 0
    cambios = True
    while (cambios):
        w_antes = w
        iteraciones+=1
        for i in range (0,n):
            if(signo(np.matmul(w,datos[i]))!=label[i]):
                w = w + label[i]*datos[i]
        if(np.array_equal(w_antes, w)):
            cambios = False
        if(iteraciones>= max_iter): break
    return w, iteraciones

#CODIGO DEL ESTUDIANTE
def clasificar (x, w):
    y = []
    for i in range (0, x.shape[0]):
        y.append(signo(np.matmul(w,x[i])))
    return y

def clasificar_p (x, w):
    y = []
    for i in range (0, x.shape[0]):
        y.append(signo_cero(np.matmul(w,x[i])))
    return y


    #DATOS DEL APARTADO 2a : x2a
x2a = np.c_[np.ones(x.shape[0]), x2a]
y = y2a

#2.a.1.a
#### Con el vector 0 como pesos iniciales
w_ini = np.zeros_like(x2a[0])
w_fin, iteraciones = ajusta_PLA(x2a, y, 1000, w_ini)

y_final = np.array(clasificar(x2a, w_fin))
y_positivo = np.where(y_final==1)
y_negativo = np.where(y_final==-1)

    #Calcular la tasa de misclassification
misclassification_rate = misclassification(y, y_final)
print("Misclassification rate: ", misclassification_rate, " %")
print("Converge en la iteracion: ", iteraciones)
    #Comprobar la frontera de clasificacion en un plot
n = np.linspace(-50,50,100)
y_n = ((-(w_fin[0]/w_fin[2])/(w_fin[0]/w_fin[1]))*n + (-w_fin[0]/w_fin[2]))

fig, ax = plt.subplots()
ax.plot(n, y_n)
ax.scatter(x2a[y_positivo, 1], x2a[y_positivo, 2], color = "green")
ax.scatter(x2a[y_negativo, 1], x2a[y_negativo, 2], color = "red")
plt.title("Perceptron con datos sin ruido")
plt.show()


#2.a.1.b
#### Con pesos iniciales aleatorios
iterations = []
for i in range(0,10):
    #CODIGO DEL ESTUDIANTE
    w_ini = np.random.uniform(0,1, size=x2a.shape[1])
    w_fin, iteraciones = ajusta_PLA(x2a, y, 1000, w_ini)
    iterations.append(iteraciones)
    
print('Valor medio de iteraciones necesario para converger: {}'.format(np.mean(np.asarray(iterations))))

input("\n--- Pulsar tecla para continuar ---\n")

# Ahora con los datos del ejercicio 1.2.b
#CODIGO DEL ESTUDIANTE
#2.a.2 

#### Con el vector 0 como pesos iniciales
x2b = np.c_[np.ones(x.shape[0]), x2b]
y = y2b

w_ini = np.zeros_like(x2b[0])
w_fin, iteraciones = ajusta_PLA(x2b, y, 1000, w_ini)

y_final = np.array(clasificar(x2b, w_fin))
y_positivo = np.where(y==1)
y_negativo = np.where(y==-1)

    #Calcular la tasa de misclassification
misclassification_rate = misclassification(y, y_final)
print("Misclassification rate: ", misclassification_rate, " %")
print("Converge en la iteracion: ", iteraciones)
    #Comprobar la frontera de clasificacion en un plot
n = np.linspace(-50,50,100)
y_n = ((-(w_fin[0]/w_fin[2])/(w_fin[0]/w_fin[1]))*n+ (-w_fin[0]/w_fin[2]))

fig, ax = plt.subplots()
ax.plot(n, y_n)
ax.scatter(x2b[y_positivo, 1], x2b[y_positivo, 2], color = "green")
ax.scatter(x2b[y_negativo, 1], x2b[y_negativo, 2], color = "red")
plt.title('Perceptron con datos ruidosos')
plt.show()

#### Con pesos iniciales aleatorios
iterations = []
for i in range(0,10):
    w_ini = np.random.uniform(0,1, size=x2b.shape[1])
    w_fin, iteraciones = ajusta_PLA(x2b, y, 1000, w_ini)
    iterations.append(iteraciones)
    
print('Valor medio de iteraciones necesario para converger: {}'.format(np.mean(np.asarray(iterations))))


input("\n--- Pulsar tecla para continuar ---\n")

###############################################################################
###############################################################################
###############################################################################

# EJERCICIO 3: REGRESIÓN LOGÍSTICA CON STOCHASTIC GRADIENT DESCENT
def RL(datos, label, epocas, tasa):
    #VALORES INICIALES
    epoca_actual = 0
    cambio = True
    w = np.zeros_like(datos[0])
    while(epoca_actual < epocas and cambio==True):
        grad = gradiente(datos, label, w)
        w_new = w - tasa*grad
        if(np.sum(np.abs(w_new - w)) < 0.01):
            cambio = False
        epoca_actual+=1
    return w, epoca_actual

def gradiente(datos, label, w):
    #E(1..n) logistic
    sumatorio = 0.0
    for i in range (0, datos.shape[0]):
        sumatorio += (label[i]*datos[i])/(1+np.exp(label[i]*w*datos[i]))
    #-1/N
    prefix = -1/datos.shape[0]
    return prefix*sumatorio

def sgdRL(datos, label, epocas, tasa):
    #VALORES INICIALES
    epoca_actual = 0
    cambio = True
    w = np.zeros_like(datos[0])
    xy = np.c_[datos,label]
    
    while(epoca_actual < epocas and cambio==True):
        #Barajamos aleatoriamente
        np.random.shuffle(xy)
        #Separamos en batches de tamaño 1
        split_xy = np.array_split(xy, datos.shape[0])  
        
        w_new = w.copy()
        for b in range (0, datos.shape[0]):
            #Separamos x e y ahora que están mezclados y cortados
            mini_x, mini_y = split_xy[b][:,0:x.shape[1]], split_xy[b][:,x.shape[1]]
            #Calculamos el gradiente de los batches en este caso de tamaño 1
            grad = gradiente(mini_x, mini_y, w_new)
            #Si la etiqueta difiere de la prediccion actualizamos los pesos
            if(RL_classifier(mini_x, w_new) != mini_y):
                w_new = w_new - (tasa*grad)
            
        #if(np.sum(np.abs(w_new - w)) < 0.001):
        if(norma2(w_new, w) < 0.01):
                cambio = False
        w = w_new
        epoca_actual+=1
    return w, epoca_actual

def norma2 (x1, x2):
    return np.sqrt(sum((x1-x2)**2))

#Clasificador de la regresion logistica usando la funcion sigmoidal
def RL_classifier(x,w):
    y = []
    for i in range (0, x.shape[0]):
        if(sigma(x[i],w) >= 0.5):
            y.append(1)
        else:
            y.append(-1)
    return y

#Funcion F = (x*w)
def f_2(x, w):
    return x[0]*w[0]+x[1]*w[1]+x[2]*w[2]

#Funcion sigmoidal
def sigma(x,w):
    return 1/(1+np.exp(-f_2(x,w)))

def Eout (N, x, y, w):
    sumatorio = 0.0
    w = np.array(w)[np.newaxis]
    for i in range (0,N):
        sumatorio += np.log(1+np.exp(-1*y[i]*np.matmul(w,x[i])))
    return (1/N) * sumatorio

#CODIGO DEL ESTUDIANTE
puntos_recta = simula_unif(2, 2, [0,2])
#m = (y2-y1)/(x2-x1)
m = (puntos_recta[1][1]-puntos_recta[0][1])/(puntos_recta[1][0]-puntos_recta[0][0])
# y1 = m*x1 + Origen -> Origen = y1 - m*x1
origen = puntos_recta[0][1] - m*puntos_recta[0][0]

x = simula_unif(100, 2, [0,2])
f = lambda x: [-1*signo(m*x[i,0]+origen - x[i,1]) for i in range (0,x.shape[0])]
y = np.array(f(x))

    #Parametrizar la recta ideal para mostrarla en plots
n = np.linspace(0,2,100)
y_n = m*n+origen


x = np.c_[np.ones(x.shape[0]), x]

w_single, epochs = sgdRL(x, y, 100, 0.01)
print("Valores finales de w: ", w_single)
print("Numero de epocas totales: ", epochs)



y_fin = RL_classifier(x, w_single)
print("Ein: ", misclassification(y, y_fin), " %")

    #Hacer el plot de los datos
fig, ax = plt.subplots()

y_fin = np.array(y_fin)
y_positivo = np.where(y_fin==1)
y_negativo = np.where(y_fin==-1)
ax.scatter(x[y_positivo, 1], x[y_positivo, 2], color = "green", label="clasificados positivos")
ax.scatter(x[y_negativo, 1], x[y_negativo, 2], color = "red", label="clasificados negativos")

ax.plot(n, y_n)
legend = ax.legend(loc="upper right", shadow=True)


plt.show()


print("Recta original: m: " , m, "origen: ", origen)

    
x_test = simula_unif(1000, 2, [0,2])
y_test = np.array(f(x_test))

x_test = np.c_[np.ones(x_test.shape[0]), x_test]
y_fin = RL_classifier(x_test, w_single)
print("Misclassification Rate de la ejecución individual: ", misclassification(y_test, y_fin), " %")
print("Eout de la ejecución individual: ", Eout(1000, x_test, y_test, w_single))

    #Hacer el plot de los datos
fig, ax = plt.subplots()

y_fin = np.array(y_fin)
y_positivo = np.where(y_fin==1)
y_negativo = np.where(y_fin==-1)
ax.scatter(x_test[y_positivo, 1], x_test[y_positivo, 2], color = "green", label="clasificados positivos")
ax.scatter(x_test[y_negativo, 1], x_test[y_negativo, 2], color = "red", label="clasificados negativos")

ax.plot(n, y_n)
legend = ax.legend(loc="upper right", shadow=True)


plt.show()

input("\n--- Pulsar tecla para continuar ---\n")
    


# Usar la muestra de datos etiquetada para encontrar nuestra solución g y estimar Eout
# usando para ello un número suficientemente grande de nuevas muestras (>999).


#CODIGO DEL ESTUDIANTE
epocas_totales = 0
eout_total = 0
for i in range (0,100):
    x = simula_unif(100, 2, [0,2])
    y = np.array(f(x))
    
    x = np.c_[np.ones(x.shape[0]), x]
    w, epochs = sgdRL(x, y, 100, 0.01)
    epocas_totales += epochs
    y_fin = RL_classifier(x, w)
    x_test = simula_unif(1000, 2, [0,2])
    x_test = np.c_[np.ones(x_test.shape[0]), x_test]
    y_test = np.array(f(x_test))
    eout_total += Eout(1000, x_test, y_test, w)
    
print("Media de epocas: ", epocas_totales/100)
print("Media de Eout: ", eout_total/100)    
    
    

input("\n--- Pulsar tecla para continuar ---\n")
