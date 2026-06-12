#include <TGraphErrors.h>
#include <iostream>
#include <fstream>
#include <TApplication.h>
#include <TF1.h>

using namespace std;

namespace data{
    double R = 0.01;
    double Q = 0.001;
    double L = 0.1;
    double k = 1e6;
}

int main(){
    TApplication app("app",  0, NULL);
    ifstream ifile;
    ifile.open("coulomb.dat");
    TGraphErrors gr;

    double d, theta, ed, etheta;
    while(ifile >> d >> theta >> ed >> etheta){
        gr.SetPoint(gr.GetN(), d, theta);
        gr.SetPointError(gr.GetN()-1, ed, etheta);
    }

    gr.Draw("AP");

    TF1 f1("f1", "[0]/(x + 0.02)^[1]");
    f1.SetParameter(0, 1e-4);
    f1.SetParameter(1, 4);

    TF1 f2("f2", "[0]*(1 - 4*0.000001/(x + 0.02)^3)/(x + 0.02)^[1]");
    f2.SetParameter(0, 1e-4);
    f2.SetParameter(1, 4);
    f2.SetLineColor(kBlue);
    gr.Fit("f1");
    gr.Fit("f2", "+");

    if(f1.GetProb() < 0.05){
        cout << "Posso escludere f1 al 5% CL" << endl;
        cout << "pvalue f1 = " << f1.GetProb() << endl;
        cout << "pvalue f2 = " << f2.GetProb() << endl;
    }
    if(f2.GetProb() < 0.05){
        cout << "Posso escludere f2 al 5% CL" << endl;
        cout << "pvalue f1 = " << f1.GetProb() << endl;
        cout << "pvalue f2 = " << f2.GetProb() << endl;
    }

    double range = 0;
    double h = 0.00001;
    while(f1.GetProb() < 0.05){
        f1.SetRange(range, 0.4);
        gr.Fit("f1", "Rq+");
        range = range + h;
    }

    cout << "Il range minimo è [" << range - h << ", +inf)" << endl;
    

    app.Run(true);
    return 0;
}