from matplotlib import pyplot as plt
import math as m
from mpl_toolkits.mplot3d.axes3d import Axes3D, get_test_data
from matplotlib import cm
import numpy as np

T = 25
dt = 0.2
dx = dy = 0.2

def win(x1,x2,y1,y2,a,b):
    if x1<=a and a<=x2 and y1<=b and b<y2:
        return 1
    else:
        return 0

X = np.arange(-10,10,dx)
Y = np.arange(0,10,dy)

# WARNING!!! DON'T DECLARE LIKE "A=V=Z"!!!!
A = np.zeros((int(T/dt),int(10/dy),int(20/dx)))
V = np.zeros((int(T/dt),int(10/dy),int(20/dx)))
Z = np.zeros((int(T/dt),int(10/dy),int(20/dx)))

# Setting initial condition
for j in range(1,int(10/dy)):
    for i in range(1,int(20/dx)):
        Z[0][j][i] = m.sin(m.pi*X[i]/5)*m.sin(m.pi*Y[j]/10)*win(-10,-5,0,10,X[i],Y[j])

for k in range(1,int(T/dt)):
    for i in range(1,int(20/dx)-1):
        for j in range(1,int(10/dy)-1):
            A[k][j][i] = 0.49*(Z[k-1][j-1][i] + Z[k-1][j+1][i] + Z[k-1][j][i+1] + Z[k-1][j][i-1] - 4*Z[k-1][j][i])/(dx*dy)
            # The realization of a wave equation
        A[k][0][i] = A[k][-1][i] = 0
        
        for j in range(1,int(10/dy)-1):
            V[k][j][i] = V[k-1][j][i] + A[k][j][i]*dt
        V[k][0][i] = V[k][-1][i] = 0

        for j in range(1,int(10/dy)-1):
            Z[k][j][i] = Z[k-1][j][i] + V[k][j][i]*dt
        Z[k][0][i] = Z[k][-1][i] = 0


X, Y = np.meshgrid(X,Y)

for k in range(int(T/dt)):
    plt.gca().clear()
    fig = plt.figure(1,figsize=plt.figaspect(0.5))
    ax = fig.add_subplot(1, 1, 1, projection='3d')
    ax.set_zlim3d(-1.2,1.2)
    surf = ax.plot_surface(X, Y, Z[k], rstride=2, cstride=2,color = 'green')
    ax.view_init(azim=-50, elev=10)
    plt.title(round(float(k*dt),2))
    plt.pause(0.2)
