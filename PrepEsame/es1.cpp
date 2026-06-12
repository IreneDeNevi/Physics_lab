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
#include <TRandom3.h>
#include <TMath.h>

using namespace std;
/*L’area del cerchio (sfera 2D) vale πr^2, il volume della sfera 3D vale 4/3πr^3. Non `e difficile immaginare che la sfera 4D abbia volume αr^4. Determinare α con il metodo Monte Carlo. Verificare che il valore tenda a pi^(n/2)Γ(n/2 +1)*r^n (n dimesioni della sfera) all’aumentare di N (numero di estrazioni). La funzione Γ (Gamma) `e
disponibile in ROOT (TMath).*/

//Semplificazione : La sfera è centrata nell'origine ed è racchiusa in un cubo (analogo metodo risolutivo es. MonteCarlo)

int main(){
  TRandom3 rnd = TRandom3();
  rnd.SetSeed(int(time(0)));
  int n = 0; //dimensione della sfera
  cout<<"Dammi la dimensione della sfera (numero intero)"<<endl;
  cin>>n;
    double raggioND = 0;
    cout<<"Dammi il raggio della sfera "<<endl;
    cin>>raggioND;

    float Nfav = 0;
    float Ntot = 0;
    double nacc = 10000;

    for (int i = 0;i<nacc;i++){
      double l = 0; //lato quadrado
      double r = 0;
      for(int j=0;j<n;j++){
	double coord = rnd.Rndm()*2*raggioND-raggioND;
	l = l+pow(coord,2);
      }
      r = sqrt(l);
      if(r<= raggioND){
	Nfav++;
      }
      Ntot++;
    }
    double f = Nfav/Ntot;
    double A = pow(2*raggioND,n);
    double VolND = A*f;
    double alpha = VolND/pow(raggioND,n);
    cout<<"alpha vale : " <<alpha <<endl;
    double alphavero = pow(M_PI,n/2)/TMath::Gamma(n/2+1);
    cout<<"alpha vero vale : "<<alphavero <<endl;
return 0;
}
