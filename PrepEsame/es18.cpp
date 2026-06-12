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
  vector<double> x;
  TH1D *h;
}

void logl(int &k , double *gin , double &f, double *par , int  iflag ){
  f = 0.0;
  for(int i=0;i<data::x.size();i++){
    f += -log(par[0]*pow(data::x[i],par[0]-1));
  }
}

int main(){
  TApplication app("app",0,0);
  TRandom3 rnd;
  rnd.SetSeed(time(0));
 

  data::h = new TH1D ("h","istogramma",100,0,1);
  TF1 f1("f1","3*pow(x,2)",0,1);

  for (int i=0;i<1000;i++){
    double tmp = f1.GetRandom();
    data::h->Fill(tmp);
    
    data::x.push_back(tmp);
  }
  
  double etheta,theta;

  TF1 *fe = new TF1("fe","[1]*[0]*pow(x,[0]-1)",0,1);
 

  TMinuit minuit(1);
  minuit.SetFCN(logl);
  minuit.SetErrorDef(0.5);
  minuit.DefineParameter(0,"Theta",fe->GetParameter(0),0.01,0.,0.);
  minuit.Command("MIGRAD");

  minuit.GetParameter(0,theta,etheta);
  fe->SetParameter(0,theta);
  fe->SetParameter(1,data::h->GetBinWidth(1)*data::h->GetEntries());
  data::h->SetMarkerStyle(20);
  data::h->Draw("E");
  fe->Draw("SAME");
  app.Run(true);
  return 0;
}
