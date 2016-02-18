// SelectionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "SelectionDlg.h"
#include "FootMarkdlg.h"
#include"FtMarkChinaDlg.h"

// SelectionDlg 对话框

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


// SelectionDlg 消息处理程序

void SelectionDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFootMarkdlg footMarkDlg(NULL,picLibraryPtr,my_foot_list);
	footMarkDlg.DoModal();//打开华师大地图
}

void SelectionDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFtMarkChinaDlg ftChinaMarkDlg(NULL,picLibraryPtr,my_foot_list);
	ftChinaMarkDlg.DoModal();//打开中国地图
}

void SelectionDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	  //设置背景图片
		  CPaintDC  dc(this);   
          CRect  rect;   
          GetClientRect(&rect);   
          CDC  dcMem;   
          dcMem.CreateCompatibleDC(&dc);   
          CBitmap  bmpBackground;   
          bmpBackground.LoadBitmap(IDB_BITMAP23);   
		  //IDB_BITMAP4是图对应的ID
          BITMAP   bitmap;   
          bmpBackground.GetBitmap(&bitmap);   
          CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground); 
		  dc.SetStretchBltMode(COLORONCOLOR);
          dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
		  bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
		  //设置背景图片

}

BOOL SelectionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

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
	// 异常: OCX 属性页应返回 FALSE
}

void SelectionDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
