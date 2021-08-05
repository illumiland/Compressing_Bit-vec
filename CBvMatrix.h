#ifndef _CVMATRIX_H_
#define _CVMATRIX_H_
#include "CMatrix.h"
#include <sdsl/bit_vectors.hpp>
using namespace sdsl;
class CBvMatrix:public CMatrix
{
	bit_vector* m_pBitVec;
	sd_vector<>* m_pSDVec;
	bool isBvMatrixDone;
public:
	CBvMatrix(vector<TiXmlElement*>& m_sortedElements);
	~CBvMatrix();
	
	static void test()
	{
		bit_vector b = {0,1,0,1,1,1,0,0,1};
		sd_vector<> sd(b);
		sd_vector<>::select_0_type sdx_sel(&sd);
		for (int i = 1; i <= 4; i++)
			cout << "i=" << i << " SEL0=" << sdx_sel(i) << endl;
		return;
	}
	
	inline bit_vector* GetBitVec() {return m_pBitVec;}
	inline sd_vector<>* GetSDBitVec() {return m_pSDVec;}
	
	int ParentBV(int nID);
	int ParentSD(int nID);
	double GetSize();
	
	void ParentSDPrepare(sd_vector<>::select_1_type*& pSel1, sd_vector<>::rank_0_type*& pRanker);
	void ParentSDDelete(sd_vector<>::select_1_type*& pSel1, sd_vector<>::rank_0_type*& pRanker);
	int ParentSDRun(sd_vector<>::select_1_type*& pSel1, sd_vector<>::rank_0_type*& pRanker, int nID);
};



#endif
