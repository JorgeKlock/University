# -*- coding: utf-8 -*-
"""
Created on Wed Apr  7 21:58:29 2021

@author: Jorge Gangoso Klöck 49398653N

"""
#PRACTICA DE MH 1
import numpy as np
import time 


#Devuelve la cantidad de elementos en un cluster
def elementos_cluster (x):
    x = np.array(x)
    return x.size

#Devuelve los K clusters que aparecen en C devolviendo los indices en arrays
def separate_clusters (C, k):
    clusters = [[None]]*k
    C = np.array(C)
    for _ in range (0, k):
        clusters[_] = np.where(C == _)
    return clusters
    
#Devuelve el centroide de un cluster x
def calcular_centroide_cluster (datos, x):
    if(elementos_cluster(x) == 0):
        return None
    else:
        return (1/elementos_cluster(x)) * sum(datos[x])


#Devuelve la norma euclidea entre dos puntos
def norma2 (x1, x2):
    return np.sqrt(sum((x1-x2)**2))

#Devuelve la norma euclidea entre un vector y un punto
def norma2_vector (v, x2):
    value = sum(norma2(v[_],x2) for _ in range(0,v.shape[0]))
    return value

#Devuelve la distancia media intra-cluster de un cluster x
def calcular_d_media_cluster (datos, x):
    centroide = calcular_centroide_cluster(datos, x)
    if(elementos_cluster(x)==0):
        return None
    else:
        return (1/elementos_cluster(x)) * norma2_vector(datos[x], centroide)

#Devuelve la distancia media intra-cluster de unos Datos y su C
def calcular_media_intra_cluster_total (muestra, C, K):
    clusters = separate_clusters(C, K)
    suma = 0
    for _ in range(0, K):
        suma += calcular_d_media_cluster(muestra, clusters[_])
    return suma/K

#Devuelve la desviación general de los datos
def calcular_desviacion_general (datos, C, K):
    clusters = separate_clusters(C, K)
    return 1/K * sum(calcular_d_media_cluster(datos, clusters[_]) for _ in range(0,K))

    
# Funcion para leer los datos: readData(Datos, Restricciones)
def readData(file_x, file_y, file_z):
    #Leemos los datos de los ficheros
    with open(file_x, 'r') as f:
        datos = [[float(x) for x in line.split(',')] for line in f]
    with open(file_y, 'r') as f:
        restricciones = [[float(x) for x in line.split(',')] for line in f]
    with open(file_z, 'r') as f:
        restricciones20 = [[float(x) for x in line.split(',')] for line in f]
    #Devolvemos las matrices
    return datos, restricciones, restricciones20

#Funcion generar Centroides iniciales aleatorios
def generarCentroidesAleatorios (k, datos):
    #Generamos K centroides de dimension "dimensiones"
    centroides = []
    for _ in range (0,k):
        centroides.append(datos[_])
    return centroides

#Funcion que determina si se estan incumpliendo restricciones
def V(i, j, restricciones, C):
    if(restricciones[i][j] == 1):
        if(C[i] != C[j]):
            return 1
    if(restricciones[i][j] == -1):
        if(C[i] == C[j]):
            return 1
    return 0

#Funcion que determina si se esta incumpliendo una restriccion concreta en formato tripleta
def sub_V(restriccion, C):
    if(restriccion[2] == 1):
        if (C[restriccion[0]] != C[restriccion[1]]):
            return 1
    if(restriccion[2] == -1):
        if (C[restriccion[0]] == C[restriccion[1]]):
            return 1
    return 0
    

#Funcion transforma las restricciones a tripletas
def restrict_to_triple(restricciones):
    restricciones_t = []
    for i in range (0, len(restricciones)-1):
        for j in range (i+1, len(restricciones)):
            if(restricciones[i][j] != 0):
                restricciones_t.append([i, j, restricciones[i][j]])
    return restricciones_t

#Funcion calcular el infeasibility con restricciones tripleta
def infeasibility_t(C, restricciones):
    suma = 0
    for _ in range (0, len(restricciones)):
        suma += sub_V(restricciones[_], C)
    return suma


#Funcion para calcular el aumento de infeasibility que produce añadir una instancia en un cluster
def inc_infeasibility(cluster, restricciones, n_instancia, C, K):
    incremento = 0
    #Simulamos la inclusion del elemento en el cluster
    C_temp = C.copy()
    C_temp[n_instancia] = cluster 
    #Calculamos su influencia, para ello comprobamos las restricciones en la fila n_instancia
    for _ in range (0, len(C)):
        incremento += V(_, n_instancia, restricciones, C)
    return incremento


    
    
