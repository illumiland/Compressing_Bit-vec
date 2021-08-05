#include "CMyXML.h"
#include <fstream>

CMyXML::CMyXML()
{
	m_pDoc = (TiXmlDocument*)0;
	m_pVirtualDocElement = (TiXmlElement*)0;
}

CMyXML::~CMyXML()
{
	if (m_pDoc)
		delete m_pDoc;
	if (m_pVirtualDocElement)
		delete m_pVirtualDocElement;
}

int CMyXML::Load(const char* pFilename)
{
	m_pDoc = new TiXmlDocument(pFilename);
	if (!m_pDoc->LoadFile())
		return -1;
	m_pVirtualDocElement = new TiXmlElement(DOCNODE);
	return 0;
}

void CMyXML::ParseAllElements()
{
	m_res.clear();
	TiXmlElement *pRoot = m_pDoc->RootElement();
	TiXmlElement *pWork = pRoot;
	m_res.push_back((m_pVirtualDocElement));
	DOMFindElements(pWork, m_res);
}

void CMyXML::SortElements()
{
	vector<TiXmlElement*>::iterator itElement = m_res.begin();
	m_LookupTable.clear();
	for (; itElement < m_res.end(); itElement++)
		m_LookupTable.push_back(*itElement);
	sort(m_LookupTable.begin(), m_LookupTable.end(), TiXmlElement::EleCompare);
	vector<TiXmlElement*>::iterator it = m_LookupTable.begin();
	int id = 0;
	for(; it < m_LookupTable.end(); it++)
		(*it)->SetElementID(id++);
}

vector<TiXmlElement*>& CMyXML::GetAllElements()
{
	return m_res;
}

vector<TiXmlElement*>& CMyXML::GetSortedElements()
{
	return m_LookupTable;
}

void CMyXML::DOMFindElements(TiXmlElement* pCurrentNode, vector<TiXmlElement*>& vec_Elements)
{
	if (NULL == pCurrentNode)
		return;
	else if (pCurrentNode->NoChildren())
	{
		m_res.push_back(pCurrentNode);
		return;
	}
	else if(!pCurrentNode->NoChildren())//recursively process all child nodes
	{
		m_res.push_back(pCurrentNode);
		TiXmlElement * pChilds = pCurrentNode->FirstChildElement();//get first child
		while ( NULL != pChilds )//recursively process all child nodes
		{
			DOMFindElements(pChilds, vec_Elements);
			pChilds = pChilds->NextSiblingElement();
		}
		return;
	}
}

bool FindString(vector<string>& vec, string target)
{
	vector<string>::iterator it = vec.begin();
	for (; it != vec.end(); it++)
	{
		if (*it == target)
			return true;
	}
	return false;
}

void CMyXML::Output(std::ostream& out)
{
	char buf[BUFSIZ];
	vector<TiXmlElement*> sortedLut = this->GetSortedElements();
	vector<TiXmlElement*>::iterator itp = sortedLut.begin();
	out<<"Elements:"<<endl;
	for(; itp != sortedLut.end(); itp++)
	{
		(*itp)->GetUpwardPath(buf, sizeof(buf));
		out << "Element=\"" << (*itp)->Value() << "\", ID=" << (*itp)->GetElemetnID() << " UpwardPath=" << buf << endl;
	}
}

vector<string> CMyXML::GetPattern(unsigned int uiLen, int iCnt, bool exp)
{
	vector<string> strs;
	vector<string> res;
	vector<string> candidates;
	if (uiLen == 0 || iCnt == 0)
		return res;
	
	char buf2[BUFSIZ];
	vector<TiXmlElement*>::iterator it = m_res.begin();
	for (; it != m_res.end(); it++)
	{
		if ((*it)->GetUpwardPath(buf2, BUFSIZ) > (int)uiLen)
		{
			string s(buf2);
			string _s = s.substr(0, s.length() - 1);
			strs.push_back(_s);
		}
	}
	
	if (strs.size() == 0)
	{
		cout << "Pattern not found" << endl;
		return res;
	}
	
	srand(time(NULL));
	int iDone = 0;
	for (int i = 0; i < strs.size(); i++)
	{
		string test;
		if (strs[i].length() - uiLen == 0)
		{
			test = strs[i];
			if (!FindString(candidates, test))
				candidates.push_back(test);
		}
		else
		{
			for (int  j = 0; j < strs[i].length() - uiLen; j++)
			{
				test = strs[i].substr(j, uiLen);
				if (!FindString(candidates, test))
					candidates.push_back(test);
			}
		}
	}
	
	for (int i = 0; i < 1000; i++)
	{
		int ind1 = rand() % candidates.size();
		int ind2 = rand() % candidates.size();
		string tmp = candidates[ind1];
		candidates[ind1] = candidates[ind2];
		candidates[ind2] = tmp;
	}
	
	for (int i = 0; i < iCnt; i++)
	{
		if (i < candidates.size())
			res.push_back(candidates[i]);
	}
	
	if (exp)
	{
		std::ofstream foutPattern("exp_pattern.txt", ios::out);
		for (int i = 0; i < res.size(); i++)
			foutPattern << res[i] << endl;
		foutPattern.close();
	}
	return res;
}

vector<string> CMyXML::GetPatternXP(unsigned int uiLen, int iCnt, bool exp)
{
	vector<string> strs;
	vector<string> res;
	vector<string> candidates;
	if (uiLen == 0 || iCnt == 0)
		return res;
	
	char buf2[BUFSIZ];
	vector<TiXmlElement*>::iterator it = m_res.begin();
	for (; it != m_res.end(); it++)
	{
		if ((*it)->GetUpwardPath(buf2, BUFSIZ) > (int)uiLen)
		{
			string s(buf2);
			string _s = s.substr(0, s.length() - 1);
			strs.push_back(_s);
		}
	}
	
	if (strs.size() == 0)
	{
		cout << "Pattern not found" << endl;
		return res;
	}
	
	srand(time(NULL));
	int iDone = 0;
	for (int i = 0; i < strs.size(); i++)
	{
		string test;
		if (strs[i].length() - uiLen == 0)
		{
			test = strs[i];
			candidates.push_back(test);
		}
		else
		{
			for (int  j = 0; j < strs[i].length() - uiLen; j++)
			{
				test = strs[i].substr(j, uiLen);
				candidates.push_back(test);
			}
		}
	}
	
	for (int i = 0; i < 1000; i++)
	{
		int ind1 = rand() % candidates.size();
		int ind2 = rand() % candidates.size();
		string tmp = candidates[ind1];
		candidates[ind1] = candidates[ind2];
		candidates[ind2] = tmp;
	}
	
	for (int i = 0; i < iCnt; i++)
	{
		if (i < candidates.size())
		{
			string s = candidates[i];
			reverse(s.begin(), s.end());
			res.push_back(s);
		}
		else
		{
			string s = candidates[i % candidates.size()];
			reverse(s.begin(), s.end());
			res.push_back(s);
		}
	}
	
	if (exp)
	{
		std::ofstream foutPattern("exp_pattern.txt", ios::out);
		for (int i = 0; i < res.size(); i++)
			foutPattern << res[i] << endl;
		foutPattern.close();
	}
	return res;
}
