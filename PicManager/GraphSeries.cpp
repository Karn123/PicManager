// GraphSeries.cpp : implementation file
//

#include "stdafx.h"
//#include "testdraw.h"
#include "GraphSeries.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphSeries

CGraphSeries::CGraphSeries()
{
	for(int i = 0; i < 10; i++)
		dataValue[i] = 0;
}

CGraphSeries::~CGraphSeries()
{
}


BEGIN_MESSAGE_MAP(CGraphSeries, CStatic)
	//{{AFX_MSG_MAP(CGraphSeries)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphSeries message handlers

void CGraphSeries::SetLabel(CString label)
{
	seriesLabel = label;
}

void CGraphSeries::SetData(int group, int dValue)
{
	dataValue[group] = dValue;
}

CString CGraphSeries::GetLabel()
{
	return seriesLabel;
}

int CGraphSeries::GetData(int group)
{
	return dataValue[group];
}

