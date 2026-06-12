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
#include "MYTF1.h"

using namespace std;

int main(){
  MYTF1 f("f","pow(x,3)",-10,10);
  double x0 = 1;
  double d1 = f.Derivata(x0);
  double d2 = f.Derivata2(x0);
  cout<<"la derivata prima vale "<<d1 <<endl;
  cout<<"la derivata seconda vale  "<<d2 <<endl;
  return 0;
}
