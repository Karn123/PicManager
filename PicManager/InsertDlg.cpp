// InsertDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MainUI.h"
#include "InsertDlg.h"
#include"PicRecord.h"
#include<string>
using namespace std;
// CInsertDlg 对话框

IMPLEMENT_DYNAMIC(CInsertDlg, CDialog)

CInsertDlg::CInsertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertDlg::IDD, pParent)
	, m_creatTime(COleDateTime::GetCurrentTime())
	, m_FileName(_T(""))
{

}

CInsertDlg::CInsertDlg(CWnd* pParent ,PictureInfoList *picIptr_,List<Node<PictureRecord>*> *x_list_)
	: CDialog(CInsertDlg::IDD, pParent)
	, m_creatTime(COleDateTime::GetCurrentTime())
{
		picIptr=picIptr_;
		x_list=x_list_;
}


CInsertDlg::~CInsertDlg()
{
}

void CInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_creatTime);
	DDX_Text(pDX, IDC_EDIT2, m_FileName);
}


BEGIN_MESSAGE_MAP(CInsertDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CInsertDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInsertDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CInsertDlg::OnBnClickedButton3)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CInsertDlg 消息处理程序

void CInsertDlg::OnBnClickedButton1()  //打开按钮
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("JPEG文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||");
	CFileDialog fileDlg(true,_T("*.jpg"),NULL,0,szFilter,this);

	CString strFilePath;

	if(IDOK == fileDlg.DoModal())
	{
	   strFilePath = fileDlg.GetPathName();//获取选择的文件路径
	   SetDlgItemText(IDC_EDIT1,strFilePath);  //将其显示在文本框

	   m_FileName=fileDlg.GetPathName();
	   SetDlgItemText(IDC_EDIT2,fileDlg.GetFileName()); //将文件名显示在文本框
	   string fileName = (CStringA)strFilePath;
	   char tmpname[100];
	   strcpy(tmpname,fileName.c_str());
	   PdfJpeg jepg(tmpname); //加入的PdfJpeg类
       int readResult = jepg.ReadImage(); 
	   if(readResult == -1)
	   {
	       MessageBox(_T("Error in read file: "));		  
		   return ;
	   }
       int width = jepg.GetWidth();
	   int height = jepg.GetHeight();
	   int size = int((jepg.GetDataLength())/1024.0+1); //上取整数
	   SetDlgItemInt(IDC_EDIT3,width); 
	   SetDlgItemInt(IDC_EDIT4,height);
	   SetDlgItemInt(IDC_EDIT5,size);

	   CFileStatus  status;//获取文件相关时间
	   if(CFile::GetStatus(strFilePath, status))
	   {
	/*CTime m_ctime	文件创建的时间。  CTime m_mtime	文件最后一次修改的时间 	CTime m_atime	最后一次访问文件并读取的时间。*/
	       //先把Ctime转换成time_t，然后再转成COleDateTime 
           time_t time2=status.m_mtime.GetTime(); //CTime-->time_t
	       COleDateTime time3(time2); //time_t--->COleDateTime
	       m_creatTime = time3;
                    UpdateData(false);

		}		
	}
}
void CInsertDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CInsertDlg::OnBnClickedButton3()
{
	// TODO: 
	
	OthersType other;
	string key="000000.jpg";
	other.width=312;
	other.height=231;
	other.detail="";
	other.hlocation="";
    other.hmap="";
    other.titleEn="Katy";
	other.owner="Perry";
	other.size=37129;
    other.time=10000000000;
	CString mapName;
	if(((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck())
		{
			other.location="华师大";
			other.map="上海";
			PictureRecord p(key,other);
			Node<PictureRecord> *m=new Node<PictureRecord>(p);
			if(picIptr->Insert(p)==success){
				x_list->insert(x_list->size(),m);
				
	
				mapName =_T("华师大，添加成功！");
			}
			else mapName =_T("华师大，添加失败！");
			
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck())
	{
			other.location="南大";
			other.map="南京";
			PictureRecord p(key,other);
			picIptr->Insert(p);
			Node<PictureRecord> *m=new Node<PictureRecord>(p);
			m->entry=p;
			if(x_list->insert(x_list->size(),m)==success)
				mapName =_T("中国，添加成功！" );
			else mapName =_T("中国，添加失败！");
	}
		MessageBox(mapName);
}

BOOL CInsertDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	HBITMAP   hBitmap;   
    hBitmap = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP29)); 
   ((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap);
	
     HBITMAP   hBitmap_3;   
	 hBitmap_3=LoadBitmap(AfxGetInstanceHandle(),   
	 MAKEINTRESOURCE(IDB_BITMAP12)); 
	 ((CButton *)GetDlgItem(IDC_BUTTON2))->SetBitmap(hBitmap_3);
		 // IDB_BITMAP12为资源图片ID 
		//图片IDB_BITMAP12覆盖按钮IDC_BUTTON2

	 HBITMAP   hBitmap_1;   
	 hBitmap_1=LoadBitmap(AfxGetInstanceHandle(),   
	 MAKEINTRESOURCE(IDB_BITMAP28)); 
	 ((CButton *)GetDlgItem(IDC_BUTTON3))->SetBitmap(hBitmap_1);



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CInsertDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	//置背景图片
		  CPaintDC  dc(this);   
          CRect  rect;   
          GetClientRect(&rect);   
          CDC  dcMem;   
          dcMem.CreateCompatibleDC(&dc);   
          CBitmap  bmpBackground;   
          bmpBackground.LoadBitmap(IDB_BITMAP21);   
		  //IDB_BITMAP4是图对应的ID
          BITMAP   bitmap_1;   
          bmpBackground.GetBitmap(&bitmap_1);   
          CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground); 

		  dc.SetStretchBltMode(COLORONCOLOR);

          dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
		  bitmap_1.bmWidth,bitmap_1.bmHeight,SRCCOPY); 
		  //设置背景图片
}
