
##Numerov method

import matplotlib.pyplot as plt
import numpy as np
import math

## La proposta di implementazione e' divisa quattro step
## Step 1 (S1)
## Step 2 (S2)
## Step 3 (S3)
## Step 4 (S4)
## il doppio ## indice un commento mentre # indica una
## comando gia' pronto, utilizzabile quando le parti
## precedenti sono completate

def V(xi):
##S1 da riempire
    V = xi**2
   # V = xi**2+0.100*xi**4 #caso armonico v = xi**2+gamma*xi**4
    return V

def b(eps,xi):
    ##S1 da riempire
    ##   calcolo di b a partire a E (eps), x e h (globale)
    b  = (2*eps-V(xi))*((h**2)/12)
    return b

def numerov(n1,n2,eps):
##S1/S2 da completare: riempe i valori di psi(xi) da i=n1 a i=n2 (compresi entrambi)
    
    psi = np.array(xi)*0  ## copio xi in psi e lo setto a zero
    ## j   = 1            ## intero che definisce incremento: indice i, i+j,i+2*j -> i, i+1, i+2
    
    ##S2     definisco indice j in modo che 1 se n2>n1, -1 se n2<n1 (vedi sign di numpy)
    
    j = np.sign(n2-n1)
    psi[n1] = 0
    psi[n1+j] = 1e-6
        
    ##S1/S2  fornisco i primi due valori di psi
    ##S1/S2  implemento Numerov
    for i in range(n1+2*j,n2+j,j):
        psi[i] = (2*psi[i-j]*(1-5*b(eps,xi[i-j])) - psi[i-2*j]*(1+b(eps,xi[i-2*j])))/(1+b(eps,xi[i]))
    return psi

def evalDerivative(eps):
    ##S3 per energia eps fornita
##   crea sequenza left e right
    global psir,psil
    psil = numerov(0,nmatch+1,eps)
    psir = numerov(n-1,nmatch-1,eps)
    
    alpha = (psil[nmatch]/psir[nmatch])
    psir = psir*alpha
    
    dpsil = (psil[nmatch+1]-psil[nmatch-1])/(2*h)
    dpsir = (psir[nmatch+1]-psir[nmatch-1])/(2*h)
    diff = (dpsir - dpsil)
##   le normalizza a nmatch
##   ...
##   calcola la differenza (diff) tra le derivate centrate (left e right) in match
##   diff = 0.
##   ...
    return diff

def findE(emin,emax,tol):
##  implementazione di bisezione gia' fornita
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

##S1 ok
#epsilon = 0.5 # o altra energia di stato definito
## Numerov deve funzionare con chiamata
##psi=numerov(0,n-1,epsilon)
##psi=numerov(n-1,0,epsilon)
## verificare con

#plt.plot(xi,psir)
#plt.plot(xi,psil)
#plt.show()

##S2 ok
##il passo precedente deve funzionare con sia con 
##  psi = numerov(0,n-1,epsilon)
##che con 
##  psi = numerov(n-1,0,epsilon)


##S3 ok
##commentare i punti precedenti (a parte le definizioni iniziali del Main code
##completare evalDerivative e poi chiamare findE 
e = findE(1.2,1.7,0.0001)
print "Energy ", e

psi = psir
psi[0:nmatch] = psil[0:nmatch]
plt.plot(xi,psi)
##plt.plot(xi,psil)
plt.show()
##S4 ok 
##copiare psr nella parte 'vuota' di psil di modo che psil rappresenti tutta psi(x)
##nell'intervallo dato o, alternativamente, copiarle entrambe in una nuova psi

