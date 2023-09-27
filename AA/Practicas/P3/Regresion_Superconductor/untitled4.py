# -*- coding: utf-8 -*-
"""
Created on Wed Jun  2 20:56:26 2021

@author: jorge
"""
##### Imports 
#=============
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from statsmodels.stats.outliers_influence import variance_inflation_factor


##### Lectura de datos
#======================
datos = pd.read_csv('Datos/train.csv')
y = datos['critical_temp']
X = datos.drop(columns = 'critical_temp')

X_train, X_test, y_train, y_test = train_test_split(
                                X,
                                y,
                                train_size   = 0.8,
                                random_state = None,
                                shuffle      = True
                            )

datos_train = np.c_[X_train, y_train]
datos_train = pd.DataFrame(data = datos_train, columns = datos.columns)
##### Aproximación Matemática
#============================
### Obtener matriz de correlación
corr = datos_train.corr()
corr.style.background_gradient(cmap='coolwarm')

### Obtener VIF
vif = pd.DataFrame()
vif["features"] = datos_train.columns
vif["vif_Factor"] = [variance_inflation_factor(datos_train.values, i) for i in range(datos_train.shape[1])]
vif
### Analizar que variables deben quedarse y cuales no

datos_train.drop(datos_train.columns.difference(['number_of_elements','wtd_entropy_atomic_mass','entropy_fie','range_fie','wtd_std_fie','atomic_radius','wtd_entropy_atomic_radius','range_atomic_radius','std_atomic_radius','wtd_std_atomic_radius','wtd_entropy_FusionHeat','range_ThermalConductivity','std_ThermalConductivity','wtd_std_ThermalConductivity','entropy_Valence','wtd_entropy_Valence']), 1, inplace=True)
datos_train.drop(columns = ['wtd_entropy_atomic_mass','entropy_fie','wtd_entropy_atomic_radius','entropy_Valence','wtd_entropy_Valence'], inplace=True)
##### Aproximación Matemática
#============================
### Obtener matriz de correlación
corr = datos_train.corr()
corr.style.background_gradient(cmap='coolwarm')
#vif
vif = pd.DataFrame()
vif["features"] = datos_train.columns
vif["vif_Factor"] = [variance_inflation_factor(datos_train.values, i) for i in range(datos_train.shape[1])]
vif
