#include "CMatrix.h"

CMatrix::CMatrix(vector<TiXmlElement*>& m_sortedElements)
{
	vector<TiXmlElement*>::iterator itElements = m_sortedElements.begin();
	for (; itElements != m_sortedElements.end(); itElements++)
	{
		string strKey((*itElements)->Value());
		if (strKey == DOCNODE)
			continue;	//ignore the virtual root node
		map<string, vector<int> >::iterator itMap = m_matrix.find(strKey);
		if (itMap == m_matrix.end())
		{
			vector<int> row(m_sortedElements.size());
			m_matrix.insert(pair<string, vector<int> >(strKey, row));
		}
		m_nElements = m_sortedElements.size();
		int id = (*itElements)->GetElemetnID();
		int parentid = ((TiXmlElement*)((*itElements)->Parent()))->GetElemetnID();
		char* ptmp = (char*)(*itElements)->Value();
		char* ptmpParent = (char*)((TiXmlElement*)((*itElements)->Parent()))->Value();

		if (((TiXmlElement*)((*itElements)->Parent()))->Type() == TiXmlNode::TINYXML_DOCUMENT)
			m_matrix[strKey][0]++;
		else
		{
			int parentID = ((TiXmlElement*)((*itElements)->Parent()))->GetElemetnID();
			m_matrix[strKey][parentID]++;
		}
	}
}

const map<string, vector<int> >& CMatrix::GetMatrix()
{
	return m_matrix;
}

void CMatrix::Output(ostream& out)
{
	map<string, vector<int> >::iterator itMap = m_matrix.begin();
	out << "Matrix :" << endl;
	for(; itMap != m_matrix.end(); itMap++)
	{
		out << itMap->first << ":\t";
		vector<int>::iterator itVec = itMap->second.begin();
		for (; itVec != itMap->second.end(); itVec++)
			out << (*itVec) << "\t";
		out << endl;
	}
}

void CMatrix::Print2DArray(map<string, map<string, CRange> >  ary, ostream& out)
{
	map<string, map<string, CRange> >::iterator itRow = ary.begin();
	for (; itRow != ary.end(); itRow++)
	{
		out << itRow->first << ":\t";
		map<string, CRange>::iterator itElement = (itRow->second).begin();
		for (; itElement != (itRow->second).end(); itElement++)
		{
			out << itElement->first << ":" << (itElement->second).ToString() << "\t\t";
		}
		out << endl;
	}
}

map<string, map<string, CRange> > CMatrix::Get2DArray(CLookupTable& lut)
{
	map<string, map<string, CRange> > res;
	map<string, int> lutmap = lut.GetLUT();
	map<string, int>::iterator it = lutmap.begin();
	int x = 1, y = 0;
	for (; it != lutmap.end(); it++)
	{
		string key = (*it).first;
		map<string, CRange> col;
		vector<int> vec = m_matrix[key];
		if (vec.size() == 0)
			m_matrix.erase(key);
		
		int i = 0;
		map<string, int>::iterator jt = lutmap.begin();
		for (;jt != lutmap.end(); jt++)
		{
			//cout << "ZFCX" << endl;
			map<string, int>::iterator jtNext = jt;
			jtNext++;
			//cout << "ZFCXX" << endl;
			CRange range;
			if (vec.size() == 0)
			{
				range.m_ucIsNull = 1;
				col.insert(pair<string, CRange>(jt->first, range));
			}
			else if (jtNext != lutmap.end())
			{
				//cout << jtNext->first << endl;
				int iCnt = 0;
				for (; i < (*jtNext).second; i++)
				{
					iCnt += vec[i];
				}
				
				if (iCnt)
				{
					range.m_iStart = x;
					range.m_iEnd = x + iCnt - 1;
					x = x + iCnt;
					range.m_ucIsNull = 0;
				}
				else
					range.m_ucIsNull = 1;
				col.insert(pair<string, CRange>(jt->first, range));
			}
			else 
			{
				int iCnt = 0;
				for (; i < vec.size(); i++)
				{
					iCnt += vec[i];
				}
				
				if (iCnt)
				{
					range.m_iStart = x;
					range.m_iEnd = x + iCnt - 1;
					x = x + iCnt;
					range.m_ucIsNull = 0;
				}
				else
					range.m_ucIsNull = 1;
				col.insert(pair<string, CRange>(jt->first, range));
			}
		}
		res.insert(pair<string, map<string, CRange> >(key, col));
		cout << endl;
	}
	
	return res;
}

string CMatrix::BvString()
{
	string res = "";
	int i = 0;
	map<string, vector<int> >::iterator itMap = m_matrix.begin();
	for(; itMap != m_matrix.end(); itMap++)
	{
		vector<int>::iterator itVec = itMap->second.begin();
		for (; itVec != itMap->second.end(); itVec++)
		{
			int ival = *itVec;
			
			if (ival == 0)
				res += "0";
			else
			{
				for (i = 0; i < ival; i++)
					res += "1";
				res += "0";
			}
		}
	}
	return res;
}

void CMatrix::OutputBV(ostream& out)
{
	string res = "";
	int i = 0;
	map<string, vector<int> >::iterator itMap = m_matrix.begin();
	for(; itMap != m_matrix.end(); itMap++)
	{
		vector<int>::iterator itVec = itMap->second.begin();
		for (; itVec != itMap->second.end(); itVec++)
		{
			int ival = *itVec;
			
			if (ival == 0)
				res += "0";
			else
			{
				for (i = 0; i < ival; i++)
					res += "1";
				res += "0";
			}
		}
	}
	out << res;
}
