from ctypes import c_double

import numpy as np
from ROOT import TMinuit


def model(x, a, b):
    return a * x + b


def load_data(file_name):
    x_vals = []
    y_vals = []
    ex_vals = []
    ey_vals = []

    with open(file_name, "r", encoding="utf-8") as fin:
        for line in fin:
            dt = line.split()
            if len(dt) != 4:
                continue
            x_vals.append(float(dt[0]))
            y_vals.append(float(dt[1]))
            ex_vals.append(float(dt[2]))
            ey_vals.append(float(dt[3]))

    return (
        np.asarray(x_vals, dtype=float),
        np.asarray(y_vals, dtype=float),
        np.asarray(ex_vals, dtype=float),
        np.asarray(ey_vals, dtype=float),
    )


x, y, ex, ey = load_data("pendolo.dat")


def fcn(npar, gin, f, par, iflag):
    # Weighted chi-square for linear regression.
    residuals = (y - model(x, par[0], par[1])) / ey
    f.value = float(np.sum(residuals * residuals))


minuit = TMinuit(2)
minuit.SetFCN(fcn)
minuit.DefineParameter(0, "par0", 4, 0.01, 0.0, 0.0)
minuit.DefineParameter(1, "par1", 0, 0.01, 0.0, 0.0)
minuit.Command("MIGRAD")

a = c_double(0.0)
b = c_double(0.0)
ea = c_double(0.0)
eb = c_double(0.0)
minuit.GetParameter(0, a, ea)
minuit.GetParameter(1, b, eb)

print("a = %f +- %f, b = %f +- %f" % (a.value, ea.value, b.value, eb.value))
