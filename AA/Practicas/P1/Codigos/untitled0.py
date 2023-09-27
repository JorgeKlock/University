# -*- coding: utf-8 -*-
"""
Created on Sun Apr  4 20:34:38 2021

@author: jorge
"""

# Gradiente Descendente Estocastico
def sgd(batch_size, it, eta, error2get, x, y):
    w = np.array([0.0,0.0,0.0])
    #xy[número de la muestra][componente x:0, componente y:1]
    xy = np.c_[x,y]
    for _ in range (it):
        np.random.shuffle(xy)
        split_xy = np.split()
        for batch_number in range (0, (xy.shape[0])//batch_size):
            mini_x, mini_y = xy[batch_number*batch_size:((batch_number+1)*batch_size),0:3], xy[batch_number*batch_size:((batch_number+1)*batch_size),3]
            
            for i in range (0, 3):
                summatory_batch = 0
                for j in range (0, batch_size):
                    summatory_batch += mini_x[j][i]*(H(mini_x[j],w)-mini_y[j])
                w[i] = w[i]-eta*summatory_batch
                #print(Err(x,y,w))
                if(Err(x,y,w)<error2get):
                    print("Hemos conseguido un error inferior!")
                    break      
    return w

def sgd(batch_size, it, eta, error2get, x, y):
    w = np.array([0.0,0.0,0.0])
    #xy[número de la muestra][componente x:0, componente y:1]
    xy = np.c_[x,y]
    for _ in range (it):
        np.random.shuffle(xy)
        split_xy = np.split()
        for batch_number in range (0, (xy.shape[0])//batch_size):
            mini_x, mini_y = xy[batch_number*batch_size:((batch_number+1)*batch_size),0:3], xy[batch_number*batch_size:((batch_number+1)*batch_size),3]
            
            grad = np.array(H(mini_x,w).T-mini_y)
            mini_x = np.array(mini_x)
            sumatorio = (mini_x*grad).sum(axis=1)
            w = w-eta*sumatorio
                #print(Err(x,y,w))
            if(Err(x,y,w)<error2get):
                print("Hemos conseguido un error inferior!")
                break      
    return w

def H(x,w):
    matrix = np.matrix(x*w)
    return matrix.sum(axis=1)

def Err(x,y,w):
    return ((np.power(H(x,w).T-y,2)).sum())/x.shape[0]



# Gradiente Descendente Estocastico VERSION QUE FUNCIONABA CON ERROR 0.9
def sgd(n_batches, it, eta, error2get, x, y):
    w = np.array([0.0,0.0,0.0])
    #xy[número de la muestra][componente x:0, componente y:1]
    xy = np.c_[x,y]
    for _ in range (it):
        np.random.shuffle(xy)
        split_xy = np.array_split(xy, n_batches)
        #print(split_xy)
        for b in range (0, n_batches):
            mini_x, mini_y = split_xy[b][:,0:3], split_xy[b][:,3]
            for i in range (0, 3):
                summatory_batch = 0
                for j in range (0, mini_x.shape[0]):
                    summatory_batch += mini_x[j][i]*(H(mini_x[j],w)-mini_y[j])
                w[i] = w[i]-eta*summatory_batch
                if(Err(x,y,w)<error2get):
                    print("Hemos conseguido un error inferior!")
                    break      
    return w

#Gradiente Descendente Estocastico No lineal VERSION QUE FUNCIONABA CON ERROR 1
def sgd_nl(n_batches, it, eta, error2get, x, y):
    w = np.array([0.0,0.0,0.0,0.0,0.0,0.0])
    #xy[número de la muestra][componente x:0, componente y:1]
    xy = np.c_[x,y]
    for _ in range (it):
        np.random.shuffle(xy)
        split_xy = np.array_split(xy, n_batches)
        #print(split_xy)
        for b in range (0, n_batches):
            mini_x, mini_y = split_xy[b][:,0:6], split_xy[b][:,6]
            for i in range (0, 6):
                summatory_batch = 0
                for j in range (0, mini_x.shape[0]):
                    summatory_batch += mini_x[j][i]*(H(mini_x[j],w)-mini_y[j])
                w[i] = w[i]-eta*summatory_batch
                if(Err_nl(x,y,w)<error2get):
                    print("Hemos conseguido un error inferior!")
                    break      
    return w
#Funcion de error VERSION QUE FUNCIONABA CON ERROR 0.9
def Err(x,y,w):
    summatory = 0
    for _ in range(0, x.size//3):
        summatory += np.power(H(x[_],w)-y[_],2)
    return (1/(x.size//3))*summatory
#Funcion sgd no lineal VERSION QUE FUNCIONABA CON ERROR 0.9
def sgd_nl(n_batches, it, eta, error2get, x, y):
    w = np.array([0.0,0.0,0.0,0.0,0.0,0.0])
    #xy[número de la muestra][componente x:0, componente y:1]
    xy = np.c_[x,y]
    for _ in range (it):
        np.random.shuffle(xy)
        split_xy = np.array_split(xy, n_batches)       
        for b in range (0, n_batches):
            mini_x, mini_y = split_xy[b][:,0:6], split_xy[b][:,6]
            grad = np.array(H(mini_x,w).T-mini_y)
            mini_x = np.array(mini_x)
            #print(grad)
            sumatorio = (mini_x*grad.T).sum(axis=0)
            w = w-eta*sumatorio
            if(Err(x,y,w)<error2get):
                print("Hemos conseguido un error inferior!")
                break      
    return w
