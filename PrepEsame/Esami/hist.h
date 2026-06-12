#ifndef _HIST
#define _HIST


#include <vector>
#include <TH1D.h>

#include <iostream>

using namespace std;

class hist : public TH1D{
public:
	using TH1D::TH1D;
	
void ReadFile(const char *c);
double GetUnbinnedRMS();
double GetUnbinnedMean();					

private:
vector <double> m_v;

};
#endif
