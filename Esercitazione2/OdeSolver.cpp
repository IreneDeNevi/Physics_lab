#include "Vettore.h"
#include "OdeSolver.h"
#include <cmath>

void OdeSolver::Punto(const PuntoMateriale& tmp){
  m_p.push_back(tmp);
}

const vector<PuntoMateriale>& OdeSolver::Punti() const{
  return m_p;
}

PuntoMateriale OdeSolver::Punto(unsigned int i) const{
  return m_p[i];
}

unsigned int OdeSolver::N() const{
  return m_p.size();
}

void OdeSolver::T(double t0){
  m_t=t0;
}

double OdeSolver::T() const{
  return      m_t;
}

void OdeSolver::Passo(double h){
  m_h = h;
}

double OdeSolver::Passo() const{
  return   m_h;
}


Vettore OdeSolver::m_eqDiff(unsigned int i, double t, const vector<PuntoMateriale>& p) const{
  // Acceleration from total force: a = (F_ext + sum(F_int)) / m
  Vettore f;
  if (fEsterna) {
    f = fEsterna(i, t, p);
  }

  for (unsigned int j = 0; j < p.size(); j++) {
    if (i != j && fInterna) {
      f = f + fInterna(i, j, t, p);
    }
  }
  return f * (1.0 / p[i].Massa());

}

//Da implementare a cura dello studente
void OdeSolver::Cinematica(){

  if (m_method=="Eulero"){
    vector<Vettore>  k1(m_p.size());
    vector<Vettore>  w1(m_p.size());
   
    for (unsigned int i=0;i<m_p.size();i++){
      k1[i] = m_h*m_p[i].V();
      w1[i] = m_h*m_eqDiff(i,m_t,m_p);
      
    }

    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k1[i]);
      m_p[i].V(m_p[i].V() + w1[i]);
    }

  }
  else if (m_method=="Rk2"){
    vector<Vettore>  k1(m_p.size());
    vector<Vettore>  w1(m_p.size());
    vector<Vettore>  k2(m_p.size());
    vector<Vettore>  w2(m_p.size());
    vector<PuntoMateriale> tmp(m_p);
    tmp.resize(m_p.size());
    //passo1
    for (unsigned int i=0;i<m_p.size();i++){
      k1[i] = m_h*m_p[i].V();
      w1[i] = m_h*m_eqDiff(i,m_t,m_p);
    }
    //Variabili nuove
    for(unsigned int i=0;i<m_p.size();i++){
      tmp[i].V(m_p[i].V() + (w1[i]*(0.5)));
      tmp[i].R(m_p[i].R() + (k1[i]*(0.5)));
    }
    //passo2
    for(unsigned int i=0;i<m_p.size();i++){
      k2[i] = m_h*tmp[i].V();
      w2[i] = m_h*m_eqDiff(i,m_t +((m_h)*(0.5)),tmp);
    }
  //passo3
    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k2[i]);
      m_p[i].V(m_p[i].V() + w2[i]);
      // STEP 5 implementare Runge Kutta al secondo ordine
    }
  }
  //COMPITO A CASA implementare Verlet Velocity
  else if (m_method=="VV"){
    vector<Vettore> k1(m_p.size());
    vector<Vettore> w1(m_p.size());
    vector<Vettore> w2(m_p.size());
    vector<PuntoMateriale> tmp(m_p);
    tmp.resize(m_p.size());
    //passo 1
    for(unsigned int i=0;i<m_p.size();i++){
      // Position update uses acceleration evaluated at t.
      k1[i] = m_h * (m_p[i].V() + (m_h * 0.5 * m_eqDiff(i, m_t, m_p)));
      w1[i] = m_h * m_eqDiff(i, m_t, m_p);
    }
    //passo n+1
    for(unsigned int i=0;i<m_p.size();i++){
      tmp[i].V(m_p[i].V() + (w1[i]));
      tmp[i].R(m_p[i].R() + (k1[i]));
    }
    //passo 2
    for(unsigned int i=0;i<m_p.size();i++){
       w2[i] = (0.5*m_h)*(m_eqDiff(i,m_t+m_h,m_p)+m_eqDiff(i,m_t+m_h,tmp));
    }
    //passo finale
    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k1[i]);
      m_p[i].V(m_p[i].V() + w2[i]);
    }
  }
  m_t += m_h;
}


