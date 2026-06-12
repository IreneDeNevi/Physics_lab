#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMinuit.h>
#include <TApplication.h>
#include <Math/Minimizer.h>
#include <Math/Functor.h>
#include <Math/Factory.h>

using namespace std;

namespace data{
  int n;
  vector<double> x1,t1,et1;
  vector<double> x2,t2,et2;
}

TF1 *f1;
TF1 *f2;

double func1(double x,const double *par){
  return par[2]*pow(x-par[0],2)+par[3]*(x-par[0])+par[1];
}

double func2(double x,const double *par){
  return par[4]*pow(x-par[0],2)+par[5]*(x-par[0])+par[1];
}

void chi2(int &npar, double *gin, double &f, double *par, int iflag){
  f=0;
  for(int i = 0;i<data::x1.size();i++){
    f += pow((data::t1[i]-func1(data::x1[i],par))/data::et1[i],2) +pow((data::t2[i]-func2(data::x2[i],par))/data::et2[i],2);
  }
}


int main(){

  TApplication app("app",0,NULL);

  ifstream fp1("perno1.dat");
  ifstream fp2("perno2.dat");
  double tx1,tt1,tex1,tet1;
  double tx2,tt2,tex2,tet2;


  TGraphErrors gr1;
  while (fp1 >> tx1 >> tt1 >> tex1 >> tet1){
    data::x1.push_back(tx1);
    data::t1.push_back(tt1);
    data::et1.push_back(tet1);
    gr1.SetPoint(gr1.GetN(),tx1,tt1);
    gr1.SetPointError(gr1.GetN()-1,tex1,tet1);
  }

  TGraphErrors gr2;
  while (fp2 >> tx2 >> tt2 >> tex2 >> tet2){
    data::x2.push_back(tx2);
    data::t2.push_back(tt2);
    data::et2.push_back(tet2);
    gr2.SetPoint(gr2.GetN(),tx2,tt2);
    gr2.SetPointError(gr2.GetN()-1,tex2,tet2);
  }
  data::n=data::x1.size();

  f1 = new TF1("f1","[2]*(x-[0])^2+[3]*(x-[0])+[1]",data::x1[0],data::x1[data::n]);
  f2 = new TF1("f2","[2]*(x-[0])^2+[3]*(x-[0])+[1]",data::x1[0],data::x1[data::n]);

  gr1.Fit("f1");
  gr2.Fit("f2");
  gr1.Draw("AP");
  gr2.Draw("P");
 

  // Minuit
  TMinuit *minuit = new TMinuit(6);
  minuit->SetFCN(chi2);
  minuit->SetPrintLevel(1);
  minuit->DefineParameter(0,"x0",f1->GetParameter(0),0.01,0.,0.);
  minuit->DefineParameter(1,"T",4.,0.01,0.,0.);
  minuit->DefineParameter(2,"alpha1",f1->GetParameter(2),0.01,0.,0.);
  minuit->DefineParameter(3,"beta1",f1->GetParameter(3),0.01,0.,0.);
  minuit->DefineParameter(4,"alpha2",f2->GetParameter(2),0.01,0.,0.);
  minuit->DefineParameter(5,"beta2",f2->GetParameter(3),0.01,0.,0.);
  minuit->Command("MIGRAD");
  double T,eT;
  double a1,a2,ea2,ea1,b1,b2,eb1,eb2,x0,ex0;
  minuit->GetParameter(0,x0,ex0);
  minuit->GetParameter(1,T,eT);
  minuit->GetParameter(2,a1,ea1);
  minuit->GetParameter(3,b1,eb1);
  minuit->GetParameter(4,a2,ea2);
  minuit->GetParameter(5,b2,eb2);
  cout <<"Il periodo di isocronia vale " <<T <<" +- " <<eT <<endl;
  app.Run(true);

  return 0;

}
