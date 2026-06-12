#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <TCanvas.h>
#include <TH1D.h>
#include <TF1.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <Math/Minimizer.h>
#include <Math/Functor.h>
#include <Math/Factory.h>

/*  (Esame 21/01/19) Sono state effettuatenmisurex1,...,xn di una grandezza X distribuita secondo (fileDatiGamma.dat)la distribuzione:f(x,θ) =x^2(exp(−x/θ)/(2θ^3))•Si determini la miglior stima del parametro theta e il suo errore.•Si sovrapponga la distribuzione (con il parametro determinato al punto precedente) ai dati
 */

using namespace std;

namespace data{
  vector<double> v;
}

int main(){

  TApplication app("app",0,NULL);
  ifstream ifile ("DatiGamma.dat");
  double x;
  TH1D h ("h","Istogramma",30,0,26);
  while(ifile >>x){
    data::v.push_back(x);
    h.Fill(x);
  }
  TF1 *f = new TF1("f","[1]*(pow(x,2)*exp(-x/[0])/(2*pow([0],3)))",0,1);
  
  double area = h.GetEntries()*h.GetBinWidth(1);
  f->SetParameter(0,1);
  f->SetParName(0,"theta");
  f->SetParameter(1,area);
  h.SetMarkerStyle(20);
  h.Draw();
  h.Fit("f");
  
  app.Run(true);

  return 0;
}
