// SelectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "SelectionDlg.h"
#include "FootMarkdlg.h"
#include"FtMarkChinaDlg.h"

// SelectionDlg �Ի���

IMPLEMENT_DYNAMIC(SelectionDlg, CDialog)

SelectionDlg::SelectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelectionDlg::IDD, pParent)
{

}

SelectionDlg::SelectionDlg(CWnd* pParent , PictureInfoList * picLibraryPtr_,
	List<Node<PictureRecord>*>  *my_foot_list_):CDialog(SelectionDlg::IDD, pParent)
{
	 picLibraryPtr=picLibraryPtr_;
	 my_foot_list=my_foot_list_;
}

SelectionDlg::~SelectionDlg()
{
}

void SelectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SelectionDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &SelectionDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &SelectionDlg::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON3, &SelectionDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// SelectionDlg ��Ϣ�������

void SelectionDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFootMarkdlg footMarkDlg(NULL,picLibraryPtr,my_foot_list);
	footMarkDlg.DoModal();//�򿪻�ʦ���ͼ
}

void SelectionDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFtMarkChinaDlg ftChinaMarkDlg(NULL,picLibraryPtr,my_foot_list);
	ftChinaMarkDlg.DoModal();//���й���ͼ
}

void SelectionDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	  //���ñ���ͼƬ
		  CPaintDC  dc(this);   
          CRect  rect;   
          GetClientRect(&rect);   
          CDC  dcMem;   
          dcMem.CreateCompatibleDC(&dc);   
          CBitmap  bmpBackground;   
          bmpBackground.LoadBitmap(IDB_BITMAP23);   
		  //IDB_BITMAP4��ͼ��Ӧ��ID
          BITMAP   bitmap;   
          bmpBackground.GetBitmap(&bitmap);   
          CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground); 
		  dc.SetStretchBltMode(COLORONCOLOR);
          dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
		  bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
		  //���ñ���ͼƬ

}

BOOL SelectionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	HBITMAP   hBitmap;   
    hBitmap = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP12)); 
   ((CButton *)GetDlgItem(IDC_BUTTON3))->SetBitmap(hBitmap);

	HBITMAP   hBitmap_1;   
    hBitmap_1 = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP25)); 
   ((CButton *)GetDlgItem(IDC_BUTTON2))->SetBitmap(hBitmap_1);
	
	HBITMAP   hBitmap_2;   
    hBitmap_2 = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP24)); 
   ((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap_2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void SelectionDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
