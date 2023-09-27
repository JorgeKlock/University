# -*- coding: utf-8 -*-
"""
Created on Tue Jun  8 00:36:39 2021

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
filename = 'DX2.txt'
with open(filename, 'r') as file:
    datos = np.array(file.read().splitlines())
    title = datos[0].split(' ')
    datos = np.array([[x for x in line.split(' ')] for line in datos[:]], dtype=object)

print(datos.shape)

for i in range (0, datos.shape[0]):
    for j in range (0, len(datos[i])):
        datos[i][j] = datos[i][j].lower()
        if (datos[i][j] == 'cero'):
            datos[i][j] = 0
        elif (datos[i][j] == 'uno'):
            datos[i][j] = 1
            
with open(filename, 'w') as file:
    for i in range (0, datos.shape[0]):
        for j in range (0, len(datos[i])):
            file.write((str)(datos[i][j]))