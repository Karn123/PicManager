// ReplaceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "ReplaceDlg.h"
#include<string>
using namespace std;

// CReplaceDlg 对话框

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


// CReplaceDlg 消息处理程序

void CReplaceDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
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
	{//拿到文件名为fileName的PictureRecord
		p.info.height=Height;
		p.info.width=Width;
		p.info.titleEn=Title;
		p.info.location=Loc;
		p.info.map=Map;
		if(pInfoptr->replace(p)==success)
		MessageBox(_T("修改成功！"));
		else  MessageBox(_T("文件名不存在！"));
	}
	else
	    MessageBox(_T("文件名不存在！"));
}


void CReplaceDlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

BOOL CReplaceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  在此添加额外的初始化
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
	m_font->CreatePointFont(150, CString("黑体"), NULL);
	m_edit->SetFont(m_font, TRUE);//改变编辑框字体属性
	
	CEdit *m_edit_1 = (CEdit*)GetDlgItem(IDC_EDIT4);
	CFont *m_font_1 = new CFont;
	m_font_1->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_1->SetFont(m_font_1, TRUE);//改变编辑框字体属性

	CEdit *m_edit_2 = (CEdit*)GetDlgItem(IDC_EDIT5);
	CFont *m_font_2 = new CFont;
	m_font_2->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_2->SetFont(m_font_2, TRUE);//改变编辑框字体属性
	
	CEdit *m_edit_3 = (CEdit*)GetDlgItem(IDC_EDIT6);
	CFont *m_font_3 = new CFont;
	m_font_3->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_3->SetFont(m_font_3, TRUE);//改变编辑框字体属性

	CEdit *m_edit_4 = (CEdit*)GetDlgItem(IDC_EDIT7);
	CFont *m_font_4 = new CFont;
	m_font_4->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_4->SetFont(m_font_4, TRUE);//改变编辑框字体属性
	
	CEdit *m_edit_5 = (CEdit*)GetDlgItem(IDC_EDIT8);
	CFont *m_font_5 = new CFont;
	m_font_5->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_5->SetFont(m_font_5, TRUE);//改变编辑框字体属性
	
	CEdit *m_edit_6 = (CEdit*)GetDlgItem(IDC_1);
	CFont *m_font_6 = new CFont;
	m_font_6->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_6->SetFont(m_font_6, TRUE);//改变编辑框字体属性

	CEdit *m_edit_7 = (CEdit*)GetDlgItem(IDC_2);
	CFont *m_font_7 = new CFont;
	m_font_7->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_7->SetFont(m_font_7, TRUE);//改变编辑框字体属性

	CEdit *m_edit_8= (CEdit*)GetDlgItem(IDC_3);
	CFont *m_font_8 = new CFont;
	m_font_8->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_8->SetFont(m_font_8, TRUE);//改变编辑框字体属性

	CEdit *m_edit_9= (CEdit*)GetDlgItem(IDC_4);
	CFont *m_font_9= new CFont;
	m_font_9->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_9->SetFont(m_font_9, TRUE);//改变编辑框字体属性
	
	CEdit *m_edit_10 = (CEdit*)GetDlgItem(IDC_5);
	CFont *m_font_10= new CFont;
	m_font_10->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_10->SetFont(m_font_10, TRUE);//改变编辑框字体属性

	CEdit *m_edit_11 = (CEdit*)GetDlgItem(IDC_6);
	CFont *m_font_11 = new CFont;
	m_font_11->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_11->SetFont(m_font_11, TRUE);//改变编辑框字体属性

	CEdit *m_edit_12= (CEdit*)GetDlgItem(IDC_7);
	CFont *m_font_12 = new CFont;
	m_font_12->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_12->SetFont(m_font_12, TRUE);//改变编辑框字体属性

	CEdit *m_edit_13 = (CEdit*)GetDlgItem(IDC_8);
	CFont *m_font_13= new CFont;
	m_font_13->CreatePointFont(150, CString("黑体"), NULL);
	m_edit_13->SetFont(m_font_13, TRUE);//改变编辑框字体属性

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CReplaceDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CPaintDC  dc(this);   
    CRect  rect;   
    GetClientRect(&rect);   
    CDC  dcMem;   
    dcMem.CreateCompatibleDC(&dc);   
    CBitmap  bmpBackground;   
    bmpBackground.LoadBitmap(IDB_BITMAP19);   
		  //IDB_BITMAP7是图对应的ID,设置背景图片
                  
    BITMAP   bitmap;   
    bmpBackground.GetBitmap(&bitmap);   
    CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground); 
	dc.SetStretchBltMode(COLORONCOLOR);
    dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
	bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
		  //设置背景图片



}

void CReplaceDlg::OnStnClicked7()
{
	// TODO: 在此添加控件通知处理程序代码
}
