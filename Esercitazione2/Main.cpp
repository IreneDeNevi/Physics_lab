#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include <TGraph.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TStyle.h>


#include "OdeSolver.h"
#include "Vettore.h"
#include "PuntoMateriale.h"

using namespace std;

Vettore fInterna(unsigned int i,unsigned int j, double t, const vector<PuntoMateriale>& p){
  //STEP 2 definizione forza interna
  return p[i].Massa()*(p[j].CampoGravitazionale(p[i].R()));
}

Vettore fEsterna(unsigned int i, double t, const vector<PuntoMateriale>& p){
  //STEP 2 definizione forza esterna
  return 0;
}

int main(){ 
  
  TApplication app("app",0,NULL);
  gStyle->SetOptStat(0);

  //Lettura dei dati dal file
  double mass;
  double x,y,z,vx,vy,vz;
  ifstream f("fileInput");
  if (!f.is_open()) {
    cerr << "Cannot open input file: fileInput" << endl;
    return 1;
  }

  OdeSolver ode("Eulero");
  while (f >> mass >> vx >> x >> vy >> y >> vz >> z){
    Vettore r = Vettore(x,y,z);
    Vettore v = Vettore(vx,vy,vz);
    ode.Punto(PuntoMateriale(mass,0,r,v));
    Vettore L;
    L = (mass)*(v^r);

    cout<<"Valore momento angolare "<<L.Mod() <<endl;
  }
  // OdeSolver ode(...);
  // STEP 1 creazione dell'oggetto della classe OdeSolver
  //   - creazione oggetto OdeSolver vuoto, assegnazione con il metodo Punto
  //   - creazione di vector<PuntoMateriale> e poi creazione di OdelSover

  // Creazione classe OdeSolver (per la soluzione dell'equ. diff.)
  ode.fInterna = fInterna;
  ode.fEsterna = fEsterna;
  ode.Passo(0.5);

  
  //Creazione dei grafici (uno per pianeta)
  vector<TGraph> gr(ode.N());
  TCanvas c("c","",10,10,500,500);
  
  //Preparazione grafico delle coordinate dei pianeti
  double size=5; // 5 unita' astronimiche
  gPad->DrawFrame(-size,-size,size,size);
  int color[10]={kOrange+1,kViolet+1,kGreen+2,kAzure+1,kRed+2,kRed-7,kCyan-8,kBlue-7,kBlue+1,kBlue+2};
  for (unsigned int i=0;i<ode.N();i++){
    gr[i].SetPoint(0,ode.Punto(i).R().X(),ode.Punto(i).R().Y());
    gr[i].SetMarkerColor(color[i]); gr[i].SetMarkerStyle(20); gr[i].SetMarkerSize(0.1);
    if (i==0) gr[i].SetMarkerSize(1);
    gr[i].Draw("P");
  }
  gPad->Modified(); gPad->Update();
  app.Run(true);

  //Run del metodo numerico + grafico in tempo reale delle coordinate e del mom. angolare totale
  int step = 1;
  while (ode.T()<365){
    ode.Cinematica();
    for (unsigned int i=0;i<ode.N();i++){
      gr[i].SetPoint(step,ode.Punto(i).R().X(),ode.Punto(i).R().Y());
      //STEP 4 riempimento delle grafico gr[i] con le coordinate aggiornate dei pianeti
    }
    step++;
    gPad->Modified(); gPad->Update();
  }

  app.Run(true);

  return 0;
  
  
}
