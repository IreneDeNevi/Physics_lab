from __future__ import division
from ROOT import *
from math import *
from array import *
from numpy import *
import matplotlib.pyplot as plt
import time

#Parte uno
def Pearson(h):
    chi2 = 0.0
    N = 11 #numero di conteggi
    mean = h.GetMean()
    Ntot = h.GetEntries()
    for i in range(0,N):
        nu = Ntot*TMath.Poisson(h.GetBinCenter(i+1),mean) #eventi con distribuzione poissoniana che centro nel bin 
        chi2 += pow(h.GetBinCenter(i)-nu,2)/nu
    return chi2

h = TH1D ("h","",11,-0.5,10.5)
for line in open ("Conteggi.dat"):
    line_str = line.split()
    data = int(line_str[0])
    f=  int(line_str[1])
    for j in range(0,f):
        h.Fill(data)


h.Draw()
#Chi quadro di pearson
CP = TF1("CP","(1/([1]*pow(2,[0]*0.5)))*(pow(x,[1]-0.5)*exp(-0.5*x**2")
CP.SetParameter(0,11)
CP.SetParameter(1,TMath.Gamma(0.5*11))

CS = Pearson(h) #CHI SQUARE
p_value = 1-CP.Integral(0,CS)
print("IL p_value vale ",p_value)

#Parte due
gr = TF1("gr","[0]*TMath::Poisson(x,[1])")
gr.SetParameter(0,h.GetEntries()*h.GetBinWidth(1))
gr.SetParameter(1,h.GetMean())
h.Fit("gr","L")

print("il pvalue vale ",gr.GetProb())
gPad.Update()
gApplication.Run(True)
