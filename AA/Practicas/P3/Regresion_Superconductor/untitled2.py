# -*- coding: utf-8 -*-
"""
Created on Sun May 23 19:05:19 2021

@author: jorge
"""
import numpy as np
import pandas as pd
# Gráficos
# ==============================================================================
import matplotlib.pyplot as plt
import matplotlib.font_manager
from matplotlib import style
style.use('ggplot') or plt.style.use('ggplot')

#####Extraer datos estadísticos a fichero
#file = open('output.txt', 'w')
#pd.set_option('display.max_columns', None)
#file.write(str(X.describe(percentiles=None)))
#file.close()

with open('train.csv', 'r') as file:
    #datos = [[x for x in line.split(',')] for line in file]
    datos = np.array(file.read().splitlines())
    title = datos[0].split(',')
    #title = [[str(x) for x in line.split(',')] for line in datos[0]]
    datos = np.array([[float(x) for x in line.split(',')] for line in datos[1:]])

#Title = datos[0] contiene los titulos de las columnas
#Datos [0:21262] contiene los valores de las [0:80] características, y de Y (columna 81)
#print(title)
#print(datos[21262][81])


fig, ax = plt.subplots()
for i in range(0, 5):
    ax.scatter(datos[:][i], datos[:][81], label=title[i], marker="+")
plt.xlabel("Características base")
plt.ylabel("Temperatura Critica")
legend = ax.legend(loc="lower right", shadow=True, fontsize="x-small")
plt.show()

print("-----------Medias---------")
for i in range (0,80):
    media = np.mean(datos[:,i])
    print(title[i],": ", media)

print("-----------Varianzas---------")
for i in range (0,80):
    varianza = np.var(datos[:,i])
    print(title[i],": ", varianza)


#######################################
#COSAS
#######################################


# Entrenamiento modelo PCA con escalado de los datos
# ==============================================================================
pca_pipe = make_pipeline(StandardScaler(), PCA())
pca_pipe.fit(datos)

# Se extrae el modelo entrenado del pipeline
modelo_pca = pca_pipe.named_steps['pca']

# Se combierte el array a dataframe para añadir nombres a los ejes.
frame = pd.DataFrame(
    data    = modelo_pca.components_,
    columns = datos.columns,
    index   = ['PC'+str(i) for i in range (0,81)]
)
print(frame)

# Heatmap componentes
# ==============================================================================
fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(4, 2))
componentes = modelo_pca.components_
plt.imshow(componentes.T, cmap='viridis', aspect='auto')
plt.yticks(range(len(datos.columns)), datos.columns)
plt.xticks(range(len(datos.columns)), np.arange(modelo_pca.n_components_) + 1)
plt.grid(False)
plt.colorbar();

# Porcentaje de varianza explicada por cada componente
# ==============================================================================
print('----------------------------------------------------')
print('Porcentaje de varianza explicada por cada componente')
print('----------------------------------------------------')
print(modelo_pca.explained_variance_ratio_)

fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(6, 4))
ax.bar(
    x      = np.arange(modelo_pca.n_components_) + 1,
    height = modelo_pca.explained_variance_ratio_
)

for x, y in zip(np.arange(len(datos.columns)) + 1, modelo_pca.explained_variance_ratio_):
    label = round(y, 2)
    ax.annotate(
        label,
        (x,y),
        textcoords="offset points",
        xytext=(0,10),
        ha='center'
    )

ax.set_xticks(np.arange(modelo_pca.n_components_) + 1)
ax.set_ylim(0, 1.1)
ax.set_title('Porcentaje de varianza explicada por cada componente')
ax.set_xlabel('Componente principal')
ax.set_ylabel('Por. varianza explicada');

# Porcentaje de varianza explicada acumulada
# ==============================================================================
prop_varianza_acum = modelo_pca.explained_variance_ratio_.cumsum()
print('------------------------------------------')
print('Porcentaje de varianza explicada acumulada')
print('------------------------------------------')
print(prop_varianza_acum)

fig, ax = plt.subplots(nrows=1, ncols=1, figsize=(6, 4))
ax.plot(
    np.arange(len(datos.columns)) + 1,
    prop_varianza_acum,
    marker = 'o'
)

for x, y in zip(np.arange(len(datos.columns)) + 1, prop_varianza_acum):
    label = round(y, 2)
    ax.annotate(
        label,
        (x,y),
        textcoords="offset points",
        xytext=(0,10),
        ha='center'
    )
    
ax.set_ylim(0, 1.1)
ax.set_xticks(np.arange(modelo_pca.n_components_) + 1)
ax.set_title('Porcentaje de varianza explicada acumulada')
ax.set_xlabel('Componente principal')
ax.set_ylabel('Por. varianza acumulada');

# Proyección de las observaciones de entrenamiento
# ==============================================================================
proyecciones = pca_pipe.transform(X=datos)
proyecciones = pd.DataFrame(
    proyecciones,
    columns = ['PC'+str(i) for i in range (0,81)],
    index   = datos.index
)
print(proyecciones.head())

# Correlación entre columnas numéricas
# ==============================================================================
datos = pd.read_csv('train.csv')
datos = datos.drop(columns = datos.columns[81])

def tidy_corr_matrix(corr_mat):
    '''
    Función para convertir una matriz de correlación de pandas en formato tidy
    '''
    corr_mat = corr_mat.stack().reset_index()
    corr_mat.columns = ['variable_1','variable_2','r']
    corr_mat = corr_mat.loc[corr_mat['variable_1'] != corr_mat['variable_2'], :]
    corr_mat['abs_r'] = np.abs(corr_mat['r'])
    corr_mat = corr_mat.sort_values('abs_r', ascending=False)
    
    return(corr_mat)

corr_matrix = datos.select_dtypes(include=['float64', 'int']) \
              .corr(method='pearson')
print(tidy_corr_matrix(corr_matrix))


#ELECCION DE HIPERPARAMETROS USANDO EL GRIDCV
#param_grid = [{'K': [15,16,17,18,19,20], 'landa': [0.01,0.001,0.0001]}]
parameters = {'fit_intercept':[True,False], 'normalize':[True,False], 'copy_X':[True, False]}
model = LinearRegression()
model.fit(X_train, y_train)
# print prediction results without CV
predictions = model.predict(X_test) 
grid = GridSearchCV(estimator= LinearRegression(), param_grid=parameters, cv=5)
# fitting the model for grid search 
grid.fit(X_train, y_train) 
 
# print best parameter after tuning 
print(grid.best_params_) 
grid_predictions = grid.predict(X_test) 