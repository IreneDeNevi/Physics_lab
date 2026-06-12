from ROOT import TH1D, TH2D, TCanvas, TRandom3, gApplication
import time
import math as m

rnd = TRandom3()
rnd.SetSeed(int(time.time()))

h1 = TH1D("h1", "", 20, -5, 5)
h2 = TH2D("h2", "", 20, -5, 5, 20, -5, 5)

for i in range(0, 100):
    # Box-Muller transform from uniform randoms.
    u = -m.log(1 - rnd.Rndm())
    th = rnd.Rndm() * 2 * m.pi
    r = m.sqrt(2 * u)
    x = r * m.cos(th)
    y = r * m.sin(th)
    h1.Fill(x)
    h1.Fill(y)
    h2.Fill(x, y)

c1 = TCanvas()
h1.Draw()
c2 = TCanvas()
h2.Draw()

gApplication.Run(True)
