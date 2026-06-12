from ROOT import *
from math import *
from numpy import *
from array import *
import time

'''
In un esperimento, in una certa regione di interesse, si osservano 30 eventi (attesi 15). Si pu`o rigettare l’ipotesi nulla al 5% di significanza ? Qual `e l’intervallo al 95% C.L. del numero di eventi in eccesso ?
'''

N_eventi = 30 #segnali
N_attesi = 15 #background

#Parte uno

Prob = 0
for i in range(0,N_eventi):
    Prob += TMath.PoissonI(i,N_attesi)
p_value = 1-Prob
print("Il p_value vale ",p_value)
if (p_value <0.05 or p_value >1):
    print("Ipotesi nulla rigetta ")

#Parte due

counter=0;
Prob1=1;
while(Prob1>0.05):
    Prob1=0;
    counter +=1
    for i in range(0,N_attesi):
        Prob1 += TMath.PoissonI(i,N_attesi+counter)
        
print("Il numero di dati per avere il 95% di CL ",N_attesi+counter)
