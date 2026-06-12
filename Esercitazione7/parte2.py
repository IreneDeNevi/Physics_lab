from ROOT import *
from math import *
import numpy as np
from iminuit import Minuit
from scipy import stats

h = TH1D("h","Istogramma lowstat",80,0,40)

f = TF1("f","TMath::PoissonI(x,[0])")
f.SetParameter(0,22.35) #fondo aspettato Nb
f.SetParName(0,"Nb")

c = 0
for data in open("dati_lowstat.dat",'r'):
    if float(data)>14 and float(data)<16:
        c = c+1
    h.Fill(float(data))
    
print(c)
q = 0
for i in range(0,c+1,1):
    q = q+TMath.PoissonI(i,22.35)
p = 1-q    
print(p)

