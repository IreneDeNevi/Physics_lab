from ROOT import *
from math import *
import numpy as np
from iminuit import Minuit

def chi2(par):
    sum = ((par[0]-E)/ErrE)**2+((par[1]/par[0]-he)/Errhe)**2+((par[0]/par[2]-ek)/Errek)**2+((par[1]/par[2]-hk)/Errhk)**2
    return sum 

#ricavo e,h,k
par = np.ndarray(3)
par[0] = 1.602#*e-19 #carica elettrone vera
par[1] = 6.626#*e-34 #h vero
par[2] = 1.380649#*e-23 #k vero
E = 1.586509#*e-19      #carica elettrone partorito
ErrE = 0.068326#*e-19   #errore partorito
#dati su RC
he = 4.2312#*e-15
Errhe = 1.3#*e-18
ek = 1.16138#*e+4
Errek = 4.65#*e+1
hk = 4.7027#*e-11
Errhk = 1.5854#*e-12

#Metodo Minuit
m = Minuit.from_array_func(chi2,par,error=0.01,errordef=1,print_level=1)
m.migrad()

print "I parametri ottenuti minimizzando il chi2 sono "
print "e = %f +- %f" %(m.values[0],m.errors[0])
print "h = %f +- %f" %(m.values[1],m.errors[1])
print "k = %f +- %f" %(m.values[2],m.errors[2])

#Contour delle regioni con 68 per cento di probabilita
xminos1,yminos1,ctr1 = m.mncontour('x0','x1', sigma = 1,numpoints = 100) #(e,h)
xminos2,yminos2,ctr2 = m.mncontour('x0','x2', sigma = 1,numpoints = 100) #(e,k)
xminos3,yminos3,ctr3 = m.mncontour('x1','x2', sigma = 1,numpoints = 100) #(h,k)

f1 = TGraph()
for i in range(0,len(ctr1)):
    f1.SetPoint(i,ctr1[i][0],ctr1[i][1]) #(e,h)
f2 = TGraph()
for i in range(0,len(ctr2)):
    f2.SetPoint(i,ctr2[i][0],ctr2[i][1]) #(e,k)
f3 = TGraph()
for i in range(0,len(ctr3)):
    f3.SetPoint(i,ctr3[i][0],ctr3[i][1]) #(h,k)

#Dati Veri
El = 1.602
H = 6.626
K = 1.38064

c1=TCanvas()
f1.SetPoint(0,El,H)
f1.SetMarkerStyle(20)
f1.Draw("AP")
f1.SetTitle("Contour (e/h)")
c2 = TCanvas()
f2.SetPoint(0,El,K)
f2.SetMarkerStyle(20)
f2.SetMarkerColor(8)
f2.Draw("AP")
f2.SetTitle("Contour (e/k)")
c3= TCanvas()
f3.SetPoint(0,H,K)
f3.SetMarkerStyle(20)
f3.SetMarkerColor(2)
f3.Draw("AP")
f3.SetTitle("Contour (h/k)")

gApplication.Run(True)
