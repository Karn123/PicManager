// FtMarkChinaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "FtMarkChinaDlg.h"


// CFtMarkChinaDlg 对话框

IMPLEMENT_DYNAMIC(CFtMarkChinaDlg, CDialog)

CFtMarkChinaDlg::CFtMarkChinaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFtMarkChinaDlg::IDD, pParent)
{

}

CFtMarkChinaDlg::CFtMarkChinaDlg(CWnd* pParent, PictureInfoList * picLibraryPtr_,
						   List<Node<PictureRecord>*>  *my_foot_list_)
: CDialog(CFtMarkChinaDlg::IDD, pParent)
{
  picLibraryPtr=picLibraryPtr_;
  my_foot_list=my_foot_list_;
}


CFtMarkChinaDlg::~CFtMarkChinaDlg()
{
}

void CFtMarkChinaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFtMarkChinaDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CFtMarkChinaDlg 消息处理程序

void CFtMarkChinaDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CDialog::OnPaint();
				//显示背景图开始
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
    bmpBackground.LoadBitmap(IDB_BITMAP22); 

	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0,0,rect.Width(), rect.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	
	 //绘制足迹信息    
	int count = ecnuMap.get_verterxCount();
	VertexRecord vr; //图中节点记录
	const List<const Node<PictureRecord>*>* trackListPtr=NULL;//图中点对应的照片集合
	//依次绘制地图上每个节点的照片数量 
    for(int i=0; i<count; i++)
	{
	 ecnuMap.get_trackByIndex(i,vr,trackListPtr);
	  if(trackListPtr!=NULL&&trackListPtr->size()>0)
	  {
	    dc.Ellipse(vr.the_x()-10, vr.the_y()-10, vr.the_x()+10, vr.the_y()+10);//围绕中心点画个圆形；
		dc.SetTextColor(RGB(255,0,0));
        
		CString tmp;
		tmp.Format(_T("%d"),trackListPtr->size());//绘制数量
	    dc.TextOut(vr.the_x()-8,vr.the_y() , tmp);	
	  }	
	}

}

BOOL CFtMarkChinaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
		//按照图像比例显示图形。
	CRect   temprect(0,0,800,667);   
    CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE); 

	if(ecnuMap.Initialize("中国","China")==success)
	   MessageBox(_T("OK,Now map is initialized."));
	else
	   MessageBox(_T("error,map load failed."));
         //查找得到足迹
	picLibraryPtr->searchByFootmark(ecnuMap);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFtMarkChinaDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonDown(nFlags, point);

	int no,index;
	//找到用户点击位置对应的地图中的节点编号no和存储下标index
	ecnuMap.positionToNum(point.x,point.y,index,no);

	VertexRecord vr; //图中节点记录
	const List <const Node<PictureRecord>*> *trackListPtr=NULL;
	//图中点对应的照片集合
	//获得该节点对应的照片信息
	ecnuMap.get_trackByIndex(index,vr,trackListPtr);
	CString tmp(vr.the_location().c_str());
	
    CString str_x;//X坐标
	CString str_y;//Y坐标
	str_x.Format(_T("%d"),point.x);//转换point.x到str_x
	str_y.Format(_T("%d"),point.y); //转换point.y到str_y
    
    tmp =str_x+_T(",")+str_y+_T(",")+tmp;
	CString imageNames("");
	const Node<PictureRecord >* cptr;//照片记录的指针

	for (int i=0;i<trackListPtr->size();i++)
	{
		trackListPtr->retrieve(i,cptr);
		CString tmpName(cptr->entry.the_key().c_str());
		imageNames = imageNames+ _T(",")+tmpName;	
	}
	MessageBox(tmp + imageNames);
	CDialog::OnLButtonDown(nFlags, point);

}
