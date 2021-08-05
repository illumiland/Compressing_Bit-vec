#ifndef _CLABELLEDTREECOUNT_H_
#define _CLABELLEDTREECOUNT_H_

#include "CBvMatrix.h"
#include "CBvLookupTable.h"

class CLabelledTreeCount
{
private:
	CBvMatrix* m_pMatrix;
	CBvLookupTable* m_pLut;
	int m_nAllNodes;
	map<string, map<string, CRange> > m_2DArray;
public:
	CLabelledTreeCount(CBvMatrix* pMatrix, CBvLookupTable* pLut);
	static map<int, int> FilterSet(map<int, int> set, CRange range);
	bool Count(vector<string> pattern, int& iPatternCnt, map<int, int>& nodes);
};

#endif
