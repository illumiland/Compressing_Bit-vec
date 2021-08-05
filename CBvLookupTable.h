#ifndef _CBVLOOKUP_TABLE_H_
#define _CBVLOOKUP_TABLE_H_
#include <sdsl/bit_vectors.hpp>
#include "CLookupTable.h"
using namespace sdsl;

class CBvLookupTable:public CLookupTable
{
protected:
	bit_vector* m_pBitVec;
	sd_vector<>* m_pSdVec;
public:
	CBvLookupTable(vector<TiXmlElement*>& m_sortedElements);
	~CBvLookupTable();	
	bool LabelBV(int nID, string& elementName);
	bool LabelSD(int nID, string& elementName);
};

#endif
