#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraph.h>
#include <TApplication.h>

using namespace std;

namespace data{
  vector<double> w;
  vector<double> v;
}

int main(){
  
  TApplication app("app",0,NULL);
  ifstream ifile("dati_S.dat");
  if (!ifile.is_open()) {
    cerr << "Cannot open dati_S.dat" << endl;
    return 1;
  }

  TGraph g;
  double x,y,y1;
  

  int i=0;
  while(ifile>>x>>y){
    data::v.push_back(x);
    data::w.push_back(y);

    y1 = pow(10,(y/20));
     if (x>7000){
    g.SetPoint(i,x,y1);
    i++;
      }
  }
  TCanvas c0;
  g.Draw("AP*");
  double media = g.GetMean(2);
  double errore = g.GetRMS(2);
  
  TF1 f("f","(4*[0]*[1]*[2]*[3])+([4]*[4])");
  // TF1 *f = new TF1("f","((4*[0]*[1]*[2]*[3])+([4]*[4])+([5]*[2])^2)"); //V_i^2 = 4kTRB_n + V^2 + I^2 R^2
  f.GetParameter(0);
  f.SetParName(0,"Boltzmann constant");
  f.SetParameter(1,290);
  f.SetParError(1,0.001);
  f.SetParName(1,"Temperature");
  f.SetParameter(2,55390);
  f.SetParError(2,0.001);
  f.SetParName(2,"R");
  f.FixParameter(3,1000);
  f.SetParName(3,"Bandwidth");
  f.SetParameter(4,18e-3); // 18 mV
  f.SetParError(4,1e-3);
  f.SetParName(4,"Voltage");
  f.SetParameter(5,2e-4);
  f.SetParName(5,"Current");
  f.SetParError(5,1e-5);
  
  g.Fit(&f,"S");
  

  cout<<"Media = " <<media <<endl;
  cout<<"Errore =" <<errore <<endl; 
  
  app.Run(true);
  return 0;
}
