#include <cmath>
#include <iostream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TMath.h>
#include <TApplication.h>


using namespace std;

double diff(TF1 f,double x,double epsilon){
  return abs(f.Eval(x-epsilon)-f.Eval(x))-abs(f.Eval(x+epsilon)-f.Eval(x));
}

int main(){
  
  //Parte uno : rispondere al cout
  
  TApplication app("app",0,0);
  TRandom3 rnd;
  rnd.SetSeed(time(0));
  TH1D h("h","",20,0,0);
  
  TF1 f("f","1/x",0,2);
  
  double epsilon = 0;
  double x = 1;
  double lim = 0.1;
  double res = diff(f,1,epsilon);
  
  while(res<=lim){
    epsilon += 0.00001;
    res = diff(f,1,epsilon);
  }
  
  cout <<"A partire da epsilon = "<<epsilon<<" non è più valida la propagazione con le derivate" <<endl;
  
  //Parte due : Ricavare f(x) sapendo che x è distribuita Gaussiamente
  
  TGraph g;
  double sigma = 2*epsilon/sqrt(3);
  for (int i =0;i<100;i++){
    double x1 = rnd.Gaus(x,sigma);
    double y = f.Eval(x1);
    h.Fill(y);
    g.SetPoint(i,x1,y);
  }
  TCanvas c0;
  h.Draw();
  TCanvas c1;
  g.Draw("AP");
  g.SetMarkerStyle(20);
  
  app.Run(true);
  
  return 0;
}
