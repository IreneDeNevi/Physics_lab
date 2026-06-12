
##Numerov method

import matplotlib.pyplot as plt
import numpy as np
import math


def V(xi):
    
    V = xi**2
   # V = xi**2+0.100*xi**4 #caso armonico v = xi**2+gamma*xi**4
    return V

def b(eps,xi):

    b  = (2*eps-V(xi))*((h**2)/12)

    return b

def numerov(n1,n2,eps):

    psi = np.array(xi)*0  
    j = np.sign(n2-n1)
    psi[n1] = 0
    psi[n1+j] = 1e-6

    for i in range(n1+2*j,n2+j,j):
        psi[i] = (2*psi[i-j]*(1-5*b(eps,xi[i-j])) - psi[i-2*j]*(1+b(eps,xi[i-2*j])))/(1+b(eps,xi[i]))
    return psi


def evalDerivative(eps):

    global psir,psil
    
    psil = numerov(0,nmatch+1,eps)
    psir = numerov(n-1,nmatch-1,eps)
    
    alpha = (psil[nmatch]/psir[nmatch])
    psir = psir*alpha
    
    dpsil = (psil[nmatch+1]-psil[nmatch-1])/(2*h)
    dpsir = (psir[nmatch+1]-psir[nmatch-1])/(2*h)
    diff = (dpsir - dpsil)

    return diff;

def findE(emin,emax,tol):
    while (emax-emin>tol):
        emed = (emin+emax)/2
        if evalDerivative(emin)*evalDerivative(emed)<0:
            emax = emed
        else:
            emin = emed
    return (emin+emax)/2;





## Main code
n       = 14000
nmatch  = 10000
xi      = np.linspace(-7.,7,n)
h       = xi[1]-xi[0]

e = findE(0.2,0.7,0.0001)
print ("Energy", 2*e)
psi =  np.array(xi)
for i in range (0,n,1):
    if i <nmatch :
        psi[i] = psil[i]
    else:
        psi[i] = psir[i]

plt.plot(xi,psi)
plt.show()



for i in range(0,15,1):
    emax = 10
    a = np.linspace(0,emax,20)
    if evalDerivative(i)*evalDerivative(i+1)<0:
        print("Energia stato fisico",findE(a[i],a[i+1],0.005))
        
m = 0
for i in range(0,n,1):
    m = m + (psil[i]*h)
   
    

plt.plot(xi,psil/m)

plt.show()
