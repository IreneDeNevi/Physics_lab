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
  vector<double>v;
  vector<double>w;
  vector<double>l;
}

int main(){
  
TApplication app("app",NULL,0);
 ifstream ifile("dati.dat");
 double R,R1,medie,err;
 TGraphErrors g;
 int i = 0;

 while(ifile>>R>>medie>>err){
   data::v.push_back(R);
   data::w.push_back(medie);
   data::l.push_back(err);
   R1 = sqrt(R);
   g.SetPoint(i,R1,medie);
   g.SetPointError(i,10^-3,err);
   i++;
 }
  TF1 *f = new TF1("f","(4*[0]*[1]*x*[2])");
  f->SetParameter(0,10^-23);
  f->GetParameter(0);
  f->SetParName(0,"costante di Boltzmann");
  f->SetParameter(1,290);
  f->SetParError(1,0.001);
  f->SetParName(1,"Temperatura");
  f->FixParameter(2,1000);
  f->SetParName(2,"Frequenza");
  
 g.Fit("f","S");
 g.Draw("AP*");
 app.Run(true);

return 0;

}
