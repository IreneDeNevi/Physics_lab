#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TH1D.h>
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
}

void fcn(int &k, double *gin, double &f,double *par, int iflag){
  f = 0;
  for(int i = 0; i<data::x.size();i++){
    f += -log(1/(2+(2*par[1])/3.)*(1+par[0]*data::x[i]+par[1]*pow(data::x[i],2))); 
}
}

int main(){
  TApplication app("app",0,NULL);
  TH1D h ("h","Istogramma di scattering",20,-1,1);
  ifstream ifile("Es4Data.dat");
  double tmp;
  while(ifile>>tmp){
    h.Fill(tmp);
    data::x.push_back(tmp);
  }
  TMinuit *minuit = new TMinuit(2);
  minuit->SetFCN(fcn);
  minuit->SetErrorDef(0.5);
  minuit->DefineParameter(0,"Alpha",0.5,0.1,0.,0.);
  minuit->DefineParameter(1,"Beta",0.5,0.1,0.,0.);

  minuit->Command("MIGRAD");

  double alpha,beta,ealpha,ebeta;
  minuit->GetParameter(0,alpha,ealpha);
  minuit->GetParameter(1,beta,ebeta);
  
  h.SetMinimum(0);
  h.SetMarkerStyle(20);
  h.Draw("E");
  
  TF1 *func = new TF1("func","[2]*1/(2+([1]*2)/3.)*(1+[0]*x+pow(x,2)*[1])",-1,1);
  func->SetParameter(0,alpha);
  func->SetParameter(1,beta);
  func->SetParameter(2,h.GetEntries()*h.GetBinWidth(1));
  func->Draw("SAME");

  app.Run(true);
  
  return 0;
}
