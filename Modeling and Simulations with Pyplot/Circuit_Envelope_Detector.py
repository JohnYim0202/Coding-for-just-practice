from matplotlib import pyplot as plt
import math

t   = [0,0]

Vin = [0,0]
Vd  = [0,0]
Vc  = [0,0]
Vr  = [0,0]

I1  = [0,0]
I2  = [0,0]
Q   = [0,0]

T  = 30         # Duaration
dt = 0.0005     # Time Interval
N  = int(T/dt)  # No. of samples
w0 = 2.0        # Angular freq. of a sinusoid

C  = 0.10       # Capacitor
R  = 3.00       # Resistor

for cnt in range (N):
    t.append(t[-1]+dt)
    Vin.append((2.0*math.sin(0.5*w0*t[-1])+5)*math.sin(15.0*w0*t[-1]))
    
    if Vin[-1] >= Vc[-1]:
        I1.append(C*(Vc[-1] - Vc[-2])/dt)
        Vc.append(Vin[-1])
    else:
        I1.append(0)
        Vc.append((Q[-1] - I2[-1]*dt)/C)

    Vr.append(Vc[-1])
    I2.append(Vr[-1]/R)
    Q.append(C*Vc[-1])
    Vd.append(Vin[-1] - Vc[-1])



# Now, I'll pass the Vc(t) through the LPF.
'''
Vs  = [0,0]
i   = [0,0]
q   = [0,0]
vc  = [0,0]

for ct in range(N):
    Vs.append(Vc[ct])
    i.append((Vs[-1] - q[-1]/C)/R)
    q.append(q[-1] + i[-1]*dt)
    vc.append(q[-1]/C)
'''

fig=plt.figure(1, figsize=(15,5)) #From here, I will plot graphs.
plt.plot(t,Vin,'r',label='Applied Voltage on Circuit',linewidth = 2.0)
plt.plot(t,Vc ,'g',label='Voltage drop across a capacitor')
plt.title('Graphs for Circuit with a diode')
plt.xlabel('Time(sec)')
plt.ylabel('Voltage(V)')
plt.grid()
plt.legend()

'''
fig=plt.figure(2, figsize=(15,5)) #From here, I will plot graphs.
plt.plot(t,Vs,'g',label='Source Voltage')
plt.plot(t,vc,'b',label='Filtered Voltage')
plt.grid()
plt.legend()
'''

plt.show()





