// SearchByLoc.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "SearchByLoc.h"


#include<cstring>
#include<string>

#include <atlimage.h>


// CSearchByLoc 对话框

IMPLEMENT_DYNAMIC(CSearchByLoc, CDialog)

CSearchByLoc::CSearchByLoc(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchByLoc::IDD, pParent)
	, m_result(_T(""))
{

}

CSearchByLoc::CSearchByLoc(CWnd* pParent,PictureInfoList *picListptr_,
								 List<Node<PictureRecord>*>  *r_list_)
: CDialog(CSearchByLoc::IDD, pParent)
{
	picListptr=picListptr_;
	r_list =r_list_;
}

CSearchByLoc::~CSearchByLoc()
{
}

void CSearchByLoc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture1, m_Picture1);
	DDX_Control(pDX, IDC_Picture2, m_Picture2);
	DDX_Control(pDX, IDC_Picture3, m_Picture3);
	DDX_Control(pDX, IDC_Picture4, m_Picture4);
	DDX_Text(pDX, IDC_EDIT1, m_result);
}


BEGIN_MESSAGE_MAP(CSearchByLoc, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CSearchByLoc::OnBnClickedButton1)
	ON_BN_CLICKED(IDNext, &CSearchByLoc::OnBnClickedNext)
	ON_BN_CLICKED(IDPre, &CSearchByLoc::OnBnClickedPre)
	ON_BN_CLICKED(IDC_BUTTON2, &CSearchByLoc::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT1, &CSearchByLoc::OnEnChangeEdit1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSearchByLoc 消息处理程序

void CSearchByLoc::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}



BOOL CSearchByLoc::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  在此添加额外的初始化
	basePath = "d:\\picLibrary\\";
	currentPage=0;
	numInPages=4;
	count=r_list->size();  //传过来的r_list

	//初始化时从List中获取所有的文件名
	for(int i=0; i<count; i++)
	{
		 Node<PictureRecord> *picRec;
         r_list->retrieve(i,picRec);
		 filenames[i]=picRec->entry.the_key().c_str();
         filenames[i]=basePath+filenames[i];
	}
	   
	HBITMAP   hBitmap;   
    hBitmap = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP15)); 
   ((CButton *)GetDlgItem(IDC_BUTTON2))->SetBitmap(hBitmap);

    HBITMAP   hBitmap_1;   
    hBitmap_1 = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP12)); 
   ((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap_1);
		 // IDB_BITMAP12为资源图片ID 

	HBITMAP   hBitmap_2;   
    hBitmap_2 = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP13)); 
   ((CButton *)GetDlgItem(IDNext))->SetBitmap(hBitmap_2);

    HBITMAP   hBitmap_3;   
    hBitmap_3= LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP14)); 
   ((CButton *)GetDlgItem(IDPre))->SetBitmap(hBitmap_3);

    CEdit *m_edit = (CEdit*)GetDlgItem(IDC_EDIT1);
	CFont *m_font = new CFont;
	m_font->CreatePointFont(200, CString("黑体"), NULL);
	m_edit->SetFont(m_font, TRUE);//改变编辑框字体属性
	
	CEdit *m_edit_1 = (CEdit*)GetDlgItem(IDC_EDIT2);
	CFont *m_font_1 = new CFont;
	m_font_1->CreatePointFont(170, CString("黑体"), NULL);
	m_edit_1->SetFont(m_font_1, TRUE);//改变编辑框字体属性

	


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSearchByLoc::drawPicture(CStatic* m_Picture/*控件名称*/, int no/*控件编号0-n-1*/)
{

    	CRect rectPic;
        (*m_Picture).GetClientRect(&rectPic);   
		//m_picture为Picture Control控件变量，获得控件的区域对象
        CDC* pDC = m_Picture->GetWindowDC();    
		//获得显示控件的DC

		CImage *pImage = new CImage();
		//装载图像的类
		
		int pos = currentPage*numInPages+no;
		if (pos< count)
		{ //还有图片可以显示
			pImage->Load(filenames[pos]);//从磁盘装载图片,根据页面计算得到的图片下标
			int width = rectPic.Width();//显示区域的宽和高
			int height =rectPic.Height();
		
			int picW = pImage->GetWidth();//图片的宽和高
			int picH = pImage->GetHeight();
//计算缩放比
			double r1 = double(picW)/double(width);
			double r2 = double(picH)/double(height);
        //r为最优缩放比例
		double r=(r1>=r2?r1:r2);

		//防止缩放后失真
		SetStretchBltMode(pDC -> m_hDC,   HALFTONE);
		SetBrushOrgEx(pDC -> m_hDC,0,0,NULL);
		
		//CPoint RectP = rectPic.CenterPoint();
		//pImage->Draw(pDC->m_hDC,(RectP.x - width/2)+(width - picW / r) / 2, (RectP.y - height / 2)+(height - picH/r) / 2, int(picW / r), int(picH / r));
	//让图片居中
		CPoint RectP = rectPic.CenterPoint();
		pImage->Draw(pDC->m_hDC,(RectP.x - width/2)+(width - picW / r) / 2, (RectP.y - height / 2)+(height - picH/r) / 2, int(picW / r), int(picH / r));
		
        ReleaseDC(pDC);
		delete pImage; 
		}
		else
		{
		  m_Picture->ShowWindow(SW_HIDE);          
		}

		UpdateData(TRUE);
}	

