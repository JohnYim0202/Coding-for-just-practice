from matplotlib import pyplot as plt
import math
import random as rd
import numpy as np

X_Label = ['0','100','200','300','400','500','600']
X_pos = np.arange(0,700,100)

w = 1.0         # Width of bar
N=6             # Random No. 0~6 will be created.
M=100           # No. of Random Numbers that will be created
L=100000        # No. of Trials

m = np.arange(0,N*M,1)
s = np.zeros((1,N*M))
    
for j in range(L):
    b = 0
    for i in range(M):   
        a = rd.randint(0,N)
        b += a
    # Now, 'b' is sum of R.V.
    for i in range(N*M):
        if b==i:
            s[0][i] += 1

plt.figure(2, figsize=(15,5))
plt.xticks(X_pos,X_Label)
plt.bar(m,s[0],w,align = 'center',color='blue')
plt.xlim(-20,620)
plt.title('Visualizing CLT')
plt.xlabel('Sum of RV')
plt.ylabel('Frequency')
plt.show()
