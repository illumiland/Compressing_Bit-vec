#include "CBvLookupTable.h"

CBvLookupTable::CBvLookupTable(vector<TiXmlElement*>& m_sortedElements)
					:CLookupTable(m_sortedElements)
{
	string strLast(m_sortedElements[m_sortedElements.size() - 1]->Value());
	map<string, int>::iterator itLut = m_lut.begin();
	int iLast = m_lut[strLast];
	m_pBitVec = new bit_vector(iLast + 1, 0);
	itLut = m_lut.begin();
	for (; itLut != m_lut.end(); itLut++)
	{
		cout << itLut->second << endl;
		(*m_pBitVec)[itLut->second] = 1;
	}
	
	m_pSdVec = new sd_vector<>(*m_pBitVec);
}

CBvLookupTable::~CBvLookupTable()
{
	if (m_pBitVec)
		delete m_pBitVec;
	delete	m_pSdVec;
}

bool CBvLookupTable::LabelBV(int nID, string& elementName)
{
	if (nID >= m_nElements)
		return false;

	rank_support_v<1> rank_bitvector(m_pBitVec);
	
	int irank = rank_bitvector(nID);
	irank += (*m_pBitVec)[nID];
	map<string, int>::iterator itLut = m_lut.begin();
	for (int i = 0; i < irank - 1; i++)
		itLut++;
	elementName = (*itLut).first;
	return true;
}

bool CBvLookupTable::LabelSD(int nID, string& elementName)
{
	if (nID >= m_nElements)
		return false;

	sd_vector<>::rank_1_type ranker(m_pSdVec);

	int irank = ranker(nID);
	irank += (*m_pBitVec)[nID];
	map<string, int>::iterator itLut = m_lut.begin();
	for (int i = 0; i < irank - 1; i++)
		itLut++;
	elementName = (*itLut).first;
	return true;
}
