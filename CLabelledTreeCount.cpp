#include "CLabelledTreeCount.h"
#undef _CLABELLEDTREECOUNT_DEBUG_

CLabelledTreeCount::CLabelledTreeCount(CBvMatrix* pMatrix, CBvLookupTable* pLut)
{
	m_pMatrix = pMatrix;
	m_pLut = pLut;
	m_nAllNodes = pMatrix->GetMatrix().begin()->second.size();
	cout << "node 1:" <<  pMatrix->GetMatrix().begin()->first << endl;
	cout << "all nodes:" << m_nAllNodes << endl;
	pMatrix->Output(cout);
	m_2DArray = pMatrix->Get2DArray(*pLut);
}

map<int, int> CLabelledTreeCount::FilterSet(map<int, int> set, CRange range)
{
	map<int, int> res;
	if (!range.m_ucIsNull)
	{
		map<int, int>::iterator it = set.begin();
		for (; it != set.end(); it++)
		{
			if ((*it).first <= range.m_iEnd && (*it).first >= range.m_iStart)
				res.insert(pair<int, int>((*it).first, 0));
		}
		return res;
	}
	return res;
}

bool CLabelledTreeCount::Count(vector<string> pattern, int& iPatternCnt, map<int, int>& nodes)
{
	if (pattern.size() >= 2)
	{
		map<string, int> lut = m_pLut->GetLUT();
		map<int, int> set;
		string lastString = pattern[pattern.size() - 1];
		int iTmpStart = lut[lastString];
		map<string, int>::iterator itLut = lut.find(lastString);
		itLut++;
		int iTmpEnd = -1;
		if (itLut != lut.end())
			iTmpEnd = (*itLut).second - 1;
		else
			iTmpEnd = m_nAllNodes - 1;
		for (int i = iTmpStart; i <= iTmpEnd; i++)
		{
			set.insert(pair<int, int>(i, 0));
		}
		
		sd_vector<>::select_1_type* pSel1 = 0x00;
		sd_vector<>::rank_0_type* pRanker = 0x00;
		m_pMatrix->ParentSDPrepare(pSel1, pRanker);
		
		
		for (int i = pattern.size() - 1; i >=1; i--)
		{
			string rowInd = pattern[i];
			string colInd = pattern[i - 1];
			#ifdef _CLABELLEDTREECOUNT_DEBUG_
			cout << "row:" << rowInd << " col:" << colInd << endl;
			#endif
			CRange range =  m_2DArray[rowInd][colInd];
			#ifdef _CLABELLEDTREECOUNT_DEBUG_
			cout << range.ToString() << endl;
			#endif
			map<int, int> filteredSet = FilterSet(set, range);
			map<int, int>::iterator it  = filteredSet.begin();
			set.clear();
			//cout << "ST0" << endl;
			for (; it != filteredSet.end(); it++)
			{
				//int parent = m_pMatrix->ParentBV(it->first);
				int parent =  m_pMatrix->ParentSDRun( pSel1, pRanker, it->first);
				if (set.find(parent) == set.end())
				{
					set.insert(pair<int, int>(parent, 0));
				}
			}
			//cout << "Start2" << endl;
			#ifdef _CLABELLEDTREECOUNT_DEBUG_
			cout << "--------" << endl;
			#endif
		}
		m_pMatrix->ParentSDDelete( pSel1, pRanker);
		iPatternCnt = set.size();
		nodes = set;
		return true;
	}
	else if (pattern.size()  == 1)
	{
			map<string, int> lut = m_pLut->GetLUT();
			if (lut.find(pattern[0]) == lut.end())
				return 0;
			int iTmpStart = lut[pattern[0]];
			map<string, int>::iterator itLut = lut.find(pattern[0]);
			itLut++;
			int iTmpEnd = -1;
			if (itLut != lut.end())
				iTmpEnd = (*itLut).second - 1;
			else
				iTmpEnd = m_nAllNodes - 1;
			iPatternCnt = iTmpEnd - iTmpStart + 1;
			map<int, int> set;
			for (int i = iTmpStart; i <= iTmpEnd; i++)
				set.insert(pair<int, int>(i, 0));
			nodes = set;
			return true;
	}
	return false;
}

