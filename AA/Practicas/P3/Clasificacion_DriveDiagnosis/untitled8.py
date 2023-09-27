# -*- coding: utf-8 -*-
"""
Created on Fri Jun  4 19:38:12 2021

@author: jorge
"""

# -*- coding: utf-8 -*-
"""
Created on Fri Jun  4 15:11:23 2021

@author: jorge
"""
#====== Librerías Generales
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
#====== Librerías Preprocesamiento
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MaxAbsScaler
from sklearn import preprocessing
#====== Librerías Modelos
from sklearn import svm
#====== Librerías Evaluación
from sklearn.metrics import accuracy_score
##### Lectura de datos
#======================
datos = pd.read_csv('Datos/Sensorless_drive_diagnosis.txt', delimiter=" ")
header_names = ['A' + str(i) for i in range(datos.shape[1]-1)]
header_names.append('status')
datos.set_axis(header_names, axis=1, inplace=True)

def normalize(X):
    scaler = preprocessing.StandardScaler().fit(X)
    X_normalized = scaler.transform(X) 
    return X_normalized
#print(datos.head(5))
#print(datos.tail(5))
#print(datos.describe())

# Boxplot de los datos
fig, ax = plt.subplots()
ax.boxplot(datos)
plt.show()

# Escalar los datos
y = datos['status']
X = datos
scaler = MaxAbsScaler().fit(X)
X = scaler.transform(X)
X = pd.DataFrame(X)

# Boxplot de los datos escalados
fig, ax = plt.subplots()
ax.boxplot(X)
plt.show()

# Recuperar la columna objetivo sin escalar
X = datos.drop(columns = 'status')
datos = pd.concat([X,y], axis=1)

# Escoger un ejemplo de cada status
ejemplos = []
for i in range(datos['status'].min(), datos['status'].max()+1):
    ejemplos.append(np.where(datos['status']==i)[0][0])

# Graficar las variables de cada ejemplo escogido
fig, ax = plt.subplots()
for i in range(0, len(ejemplos)):
    ax.plot(np.arange(0, datos.columns.size-1), datos.values[ejemplos[i]][:-1], label = i+1)
legend = ax.legend(loc="upper left", shadow=True, fontsize="8")
plt.show()


X_n = normalize(X)
# Hacer el train_test split
X_train, X_test, y_train, y_test = train_test_split(X_n, y, train_size = 0.6, random_state = None, shuffle = True)




# models = {svm.SVC(), svm.LinearSVC(), svm.NuSVC()}
# model_name = []
# acc = []
# for i_model in models:
#     model_name.append(i_model)
#     model = i_model
#     # Entrenar el modelo
#     model.fit(X_train,y_train)
#     # Hacer las predicciones
#     predictions = model.predict(X_test)
#     # Valorar el modelo
#     acc.append(accuracy_score(y_test, predictions))
#     print("Model: ",i_model,"is ready")

# print(acc)

kernel = ['linear', 'poly', 'rbf', 'sigmoid']
degree = [1,2,3,4,5]

poly = []
others = []
print("start")
for i in kernel:
    if(i=='poly'):
        for j in degree:
            model = svm.NuSVC(kernel=i, degree=j, max_iter = 10)
            model.fit(X_train,y_train)
            # Hacer las predicciones
            predictions = model.predict(X_test)
            # Valorar el modelo
            poly.append(accuracy_score(y_test, predictions))
            print("Model: ", i," degree ", j, "is ready")
    else:
        model = svm.NuSVC(kernel=i, max_iter = 10)
        model.fit(X_train,y_train)
        # Hacer las predicciones
        predictions = model.predict(X_test)
        # Valorar el modelo
        others.append(accuracy_score(y_test, predictions))
        print("Model: ", i,"is ready")
    
print(poly)
print(others)

# RBF da mejores resultados