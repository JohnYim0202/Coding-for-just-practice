from matplotlib import pyplot as plt
import math

t   = [0]

Vin = [0]
Vd  = [0]
Vr  = [0]
Vc  = [0]
Vl  = [0]

Q   = [0]
Iv  = [0]
I   = [0]
A   = [0]

T  = 25         # Duaration
dt = 0.01       # Time Interval
N  = int(T/dt)  # No. of samples
w0 = 5.0        # Angular freq. of a sinusoid
R  = 1.000      # Resistor
C  = 1.00       # Capacitor
L  = 0.00       # Inductor

for cnt in range (N):
    t.append(t[-1]+dt)
    Vin.append(5.0*math.sin(w0*t[-1]))
    Iv.append((Vin[-1]-Vc[-1]-Vl[-1])/R)
    if Iv[-1]<0:
        I.append(0)
    else:
        I.append(Iv[-1])
    Q.append(Q[-1] + I[-1]*dt)
    A.append((I[-1]-I[-2])/dt)
    Vr.append(R*I[-1])
    Vl.append(L*A[-1])
    Vc.append(Q[-1]/C)
    Vd.append(Vin[-1]-Vr[-1]-Vc[-1]-Vl[-1])
    

fig=plt.figure(1) #From here, I will plot graphs.
plt.plot(t,Vin,'r',label='Applied Voltage on Circuit',linewidth = 2.0)
plt.plot(t,Vc ,'g',label='Voltage drop across a capacitor')
plt.plot(t,Vr ,'b',label='Voltage drop across a resistor')
#plt.plot(t,Vl  ,'orange',label='Voltage drop across a inductor')
plt.plot(t,Vd ,'black',label='Voltage drop across a diode',linewidth = 5.0)
plt.title('Graphs for Circuit with a diode')
plt.xlabel('Time(sec)')
plt.ylabel('Voltage(V)')
plt.grid()
plt.legend()


fig=plt.figure(2) #From here, I will plot graphs.
plt.plot(I,Vd,'ro')
plt.show()
