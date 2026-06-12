#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TMath.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <Math/Minimizer.h>
#include <Math/Functor.h>
#include <Math/Factory.h>
#include <TRandom3.h>

using namespace std;

namespace data{
  vector<double> v;
}

int main(){
  TApplication app("app",0,0);
  ifstream ifile("dati_gaus.dat");
  double x;
  TH1D h("h","istogramma gaus",100,0,0);
  while(ifile>>x){
    data::v.push_back(x);
    h.Fill(x);
  }
  TF1 f("f","[0]*([1]*TMath::Gaus(x,[2],[3],1)+(1-[1])*TMath::Gaus(x,[5],[6],1))",0,10);
  //f.SetParameter(0,h.GetBinWidth(1)*h.GetEntries()); //BINNED EXTENDED
  f.FixParameter(0,1); //BINNED
  f.SetParameter(1,0.5);
  f.SetParameter(3,0.5);
  f.SetParameter(2,4.3);
  f.SetParameter(6,0.5);
  f.SetParameter(5,5);
  f.SetParName(0,"normalizzazione");
  f.SetParName(2,"media1");
  f.SetParName(3,"sigma1");
  f.SetParName(1,"ampiezza");
  f.SetParName(5,"media2");
  f.SetParName(6,"sigma2");
  
  h.SetMarkerStyle(20);
  h.Draw("E");
  h.Fit("f","MULTI"); //BINNED
  f.SetParameter(0,h.GetEntries()*h.GetBinWidth(1));//BINNED
  f.Draw("SAME");     //BINNED
 //h.Fit("f","L"); //BINNED EXTENDED
 app.Run(true);
 return 0;
}
