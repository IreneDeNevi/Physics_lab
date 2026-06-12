#include "Vettore.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool comp(const Vettore &a,const Vettore& b){  //ordina secondo il modulo
  return a.Mod()<b.Mod();
}
int main(){
  Vettore a(1,0,0);
  Vettore b(0,1,0);
  Vettore c(0,0,1);

  double prod = a*b;
  Vettore prodv = a^b;

  cout<<prod<<endl;
  cout<<prodv<<endl;

  vector<Vettore> v;

  ifstream f("dati.dat");
  if (!f.is_open()) {
    cerr << "Cannot open dati.dat" << endl;
    return 1;
  }

  Vettore tmp;   //Vettore temporaneo per il ciclo while
  while(f >> tmp){
    v.push_back(tmp);
  }

  sort(v.begin(),v.end(),comp); //prende come funzione esterna comp

  Vettore sum; //non metto uguale a zero perchè ho già la classe che inizializza correttamente sum
  for(const auto& x : v) {     //range-based loop avoids temporary copies
    cout <<x<<endl;  
    sum = sum+x;
  }
  cout <<"sum = " <<sum <<endl;
  return 0;
}
