#include "CXBW.h"
#include <fstream>

CXBW::CXBW(char* pszXMLFile)
{
	m_pXml = new CMyXML();
	m_pXml->Load(pszXMLFile);
	m_pXml->ParseAllElements();
	m_pXml->SortElements();
	m_pLut = new CBvLookupTable(m_pXml->GetSortedElements());
	m_pMatrix = new CBvMatrix(m_pXml->GetSortedElements());
}

CXBW::~CXBW()
{
	if (m_pXml) 
		delete m_pXml;
	if (m_pLut)
		delete m_pLut;
	if (m_pMatrix)
		delete m_pMatrix;
}

int CXBW::Parent(int nID)
{
	if (nID <= 0)
		return -1;
	
	map<string, vector<int> > matrix = m_pMatrix->GetMatrix();
	map<string, int> lut = m_pLut->GetLUT();
	map<string, int> auxiliary = m_pLut->GetAuxiliary();
	map<string, int>::iterator itAux = auxiliary.begin();
	bool found = false;
	string label;
	for (;itAux != auxiliary.end(); itAux++)
	{
		if (itAux->second >= nID)
		{
			found = true;
			label = itAux->first;
			break;
		}
	}
	if (!found)
		return -1;
	int index = lut[label];
	int iSeq = nID - index + 1;
	vector<int> row = matrix[label];
	vector<int>::iterator it = row.begin();
	int iSum = 0;
	for (;it != row.end(); it++)
	{
		iSum += (*it);
		if (iSeq <= iSum)
			return (it - row.begin());
	}
	return -1;
}


bool CXBW::Label(int nID, string& elementName, char* pszPath, int bufflen)
{
	vector<TiXmlElement*> elements = m_pXml->GetSortedElements();
	vector<TiXmlElement*>::iterator it = elements.begin();
	string res = "";
	for (; it != elements.end(); it++)
	{
		TiXmlElement* pElement = *it;
		if (pElement->GetElemetnID() == nID)
		{
			res = string(pElement->Value());
			elementName = res;
			pElement->GetUpwardPath(pszPath, bufflen);
			return true;
		}
	}
	return false;
}

int CXBW::ParentBv(int nID)
{
	return m_pMatrix->ParentBV(nID);
}


bool CXBW::LabelBv(int nID, string& elementName)
{
	return m_pLut->LabelSD(nID, elementName);
}

vector<string> CXBW::GetPattern(unsigned int uiLen, int iCnt)
{
	return m_pXml->GetPatternXP(uiLen, iCnt);
}

int CXBW::Count(vector<string> patterns, double& mem)
{
	CLabelledTreeCount counter(m_pMatrix, m_pLut);
	int iPatternCnt = 0;
	map<int, int> zzd;
	counter.Count(patterns, iPatternCnt, zzd);
	mem = m_pMatrix->GetSize();
	return iPatternCnt;
}

int CXBW::CountII(vector<string> patterns, double& mem)
{
	#ifdef _MYVEC_
	cout << "USING CMYVECTOR" << endl;
	CLabelledTreeCountIII counter(m_pMatrix, m_pLut);
	#else
	CLabelledTreeCountII counter(m_pMatrix, m_pLut);
	#endif
	int iPatternCnt = 0;
	counter.Count(patterns, iPatternCnt);
	mem = m_pMatrix->GetSize();
	return iPatternCnt;
}

vector<int> CXBW::CountAll(vector<vector<string> >& allpatterns, float& timetick, double& mem)
{
	CLabelledTreeCount counter(m_pMatrix, m_pLut);
	int iPatternCnt = 0;
	vector<int> res;
	vector<vector<string> >::iterator it = allpatterns.begin();
	cout << "counting patterns from file" << endl;
	
	struct timeval start, end;
    int interval;
    gettimeofday(&start, NULL);
	for(; it != allpatterns.end(); it++)
	{
		iPatternCnt = 0;
		map<int, int> zzd;
		vector<string>::iterator itt = (*it).begin();
		cout << endl;
		
		counter.Count((*it), iPatternCnt, zzd);
		//cout << iPatternCnt << endl;
		res.push_back(iPatternCnt);
	}
	gettimeofday(&end, NULL);
	interval = 1000000*(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
	timetick = interval / 1000.0;
	mem = m_pMatrix->GetSize();
	return res;
}

vector<int> CXBW::CountAllII(vector<vector<string> >& allpatterns, float& timetick, double& mem)
{
	#ifdef _MYVEC_
	cout << "USING CMYVECTOR" << endl;
	CLabelledTreeCountIII counter(m_pMatrix, m_pLut);
	#else
	CLabelledTreeCountII counter(m_pMatrix, m_pLut);
	#endif
	int iPatternCnt = 0;
	vector<int> res;
	vector<vector<string> >::iterator it = allpatterns.begin();
	cout << "counting patterns from file" << endl;
	
	struct timeval start, end;
    int interval;
    gettimeofday(&start, NULL);
	for(; it != allpatterns.end(); it++)
	{
		iPatternCnt = 0;
		vector<string>::iterator itt = (*it).begin();
		cout << endl;
		
		counter.Count((*it), iPatternCnt);
		//cout << iPatternCnt << endl;
		res.push_back(iPatternCnt);
	}
	gettimeofday(&end, NULL);
	interval = 1000000*(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec);
	timetick = interval / 1000.0;
	mem = m_pMatrix->GetSize();
	return res;
}

void CXBW::Print()
{
	//cout << "Elements:" << endl;
	m_pXml->Output(cout);
	cout << "=================================" << endl;
	//cout << "Matrix:" << endl;
	m_pMatrix->Output(cout);
	cout << "=================================" << endl;
	//cout << "Look up table:" << endl;
	m_pLut->OutputLUT(cout);
	cout << "=================================" << endl;
	//cout << "Auxiliary information:" << endl;
	m_pLut->OutputAuxiliary(cout);
	
	ofstream fouarr("arr.txt", ios::out);
	CMatrix::Print2DArray(m_pMatrix->Get2DArray(*m_pLut), fouarr);
	fouarr.close();
}

#undef _DEBUGINFO

void CXBW::Export()
{
#ifdef _DEBUGINFO
	ofstream foutElements("exp_elements.txt", ios::out);
	ofstream foutMatrix("exp_matrix.txt", ios::out);
#endif
	ofstream foutMatrixBV("exp_matrix.BV", ios::out);
	ofstream foutLut("exp_lut.aux", ios::out);
#ifdef _DEBUGINFO
	ofstream foutAuxiliary("exp_auxiliary.txt", ios::out);
#endif

#ifdef _DEBUGINFO
	m_pXml->Output(foutElements);
	m_pMatrix->Output(foutMatrix);
#endif

	m_pMatrix->OutputBV(foutMatrixBV);
	m_pLut->OutputLUT(foutLut);

#ifdef _DEBUGINFO
	m_pLut->OutputAuxiliary(foutAuxiliary);
#endif

#ifdef _DEBUGINFO
	foutElements.close();
	foutMatrix.close();
#endif

	foutMatrixBV.close();
	foutLut.close();
	
#ifdef _DEBUGINFO
	foutAuxiliary.close();
#endif
}
