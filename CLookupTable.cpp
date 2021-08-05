#include "CLookupTable.h"

CLookupTable::CLookupTable(vector<TiXmlElement*>& m_sortedElements)
{
	m_lut.clear();
	m_auxiliary.clear();
	vector<TiXmlElement*>::iterator itElements = m_sortedElements.begin();
	m_nElements = m_sortedElements.size();

	//use a map to count number of each element
	int i = 0;
	for (; itElements != m_sortedElements.end(); itElements++)
	{
		string strKey((*itElements)->Value());
		map<string, int>::iterator itMap = m_lut.find(strKey);
		if (itMap == m_lut.end())
			m_lut.insert(pair<string, int>(strKey, i++));
		else
			i++;
	}

	map<string, int>::iterator itLut = m_lut.begin();
	itLut++;
	for (; itLut != m_lut.end(); itLut++)
	{
		map<string, int>::iterator itNext = itLut;
		itNext++;
		if (itNext != m_lut.end())
		{
			m_auxiliary.insert(pair<string, int>(itLut->first, itNext->second - 1));
		}
		else
		{
			m_auxiliary.insert(pair<string, int>(itLut->first, m_sortedElements.size() - 1));
		}
	}
	
}

CLookupTable::~CLookupTable()
{

}

void CLookupTable::OutputLUT(ostream& out)
{
	map<string, int>::iterator itMap = m_lut.begin();
	
	out << "Look Up Table:" << endl;
	for(; itMap != m_lut.end(); itMap++)
		out << itMap->first << "\t" << itMap->second <<endl;
}

void CLookupTable::OutputAuxiliary(ostream& out)
{
	map<string, int>::iterator itAuxiliary = m_auxiliary.begin();
	out << "Auxiliary:" << endl;
	for(; itAuxiliary != m_auxiliary.end(); itAuxiliary++)
		out << itAuxiliary->first << "\t" << itAuxiliary->second <<endl;
}

const map<string, int>& CLookupTable::GetLUT()
{
	return m_lut;
}

const map<string, int>& CLookupTable::GetAuxiliary()
{
	return m_auxiliary;
}
