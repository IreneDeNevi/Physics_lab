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

/*si disegni l'andamento di x in funzione di t (0,10)
x(0) = 0 e v0 è (0,c)
si sovrapponga x(t) con v0 = 0.5c,0.8 0.99c
*/
namespace data{
  double m=1, k=100, c=1;
}

double acc(double x , double v){
  double F = -data::k*x*pow(1-pow(v/data::c,2),3/2);
  return F/data::m;
}

int main(){
  TApplication app("app",0,NULL);
  double x0=0, v0=0.5, v, x, h= 0.01, t=0, tend= 10;
  int N = tend/h, i=0;
  TGraph* gr = new TGraph(N);

  //Eulero Cromer
  
  while (t<tend){
    v = v0 + h*acc(x,v);
    x = x0 + h*v;
    x0 = x;
    v0 = v;
    gr ->SetPoint(i,t,x);
    t = t+h;
    i++;
  }
  
  gr->SetMarkerColor(3);
  gr->Draw();
 
  x0=0; v0=0.8; t=0;
  i=0;
  
  TGraph* sr = new TGraph(N);
  while (t<tend){
    v = v0 + h*acc(x,v);
    x = x0 + h*v;
    x0 = x;
    v0 = v;
    sr ->SetPoint(i,t,x);
    t = t+h;
    i++;
  }
  sr->SetMarkerColor(2);
  sr->Draw("SAME");

  x0=0; v0=0.99; t=0; 
  i = 0;
  
  TGraph* fr = new TGraph(N);
  while (t<tend){
    v = v0 + h*acc(x,v);
    x = x0 + h*v;
    x0 = x;
    v0 = v;
    fr ->SetPoint(i,t,x);
    t = t+h;
    i++;
  }
  
  fr->SetMarkerColor(4);
  fr->Draw("SAME");
  
  app.Run(true);
  return 0;
}
