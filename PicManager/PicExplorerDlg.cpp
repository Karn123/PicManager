// PicExplorerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "PicExplorerDlg.h"
#include "atlImage.h"

// CPicExplorerDlg 对话框

IMPLEMENT_DYNAMIC(CPicExplorerDlg, CDialog)

CPicExplorerDlg::CPicExplorerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPicExplorerDlg::IDD, pParent)
{

}

CPicExplorerDlg::~CPicExplorerDlg()
{
}


CPicExplorerDlg::CPicExplorerDlg(CWnd* pParent,PictureInfoList *picListptr_,
								 List<Node<PictureRecord>*>  *r_list_)
: CDialog(CPicExplorerDlg::IDD, pParent)
{
	picListptr=picListptr_;
	r_list =r_list_;
}

void CPicExplorerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC1, m_Pic1);
}


BEGIN_MESSAGE_MAP(CPicExplorerDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CPicExplorerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPicExplorerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTONExit, &CPicExplorerDlg::OnBnClickedButtonexit)
	ON_BN_CLICKED(IDC_BUTTON3, &CPicExplorerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPicExplorerDlg::OnBnClickedButton4)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, &CPicExplorerDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CPicExplorerDlg 消息处理程序

BOOL CPicExplorerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//最大化Dialog，显示美观。
	//ShowWindow(SW_SHOWMAXIMIZED);


	// TODO:
	// TODO: 在此添加额外的初始化代码

		current = 0; //默认打开第一张图片
		basePath = "d:\\picLibrary\\"; //设置图片库的位置
		
		count=r_list->size(); //图片总的数量
		Node<PictureRecord> *p;
		r_list->retrieve(current,p);
		filename=p->entry.the_key().c_str();
		
		/*PictureRecord picRec;
		picListptr->retrieve(current,picRec); */
		//filename=picRec.the_key().c_str();//文件名 string-》CString

	  filename = basePath+filename; //全名
		//添加额外代码
	   HBITMAP   hBitmap;   
	   hBitmap=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP12)); 
	   ((CButton *)GetDlgItem(IDC_BUTTONExit))->SetBitmap(hBitmap);
		 // IDB_BITMAP12为资源图片ID 
		//图片IDB_BITMAP12覆盖按钮IDC_BUTTONExit

	   HBITMAP   hBitmap_1;   
	   hBitmap_1=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP13)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON2))->SetBitmap(hBitmap_1);
		 // IDB_BITMAP13为资源图片ID 
		//图片IDB_BITMAP13覆盖按钮IDC_BUTTON2

	   HBITMAP   hBitmap_2;   
	   hBitmap_2=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP14)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap_2);
		
	   HBITMAP   hBitmap_3;   
	   hBitmap_3=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP16)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON3))->SetBitmap(hBitmap_3);
		
	   HBITMAP   hBitmap_4;   
	   hBitmap_4=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP31)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON4))->SetBitmap(hBitmap_4);

	   HBITMAP   hBitmap_5;   
	   hBitmap_5=LoadBitmap(AfxGetInstanceHandle(),   
	   MAKEINTRESOURCE(IDB_BITMAP30)); 
	   ((CButton *)GetDlgItem(IDC_BUTTON5))->SetBitmap(hBitmap_5);
	    
	

		return TRUE;  // return TRUE unless you set the focus to a control
	
}

void CPicExplorerDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting

	//CDialog::OnPaint();
  
	
	  //设置背景图片
		  CPaintDC  dc(this);   
          CRect  rect;   
          GetClientRect(&rect);   
          CDC  dcMem;   
          dcMem.CreateCompatibleDC(&dc);   
          CBitmap  bmpBackground;   
          bmpBackground.LoadBitmap(IDB_BITMAP4);   
		  //IDB_BITMAP4是图对应的ID
          BITMAP   bitmap_1;   
          bmpBackground.GetBitmap(&bitmap_1);   
          CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground); 

		  dc.SetStretchBltMode(COLORONCOLOR);

          dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
		  bitmap_1.bmWidth,bitmap_1.bmHeight,SRCCOPY); 
		  //设置背景图片

	CRect rectPic;
	m_Pic1.GetClientRect(&rectPic);     //m_picture为Picture Control控件变量，获得控件的区域对象
	CDC* pDC = m_Pic1.GetWindowDC();    //获得显示控件的DC
    CImage *pImage = new CImage();//装载图像的类

	HRESULT hResult;
	hResult = pImage->Load(filename);//从磁盘装载图片,filename为class的CString类型的成员数据

	if (FAILED(hResult)) 
	{
		MessageBox(TEXT("Open photo file failed!"));
		return;
	}

	int width = rectPic.Width();//显示区域的宽和高
	int height =rectPic.Height();
		
	int picW = pImage->GetWidth();//图片的宽和高
	int picH = pImage->GetHeight();

	double r1 = double(picW)/double(width);
	double r2 = double(picH)/double(height);
    //r为最优缩放比例
    double r=(r1>=r2?r1:r2);

	//防止缩放后图片失真
	SetStretchBltMode(pDC -> m_hDC,HALFTONE);
    SetBrushOrgEx(pDC -> m_hDC, 0, 0,NULL);
	
		//让图片居中
	CPoint RectP = rectPic.CenterPoint();
	pImage->Draw(pDC->m_hDC,(RectP.x - width/2)+(width - picW / r) / 2, (RectP.y - height / 2)+(height - picH/r) / 2, int(picW / r), int(picH / r));
	ReleaseDC(pDC);
	delete pImage; 
}

void CPicExplorerDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	
	if (current > 0)
	{
	 current--;
	//PictureRecord picRec;
    //picListptr->retrieve(current,picRec);
	Node<PictureRecord> *p;
	r_list->retrieve(current,p);
	filename =p->entry.the_key().c_str();//文件名

	filename = basePath+filename;//全名

	CRect rect;
    GetDlgItem(IDC_STATIC_PIC1)->GetWindowRect(&rect);
    ScreenToClient(rect);
    InvalidateRect(&rect); 

		
	}//IDC_STATIC_PIC1为picture控件的ID
	else
		MessageBox(_T("已经是第一张了！"));

}

void CPicExplorerDlg::OnBnClickedButton2()
{
		// TODO: Add your control notification handler code here
	
if (current <count-1)
{
    current++;
      
	Node<PictureRecord> *p;
    r_list->retrieve(current,p);
	filename =p->entry.the_key().c_str();
	filename = basePath+filename;
     	
	CRect rect;
    GetDlgItem(IDC_STATIC_PIC1)->GetWindowRect(&rect);
    ScreenToClient(rect);
    InvalidateRect(&rect);
}				//刷新
	
	else
	{
		MessageBox(_T("已经是最后一张了！"));
		
	}
	

}

void CPicExplorerDlg::OnBnClickedButtonexit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CPicExplorerDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	Node<PictureRecord> *p;
	if(r_list->remove(current,p)==success)
	{	
	   MessageBox(_T("删除成功！"));
	   count--;
	   r_list->retrieve(current,p);
	   filename =p->entry.the_key().c_str();
	   filename = basePath+filename;//必须更新当前current下的filename
	   CRect rect;
	   GetDlgItem(IDC_STATIC_PIC1)->GetWindowRect(&rect);
	   ScreenToClient(rect);
	   InvalidateRect(&rect);    //刷新
	}				
		else MessageBox(_T("删除失败！"));
}
void CPicExplorerDlg::OnBnClickedButton4()//触发自动播放
{
	// TODO: 在此添加控件通知处理程序代码
	SetTimer(1,1000,NULL);//设置第1号计时器
	
}

void CPicExplorerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	
	OnBnClickedButton2();
	CDialog::OnTimer(nIDEvent);
}

void CPicExplorerDlg::OnBnClickedButton5()//取消自动播放
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
}
