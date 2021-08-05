//class for XBW
#ifndef _CXBW_H_
#define _CXBW_H_
#include "CMyXML.h"
#include "CMatrix.h"
#include "CLookupTable.h"
#include "CBvMatrix.h"
#include "CBvLookupTable.h"
#include "CLabelledTreeCount.h"
#include "CLabelledTreeCountII.h"
#include "CLabelledTreeCountIII.h"
using namespace std;
#define _MYVEC_
class CXBW
{
	CBvLookupTable* m_pLut;
	CBvMatrix* m_pMatrix;
	CMyXML* m_pXml;
public:
	CXBW(char* pszXMLFile);
	~CXBW();
	
	//parent operation
	int Parent(int nID);

	//label operation
	bool Label(int nID, string& elementName, char* pszPath, int bufflen);
	
	//label using bv
	bool LabelBv(int nID, string& elementName);
	
	int ParentBv(int nID);
	
	int Count(vector<string> patterns, double& mem);
	
	int CountII(vector<string> patterns, double& mem);
	
	vector<string> GetPattern(unsigned int uiLen, int iCnt);
	vector<int> CountAll(vector<vector<string> >& allpatterns, float& timetick, double& mem);
	vector<int> CountAllII(vector<vector<string> >& allpatterns, float& timetick, double& mem);
	
	//print to std output
	void Print();

	//export to file
	void Export();
};
#endif
