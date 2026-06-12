from __future__ import division
from ROOT import *
from math import *
from numpy import *
import matplotlib.pyplot as plt
import time

#Parte uno
h = TH1D("h","istogramma lowstat",2,0.,10)
for line in open("lowstat.dat"):
    if len(line)>0:
        h.Fill(float(line))

        
f = TF1("f","[0]*(1/2)*exp(-x/2.)",0.,10)
f.SetParameter(0,h.Integral(0,10));
c0 = TCanvas()
h.Fit("f")
p_value = f.GetProb()
print("p_value =",p_value)


#Parte due
h1 = TH1D("h1","istogramma highstat",90,0.,0.)
for line in open("highstat.dat"):
    if len(line)>0:
        h1.Fill(float(line))

c1 = TCanvas()
f1 = TF1("f1","[0]*([3]/[1]*exp(-x/[1])+(1-[3])/[2]*exp(-x/[2]))",0.,0.)
f1.FixParameter(0,1)
f1.SetParName(0,"Normalizzazione")
f1.SetParameter(1,2)
f1.SetParName(1,"tau1")
f1.SetParameter(2,350)
f1.SetParName(2,"tau2")
f1.SetParameter(3,0.2)
f1.SetParName(3,"par3")

h1.Fit("f1","0MULTI")

f1.SetParameter(0,h.GetEntries()*h.GetBinWidth(1))
f1.Draw("SAME")

tau1 = f1.GetParameter(1)
etau1 = f1.GetParError(1)
tau2 = f1.GetParameter(2)
etau2 = f1.GetParError(2)
p = 100*(f1.GetParameter(3))
q = 100-p
print("tau1 = ",tau1)
print("etau1 = ",etau1)
print("tau2 = ",tau2)
print("etau2 = ",etau2)
print("tau1 ha percentuale ",p)
print("tau2 ha percentuale ",q)
gApplication.Run(True)