void CSearchByLoc::OnBnClickedNext()
{
	// TODO: 在此添加控件通知处理程序代码
	if (currentPage < count/numInPages)
	{
		currentPage++;
      
	   CRect rect;

       GetDlgItem(IDC_Picture1)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

	   GetDlgItem(IDC_Picture2)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

       GetDlgItem(IDC_Picture3)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

	   GetDlgItem(IDC_Picture4)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

	    //InvalidateRect(CRect(109,14,165,75), true);//强制刷新
	}
	else
		MessageBox(_T("已经是最后一张了！"));
}

void CSearchByLoc::OnBnClickedPre()
{
	// TODO: 在此添加控件通知处理程序代码
	if (currentPage > 0)
	{
	  currentPage--;   
      if(m_Picture1.IsWindowVisible()== false)
         m_Picture1.ShowWindow(SW_SHOW);  
	  if(m_Picture2.IsWindowVisible() == false)
         m_Picture2.ShowWindow(SW_SHOW); 
	  if(m_Picture3.IsWindowVisible() == false)
         m_Picture3.ShowWindow(SW_SHOW); 
	   if(m_Picture4.IsWindowVisible() == false)
         m_Picture4.ShowWindow(SW_SHOW); 

	   
        CRect rect;

       GetDlgItem(IDC_Picture1)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

	   GetDlgItem(IDC_Picture2)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

       GetDlgItem(IDC_Picture3)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

	   GetDlgItem(IDC_Picture4)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 
	   //InvalidateRect(CRect(109,14,165,75), true);//强制刷新
	}
	else
		MessageBox(_T("已经是第一张了！"));
}
   
void CSearchByLoc::OnBnClickedButton2()  //查找按钮
{
	// TODO: 在此添加控件通知处理程序代码
	string loc = (CStringA)m_result; //CString -> String
	List<Node<PictureRecord>*> LocationList; //用来存title相同的图片的List
	if( picListptr->searchByLocation(loc,LocationList)==success )
	{
		  //得到所有的文件名
		  Node<PictureRecord> *p;
		  PictureRecord pr;
		  for (int k=0;k<LocationList.size(); k++)
		  {
			 if(LocationList.retrieve(k,p)==success)
			 {
				 pr=p->entry;
				 filenames[k]=pr.the_key().c_str(); //string ->String
				 filenames[k]=basePath+filenames[k];
			 }
		  }

	   currentPage=0;
	   count =LocationList.size(); //查找到的图片的总数
	   CRect rect;

       GetDlgItem(IDC_Picture1)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

       GetDlgItem(IDC_Picture2)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

       GetDlgItem(IDC_Picture3)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 
      
      GetDlgItem(IDC_Picture4)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 	
      }	
      else
          MessageBox(_T("The Word does not exist!"));
}

void CSearchByLoc::OnPaint()
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
    bmpBackground.LoadBitmap(IDB_BITMAP18);   
		  //IDB_BITMAP7是图对应的ID,设置背景图片
                  
    BITMAP   bitmap;   
    bmpBackground.GetBitmap(&bitmap);   
    CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground); 
	dc.SetStretchBltMode(COLORONCOLOR);
    dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
	bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
		  //设置背景图片

	CPaintDC   dc_1(this);   
    CRect   rect_1;   
    GetClientRect(&rect_1);   
    CDC   dcMem_1;   
    dcMem_1.CreateCompatibleDC(&dc_1);  
	drawPicture(&m_Picture1, 0);
    drawPicture(&m_Picture2, 1);
    drawPicture(&m_Picture3, 2);
    drawPicture(&m_Picture4, 3);
	//绘制照片
}

void CSearchByLoc::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	 UpdateData(TRUE);
	
}

HBRUSH CSearchByLoc::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	int id = pWnd->GetDlgCtrlID();

	CRect rc;
	switch (id)
	{
		case IDC_EDIT1:
		case IDC_EDIT2:
			pWnd->GetWindowRect(&rc);
			ScreenToClient(&rc);
			pDC->BitBlt(0, 0, rc.Width(), rc.Height(), GetDC(), rc.left, rc.top, SRCCOPY);      
				pDC->SetTextColor(RGB(255, 203, 96));
			return (HBRUSH) ::GetStockObject(NULL_BRUSH);
			break;
		
		default:
			break;
	}
	return hbr;
}
