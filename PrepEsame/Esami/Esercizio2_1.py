from ROOT import *
from math import *

Mu = 3
N = 0
pvalue = 1

while pvalue > 0.05:
    val = 0
    for i in range(0, N+1):
        val = val + TMath.Poisson(i, 3)

    pvalue = 1 - val
    N = N+1

print("N minimo per escludere l'ipotesi nulla = ", N-2)

pvalue = 0
ns = 0
h = 0.001

while pvalue < 0.05:
    pvalue = TMath.Poisson(1,ns)
    ns = ns + h

print("Il limite superiore e'", ns)
