#include "CMyVector.h"
#include <iostream>
#include <fstream>
using namespace std;

CMyVector::CMyVector(bit_vector* pBitVec)
{
	if ((*pBitVec)[0])
		m_IsFake0 = true;
	else
		m_IsFake0 = false;
	
	m_steps0.clear();
	m_steps1.clear();
	
	int iCnt0 = 0;
	int iCnt1 = 0;
	int iCnt = 0;
	
	//cout << "pl1" << endl;
	
	if (m_IsFake0)
	{
		iCnt0 = 1;
		iCnt = 1;
		m_steps0.push_back(iCnt);
		iCnt = 0;
	}
	
	//cout << "pl2" << endl;
	//cout << pBitVec->size() << endl;
	for (int i = 0; i < pBitVec->size(); i++)
	{
		if ((*pBitVec)[i])
			iCnt1 ++;
		else
			iCnt0 ++;
		iCnt++;
		if (i + 1 < pBitVec->size())
		{
			if ((*pBitVec)[i] && !(*pBitVec)[i+1])			//1=>0
			{
				m_steps1.push_back(iCnt);
				iCnt = 0;
			}
			else if (!(*pBitVec)[i] && (*pBitVec)[i+1])	//0=>1
			{
				m_steps0.push_back(iCnt);
				iCnt = 0;
			}
		} 
		else
		{
			if ((*pBitVec)[i])
				m_steps1.push_back(iCnt);
			else
				m_steps0.push_back(iCnt);
			iCnt = 0;
		}
	}
	//cout << "pl3s" << endl;
	bit_vector btmp0(iCnt0, 0);
	bit_vector btmp1(iCnt1, 0);
	int iTmp = 0;
	for (int i = 0; i < m_steps0.size(); i++)
	{
		iTmp += m_steps0[i];
		//for (int j = 0; j <=i; j++)
		//{
		//	iTmp += m_steps0[j];
		//}
		btmp0[iTmp - 1] = 1;
	}
	//cout << "\nR0" << endl;
	//cout << btmp0 << endl;
	//cout << "pl4s" << endl;
	iTmp = 0;
	for (int i = 0; i < m_steps1.size(); i++)
	{
		iTmp += m_steps1[i];
		//for (int j = 0; j <=i; j++)
		//{
		//	iTmp += m_steps1[j];
		//}
		btmp1[iTmp - 1] = 1;
	}
	//cout << "R1" << endl;
	//cout << btmp1 << endl;
	//cout << "pl5s" << endl;
	m_pR0 = new sd_vector <>(btmp0);
	m_pR1 = new rrr_vector<>(btmp1);
	cout << "My Vector Constructed!" << endl;
	cout << "\nR0" << endl;
	cout << btmp0 << endl;
	cout << "\nR1" << endl;
	cout << btmp1 << endl;
	cout << "R0, size_in_mega_bytes:" << size_in_mega_bytes(*m_pR0) << endl;
	cout << "R1, size_in_mega_bytes:" << size_in_mega_bytes(*m_pR1) << endl;
	cout << "Total, size_in_mega_bytes:" << size_in_mega_bytes(*m_pR0) + size_in_mega_bytes(*m_pR1) << endl;
	sd_vector<>::rank_1_type rank1r0(m_pR0);
	rrr_vector<>::rank_1_type rank1r1(m_pR1);
	cout << "1 in R0 :" << rank1r0(m_pR0->size()) << endl;
	cout << "1 in R1 :" << rank1r1(m_pR1->size()) << endl;
	cout << endl;
	
	ofstream fout("myvectorinfo.txt", ios::out);
	fout << "\nR0" << endl;
	fout << btmp0 << endl;
	fout << "\nR1" << endl;
	fout << btmp1 << endl;
	fout << "R0, size_in_mega_bytes:" << size_in_mega_bytes(*m_pR0) << endl;
	fout << "R1, size_in_mega_bytes:" << size_in_mega_bytes(*m_pR1) << endl;
	fout << "Total, size_in_mega_bytes:" << size_in_mega_bytes(*m_pR0) + size_in_mega_bytes(*m_pR1) << endl;
	fout << "1 in R0 :" << rank1r0(m_pR0->size()) << endl;
	fout << "1 in R1 :" << rank1r1(m_pR1->size()) << endl;
	fout.close();
}

CMyVector::~CMyVector()
{
	delete m_pR0;
	delete m_pR1;
}

void CMyVector::debug()
{
	vector<int>::iterator it0 = m_steps0.begin();
	vector<int>::iterator it1 = m_steps1.begin();
	
	cout << "\n=======================================" << endl;
	cout << "B0: " << endl;
	for (; it0 < m_steps0.end(); it0++)
	{
		cout << (*it0) << " ";
	}
	cout << endl;
	
	cout << "B1: " << endl;
	for (; it1 < m_steps1.end(); it1++)
	{
		cout << (*it1) << " ";
	}
	cout << endl;
	cout << "R0:\n" << *m_pR0 << endl;
	cout << "R1:\n" << *m_pR1 << endl;
}

int CMyVector::Select1(int ind)
{
	if (!m_IsFake0)
	{
		rrr_vector<>::rank_1_type rrrb_rank(m_pR1);
		int x = rrrb_rank(ind - 1);
		sd_vector<>::select_1_type b_sel(m_pR0);
		int y = b_sel(x + 1);
		return y + ind;
	}
	else
	{
		rrr_vector<>::rank_1_type rrrb_rank(m_pR1);
		int x = rrrb_rank(ind - 1);
		sd_vector<>::select_1_type b_sel(m_pR0);
		int y = b_sel(x + 1);
		return y + ind - 1;
	}
}

int CMyVector::Select0(int ind)
{
	if (!m_IsFake0)
	{
		sd_vector<>::rank_1_type sdb_rank(m_pR0);
		int x = sdb_rank(ind - 1);
		if (x == 0)
			return ind - 1;
		rrr_vector<>::select_1_type rrr_sel(m_pR1);
		int y = rrr_sel(x);
		return ind + y;
	}
	else
	{
		sd_vector<>::rank_1_type sdb_rank(m_pR0);
		int x = sdb_rank(ind);
		if (x == 0)
			return ind;
		rrr_vector<>::select_1_type rrr_sel(m_pR1);
		int y = rrr_sel(x);
		return ind + y;
	}
}
