#include "CLabelledTreeCountIII.h"
#undef _CLABELLEDTREECOUNT_DEBUG_

CLabelledTreeCountIII::CLabelledTreeCountIII(CBvMatrix* pMatrix, CBvLookupTable* pLut)
{
	m_pMatrix = pMatrix;
	m_pLut = pLut;
	m_nAllNodes = pMatrix->GetMatrix().begin()->second.size();
	cout << "node 1:" <<  pMatrix->GetMatrix().begin()->first << endl;
	cout << "all nodes:" << m_nAllNodes << endl;
	//pMatrix->Output(cout);
	m_pVec = pMatrix->GetBitVec();
	m_pMyVec = new CMyVector(m_pVec);
}

bool CLabelledTreeCountIII::Count(vector<string> pattern, int& iPatternCnt)
{
	iPatternCnt = 0;
	if (pattern.size() >= 2)
	{
		map<string, int> lut = m_pLut->GetLUT();
		if (lut.find(pattern[0]) == lut.end())
			return false;
		CRange currentRange;
		currentRange.m_iStart = lut[pattern[0]];
		map<string, int>::iterator itLut = lut.find(pattern[0]);
		itLut++;
		if (itLut != lut.end())
			currentRange.m_iEnd = itLut->second - 1;
		else
			currentRange.m_iEnd = m_nAllNodes - 1;
		currentRange.m_ucIsNull = 0;
		
		//cout << "-------------------" << currentRange.ToString() <<"-------------------" << endl;
		const map<string, vector<int> >& mat =  m_pMatrix->GetMatrix();
		for (int i = 1; i < pattern.size(); i++)
		{
			int iCnt = 0;
			bool found = false;
			map<string, vector<int> >::const_iterator it = mat.begin();
			//cout << "XXXX " << pattern[i] << endl;
			for (; it != mat.end(); it++)
			{
				if (pattern[i] == it->first)
				{
					found = true;
					break;
				}
				else
					iCnt++;
			}
			if (!found)
			{
				iPatternCnt = 0;
				return false;
			}
			int l = m_nAllNodes * iCnt + currentRange.m_iStart/*-1+1*/;
			int r = m_nAllNodes * iCnt + currentRange.m_iEnd + 1;
			int sell = m_pMyVec->Select0(l);
			int selr = m_pMyVec->Select0(r);
			int rank_l = sell - (l - 1);
			int rank_r = selr - (r - 1);
			currentRange.m_iStart = rank_l + 1;
			currentRange.m_iEnd = rank_r;
			//cout << "=============" << currentRange.ToString() <<"=============" << endl;
		}
		iPatternCnt = currentRange.m_iEnd - currentRange.m_iStart + 1;
		return true;
	}
	else if (pattern.size()  == 1)
	{
		map<string, int> lut = m_pLut->GetLUT();
		if (lut.find(pattern[0]) == lut.end())
			return false;
		CRange currentRange;
		currentRange.m_iStart = lut[pattern[0]];
		map<string, int>::iterator itLut = lut.find(pattern[0]);
		itLut++;
		if (itLut != lut.end())
			currentRange.m_iEnd = itLut->second - 1;
		else
			currentRange.m_iEnd = m_nAllNodes - 1;
		currentRange.m_ucIsNull = 0;
		iPatternCnt = currentRange.m_iEnd - currentRange.m_iStart + 1;
		return true;
	}
	/*
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
	*/
	return false;
}

