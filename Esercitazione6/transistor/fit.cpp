#include <iostream>
#include <fstream>
#include <cmath>
#include <TH1D.h>
#include <TF1.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TApplication.h>
#include <vector>
#include <TGraphErrors.h>
#include <stdio.h>
using namespace std;

int main(){
  ifstream ifile;
  ifile.open("pnp_T0.dat");
 
double I;
double eI;
double V;
double eV;

ofstream ofile;
ofile.open("T0.dat");

while(ifile >>V >>I >>eV >>eI){
  ofile <<V <<" "<<I  <<" " <<(eV/sqrt(3)) <<" " <<(eI/sqrt(3)) <<endl;
 }
ofile.close();

TApplication app ("app",0,NULL);
TGraphErrors gr("T0.dat");
TF1 fitexp ("fitexp","exp([0]+[1]*x/[2])-exp([0])",0,1);
fitexp.SetParameter(0,-10);
fitexp.SetParameter(1,1.2e4);
fitexp.FixParameter(2,273.15);
gr.Draw("AP");
gr.Fit("fitexp");
app.Run(true);




 return 0;
}
