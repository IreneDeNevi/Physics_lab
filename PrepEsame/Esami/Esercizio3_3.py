from __future__ import division
from ROOT import *
from math import *
from numpy import *
from array import *
import matplotlib.pyplot as plt
import time

'''
Su un area in cui sono state tracciate linee rette parallele a distanza d viene lanciato un ago sottile di lunghezza L<d.
La probabilità che l'ago intersechi una linea è
P(intersezione) = 2L/(pi*d)
Si stimi pi con il suo errore e si grafichi il valore ottenuto in funzione del numero di lanci e si confronti con il valore nominale.
'''
#Dati
 
L = 5
d = 10

#Main

rnd = TRandom3()
rnd.SetSeed(int(time.time()))

Ntot = 10000
Nfav = 0
gr = TGraph()
for i in range(0,Ntot):
    x = rnd.Rndm()*(d/2)
    th = rnd.Rndm()*(pi/2)
    y =(L/2)*sin(th)
    if (x<y):
        Nfav = Nfav+1
        alpha = (Nfav/Ntot)
        pig = (2*L)/(alpha*d)
        gr.SetPoint(i,i,pig)

A = pow(L,2)/2 #area del quadrato
epig = A*sqrt(alpha*(1-alpha)/Ntot)
gr.Draw("AC*")
print ("Il pi greco vale ",pig)
print("Errore associato",epig)

gApplication.Run(True)
