import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import time
from sklearn.model_selection import train_test_split
from sklearn.feature_selection import VarianceThreshold
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import Ridge
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import r2_score
from sklearn.metrics import mean_squared_error

from matplotlib import style
style.use('ggplot') or plt.style.use('ggplot')
import seaborn as sn

from sklearn.model_selection import cross_val_score

MEANINGFUL_CORRELATION_LIMIT = .95

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

def plot_temp_against(column):
    plt.figure()
    plt.ylabel("temp")
    plt.xlabel(column)
    plt.scatter(X[column], y, s=1)
    plt.show()

datos_train = pd.concat([X_train, y_train], axis=1)
corr = pd.DataFrame(datos_train.corr()['critical_temp'])
#corr.style.background_gradient(cmap='coolwarm')
corr['abs'] = np.abs(corr['critical_temp'])


corr = corr.sort_values(by='abs',ascending=False).drop('abs',axis=1).dropna().reset_index()
corr = corr.rename(columns={'index':'feature'}).loc[1:]
features = list(corr['feature'].loc[:8])

for i in features:
    plot_temp_against(i)


print("Single Column Plots")
#for column in X.columns:
#    plot_temp_against(column)
    
print("Distribution of critical_temp")
y.hist()
plt.show()
# Now lets check the correlation matrix
print("Correlation Matrix")
cm = X.corr()
lower_triangle_cm = np.tril(cm, -1)
kot = cm[abs(cm) >= MEANINGFUL_CORRELATION_LIMIT]
# plt.figure(figsize=(12,8))
# sn.heatmap(kot, cmap="Greens")
# plt.show()

sorted_cm_pairs = pd.DataFrame(lower_triangle_cm, columns=cm.columns, index=cm.index).unstack().sort_values()
correlated_pairs = sorted_cm_pairs[sorted_cm_pairs > MEANINGFUL_CORRELATION_LIMIT]
neg_correlated_pairs = sorted_cm_pairs[sorted_cm_pairs < -MEANINGFUL_CORRELATION_LIMIT]

print(
"""
Positively Correlated Pairs:
----------------------------
{}
   
   
Negatively Correlated Pairs:
----------------------------
{}
""".format(correlated_pairs, neg_correlated_pairs)
)
scores = []
X_rf = X_train[features]
for i in range(5,200):
    print(i)
    modelo = RandomForestRegressor(n_estimators=i)
    score = cross_val_score(modelo, X_rf, y_train, cv=5, scoring='neg_mean_squared_error')
    scores.append(score.mean())





print("fin")