#include "MYTF1.h"
#include <TF1.h>

double MYTF1::Derivata(double x){
  double eps = 1e-6;
  return (Eval(x+eps)-Eval(x-eps))/(2*eps);
}

double MYTF1::Zero(double x0, int par,int N,double tau){
  double X=x0;
  double Xn =x0;
  if(par==0){
    Xn = X-(Eval(X)/Derivata(X));
    while(Xn-X>tau){
      Xn= X-(Eval(X)/Derivata(X));
      X=Xn;
  }
}
  if(par==1){
    for (int i = 0;i<N;i++){
      Xn = X-(Eval(X) /Derivata(X));
      X=Xn;
	}
  }
  return Xn;
}
