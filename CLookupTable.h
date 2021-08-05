//class for lookuptable (LUT)
#ifndef _CLOOKUPTABLE_H_
#define _CLOOKUPTABLE_H_
#include "tinyxml.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


class CLookupTable
{
protected:
	map<string, int> m_lut;			//LUT
	map<string, int> m_auxiliary;	//Auxiliary information
	int m_nElements;
public:
	//constructor: input the elements list
	CLookupTable(vector<TiXmlElement*>& m_sortedElements);
	~CLookupTable();
	
	//return the LUT map
	const map<string, int>& GetLUT();

	//return the Auxiliary information
	const map<string, int>& GetAuxiliary();
	
	//print LUT
	void OutputLUT(ostream& out);

	//Print Auxiliary information
	void OutputAuxiliary(ostream& out);
};
#endif
