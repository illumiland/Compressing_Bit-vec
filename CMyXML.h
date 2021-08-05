//class for XML parser
#ifndef _CMYXML_H_
#define _CMYXML_H_
#include "tinyxml.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class CMyXML
{
protected:
	TiXmlDocument* m_pDoc;
	TiXmlElement* m_pVirtualDocElement;
	vector<TiXmlElement*> m_res;
	vector<TiXmlElement*> m_LookupTable;

public:
	CMyXML();
	~CMyXML();
	//load a xml from file
	int Load(const char* pFilename);

	//analyse all elements
	void ParseAllElements();

	//sort elements according to its upward path
	void SortElements();

	//get all elements (original order)
	vector<TiXmlElement*>& GetAllElements();

	//get all elements (sorted by upward path)
	vector<TiXmlElement*>& GetSortedElements();

	//travel all elements
	void DOMFindElements(TiXmlElement* pCurrentNode, vector<TiXmlElement*>& vec_Elements);

	//output all elments
	void Output(std::ostream& out);
	
	//get pattern
	vector<string> GetPattern(unsigned int uiLen, int iCnt, bool exp = true);
	
	vector<string> GetPatternXP(unsigned int uiLen, int iCnt, bool exp=true);
};
#endif
