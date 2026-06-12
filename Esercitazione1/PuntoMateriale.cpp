#include "Vettore.h"
#include "PuntoMateriale.h"
#include "Elettrone.h"
#include <cmath>

Vettore PuntoMateriale:: R(){
return m_r;
}

Vettore PuntoMateriale:: V(){
  return m_v;
}

void PuntoMateriale::R(Vettore r){
  m_r = r;
 }

void PuntoMateriale::V(Vettore v){
  m_v = v;
}

Vettore PuntoMateriale::CampoGravitazionale(Vettore r){
  //F = -GmM/(r-r0)^2 vers(r-r0)
  // a = F/m con m == massa di prova

  double G = 1;

  Vettore r0 = m_r;
  Vettore dist = r-r0;

  Vettore val = -G*Massa()/pow(dist.Mod(),2)*dist.Vers();

  return val;
}


/*


*/