#Funciones restricciones totales tripleta
def restricciones_totales(restricciones):
    return len(restricciones)

#Funcion distancia maxima entre los puntos de la entrada de datos
def distancia_maxima(datos):
    distancia_max = 0
    for i in range(0, datos.shape[0]-1):
        for j in range(i+1, datos.shape[0]):
            d = norma2(datos[i],datos[j])
            if (d > distancia_max):
                distancia_max = d
    return distancia_max

#Funcion lambda para la importancia de la infeasibility
def landa (datos, restricciones):
    return distancia_maxima(datos) / restricciones_totales(restricciones)

#Funcion para calcular el fitness
def fitness(datos, C, K, infeas, restricciones):
    media = calcular_media_intra_cluster_total(datos, C, K)
    l = landa(datos, restricciones)
    return media + l*infeas
    
#Funcion asignar a una instancia el centroide de forma greedy
def asignarInstancia(instancia, n_instancia, restricciones, centroides, C, K):
    #Comprobamos el aumento de infeasibility de asignar la instancia a un cluster
    menor_cambio = 100000
    indices_posibles = []
    centroides = np.array(centroides, dtype=object)
    for _ in range (0, K):
        #Simulamos el aumento de infeasibility
        cambio = inc_infeasibility(_, restricciones, n_instancia, C, K)
        #Comprobamos si es menor que las alternativas
        if (cambio <= menor_cambio):
            indices_posibles.append(_)
            menor_cambio = cambio
    #Tenemos en indices_posibles los clusters en los que menos restricciones incumple
    #Añadimos la instancia al cluster cuyo centroide se encuentra mas cerca
    distancia_menor = 100000
    indice_mejor = indices_posibles[0]
    for _ in indices_posibles:
        distancia = norma2(instancia, centroides[_])
        if (distancia < distancia_menor):
            distancia_menor = distancia
            indice_mejor = _
    C[n_instancia] = indice_mejor
    return 0
    

#ALGORITMO COPKM
def COPKM (datos, restricciones, K):
    C = [-1]*datos.shape[0]
    #Generamos centroides iniciales aleatorios
    centroides = generarCentroidesAleatorios(K, datos)
    #Barajamos los indices de los datos
    indices_datos = np.arange(0, datos.shape[0])
    np.random.shuffle(indices_datos)
    #Iteramos mientras cambie C
    variacion = True
    vacios = False
    while(variacion or vacios):
        C_antes = C.copy()
        #Asignamos las instancias
        vacios = False
        for _ in indices_datos:
            asignarInstancia(datos[_], _, restricciones, centroides, C, K)
        clusters = separate_clusters(C, K)
        cluster_vacio = []
        for _ in range (0,K):
            if(len(clusters[_][0]) == 0):
                vacios = True
                cluster_vacio.append(_)
            else:
                centroides[_] = calcular_centroide_cluster(datos, clusters[_])
        #Comprobamos si ha cambiado C
        if (C == C_antes): 
            variacion = False
        #Actualizamos los centroides si hay clusters vacios
        if(vacios): 
            print("El centroide ", cluster_vacio, "se randomiza")
            centroides_nuevos = generarCentroidesAleatorios(K, datos.shape[1])
            for _ in cluster_vacio:
                centroides[_] = centroides_nuevos[_]    
            #print("Ya no quedan clusters vacios!")
        #print(variacion, vacios)
    return C

#Funcion genera una solucion inicial aleatoria factible
def generar_solucion_inicial(datos, K):
    solucion = np.array([])
    #solucion = []
    #Generar datos.shape[0] valores entre 0 y K (que sea factible)
    while (factible(solucion,K) == False):
        solucion = np.random.randint(K, size = datos.shape[0])
    return solucion

#Funcion F a optimizar mediante BL
def f(C, K, datos, restricciones, lmb):
    desviacion = calcular_desviacion_general(datos, C, K)
    infeas = infeasibility_t(C, restricciones)
    return desviacion + (infeas*lmb)

    

#Funcion generar Vecindario Virtual
def generarVecindarioVirtual (Solucion, K):
    vecindario = []
    for _ in range (0, len(Solucion)):
        for i in range (0, K):
            if(i != Solucion[_]):
                vecindario.append([_,i])
    return vecindario

