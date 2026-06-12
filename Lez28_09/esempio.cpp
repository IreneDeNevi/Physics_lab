#include "esempio.h"
#include <vector>
#include <iostream>
#include <cmath>
vectorn vectorn::operator+(const vectorn& b) const{
  vectorn res(size());
  for (int i=o;i<size();i++)
    res.at(i) = at(i) + b.at(i);
  return res;
}
vectorn vectorn::operator*(double f) const{
   vectorn res(size());
  for (int i=o;i<size();i++)
    res.at(i) = at(i)*f
  return res;
}

int main(){
  vectorn v1(4,1);
  vectorn v2(4,3);
 vectorn v3(4),v4(4);
 v3 = v1+v2;
 for (auto a:v3)
   cout <<a <<endl;


  return 0;
}
