#include <vector>
#include<iostream>

using namespace std;

class vectorn: public vector<double>{
 public:
  using vector<double>::vector;
    //vectorn(int n):vector<double>(n){}
    //vectorn(int n,double val):vectorn(n){
    //for (auto& a:(*this)) a = val;
    //}
    vectorn operator+(comst vectorn&)const;
    vectorn operator*(double)const;
};
