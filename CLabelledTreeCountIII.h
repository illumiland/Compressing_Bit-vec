#ifndef _CLABELLEDTREECOUNT_III_H_
#define _CLABELLEDTREECOUNT_III_H_

#include "CMyVector.h"
#include "CBvMatrix.h"
#include "CBvLookupTable.h"
using namespace sdsl;
class CLabelledTreeCountIII
{
private:
	bit_vector* m_pVec;
	CMyVector* m_pMyVec;
	//sd_vector<>::select_0_type m_sdx_sel;
	CBvMatrix* m_pMatrix;
	CBvLookupTable* m_pLut;
	int m_nAllNodes;
public:
	CLabelledTreeCountIII(CBvMatrix* pMatrix, CBvLookupTable* pLut);
	bool Count(vector<string> pattern, int& iPatternCnt);
};
#endif