// SearchByLoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "SearchByLoc.h"


#include<cstring>
#include<string>

#include <atlimage.h>


// CSearchByLoc �Ի���

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


// CSearchByLoc ��Ϣ�������

void CSearchByLoc::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}



BOOL CSearchByLoc::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	basePath = "d:\\picLibrary\\";
	currentPage=0;
	numInPages=4;
	count=r_list->size();  //��������r_list

	//��ʼ��ʱ��List�л�ȡ���е��ļ���
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
		 // IDB_BITMAP12Ϊ��ԴͼƬID 

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
	m_font->CreatePointFont(200, CString("����"), NULL);
	m_edit->SetFont(m_font, TRUE);//�ı�༭����������
	
	CEdit *m_edit_1 = (CEdit*)GetDlgItem(IDC_EDIT2);
	CFont *m_font_1 = new CFont;
	m_font_1->CreatePointFont(170, CString("����"), NULL);
	m_edit_1->SetFont(m_font_1, TRUE);//�ı�༭����������

	


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSearchByLoc::drawPicture(CStatic* m_Picture/*�ؼ�����*/, int no/*�ؼ����0-n-1*/)
{

    	CRect rectPic;
        (*m_Picture).GetClientRect(&rectPic);   
		//m_pictureΪPicture Control�ؼ���������ÿؼ����������
        CDC* pDC = m_Picture->GetWindowDC();    
		//�����ʾ�ؼ���DC

		CImage *pImage = new CImage();
		//װ��ͼ�����
		
		int pos = currentPage*numInPages+no;
		if (pos< count)
		{ //����ͼƬ������ʾ
			pImage->Load(filenames[pos]);//�Ӵ���װ��ͼƬ,����ҳ�����õ���ͼƬ�±�
			int width = rectPic.Width();//��ʾ����Ŀ�͸�
			int height =rectPic.Height();
		
			int picW = pImage->GetWidth();//ͼƬ�Ŀ�͸�
			int picH = pImage->GetHeight();
//�������ű�
			double r1 = double(picW)/double(width);
			double r2 = double(picH)/double(height);
        //rΪ�������ű���
		double r=(r1>=r2?r1:r2);

		//��ֹ���ź�ʧ��
		SetStretchBltMode(pDC -> m_hDC,   HALFTONE);
		SetBrushOrgEx(pDC -> m_hDC,0,0,NULL);
		
		//CPoint RectP = rectPic.CenterPoint();
		//pImage->Draw(pDC->m_hDC,(RectP.x - width/2)+(width - picW / r) / 2, (RectP.y - height / 2)+(height - picH/r) / 2, int(picW / r), int(picH / r));
	//��ͼƬ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	    //InvalidateRect(CRect(109,14,165,75), true);//ǿ��ˢ��
	}
	else
		MessageBox(_T("�Ѿ������һ���ˣ�"));
}

void CSearchByLoc::OnBnClickedPre()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	   //InvalidateRect(CRect(109,14,165,75), true);//ǿ��ˢ��
	}
	else
		MessageBox(_T("�Ѿ��ǵ�һ���ˣ�"));
}
   
void CSearchByLoc::OnBnClickedButton2()  //���Ұ�ť
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	string loc = (CStringA)m_result; //CString -> String
	List<Node<PictureRecord>*> LocationList; //������title��ͬ��ͼƬ��List
	if( picListptr->searchByLocation(loc,LocationList)==success )
	{
		  //�õ����е��ļ���
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
	   count =LocationList.size(); //���ҵ���ͼƬ������
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
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CPaintDC  dc(this);   
    CRect  rect;   
    GetClientRect(&rect);   
    CDC  dcMem;   
    dcMem.CreateCompatibleDC(&dc);   
    CBitmap  bmpBackground;   
    bmpBackground.LoadBitmap(IDB_BITMAP18);   
		  //IDB_BITMAP7��ͼ��Ӧ��ID,���ñ���ͼƬ
                  
    BITMAP   bitmap;   
    bmpBackground.GetBitmap(&bitmap);   
    CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground); 
	dc.SetStretchBltMode(COLORONCOLOR);
    dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
	bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
		  //���ñ���ͼƬ

	CPaintDC   dc_1(this);   
    CRect   rect_1;   
    GetClientRect(&rect_1);   
    CDC   dcMem_1;   
    dcMem_1.CreateCompatibleDC(&dc_1);  
	drawPicture(&m_Picture1, 0);
    drawPicture(&m_Picture2, 1);
    drawPicture(&m_Picture3, 2);
    drawPicture(&m_Picture4, 3);
	//������Ƭ
}

void CSearchByLoc::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	 UpdateData(TRUE);
	
}

HBRUSH CSearchByLoc::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
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
