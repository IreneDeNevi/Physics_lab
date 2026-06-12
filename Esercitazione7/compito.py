from ROOT import TH1D, TF1, TMath, TCanvas, gApplication, gPad


def load_data(file_name):
    values = []
    with open(file_name, "r", encoding="utf-8") as fin:
        for line in fin:
            line = line.strip()
            if not line:
                continue
            values.append(float(line))
    return values


def compute_upper_limit(n_obs, nbkg, alpha=0.05):
    sup = 0
    pvalue = 1.0
    while pvalue > alpha:
        pvalue = 0.0
        for i in range(0, n_obs + 1):
            pvalue += TMath.PoissonI(i, nbkg + sup)
        sup += 1
    return sup, pvalue


def main():
    # Counting analysis in the signal window.
    h = TH1D("h", "High-stat histogram", 50, 0, 40)
    values = load_data("dati_highstat.dat")

    n_obs = 0
    for value in values:
        if 14 < value < 16:
            n_obs += 1
        h.Fill(value)

    print("Observed events in [14,16]:", n_obs)

    nbkg = 44.7
    sup, pvalue = compute_upper_limit(n_obs, nbkg)
    print("Poisson p-value:", pvalue)
    print("Upper-limit signal events:", sup)

    # Signal + background model for binned fit.
    g = TF1("g", "[0]*([1]*TMath::Gaus(x,[2],[3],1)+[5]*exp(-x/[4]))", 0, 50)
    area = h.GetEntries() * h.GetBinWidth(1)
    g.SetParameter(0, area)
    g.SetParameter(1, 0.1)
    g.SetParameter(2, 15)
    g.SetParameter(3, 0.5)
    g.SetParameter(4, 10)
    g.SetParameter(5, 60)
    g.SetParName(2, "mean")
    g.SetParName(3, "sigma")
    g.SetParLimits(3, 0.3, 0.7)

    c1 = TCanvas("c1", "Counting analysis", 800, 500)
    h.Draw()
    g.Draw("SAME")
    h.Fit("g")
    gPad.Modified()
    c1.Update()

    gApplication.Run(True)


if __name__ == "__main__":
    main()
