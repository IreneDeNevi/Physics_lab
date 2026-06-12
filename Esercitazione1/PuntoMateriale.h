#ifndef _PUNTOMATERIALE
#define _PUNTOMATERIALE
#include "Vettore.h"
#include "Particella.h"
#include "Elettrone.h"

//Progettazione della gerarchia di classi

class PuntoMateriale: public Particella{ //la classe punto materiale dipende dalla classe particella inoltre la keyword public regola l'accesso della classe derivata nella classe base
 public:
 PuntoMateriale(Particella p=Particella(), Vettore r=Vettore(), Vettore v=Vettore()):Particella(p),m_r(r),m_v(v){}  //è buona norma mettere costruttori di default (Particella(),Vettore())
 PuntoMateriale(double massa, double carica, Vettore r, Vettore v):PuntoMateriale(Particella(massa,carica),r,v){}

   //Metodi Getter
   
  Vettore R();
  Vettore V();

//Metodi Setter

  void R(Vettore);
  void V(Vettore);

//Metodo Campo Gravitazionale

  Vettore CampoGravitazionale(Vettore);
  
 private:     
  Vettore m_r; 
  Vettore m_v;
  
};

#endif
/* 
Nel primo costruttore metto in argomento del membro private la parte della classe PUNTOMATERIALE (oggetto della claasse base) Tale procedimento si dice per elencazione
 PM per massa carica si costruisce per delega con il costruttore precedente, dotato di sintassi simile
PUBLIC dopo la definizione di classe PM (non nelle graffe) definisce come i menbri della classe base sono visibili nella classe derivata
definisco Vettore R e V perchè cosi li posso manipolare anche se private
*/
