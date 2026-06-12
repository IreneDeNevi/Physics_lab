from ROOT import *
from math import *
import numpy as np
from iminuit import Minuit
from scipy import stats



sup = 0 #numero di eventi
h = TH1D("h","Istogramma highstat",50,0,40)

f = TF1("f","TMath::PoissonI(x,[0])")
f.SetParameter(0,44.7) #fondo aspettato Nb
f.SetParName(0,"Nb")

Nobs = 0
for data in open("dati_highstat.dat",'r'):
    if float(data)>14 and float(data)<16:
        Nobs=Nobs+1
        
    h.Fill(float(data))
    
print("Il valore di Nobs vale "),Nobs

pvalue = 1
while (pvalue >0.05):
    pvalue = 0
    for i in range(0,Nobs+1,1):
        pvalue  = pvalue+TMath.PoissonI(i,44.7+sup)
    sup = sup+1
    
        

print ("Il pvalue associato alla Poissoniana vale "),pvalue
print("Il numero di eventi  associato alla Poissoniana vale "),sup


#UnbinnedFit
tree = TTree()
tree.ReadFile("dato_highstat.dat","t")
g = TF1("g","[0]*([1]*TMath::Gaus(x,[2],[3],1)+[5]*exp(-x/[4]))",0,50)

#g.SetParameter(0,1)  #Unbinned
area = h.GetEntries()*h.GetBinWidth(1)
g.SetParameter(0,area)  #Binned
g.SetParameter(1,0.1)
g.SetParameter(2,15) #valore medio
g.SetParameter(3,0.5) #sigma
g.SetParameter(4,10)
g.SetParameter(5,60)
g.SetParName(2,"valore medio")
g.SetParName(3,"sigma")
g.SetParLimits(3,0.3,0.7)

c1 = TCanvas()
tree.UnbinnedFit("f","t")
h.Draw()
g.Draw("SAME")
h.Fit("g")

gPad.Modified()

gApplication.Run(True)
