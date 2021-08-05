#ifndef _CLABELLEDTREECOUNT_II_H_
#define _CLABELLEDTREECOUNT_II_H_

#include "CMyVector.h"
#include "CBvMatrix.h"
#include "CBvLookupTable.h"

class CLabelledTreeCountII
{
private:
	sd_vector<>* m_pSDVec;
	sd_vector<>::select_0_type m_sdx_sel;
	CBvMatrix* m_pMatrix;
	CBvLookupTable* m_pLut;
	int m_nAllNodes;
public:
	CLabelledTreeCountII(CBvMatrix* pMatrix, CBvLookupTable* pLut);
	bool Count(vector<string> pattern, int& iPatternCnt);
};
#endif