#include "CBvMatrix.h"

CBvMatrix::CBvMatrix(vector<TiXmlElement*>& m_sortedElements)
	:CMatrix(m_sortedElements)
{
	string bvString = BvString();
	m_pBitVec = new bit_vector(bvString.length(), 0);
	string::iterator it = bvString.begin();
	for (int i = 0; it != bvString.end(); i++, it++)
		if ((*it) == '1')
			(*m_pBitVec)[i] = 1;
	
	m_pSDVec = new sd_vector<>(*m_pBitVec);
}

CBvMatrix::~CBvMatrix()
{
	if (m_pBitVec)
		delete m_pBitVec;
	delete m_pSDVec;
}

int CBvMatrix::ParentBV(int nID)
{
	bit_vector::select_1_type sel1(m_pBitVec);
	rank_support_v<0> rank_bitvector(m_pBitVec);
	int selectID = sel1(nID);
	int rank = rank_bitvector(selectID);
	int iParent = rank % m_nElements;
	return iParent;
}



int CBvMatrix::ParentSD(int nID)
{
	sd_vector<>::select_1_type sel1(m_pSDVec);
	//rank_support_v<0> rank_bitvector(m_pSDVec);
	sd_vector<>::rank_0_type ranker(m_pSDVec);
	
	int selectID = sel1(nID);
	int rank = ranker(selectID);
	int iParent = rank % m_nElements;
	return iParent;
}

void CBvMatrix::ParentSDPrepare(sd_vector<>::select_1_type*& pSel1, sd_vector<>::rank_0_type*& pRanker)
{
	pSel1 = new sd_vector<>::select_1_type(m_pSDVec);
	pRanker = 	new sd_vector<>::rank_0_type (m_pSDVec);
	return ;
}

void CBvMatrix::ParentSDDelete(sd_vector<>::select_1_type*& pSel1, sd_vector<>::rank_0_type*& pRanker)
{
	delete pSel1;
	delete pRanker;
	return;
}

int CBvMatrix::ParentSDRun(sd_vector<>::select_1_type*& pSel1, sd_vector<>::rank_0_type*& pRanker, int nID)
{
	int selectID = (*pSel1)(nID);
	int rank = (*pRanker)(selectID);
	int iParent = rank % m_nElements;
	return iParent;
}

double CBvMatrix::GetSize()
{
	return size_in_mega_bytes(*m_pSDVec);
}
