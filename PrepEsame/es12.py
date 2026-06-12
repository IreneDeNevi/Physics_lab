from ROOT import *
from math import *
from numpy import *
from array import *
import time

rnd = TRandom3()
rnd.SetSeed(int(time.time()))

Ntot = 1000
h = TH1D("h","",70,0,40)
lam = 1;
mu = 10

for i in range (0,Ntot):
    counter=0; #N
    S = 0;     #Somma
    while(S<mu):
        x = -1./lam*log(1-rnd.Rndm())
        S = S+x;
        counter = counter+1
    h.Fill(counter-1)
       
f = TF1("f","[1]*TMath::Poisson(x,[0])",0,40)
f.SetParameter(0,10)
f.SetParName(0,",mu")
f.SetParameter(1,h.GetEntries()*h.GetBinWidth(1))
f.SetParName(1,"normalizzazione")



h.Draw()
h.Fit("f","L")

gApplication.Run(True)
