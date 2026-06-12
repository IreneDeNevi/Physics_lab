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

using namespace std;

void hist::ReadFile(const char *c){
  double tmp;
  ifstream ifile(c);
  while(ifile>>tmp){
    Fill(tmp);
    m_v.push_back(tmp);
  }
}
double hist::GetUnbinnedMean(){
  double m = 0;
  for (int i = 0; i<m_v.size();i++){
    m += m_v[i];
  }
  double media = m/m_v.size();
  return media;
}

double hist::GetUnbinnedRMS(){
  double m = GetUnbinnedMean();
  double s = 0;
  for (int i = 0; i<m_v.size();i++){
    s += pow(m_v[i]-m,2);
  }
  return s/m_v.size();
}
