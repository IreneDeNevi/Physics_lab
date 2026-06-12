#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TGraph.h>
#include <TMath.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <Math/Minimizer.h>
#include <Math/Functor.h>
#include <Math/Factory.h>


using namespace std;
//Definisco l'accelerazione
double a(double x,double t){
  double m = 1.0;
  double A = 0.1;
  double w = 0.25;
  double k = 0.25;
  return (A*sin(w*t)-k*x)/m;
}

int main(){
  TApplication app("app",NULL,NULL);
  TGraph gr;

  double h = 1.;
  double x = 1;
  double v = 0;
  for(int t = 0;t<101;t++){
    double a_n = a(x,t*h);
    x = x + h*v + (pow(h,2)*a_n)/2;
    v = v + (h*(a(x,t*h+h)+a_n))/2;
    gr.SetPoint(t,t*h,x);
  }
  //Grafico l'andamento di x in funzione di t, sapendo che t appartiene all'intervallo [0,100]
  gr.Draw("AC*");
  app.Run(true);


return 0;
}
