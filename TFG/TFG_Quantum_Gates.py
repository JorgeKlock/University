#!/usr/bin/env python
# coding: utf-8

# ## TRABAJO FIN DE GRADO (Apéndice: puertas cuánticas)
# ### Grado en Ingeniería Informática - Universidad de Granada
# 
# # Los límites de la computación cuántica para la resolución de problemas NP
# 
# 
# ##### Autor: Jorge Gangoso Klock
# ##### Tutor1: Jesús García Miranda
# ##### Tutor2: Antonio M. Lallena Rojo

# Este documento incorpora algunas de las pruebas que se han realizado empleando puertas cuánticas básicas. Su funcionamiento está descrito en la memoria y sólo se muestran algunas de ellas. Para cambiar la puerta sobre la que se realizan pruebas basta con modificar cualquier circuito y añadir/quitar las puertas que convenga.

# In[1]:


## Test de las quantum gates 
from qiskit import *
from qiskit.tools.visualization import circuit_drawer
from qiskit.tools.visualization import plot_bloch_multivector
from qiskit.quantum_info import state_fidelity
from qiskit.quantum_info import Statevector
import numpy as np

q_s = QuantumRegister(1)
q = QuantumRegister(2)


# In[13]:


# P - Gate
qc = QuantumCircuit(q_s)
qc.h(q_s)
qc.p(np.pi/4, q_s)

simulator = Aer.get_backend('statevector_simulator')
result = execute(qc, backend=simulator).result()
statevector = result.get_statevector()

qc.draw(output = 'mpl')


# In[14]:


plot_bloch_multivector(statevector)


# In[15]:


backend = BasicAer.get_backend('unitary_simulator')
job = backend.run(transpile(qc, backend))
job.result().get_unitary(qc, decimals=3)


# In[2]:


# Controlled Z - Gate
qc = QuantumCircuit(q)
qc.x(q[1])
qc.x(q[0])
qc.cz(q[1],q[0])

simulator = Aer.get_backend('statevector_simulator')
result = execute(qc, backend=simulator).result()
statevector = result.get_statevector()

qc.draw(output = 'mpl')


# In[3]:


plot_bloch_multivector(statevector)


# In[4]:


backend = BasicAer.get_backend('unitary_simulator')
job = backend.run(transpile(qc, backend))
job.result().get_unitary(qc, decimals=3)


# In[5]:


# SWAP - Gate
qc = QuantumCircuit(q)
qc.x(q[1])
qc.swap(q[0],q[1])

simulator = Aer.get_backend('statevector_simulator')
result = execute(qc, backend=simulator).result()
statevector = result.get_statevector()

qc.draw(output = 'mpl')


# In[6]:


plot_bloch_multivector(statevector)


# In[7]:


backend = BasicAer.get_backend('unitary_simulator')
job = backend.run(transpile(qc, backend))
job.result().get_unitary(qc, decimals=3)


# In[19]:


# Controlled Hadamard - Gate
qc = QuantumCircuit(q)
qc.x(q[1])
qc.ch(q[1],q[0])

simulator = Aer.get_backend('statevector_simulator')
result = execute(qc, backend=simulator).result()
statevector = result.get_statevector()

qc.draw(output = 'mpl')


# In[20]:


plot_bloch_multivector(statevector)


# In[21]:


backend = BasicAer.get_backend('unitary_simulator')
job = backend.run(transpile(qc, backend))
job.result().get_unitary(qc, decimals=3)

