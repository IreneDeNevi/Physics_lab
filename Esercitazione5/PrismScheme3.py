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
    A = n2-(B/lambda2**2)
    return A,B

#Main

A,B = GetAB(th0,th1,th2)

eA0,eB0 = GetAB(th0+eth/sqrt(3),th1,th2)
eA1,eB1 = GetAB(th0,th1+eth/sqrt(3),th2)
eA2,eB2 = GetAB(th0,th1,th2+eth/sqrt(3))

sigmaA = sqrt((eA0-A)**2+(eA1-A)**2+(eA2-A)**2) 

sigmaB = sqrt((eB0-B)**2+(eB1-B)**2+(eB2-B)**2) 

rnd = TRandom3()
rnd.SetSeed(int(time.time()))


h0 = TH1D("h0","",100,0,0)
h1 = TH1D("h1","",100,0,0)
h2 = TH2D("h2","",100,0,0,100,0,0)
for i in range(0,10000):
    Th0 = rnd.Gaus(th0,eth/sqrt(3))
    Th1 = rnd.Gaus(th1,eth/sqrt(3))
    Th2 = rnd.Gaus(th2,eth/sqrt(3))
    X,Y = GetAB(Th0,Th1,Th2)
    h0.Fill(X) 
    h1.Fill(Y)
    h2.Fill(X,Y)
  
c0 = TCanvas()
h0.Draw()
c1 = TCanvas()
h1.Draw()
c2 = TCanvas()
h2.Draw()



Af = h0.GetMean()
eAf = h0.GetRMS()
Bf = h1.GetMean()
eBf = h1.GetRMS()

CC= h2.GetCorrelationFactor()

print "A = ", A, "+-", sigmaA
print "B = ", B, "+-", sigmaB
print "A1 = ",Af, "+-",eAf
print " B1 = ",Bf, "+-",eBf

print "Coefficiente di Correlazione = ",CC
gApplication.Run(True)
