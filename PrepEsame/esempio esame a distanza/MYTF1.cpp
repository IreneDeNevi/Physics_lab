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

double MYTF1::Derivata(double x){
  double eps = 1e-6;
  return (Eval(x+eps)-Eval(x-eps))/(2*eps);
}
double MYTF1::Derivata2(double x){
  double h = 1e-6;
  return (Eval(x+h)-Eval(x-h)-2*(Eval(x))) /(pow(h,2));
}
