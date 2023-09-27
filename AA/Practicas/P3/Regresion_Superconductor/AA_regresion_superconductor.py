# -*- coding: utf-8 -*-
"""
Created on Sun May 23 15:50:36 2021

@author: jorge
"""
#====== Librerías Generales
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
#====== Librerías Preprocesamiento
from sklearn.model_selection import train_test_split
from sklearn.feature_selection import VarianceThreshold
from sklearn import preprocessing
#====== Librerías Modelos
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import Ridge
from sklearn.ensemble import RandomForestRegressor
#====== Librerías Evaluación
from sklearn.metrics import r2_score
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import cross_val_score

def normalize(X):
    scaler = preprocessing.StandardScaler().fit(X)
    X_normalized = scaler.transform(X) 
    return X_normalized
def get_redundant_pairs(df):
    '''Get diagonal and lower triangular pairs of correlation matrix'''
    pairs_to_drop = set()
    cols = df.columns
    for i in range(0, df.shape[1]):
        for j in range(0, i+1):
            pairs_to_drop.add((cols[i], cols[j]))
    return pairs_to_drop

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

# Normalizamos los datos dividiendo por la media para garantizar un criterio de igualdad al hacer la eliminación
# por VarianceThreshold
X_normalized = X_train/X_train.mean()
    #Creamos y ajustamos la poda
selector = VarianceThreshold(0.05)
selector.fit(X_normalized)
indexes = selector.get_support()
    #Aplicamos la poda con los índices obtenidos
X_train = X_train.loc[:,indexes]
X_test = X_test.loc[:,indexes]

# Obtener matriz de correlación
datos_train = pd.concat([X_train, y_train], axis=1)
corr = datos_train.corr()
# Eliminar aquellos elementos que estén correlacionados con la variable Tc en menos de 0.1 [col 58]
indexes = np.where(abs(corr.values[:,-1])<0.1)[0].tolist()
X_train = X_train.drop(X_train.columns[indexes], axis=1)
X_test = X_test.drop(X_test.columns[indexes], axis=1)

# Eliminar aquellos elementos que estén correlacionados entre sí en más de 0.8
corr = X_train.corr()
correlated_features = set()
for i in range(len(corr.columns)):
    for j in range(i):
        if abs(corr.iloc[i, j]) > 0.9:
            colname = corr.columns[i]
            correlated_features.add(colname)
correlated_features = list(correlated_features)
X_train = X_train.drop(columns = correlated_features)
X_test = X_test.drop(columns = correlated_features)

# Observación del heatmap final
corr = X_train.corr()
corr.style.background_gradient(cmap='coolwarm')

##### Testear cuantas variables usar de entre las relevantes
#===========================================================
datos_train = pd.concat([X_train, y_train], axis=1)
corr = pd.DataFrame(datos_train.corr()['critical_temp'])
#corr.style.background_gradient(cmap='coolwarm')
corr['abs'] = np.abs(corr['critical_temp'])
corr = corr.sort_values(by='abs',ascending=False).drop('abs',axis=1).dropna().reset_index()

corr.style.background_gradient(cmap='coolwarm')

print("Tenga paciencia, esto puede durar unos segundos")

# Ir usando iterativamente cada vez más variables para el modelo hasta las N finales
model = LinearRegression()
corr = corr.rename(columns={'index':'feature'}).loc[1:]
total_r2 = []
total_rmse = []
models = {LinearRegression(), Ridge(), RandomForestRegressor(max_depth = 8, n_estimators = 10)}
model_name = []
for i_model in models:
    r2 = []
    rmse = []
    model_name.append(i_model)
    for row in corr.index:
        model = i_model
        features = list(corr['feature'].loc[:row])
        X_features = X_train[features]
        X_train2, X_test2, y_train2, y_test2 = train_test_split(X_features, y_train, test_size=0.3, random_state=10)
        # Entrenar el modelo
        model.fit(X_train2,y_train2)
        # Hacer las predicciones
        predictions = model.predict(X_test2)
        # Valorar el modelo
        r2.append(r2_score(y_test2, predictions))
        rmse.append(mean_squared_error(y_test2, predictions, squared=False)) 
    total_r2.append(r2)
    total_rmse.append(rmse)
    print("Model: ",i_model,"is ready")
    
