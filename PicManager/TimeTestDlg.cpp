// TimeTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "TimeTestDlg.h"


// TimeTestDlg �Ի���

IMPLEMENT_DYNAMIC(TimeTestDlg, CDialog)

TimeTestDlg::TimeTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TimeTestDlg::IDD, pParent)
{

}

TimeTestDlg::~TimeTestDlg()
{
	if(testGraph!=NULL)
	delete testGraph;
}

void TimeTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TimeTestDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &TimeTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &TimeTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &TimeTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &TimeTestDlg::OnBnClickedButton4)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON9, &TimeTestDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// TimeTestDlg ��Ϣ�������

void TimeTestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	testGraph->SetGraphType(1);
	Invalidate(TRUE); 

}

void TimeTestDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	testGraph->SetGraphType(0);
	Invalidate(TRUE); 
}

void TimeTestDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	testGraph->SetGraphType(2);
	Invalidate(TRUE); 

}

void TimeTestDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(testGraph!=NULL)
	    delete testGraph;
	testGraph=NULL;
    CDialog::OnOK();
}

BOOL TimeTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	HBITMAP   hBitmap;   
    hBitmap = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP12)); 
   ((CButton *)GetDlgItem(IDC_BUTTON9))->SetBitmap(hBitmap);

	testGraph = new CGraph();
    
	testGraph->SetGraphTitle(_T("Test Results"));
	testGraph->SetTickRange(100);
	testGraph->SetTickSpace(10);
	testGraph->SetXAxisAlignment(0);
	testGraph->SetXAxisLabel(_T("Students"));
    testGraph->SetYAxisLabel(_T("Test Time"));

    CGraphSeries* series1 = new CGraphSeries();
    CGraphSeries* series2 = new CGraphSeries();
    CGraphSeries* series3 = new CGraphSeries();


	series1->SetLabel(_T("ByTitle"));
	series2->SetLabel(_T("ByLoc"));
	series3->SetLabel(_T("ByFootMark"));
	

	series1->SetData(0, 83);
	series1->SetData(1, 78);
	series1->SetData(2, 89);

	series2->SetData(0, 81);
	series2->SetData(1, 75);
	series2->SetData(2, 85);

	series3->SetData(0, 93);
	series3->SetData(1, 87);
	series3->SetData(2, 88);

	testGraph->AddSeries(series1);
	testGraph->AddSeries(series2);
	testGraph->AddSeries(series3);

	testGraph->SetLegend(0, _T("Stu1"));
	testGraph->SetLegend(1, _T("Stu2"));
	testGraph->SetLegend(2, _T("Stu3"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void TimeTestDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	 //���Ʊ���ͼƬ
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
    bmpBackground.LoadBitmap(IDB_BITMAP27); 

	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0,0,rect.Width(), rect.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	

   //����ֱ��ͼ��ͼ
	 CWnd* graphFrame = (CWnd*)GetDlgItem(IDC_STATIC);
     CDC* pDC = graphFrame->GetDC();     
	 testGraph->DrawGraph(pDC);
	 ReleaseDC(pDC);


}

void TimeTestDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
