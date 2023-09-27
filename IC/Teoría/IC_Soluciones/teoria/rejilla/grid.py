import numpy as np

# Input grid
A = np.array([
    [1,3,4,5,1,2,3,1,4,2,4,4,3,4,4,3,2,3,4,2],
    [3,4,5,5,5,1,2,4,1,3,5,1,5,5,4,5,5,4,1,4],
    [3,4,3,3,4,3,5,3,5,4,3,1,2,4,3,3,2,3,2,5],
    [3,3,4,4,1,4,2,3,1,2,4,2,3,4,2,5,4,3,2,2],
    [3,3,4,4,3,2,1,3,2,2,5,2,2,3,2,3,4,3,2,1]
    ])

def dist(u, v):
    dst = 0
    for i in range(len(u)):
        dst += abs(u[i]-v[i])
    return dst

# Gets distance matrix
dist_matrix = np.full([A.shape[1], A.shape[1]], np.inf)

for i in range(A.shape[1]-1):
    for j in range(1 + i, A.shape[1]):
         dist_matrix[(i, j)] = dist_matrix[(j, i)] = dist(A[:,i], A[:,j])

# List were we are storing all the matrix that we are calculating
matrixes = [dist_matrix]

agrupations = {}
for i in range(dist_matrix.shape[0]):
    agrupations[i] = [i]

for k in range(15):
    """
    last: Matriz actual (con las distancias entre las agrupaciones hasta esta iteración)
    min_dist: Mínima distancia en la matriz actual
    min_ind: Una de las posiciones donde se alcanza el minimo de la matriz (agrupación que vamos a realizar).
    agrupations: Diccionario con la correspondencia entre las filas de la matriz original de distancias y la actual.
        agrupations[i] = [a, b, c] significa que la fila y columna y i-ésima representa las filas a, b y c de la matriz de distancias original
    """

    last = matrixes[-1]
    print(last)
    min_dist = np.amin(last)
    mins_ind = np.where(last == min_dist)
    min_ind = [mins_ind[0][0], mins_ind[1][0]]

    new = np.full([last.shape[0]-1, last.shape[1]-1], np.inf)

    aux = np.delete(last, min_ind, 0)
    aux = np.delete(aux, min_ind, 1)
    new[:-1, :-1] = aux

    row = 0
    for i in range(last.shape[0]):
        if i == min_ind[0] or i == min_ind[1]:
            continue
        new[row, -1] = min(last[i, min_ind[0]], last[i, min_ind[1]])
        row += 1

    matrixes.append(new)

    new_agrup = {}
    col = 0
    for i in range(new.shape[0]):
        if i < new.shape[0] - 1:
            if col in min_ind:
                col += 1
            new_agrup[i] = agrupations[col]
        else:
            new_agrup[i] = agrupations[min_ind[0]] + agrupations[min_ind[1]]
        col += 1

    print("---------- Iteración", k+1, "----------")
    print("- Agrupación", agrupations[min_ind[0]], " + ", agrupations[min_ind[1]])
    print("- Distancia mínima", min_dist)

    agrupations = new_agrup
    print(agrupations)
    print()
