# -*- coding: utf-8 -*-
"""
Created on Fri Jun  4 02:29:20 2021

@author: jorge
"""
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from sklearn.model_selection import cross_val_score
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
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
datos_train = pd.concat([X_train, y_train], axis=1)
corr = pd.DataFrame(datos_train.corr()['critical_temp'])
#corr.style.background_gradient(cmap='coolwarm')
corr['abs'] = np.abs(corr['critical_temp'])


corr = corr.sort_values(by='abs',ascending=False).drop('abs',axis=1).dropna().reset_index()
corr = corr.rename(columns={'index':'feature'}).loc[1:]
features = list(corr['feature'].loc[:8])

scores = []
X_rf = X_train[features]
modelo = RandomForestRegressor(n_estimators=10, max_features="auto")
score = cross_val_score(modelo, X_rf, y_train, cv=5, scoring='neg_mean_squared_error')
scores.append(score.mean())
modelo = RandomForestRegressor(n_estimators=10, max_features="sqrt")
score = cross_val_score(modelo, X_rf, y_train, cv=5, scoring='neg_mean_squared_error')
scores.append(score.mean())
modelo = RandomForestRegressor(n_estimators=10, max_features="log2")
score = cross_val_score(modelo, X_rf, y_train, cv=5, scoring='neg_mean_squared_error')
scores.append(score.mean())
print(scores)


