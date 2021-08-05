#ifndef _CMYVECTOR_H_
#define _CMYVECTOR_H_
#include <vector>
#include <sdsl/bit_vectors.hpp>
using namespace std;
using namespace sdsl;
class CMyVector
{
protected:
	vector<int> m_steps0;
	vector<int> m_steps1;
	bool m_IsFake0;
	sd_vector <>* m_pR0;
	rrr_vector<>* m_pR1;
public:
	CMyVector(bit_vector* pBitVec);
	~CMyVector();
	int Select1(int ind);
	int Select0(int ind);
	void debug();
};
#endif
