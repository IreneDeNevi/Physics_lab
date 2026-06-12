from ROOT import *
from math import *
from numpy import *
from array import *
import time


def a (x,v):
    m = 2.0;
    k = 7.5;
    delta = 4.5
    beta = sqrt(delta*pow(m,2)+4*k*m)
    return -(x*k+v*beta)/m


x = 1;
v1 = 0;
gr = TGraph()
h = 1

for v in range (0,101):
    a_n = a(x,v)
    x = x+h*v + (pow(h,2)*a_n)/2;
    v1 = v1 + (h*a(x,v+1)+a_n)/2;
    gr.SetPoint(v,x,v1)

gr.Draw("AC*")
gApplication.Run(True)
