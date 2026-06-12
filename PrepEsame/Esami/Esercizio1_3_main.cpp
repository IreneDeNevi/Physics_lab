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
#include "hist.h"
#include <TRandom3.h>
/*
Si implementi una classe derivata da TH1D in grado di riempire un instogramma e il metodo deve calcolare media e varianza unbinned, che devono essere ritornate dai metodi double getunbinnedmead() e double getunbinnedrms()
costruire un main.cpp
*/

using namespace std;

int main(){
  TApplication app("app",0,NULL);
  TCanvas c1;
  hist h("h","istogramma lowstat",15,0,10);
  h.ReadFile("lowstat.dat");
  h.Draw();
  double mean = h.GetUnbinnedMean();
  double rms = h.GetUnbinnedRMS();

  cout<<"media = "<<mean<<endl;
  cout<<"varianza = "<<rms<<endl;
  app.Run(true);

  return 0;
}