#Graficar los resultados de rmse y r2
fig, ax = plt.subplots(figsize=(12,8))
fig2, ax2 = plt.subplots(figsize=(12,8))
for i in range(0,len(models)):    
    ax.plot(np.arange(0,corr.index.size)+1, total_r2[i], label = model_name[i])
    ax2.plot(np.arange(0,corr.index.size)+1, total_rmse[i], label = model_name[i])
    ax.set(title='R2 coefficient')
    ax2.set(title='RMS error')
    legend = ax.legend(loc="lower right", shadow=True, fontsize=8)
    legend = ax2.legend(loc="upper right", shadow=True, fontsize=8)
plt.show()

#Podemos ver como el mejor resultado lo obtiene random forest con las 8 variables principales.
#Si bien es el modelo más lento, es el que mejor nos permitirá entender el problema ya que 
#es el que mejor ajusta la función objetivo

# Usar validación cruzada para comprobar el mejor ajuste posible usando M variables
# Primero que nada cogemos nuestra X_train original (los de test no deben contaminarse en ningún momento)
# y extraemos las M características más importantes de ellos
features = list(corr['feature'].loc[:8])
X_rf = X_train[features]
X_test_f = X_test[features]
print("=====Características relevantes======")
print(features)

#Esta parte de código permanece comentada debido a la alta cantidad de tiempo que requiere (1-2 horas aprox.) 
#Los resultados de su ejecución se muestran en la memoria
    # Decidir la cantidad de estimators (árboles)
#scores = []
#for i in range(5,200):
#    print(i)
#    modelo = RandomForestRegressor(n_estimators=i)
#    score = cross_val_score(modelo, X_rf, y_train, cv=5, scoring='neg_mean_squared_error')
#    scores.append(score.mean())

#plt.plot(np.arange(5,200), scores)   
    
    
    # Decidir la cantidad máxima de features (auto, sqrt, log2)
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
print("========= SCORES ===========")
print("Valores de error negativo-cuadrático-medio de auto, sqrt y log2: ", scores)

# Hacemos el fit con el conjunto de X_train completo (M características)
modelo = RandomForestRegressor(n_estimators=75, max_features='sqrt').fit(X_rf,y_train)
# Ordenamos los elementos de X_train mediante la variable Tc de menor a mayor
XY = np.c_[X_test_f, y_test]
XY = XY[XY[:,-1].argsort()]
y_test = XY[:,-1]
X_test_rf = XY[:,0:-1]
# Hacemos la predicción
predictions = modelo.predict(X_test_rf)
# Graficamos las predicciones y los valores originales de cada elemento (siguiendo el orden declarado anteriormente)
fig, ax = plt.subplots()
ax.scatter(np.arange(1,X_test.shape[0]+1), predictions, color = "green", label="predicciones obtenidas")
ax.scatter(np.arange(1,X_test.shape[0]+1), y_test, color = "red", label="valores originales")
legend = ax.legend(loc="upper right", shadow=True)
ax.set(title='Predicciones y Valores reales', xlabel='Elemento i-esimo', ylabel='Tc')
plt.show()
# Graficamos las predicciones frente a los valores reales
fig, ax = plt.subplots()
ax.scatter(y_test, predictions)
ax.set(title='Dispersión del Error', xlabel='Tc Real', ylabel='Tc Predicción')
plt.show()

plt.figure()
print("==== Valoración del modelo entrenado con 70% del DataSet ====")
print("Eout: ", mean_squared_error(y_test, predictions, squared=False))
sorted_idx = modelo.feature_importances_.argsort()
plt.barh(X_rf.columns[sorted_idx], modelo.feature_importances_[sorted_idx])

# Entrenamos ahora el modelo con el 100% de los datos
X_rf_full = X[features]
modelo = RandomForestRegressor(n_estimators=75, max_features='sqrt').fit(X_rf_full,y)
predictions = modelo.predict(X_rf_full)
print("==== Valoración del modelo entrenado con 100% del DataSet ====")
print("Ein: ", mean_squared_error(y, predictions, squared=False))
fig, ax = plt.subplots()
ax.scatter(y, predictions)
ax.set(title='Dispersión del Error', xlabel='Tc Real', ylabel='Tc Predicción')
plt.show()

