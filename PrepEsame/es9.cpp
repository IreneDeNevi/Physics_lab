#include <cmath>
#include <iostream>
#include <vector>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TGraph.h>
#include <TMath.h>
#include <TApplication.h>

#include "MYTF1.h"

using namespace std;

int main(){
  
  MYTF1 f("f","pow(x,2)-4",-5,5);
  double x0 = 0;
  double xN = f.Zero(x0,1,1000,0.01);
  cout<<"zero per n cicli " <<xN <<endl;

  double xt= f.Zero(x0,0,1000,0.01);
  cout<<"zero per tolleranza" <<xt <<endl;
  
  
  return 0;
}
