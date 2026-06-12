from   ROOT import *
from   math import *
import time


#Parametri e misure
lambda1 = 579.1
lambda2 = 404.7
alpha   = pi/3
th0     = 1.5701
th1     = 2.6958
th2     = 2.7904
eth     = 0.0005

#Funzione 
def GetAB(th0,th1,th2):                      
    n1 = sin((th1-th0+alpha)/2)/(sin(alpha/2))
    n2 = sin((th2-th0+alpha)/2)/(sin(alpha/2))
    B = (n1-n2)/((1/lambda1**2)-(1/lambda2**2))
    A = n2 - (B/lambda2**2)
    return A,B

#Main
A,B = GetAB(th0,th1,th2)

eA0,eB0 = GetAB(th0+eth/sqrt(3),th1,th2)
eA1,eB1 = GetAB(th0,th1+eth/sqrt(3),th2)
eA2,eB2 = GetAB(th0,th1,th2+eth/sqrt(3))

#Verifica che le relazioni siano lineari
eA0r,eB0r = GetAB(th0-eth/sqrt(3),th1,th2)
eA1r,eB1r = GetAB(th0,th1-eth/sqrt(3),th2)
eA2r,eB2r = GetAB(th0,th1,th2-eth/sqrt(3))
CheckA0 = abs(eA0-eA0r)
CheckB0 = abs(eB0-eB0r)
CheckA1 = abs(eA1-eA1r)
CheckB1 = abs(eB1-eB1r)
CheckA2 = abs(eA2-eA2r)
CheckB2 = abs(eB2-eB2r)

sigmaA = sqrt((eA0-A)**2+(eA1-A)**2+(eA2-A)**2)
sigmaB = sqrt((eB0-B)**2+(eB1-B)**2+(eB2-B)**2)

print "A = ",A, "+-", sigmaA
print "B = ",B, "+-", sigmaB
