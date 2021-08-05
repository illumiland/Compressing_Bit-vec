#include <iostream>
#include "CMyVector.h"
#include <sdsl/bit_vectors.hpp>
using namespace std;
using namespace sdsl;

int main()
{
	bit_vector b = {0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1};
	sd_vector<> sd(b);
	sd_vector<>::select_0_type sdx_sel(&sd);
	for (int i = 1; i <= 8; i++)
		cout << "i=" << i << " SEL0=" << sdx_sel(i) << endl;
	
	cout << "==============================" << endl;
	
	CMyVector myvec(&b);
	for (int i = 1; i <= 8; i++)
		cout << "i=" << i << " SEL0=" << myvec.Select0(i) << endl;
	return 0;
}
