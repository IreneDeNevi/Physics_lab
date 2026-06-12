from __future__ import division
from ROOT import *
from math import *
from numpy import *
import matplotlib.pyplot as plt
import time

'''
Moto di una biglia in acqua 
forze in gioco: forza viscosa, forza peso, spinta di archimede
Graficare con e senza spinta di archimede
'''
#Dati
rho=1
rho0 = 8000
mu = 0.001
r = 0.01

massa = rho0*(4/3)*pi*pow(r,3)

n = 1000
t = linspace(0,10,n)
s = t[1]-t[0] #passo
h = array(t)
v = array(t)
v[0] = 0
h[0] = 100
hNA = array(t)
vNA = array(t)
hNA[0] = 0
vNA[0]= 0

#main

def Fv(v):
    Re = 2*rho*r/mu
    Cd = (24*v/Re) + (4*pow(abs(v),3/4)/Re) + 0.4*pow(v,2)
    return (1/2)*Cd*rho*pi*pow(r,2)

def Fp():
    g = 9.81
    return massa*g

def Sa():
    g = 9.81
    return rho*g*(4/3)*pi*pow(r,3)

def Acc(v,boolo):
    if(boolo ==0):
        return (Fv(v)+Fp())/massa
    else:
        return (Fv(v)+Fp()+Sa())/massa


def RK(step,x,v,boolo):
    k1 = s*v
    w1 = s*Acc(v,boolo)

    x_tmp = x + (k1)/2
    v_tmp = v + (w1)/2
    
    k2= s*v_tmp
    w2=s*Acc(v_tmp,boolo)

    x1 = x +k2
    v1 = v+ w2
    
    return x1,v1

boolo = 1
for i in range(1,n-1):
    ty, tv = RK(s,h[i-1],v[i-1],boolo)
    if(ty <=0):
        for j in range(i,n-1):
            h[j]=0
            v[j]=0
        break
    h[i] = ty
    v[i] = tv

boolo = 0
for i in range(1,n-1):
    ty, tv = RK(s,hNA[i-1],vNA[i-1],boolo)
    if(ty <=0):
        for j in range(i,n-1):
            hNA[j]=0
            vNA[j]=0
        break
    hNA[i] = ty
    vNA[i] = tv
    
plt.plot(t,h,t,hNA)
plt.xlabel('Tempo')
plt.ylabel('Posizione')
plt.title('Caduta di una biglia in fluido viscoso')
plt.show()


