// ReplaceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "ReplaceDlg.h"
#include<string>
using namespace std;

// CReplaceDlg �Ի���

IMPLEMENT_DYNAMIC(CReplaceDlg, CDialog)

CReplaceDlg::CReplaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReplaceDlg::IDD, pParent)
	, m_fileName(_T(""))
	, m_Title(_T(""))
	, m_loc(_T(""))
	, m_map(_T(""))
	, m_height(0)
	, m_width(0)
{

}

CReplaceDlg::CReplaceDlg(CWnd* pParent,PictureInfoList * pInfoptr_,
List<Node<PictureRecord>*>  *rp_list_): CDialog(CReplaceDlg::IDD, pParent)
{
	pInfoptr=pInfoptr_;
	rp_list=rp_list_;
}


CReplaceDlg::~CReplaceDlg()
{
}

void CReplaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_fileName);

	DDX_Text(pDX, IDC_EDIT4, m_Title);
	DDX_Text(pDX, IDC_EDIT5, m_loc);
	DDX_Text(pDX, IDC_EDIT6, m_map);
	DDX_Text(pDX, IDC_EDIT7, m_height);
	DDX_Text(pDX, IDC_EDIT8, m_width);
}


BEGIN_MESSAGE_MAP(CReplaceDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CReplaceDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CReplaceDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT7, &CReplaceDlg::OnEnChangeEdit7)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_7, &CReplaceDlg::OnStnClicked7)
END_MESSAGE_MAP()


// CReplaceDlg ��Ϣ�������

void CReplaceDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}


void CReplaceDlg::OnBnClickedOk()
{	
	UpdateData(TRUE);
	string fileName=(CStringA)m_fileName;
	int Height=m_height;
	int Width=m_width;
	string Title=(CStringA)m_Title; //CString -> String
	string Loc=(CStringA)m_loc;
	string Map=(CStringA)m_map;
	
	PictureRecord p;

	if(pInfoptr->searchByKey(fileName,p)==success)
	{//�õ��ļ���ΪfileName��PictureRecord
		p.info.height=Height;
		p.info.width=Width;
		p.info.titleEn=Title;
		p.info.location=Loc;
		p.info.map=Map;
		if(pInfoptr->replace(p)==success)
		MessageBox(_T("�޸ĳɹ���"));
		else  MessageBox(_T("�ļ��������ڣ�"));
	}
	else
	    MessageBox(_T("�ļ��������ڣ�"));
}


void CReplaceDlg::OnEnChangeEdit7()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

BOOL CReplaceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_height=0;
	m_width=0;

	HBITMAP   hBitmap;   
    hBitmap = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP12)); 
   ((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap);
	
	 HBITMAP   hBitmap_1;   
    hBitmap_1 = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP20)); 
	((CButton *)GetDlgItem(IDOK))->SetBitmap(hBitmap_1);

	CEdit *m_edit = (CEdit*)GetDlgItem(IDC_EDIT1);
	CFont *m_font = new CFont;
	m_font->CreatePointFont(150, CString("����"), NULL);
	m_edit->SetFont(m_font, TRUE);//�ı�༭����������
	
	CEdit *m_edit_1 = (CEdit*)GetDlgItem(IDC_EDIT4);
	CFont *m_font_1 = new CFont;
	m_font_1->CreatePointFont(150, CString("����"), NULL);
	m_edit_1->SetFont(m_font_1, TRUE);//�ı�༭����������

	CEdit *m_edit_2 = (CEdit*)GetDlgItem(IDC_EDIT5);
	CFont *m_font_2 = new CFont;
	m_font_2->CreatePointFont(150, CString("����"), NULL);
	m_edit_2->SetFont(m_font_2, TRUE);//�ı�༭����������
	
	CEdit *m_edit_3 = (CEdit*)GetDlgItem(IDC_EDIT6);
	CFont *m_font_3 = new CFont;
	m_font_3->CreatePointFont(150, CString("����"), NULL);
	m_edit_3->SetFont(m_font_3, TRUE);//�ı�༭����������

	CEdit *m_edit_4 = (CEdit*)GetDlgItem(IDC_EDIT7);
	CFont *m_font_4 = new CFont;
	m_font_4->CreatePointFont(150, CString("����"), NULL);
	m_edit_4->SetFont(m_font_4, TRUE);//�ı�༭����������
	
	CEdit *m_edit_5 = (CEdit*)GetDlgItem(IDC_EDIT8);
	CFont *m_font_5 = new CFont;
	m_font_5->CreatePointFont(150, CString("����"), NULL);
	m_edit_5->SetFont(m_font_5, TRUE);//�ı�༭����������
	
	CEdit *m_edit_6 = (CEdit*)GetDlgItem(IDC_1);
	CFont *m_font_6 = new CFont;
	m_font_6->CreatePointFont(150, CString("����"), NULL);
	m_edit_6->SetFont(m_font_6, TRUE);//�ı�༭����������

	CEdit *m_edit_7 = (CEdit*)GetDlgItem(IDC_2);
	CFont *m_font_7 = new CFont;
	m_font_7->CreatePointFont(150, CString("����"), NULL);
	m_edit_7->SetFont(m_font_7, TRUE);//�ı�༭����������

	CEdit *m_edit_8= (CEdit*)GetDlgItem(IDC_3);
	CFont *m_font_8 = new CFont;
	m_font_8->CreatePointFont(150, CString("����"), NULL);
	m_edit_8->SetFont(m_font_8, TRUE);//�ı�༭����������

	CEdit *m_edit_9= (CEdit*)GetDlgItem(IDC_4);
	CFont *m_font_9= new CFont;
	m_font_9->CreatePointFont(150, CString("����"), NULL);
	m_edit_9->SetFont(m_font_9, TRUE);//�ı�༭����������
	
	CEdit *m_edit_10 = (CEdit*)GetDlgItem(IDC_5);
	CFont *m_font_10= new CFont;
	m_font_10->CreatePointFont(150, CString("����"), NULL);
	m_edit_10->SetFont(m_font_10, TRUE);//�ı�༭����������

	CEdit *m_edit_11 = (CEdit*)GetDlgItem(IDC_6);
	CFont *m_font_11 = new CFont;
	m_font_11->CreatePointFont(150, CString("����"), NULL);
	m_edit_11->SetFont(m_font_11, TRUE);//�ı�༭����������

	CEdit *m_edit_12= (CEdit*)GetDlgItem(IDC_7);
	CFont *m_font_12 = new CFont;
	m_font_12->CreatePointFont(150, CString("����"), NULL);
	m_edit_12->SetFont(m_font_12, TRUE);//�ı�༭����������

	CEdit *m_edit_13 = (CEdit*)GetDlgItem(IDC_8);
	CFont *m_font_13= new CFont;
	m_font_13->CreatePointFont(150, CString("����"), NULL);
	m_edit_13->SetFont(m_font_13, TRUE);//�ı�༭����������

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CReplaceDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CPaintDC  dc(this);   
    CRect  rect;   
    GetClientRect(&rect);   
    CDC  dcMem;   
    dcMem.CreateCompatibleDC(&dc);   
    CBitmap  bmpBackground;   
    bmpBackground.LoadBitmap(IDB_BITMAP19);   
		  //IDB_BITMAP7��ͼ��Ӧ��ID,���ñ���ͼƬ
                  
    BITMAP   bitmap;   
    bmpBackground.GetBitmap(&bitmap);   
    CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground); 
	dc.SetStretchBltMode(COLORONCOLOR);
    dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
	bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
		  //���ñ���ͼƬ



}

void CReplaceDlg::OnStnClicked7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
