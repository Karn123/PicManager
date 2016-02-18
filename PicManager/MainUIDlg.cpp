// MainUIDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "MainUI.h"
#include "MainUIDlg.h"
#include "PicExplorerDlg.h"
#include"ReplaceDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMainUIDlg �Ի���




CMainUIDlg::CMainUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainUIDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SearchByTitle, &CMainUIDlg::OnBnClickedButtonSearchbytitle)
	ON_BN_CLICKED(IDC_BUTTON_explore, &CMainUIDlg::OnBnClickedButtonexplore)
	ON_BN_CLICKED(IDC_BUTTON_Track, &CMainUIDlg::OnBnClickedButtonTrack)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainUIDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_Insert, &CMainUIDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_SearchByLoc, &CMainUIDlg::OnBnClickedButtonSearchbyloc)
	ON_BN_CLICKED(IDC_BUTTON_Replace, &CMainUIDlg::OnBnClickedButtonReplace)
	ON_BN_DOUBLECLICKED(IDC_BUTTON_Track, &CMainUIDlg::OnBnDoubleclickedButtonTrack)
	ON_BN_CLICKED(IDC_BUTTON_Testing, &CMainUIDlg::OnBnClickedButtonTesting)
END_MESSAGE_MAP()


// CMainUIDlg ��Ϣ�������

BOOL CMainUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	if(picLibrary.initialization(list_trans)==success)
	{	   
	MessageBox(TEXT("OK,Now photo List is initialized."));
	}

	else
	{
	    MessageBox(TEXT("Error in Photo List initializing."));
	}


	   HBITMAP   hBitmap;   
	   hBitmap = LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP12)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap);
		 // IDB_BITMAP3Ϊ��ԴͼƬID 
		//ͼƬIDB_BITMAP3���ǰ�ťIDC_BUTTON1

	   HBITMAP   hBitmap_1;   
	   hBitmap_1=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP2)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON_explore))->SetBitmap(hBitmap_1);

	    HBITMAP   hBitmap_2;   
	   hBitmap_2= LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP3)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON_Track))->SetBitmap(hBitmap_2);

	   HBITMAP   hBitmap_3;   
	   hBitmap_3=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP5)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON_Remove))->SetBitmap(hBitmap_3);
		
	   HBITMAP   hBitmap_4;   
	   hBitmap_4=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP8)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON_Insert))->SetBitmap(hBitmap_4);

	   HBITMAP   hBitmap_5;   
	   hBitmap_5=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP6)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON_Replace))->SetBitmap(hBitmap_5);

	   HBITMAP   hBitmap_6;   
	   hBitmap_6=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP11)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON_SearchByLoc))->SetBitmap(hBitmap_6);

	   HBITMAP   hBitmap_7;   
	   hBitmap_7=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP9)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON_Testing))->SetBitmap(hBitmap_7);

	   HBITMAP   hBitmap_8;   
	   hBitmap_8=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP10)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON_SearchByTitle))->SetBitmap(hBitmap_8);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMainUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMainUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialog::OnPaint();
		  CPaintDC  dc(this);   
          CRect  rect;   
          GetClientRect(&rect);   
          CDC  dcMem;   
          dcMem.CreateCompatibleDC(&dc);   
          CBitmap  bmpBackground;   
          bmpBackground.LoadBitmap(IDB_BITMAP7);   
		  //IDB_BITMAP7��ͼ��Ӧ��ID,���ñ���ͼƬ
                  
          BITMAP   bitmap;   
          bmpBackground.GetBitmap(&bitmap);   
          CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground); 
		  dc.SetStretchBltMode(COLORONCOLOR);
          dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
		  bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
		  //���ñ���ͼƬ
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMainUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMainUIDlg::OnBnClickedButtonSearchbytitle()
{
	// TODO: Add your control notification handler code here
	CSearchDlg searchDlg(NULL,&picLibrary,&list_trans);
	searchDlg.DoModal();
}

void CMainUIDlg::OnBnClickedButtonexplore()
{
	// TODO: 
	
	CPicExplorerDlg picExplorerDlg(NULL,&picLibrary,&list_trans);

	picExplorerDlg.DoModal();
}

void CMainUIDlg::OnBnClickedButtonTrack()
{
	// TODO:
	SelectionDlg selectionDlg(NULL,&picLibrary,&list_trans);
	selectionDlg.DoModal();
}


void CMainUIDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void CMainUIDlg::OnBnClickedButtonInsert()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CInsertDlg insertDlg(NULL,&picLibrary,&list_trans);
	insertDlg.DoModal();
}

void CMainUIDlg::OnBnClickedButtonSearchbyloc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CSearchByLoc searchByLoc(NULL,&picLibrary,&list_trans);

	searchByLoc.DoModal();

}

void CMainUIDlg::OnBnClickedButtonReplace()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CReplaceDlg replaceDlg(NULL,&picLibrary,&list_trans);
	replaceDlg.DoModal();//������Dlg
	
}

void CMainUIDlg::OnBnDoubleclickedButtonTrack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CFtMarkChinaDlg ChinaFootMarkdlg(NULL,&picLibrary,&list_trans);
	//ChinaFootMarkdlg.DoModal();
	
}

void CMainUIDlg::OnBnClickedButtonTesting()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TimeTestDlg timeDlg(NULL);
	timeDlg.DoModal();
}
