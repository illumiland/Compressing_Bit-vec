//class for matrix
#ifndef _CMATRIX_H_
#define _CMATRIX_H_
#include "tinyxml.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include "CLookupTable.h"

using namespace std;

class CRange
{
public:
	int m_iStart;
	int m_iEnd;
	unsigned char m_ucIsNull;
	CRange(int iStart = 0, int iEnd = 0, unsigned char ucIsNull = 0xFF)
	{
		m_iStart = iStart;
		m_iEnd = iEnd;
		m_ucIsNull = ucIsNull;
	}
	
	string ToString()
	{
		string res;
		if (m_ucIsNull)
			return "null";
		else
		{
			char szBuf[BUFSIZ];
			sprintf(szBuf, "[%d,%d]", m_iStart, m_iEnd);
			return string(szBuf);
		}
	}
};

class CMatrix
{
protected:
	map<string, vector<int> > m_matrix;
	int m_nElements;
public:
	//constructor: input the sorted elements list
	CMatrix(vector<TiXmlElement*>& m_sortedElements);
	
	//get matrix map
	const map<string, vector<int> >& GetMatrix();

	string BvString();

	map<string, map<string, CRange> > Get2DArray(CLookupTable& lut);
	
	static void Print2DArray(map<string, map<string, CRange> > ary, ostream& out);
	
	//output the matrix
	void Output(ostream& out);
	
	void OutputBV(ostream& out);
};
#endif
