#====== Librerías Generales
import numpy as np
import pandas as pd
import time
import matplotlib.pyplot as plt
#====== Librerías Preprocesamiento
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MaxAbsScaler
#====== Librerías Modelos
from sklearn import svm
#====== Librerías Evaluación
from sklearn.metrics import accuracy_score
from sklearn.metrics import plot_confusion_matrix
from sklearn.metrics import confusion_matrix
##### Lectura de datos
#======================
datos = pd.read_csv('Datos/Sensorless_drive_diagnosis.txt', delimiter=" ")
header_names = ['A' + str(i) for i in range(datos.shape[1]-1)]
header_names.append('status')
datos.set_axis(header_names, axis=1, inplace=True)

y = datos['status']
X = datos
X = datos.drop(columns = 'status')
print(X.shape)
#REDUCCION DE DIMENSIONALIDAD
# Obtener matriz de correlación y eliminar las variables muy relacionadas
corr = X.corr()
corr.style.background_gradient(cmap='coolwarm')

correlated_features = set()
for i in range(len(corr.columns)):
    for j in range(i):
        if abs(corr.iloc[i, j]) > 0.9:
            colname = corr.columns[i]
            correlated_features.add(colname)
correlated_features = list(correlated_features)
X = X.drop(columns = correlated_features)
print(X.shape)

# Obtener matriz de correlación y eliminar las variables poco relacionadas con el status
datos_train = pd.concat([X, y], axis=1)
corr = pd.DataFrame(datos_train.corr()['status'])

indexes = np.where(abs(corr.values[:,-1])<0.1)[0].tolist()
X = X.drop(X.columns[indexes], axis=1)
print(X.shape)

# Test del modelo en el conjunto de datos 80%
X_train, X_test, y_train, y_test = train_test_split(X, y, train_size = 0.8, random_state = None, shuffle = True)

#====================================================
# ESTA PARTE SE COMENTA DEBIDO A LA LARGA DURACIÓN (15 min aprox), puede descomentarse para su evaluación
# kernel = ['linear', 'poly', 'rbf', 'sigmoid']
# degree = [1,2,3,4,5]

# poly = []
# others = []
# print("start")
# for i in kernel:
#     if(i=='poly'):
#         for j in degree:
#             model = svm.NuSVC(kernel=i, degree=j)
#             model.fit(X_train,y_train)
#             # Hacer las predicciones
#             predictions = model.predict(X_test)
#             # Valorar el modelo
#             poly.append(accuracy_score(y_test, predictions))
#             print("Model: ", i," degree ", j, "is ready")
#     else:
#         model = svm.NuSVC(kernel=i)
#         model.fit(X_train,y_train)
#         # Hacer las predicciones
#         predictions = model.predict(X_test)
#         # Valorar el modelo
#         others.append(accuracy_score(y_test, predictions))
#         print("Model: ", i,"is ready")
    
# print(poly)
# print(others)

#=============================================

modelo = svm.NuSVC()
tini = time.time()
modelo.fit(X_train, y_train)
tfin = time.time()
print("Tiempo: ", tfin-tini)
# Hacer las predicciones
predictions = modelo.predict(X_test)
# Valorar el modelo
score = accuracy_score(y_test, predictions)
matrix = confusion_matrix(y_test, predictions)
print("Eout(0 worst, 1 best): ", score)
plot_confusion_matrix(modelo, X_test, y_test)

#Entrenar el modelo con el set entero 100% y calcular Ein
modelo = svm.NuSVC()
tini = time.time()
modelo.fit(X, y)
tfin = time.time()
predictions = modelo.predict(X)
score = accuracy_score(y, predictions)
print("Ein: ", score)
plot_confusion_matrix(modelo, X, y)