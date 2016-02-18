// InsertDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "InsertDlg.h"
#include"PicRecord.h"
#include<string>
using namespace std;
// CInsertDlg �Ի���

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


// CInsertDlg ��Ϣ�������

void CInsertDlg::OnBnClickedButton1()  //�򿪰�ť
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("JPEG�ļ�(*.jpg)|*.jpg|�����ļ�(*.*)|*.*||");
	CFileDialog fileDlg(true,_T("*.jpg"),NULL,0,szFilter,this);

	CString strFilePath;

	if(IDOK == fileDlg.DoModal())
	{
	   strFilePath = fileDlg.GetPathName();//��ȡѡ����ļ�·��
	   SetDlgItemText(IDC_EDIT1,strFilePath);  //������ʾ���ı���

	   m_FileName=fileDlg.GetPathName();
	   SetDlgItemText(IDC_EDIT2,fileDlg.GetFileName()); //���ļ�����ʾ���ı���
	   string fileName = (CStringA)strFilePath;
	   char tmpname[100];
	   strcpy(tmpname,fileName.c_str());
	   PdfJpeg jepg(tmpname); //�����PdfJpeg��
       int readResult = jepg.ReadImage(); 
	   if(readResult == -1)
	   {
	       MessageBox(_T("Error in read file: "));		  
		   return ;
	   }
       int width = jepg.GetWidth();
	   int height = jepg.GetHeight();
	   int size = int((jepg.GetDataLength())/1024.0+1); //��ȡ����
	   SetDlgItemInt(IDC_EDIT3,width); 
	   SetDlgItemInt(IDC_EDIT4,height);
	   SetDlgItemInt(IDC_EDIT5,size);

	   CFileStatus  status;//��ȡ�ļ����ʱ��
	   if(CFile::GetStatus(strFilePath, status))
	   {
	/*CTime m_ctime	�ļ�������ʱ�䡣  CTime m_mtime	�ļ����һ���޸ĵ�ʱ�� 	CTime m_atime	���һ�η����ļ�����ȡ��ʱ�䡣*/
	       //�Ȱ�Ctimeת����time_t��Ȼ����ת��COleDateTime 
           time_t time2=status.m_mtime.GetTime(); //CTime-->time_t
	       COleDateTime time3(time2); //time_t--->COleDateTime
	       m_creatTime = time3;
                    UpdateData(false);

		}		
	}
}
void CInsertDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			other.location="��ʦ��";
			other.map="�Ϻ�";
			PictureRecord p(key,other);
			Node<PictureRecord> *m=new Node<PictureRecord>(p);
			if(picIptr->Insert(p)==success){
				x_list->insert(x_list->size(),m);
				
	
				mapName =_T("��ʦ����ӳɹ���");
			}
			else mapName =_T("��ʦ�����ʧ�ܣ�");
			
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck())
	{
			other.location="�ϴ�";
			other.map="�Ͼ�";
			PictureRecord p(key,other);
			picIptr->Insert(p);
			Node<PictureRecord> *m=new Node<PictureRecord>(p);
			m->entry=p;
			if(x_list->insert(x_list->size(),m)==success)
				mapName =_T("�й�����ӳɹ���" );
			else mapName =_T("�й������ʧ�ܣ�");
	}
		MessageBox(mapName);
}

BOOL CInsertDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	HBITMAP   hBitmap;   
    hBitmap = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP29)); 
   ((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap);
	
     HBITMAP   hBitmap_3;   
	 hBitmap_3=LoadBitmap(AfxGetInstanceHandle(),   
	 MAKEINTRESOURCE(IDB_BITMAP12)); 
	 ((CButton *)GetDlgItem(IDC_BUTTON2))->SetBitmap(hBitmap_3);
		 // IDB_BITMAP12Ϊ��ԴͼƬID 
		//ͼƬIDB_BITMAP12���ǰ�ťIDC_BUTTON2

	 HBITMAP   hBitmap_1;   
	 hBitmap_1=LoadBitmap(AfxGetInstanceHandle(),   
	 MAKEINTRESOURCE(IDB_BITMAP28)); 
	 ((CButton *)GetDlgItem(IDC_BUTTON3))->SetBitmap(hBitmap_1);



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CInsertDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	//�ñ���ͼƬ
		  CPaintDC  dc(this);   
          CRect  rect;   
          GetClientRect(&rect);   
          CDC  dcMem;   
          dcMem.CreateCompatibleDC(&dc);   
          CBitmap  bmpBackground;   
          bmpBackground.LoadBitmap(IDB_BITMAP21);   
		  //IDB_BITMAP4��ͼ��Ӧ��ID
          BITMAP   bitmap_1;   
          bmpBackground.GetBitmap(&bitmap_1);   
          CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground); 

		  dc.SetStretchBltMode(COLORONCOLOR);

          dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
		  bitmap_1.bmWidth,bitmap_1.bmHeight,SRCCOPY); 
		  //���ñ���ͼƬ
}
