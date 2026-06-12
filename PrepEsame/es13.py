from ROOT import *
from math import *
from numpy import *
from array import *
import time
import matplotlib.pyplot as pl

'''
Date le misure x1 = 1 ± 0.1 e x2 = 2 ± 0.1 con coefficiente di correlazione ρ = 1 si calcoli x2 − x1 con il suo errore e si giustifichi il risultato. Graficare il risultato e il suo errore in funzione di ρ.
'''

x1 = 1
x2 = 2
errx1 = 0.1
errx2 = 0.1
rho = 1;

f = x2-x1;
rho1 = linspace(-1,1,100)
sigma = zeros(100);
for i in range (0,100):
    sigma[i] = sqrt(errx1**2+errx2**2-2*abs(rho1[i])*errx1**2*errx2**2)


pl.plot(rho1,sigma);
pl.show();
