# -*- coding: utf-8 -*-
"""
Created on Fri Jun  4 20:16:05 2021

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


# Escalar los datos
y = datos['status']
X = datos
X = datos.drop(columns = 'status')
# Obtener matriz de correlación
datos_train = pd.concat([X, y], axis=1)
corr = datos_train.corr()

print(corr)