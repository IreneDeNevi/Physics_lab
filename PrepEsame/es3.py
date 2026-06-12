from ROOT import *
from math import *
from numpy import *
from scipy import stats

q = 1.6e-19
B=0.1
V=1e3
Ma=1.66e-27

rvs=([])
h=TH1D("h","",150,0.555,0.6)

for line in open("Dati_Spettrometro.dat"):
    if len(line)>0:
        h.Fill(float(line))
        rvs.append(float(line))
D,p=stats.kstest(rvs,"norm",(0.555,0.6))
print("p_value = ",p)

f=TF1("f","[0]*([1]*TMath::Gaus(x,[2],[3],1) + (1-[1])*TMath::Gaus(x,[4],[5],1))",0.555,0.6)
f.SetParameter(0,h.GetEntries()*h.GetBinWidth(1))
f.SetParameter(1,0.05)
f.SetParameter(2,0.58)
f.SetParameter(3,0.005)
f.SetParameter(4,0.57)
f.SetParameter(5,0.0005)

h.Fit("f","L")

m1 = (f.GetParameter(2))*(q)*(B**2)/(2*V)
m2 = (f.GetParameter(4))*(q)*(B**2)/(2*V)

print("Massa atomica primo elemento = ",m1/Ma)
print("Massa atomica secondo elemento = ",m2/Ma)

h.Draw()
gApplication.Run(True)
