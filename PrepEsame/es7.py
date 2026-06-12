from ROOT import *
from math import *
from numpy import *
from array import *
import random as rnd
from scipy import stats
'''
Una certa costante che ha valore noto (x0) pari a 10 (in qualche unit`a) viene misurata in un
esperimento caratterizzato da un errore statistico (σ) di 2 ed uno massimo (∆) di 2.
• Usando il metodo di Monte Carlo (“seme” pari a 123456789) si generino 1000 misure. Ciascuna misura `e
descritta da una variabile aleatoria x distribuita uniformemente (±∆) intorno ad una variabile x

0 a sua volta

distribuita secondo una gaussiana centrata su x0 con deviazione standard (σ).
• Si dica se la distribuzione ottenuta `e compatibile con una gaussiana centrata in x0 e con errore dato dalla
combinazione dell’errore statistico e massimo.
'''
#Dati

x0 = 10;
delta = 2;
sigma = 2;

#Main
rvs = ([])
rnd = TRandom3()
rnd.SetSeed(123456789)

h0 = TH1D("h0","",50,0,0);
for i in range(0,1000):
    xprimo = rnd.Gaus(x0,sigma);
    x = xprimo+2*(rnd.Rndm()-delta)*delta
    h0.Fill(x)
    rvs.append(x)
D,p = stats.kstest(rvs,"norm",(0,20))
print("p_value = " ,p)

f = TF1("f","[0]*TMath::Gaus(x,[1],[2],1)",0,20)
f.SetParameter(0,1)
f.SetParameter(1,x0)
f.SetParameter(2,sigma)


'''
q = 1-f.GetProb()
print("p_value secondo GetProb vale ",q)
if(q>0.5):
    print("La nostra distribuzione e gaussiana")
else:
    print("i dati non seguono una distribuzione gaussiana ")
'''

h0.Draw()
h0.Fit("f","L")
gApplication.Run(True)
