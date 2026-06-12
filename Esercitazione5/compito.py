from ROOT import TF1, TGraphErrors, TCanvas, gApplication
from array import array
import math

# Input constants (from laboratory measurements)
A = 1.7298
eA = 0.0003
B = 13462.0
eB = 58.0
rho = -0.876

orders = array("d", [3, 4, 5, 6])
theta = array("d", [2.6773, 2.7324, 2.7651, 2.7846])
theta0 = 1.5701
etheta = 0.0005
alpha = math.pi / 3.0


def lam(order, theta_i, theta0_i, A_i, B_i):
    # Relative index from prism geometry.
    n_rel = math.sin(((theta_i - theta0_i) + alpha) / 2.0) / math.sin(alpha / 2.0)
    return math.sqrt(B_i / (n_rel - A_i))


def fit_radius(l_values):
    fit_fun = TF1("fit_fun", "1/([1]*(1/[0]^2-1/x^2))", 300, 400)
    fit_fun.FixParameter(0, 2.0)
    fit_fun.SetParameter(1, 1e-6)

    graph = TGraphErrors(len(orders))
    for i in range(len(orders)):
        lref = l_values[i]
        lup = lam(orders[i], theta[i] + etheta / math.sqrt(3.0), theta0, A, B)
        el = abs(lup - lref)
        graph.SetPoint(i, orders[i], lref)
        graph.SetPointError(i, 0.0, el)

    graph.Fit("fit_fun", "Q")
    return graph, fit_fun.GetParameter(1), fit_fun.GetParError(1)


# Nominal fit
lambda_nominal = [lam(orders[i], theta[i], theta0, A, B) for i in range(len(orders))]
graph, R, eR = fit_radius(lambda_nominal)

# Systematic shifts
lambda_A = [lam(orders[i], theta[i], theta0, A + eA, B) for i in range(len(orders))]
_, RA, _ = fit_radius(lambda_A)

lambda_B = [lam(orders[i], theta[i], theta0, A, B + eB) for i in range(len(orders))]
_, RB, _ = fit_radius(lambda_B)

lambda_t0 = [lam(orders[i], theta[i], theta0 + etheta, A, B) for i in range(len(orders))]
_, Rt0, _ = fit_radius(lambda_t0)

# Correlated uncertainty from A and B plus statistical and theta0 contributions
eAB = math.sqrt((RA - R) ** 2 + (RB - R) ** 2 + 2.0 * rho * (RA - R) * (RB - R))
eTot = math.sqrt(eAB ** 2 + eR ** 2 + (Rt0 - R) ** 2)

print()
print("R = {:.6g} +/- {:.6g}".format(R, eTot))
print("theta0 contribution      = {:.6g}".format(abs(Rt0 - R)))
print("theta_i contribution     = {:.6g}".format(eR))
print("A/B contribution         = {:.6g}".format(eAB))
print()

c1 = TCanvas("c1", "Dispersion fit", 800, 500)
graph.SetTitle("Prism calibration;Order m;lambda")
graph.Draw("AP")
c1.Update()

gApplication.Run(True)