#Funcion generar Vecino a partir de solucion y operador
def generarVecino (Solucion, operador):
    vecino = Solucion.copy()
    vecino[operador[0]] = operador[1]
    return vecino

#Funcion de factibilidad de una solucion
def factible (Solucion, K):
    es_factible = True
    clusters = separate_clusters(Solucion, K)
    for _ in range(0,K):
        if (len(clusters[_][0]) == 0): es_factible = False
    return es_factible

#Funcion Busqueda Local
def BL (S_ini, datos, restricciones, K, maxIter):
    Solucion = S_ini
    #Calculamos landa ya que es constante para todo el programa solo una vez
    lmb = landa(datos, restricciones)
    mejora = True
    mejor_valor = f(Solucion, K, datos, restricciones, lmb)
    iteraciones = 0
    while (iteraciones < maxIter and mejora):
        print(iteraciones)
        mejora = False
        iteraciones += 1
        op_vecindario = generarVecindarioVirtual (Solucion, K)
        np.random.shuffle(op_vecindario)
        while (op_vecindario and mejora == False):
            op_vecino = op_vecindario.pop()
            vecino = generarVecino(Solucion, op_vecino)
            if(factible(vecino, K)):
                valor_vecino = f(vecino, K, datos, restricciones, lmb)
                if(valor_vecino < mejor_valor):
                    mejor_valor = valor_vecino
                    Solucion = vecino
                    mejora = True
        #Fin del While
    return Solucion

######## PONER A TRUE EL ARCHIVO DE DATOS Y EL TIPO DE RESTRICCIONES DESEADO ######
###################################################################################
zoo = True
glass = False
bupa = False
restricciones10_t = True
restricciones20_t = False

#Definimos a priori la cantidad de clusters K
K_zoo = 7
K_glass = 7
K_bupa = 16
#Definimos una semilla aleatoria 
semilla = 5
np.random.seed(semilla)

#Definimos el archivo que deseamos usar
if(zoo): nombre = 'zoo'
if(bupa): nombre = 'bupa'
if(glass): nombre = 'glass'
#Definimos la K del archivo
if(zoo): K = K_zoo
if(bupa): K = K_bupa
if(glass): K = K_glass
#Definimos el error de referencia
REF_ERROR = 0
if(zoo): REF_ERROR = 0.904799856
if(bupa): REF_ERROR = 0.22924805
if(glass): REF_ERROR = 0.364290282
#Definimos las iteraciones máximas
N_IT = 100000

file = 'Datos/'+ nombre +'_set.dat'
rest_file = 'Datos/'+ nombre +'_set_const_10.const'
rest_20_file = 'Datos/'+ nombre +'_set_const_20.const'


#Importamos datos de ficheros
datos, restricciones, restricciones20 = readData(file, rest_file, rest_20_file)
datos = np.array(datos)

if (restricciones10_t): 
    restricciones = np.array(restricciones)
if (restricciones20_t): 
    restricciones = np.array(restricciones20)

#Generamos solucion inicial
s_ini = generar_solucion_inicial(datos, K)
restricciones_t = restrict_to_triple(restricciones)


#Ejecutamos BL
start_time = time.time()
S = BL(s_ini, datos, restricciones_t, K, N_IT)
execution_time = (time.time() - start_time)

infeas = infeasibility_t(S, restricciones_t)
lmb = landa(datos, restricciones) 
print("instra-cluster:", calcular_media_intra_cluster_total(datos, S, K))
print("error_dist: ", (np.abs(calcular_media_intra_cluster_total(datos, S, K) - REF_ERROR)))
print("agregado:", f(S, K, datos, restricciones_t, lmb))
print("infeasibility:" , infeas)
print("fitness: ", fitness(datos, S, K, infeas, restricciones))
print("time: ", execution_time)
print("seed: ", semilla)


start_time = time.time()
C = COPKM(datos, restricciones, K)
execution_time = (time.time() - start_time)

print(C)
lmb = landa(datos, restricciones) 
infeas = infeasibility_t(C, restricciones_t)
print("instra-cluster:", calcular_media_intra_cluster_total(datos, C, K))
print("error_dist: ", (np.abs(calcular_media_intra_cluster_total(datos, C, K) - REF_ERROR)))
print("agregado:", f(C, K, datos, restricciones_t, lmb))
print("infeasibility:" , infeas)
print("time: ", execution_time)
print("seed: ", semilla)




