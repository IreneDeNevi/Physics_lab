#ifndef _MYTF1
#define _MYTF1

#include <TF1.h>

class MYTF1:public TF1{
public:
using TF1::TF1;
double Derivata(double x);
double Derivata2(double x);
};
#endif
