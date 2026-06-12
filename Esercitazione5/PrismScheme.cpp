#include <iostream>
#include <cmath>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TApplication.h>
#include <vector>
#include <TGraphErrors.h>
#include <TF1.h>

using namespace std;

namespace ex{
  double alpha   = M_PI/3;
  double lambda1 = 579.1;
  double lambda2 = 404.7;
  double th0   = 1.5701;
  double th1   = 2.6958;
  double th2   = 2.7904;
  double eth   = 0.0005;
}

namespace ex1{
  double th3 = 2.6773;
  double th4 = 2.7324;
  double th5 = 2.7651;
  double th6 = 2.7846;
  double eth = 0.0005;
}

void GetAB(double th0, double th1, double th2, double &A, double &B){
  double n1,n2;
  n1 = sin((th1-th0+ex::alpha)/2)/sin(ex::alpha/2);
  n2 = sin((th2-th0+ex::alpha)/2)/sin(ex::alpha/2);
  A  = n2-(n1-n2)*pow(ex::lambda1,2)/(pow(ex::lambda2,2)-pow(ex::lambda1,2));  //A = n2 -(B/pow(exp::lambda2,2))
  B  = (n1-n2)*pow(ex::lambda1,2)*pow(ex::lambda2,2)/(pow(ex::lambda2,2)-pow(ex::lambda1,2));
}

double GetLambda(double th0, double th3, double A, double B){
  double lambda = sqrt(B/sin((th3-th0+ex::alpha)/2)/sin(ex::alpha/2)-A);
  return lambda;
}

int main(){
  double sigmth=ex::eth/sqrt(3);
  TRandom3 rnd = TRandom3();
  rnd.SetSeed(1234567890);
  TApplication app("app",0,NULL);
  
  TH1D h0("distrA","",100,0,0);
  TH1D h1("distrB","",100,0,0);
  TH2D h2("distrAB","",100,0,0,100,0,0);
  
  for(int i = 0;i<10000;i++){
    double Th0 = rnd.Rndm()*(2*ex::eth)+(ex::th0+ex::eth)-(2*ex::eth);
    double Th1 = rnd.Rndm()*(2*ex::eth)+(ex::th1+ex::eth)-(2*ex::eth);
    double Th2 = rnd.Rndm()*(2*ex::eth)+(ex::th2+ex::eth)-(2*ex::eth);
    double X,Y;
    GetAB(Th0,Th1,Th2,X,Y);
    h0.Fill(X);
    h1.Fill(Y);
    h2.Fill(X,Y);
  }

  
 double a = h0.GetMean();
  double b = h1.GetMean();
double  sigmaA = h0.GetRMS();
double  sigmaB = h1.GetRMS();
double  CC = h2.GetCorrelationFactor();
  
  cout <<"A = "<<a <<" +- "<<sigmaA<<"" <<endl;
  cout <<"B = "<<b <<" +- "<<sigmaB<<"" <<endl;
  cout <<"Il Fattore di Correlazione è = "<<CC  <<endl;
  //Compito a casa						  
  vector<double> VRh,eVRh;  //Vettori vuoti che conterranno Rh e rispettivo errore
  for(int j=0;j<3;j++){
    TH1D lambda3("lambda3","",100,0,0);
    TH1D lambda4("lambda4","",100,0,0);
    TH1D lambda5("lambda5","",100,0,0);
    TH1D lambda6("lambda6","",100,0,0);
    //MC
    for(int i=0;i<10000;i++){
      double Th0 = rnd.Rndm()*(2*ex::eth)+(ex::th0+ex::eth)-(2*ex::eth);
      double Th3 = rnd.Rndm()*(2*ex::eth)+(ex1::th3+ex::eth)-(2*ex::eth);
      double Th4 = rnd.Rndm()*(2*ex::eth)+(ex1::th4+ex::eth)-(2*ex::eth);
      double Th5 = rnd.Rndm()*(2*ex::eth)+(ex1::th5+ex::eth)-(2*ex::eth);
      double Th6 = rnd.Rndm()*(2*ex::eth)+(ex1::th6+ex::eth)-(2*ex::eth);
      
      double L3= 1./GetLambda(Th0,Th3,a,b);
      double L4= 1./GetLambda(Th0,Th4,a,b);
      double L5= 1./GetLambda(Th0,Th5,a,b);
      double L6= 1./GetLambda(Th0,Th6,a,b);
      lambda3.Fill(L3);
      lambda4.Fill(L4);
      lambda5.Fill(L5);
      lambda6.Fill(L6);
    }
    
    double l3,l4,l5,l6,sigma3,sigma4,sigma5,sigma6; //sto finendo i nomi
    vector<double> V,eV; //vettori vuoti che contengono 1/lambda e i suoi errori
      
    l3 = lambda3.GetMean();
    sigma3 = lambda3.GetRMS();
    l4 = lambda4.GetMean();
    sigma4 = lambda4.GetRMS();
    l5 = lambda5.GetMean();
    sigma5 = lambda5.GetRMS();
    l6 = lambda6.GetMean();
    sigma6 = lambda6.GetRMS();
    
    
    cout <<"1/lambda3 = "<<l3 <<" +- "<<sigma3 <<endl;
    cout <<"1/lambda4 = "<<l4 <<" +- "<<sigma4 <<endl;
    cout <<"1/lambda5 = "<<l5 <<" +- "<<sigma5 <<endl;
    cout <<"1/lambda6 = "<<l6 <<" +- "<<sigma6 <<endl;
    
    V.push_back(l3);
    eV.push_back(sigma3);
    V.push_back(l4);
    eV.push_back(sigma4);
    V.push_back(l5);
    eV.push_back(sigma5);
    V.push_back(l6);
    eV.push_back(sigma6);
    
    TGraphErrors f1;
    int m = 3;
    
    for(int i = 0; i<V.size();i++){
      f1.SetPoint(i,pow(1./m,2),V[i]);
      f1.SetPointError(i,0,eV[i]);
      m++;
    }
    TF1 f("f","[0]*(1./4-x^2)",0,1);  //fit di 1/λ in funzione di 1/m^2
     f.SetParameter(0,pow(10,-2));
    f.SetParName(0,"Costante Rh");
    
    TCanvas c1;
    f1.Draw();
    f1.Fit("f");  
    f1.GetXaxis()->SetTitle("1/m^{2}");
    f1.GetYaxis()->SetTitle("1/λ");
    
    
    double Rh,eRh;
    Rh = f.GetParameter(0);
    eRh = f.GetParError(0);
    VRh.push_back(Rh);
    eVRh.push_back(eRh);
    
    if(j==0){      //al primo giro trovo Rh con il suo errore, tenendo
      a = a+sigmaA;//conto degli errori solo sugli angoli teta;
    }              //al secondo giro vario A, al terzo B
    else if(j==1){
      a = a;
      b = b+sigmaB;
      }
    
  }
  
  
  double errRh1,errRh2, dfA,dfB;
  dfA=VRh[1]-VRh[0];
  dfB=VRh[2]-VRh[0];
  errRh2=pow(dfA,2)+pow(dfB,2)+2*CC*dfA*dfB;
  errRh1=sqrt(pow(dfA,2)+pow(dfB,2)+2*CC*dfA*dfB);
  
  cout <<"L'errore su Rh dovuto ad A e B è " << errRh1 << endl;
  
  double Rhf, eRhf;
  eRhf=sqrt(pow(eVRh[0],2)+errRh2);
  Rhf=VRh[0];
  
  cout << "Rh_f =  " << Rhf << " +- " << eRhf << endl;
  
  return 0;
  app.Run(true);
}


