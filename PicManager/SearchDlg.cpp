// SearchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "SearchDlg.h"
#include<cstring>
#include<string>

#include <atlimage.h>


// CSearchDlg �Ի���

IMPLEMENT_DYNAMIC(CSearchDlg, CDialog)

CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
	, m_result(_T(""))
{

}

CSearchDlg::CSearchDlg(CWnd* pParent,PictureInfoList *picListptr_,
								 List<Node<PictureRecord>*>  *r_list_)
: CDialog(CSearchDlg::IDD, pParent)
{
	picListptr=picListptr_;
	r_list =r_list_;
}

CSearchDlg::~CSearchDlg()
{
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_result);
	DDX_Control(pDX, IDC_Pic1, m_Pic1);
	DDX_Control(pDX, IDC_Pic2, m_Pic2);
	DDX_Control(pDX, IDC_Pic3, m_Pic3);
	DDX_Control(pDX, IDC_Pic4, m_Pic4);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CSearchDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CSearchDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT2, &CSearchDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON2, &CSearchDlg::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CSearchDlg::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_Pic1, &CSearchDlg::OnStnClickedPic1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSearchDlg ��Ϣ�������

void CSearchDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void CSearchDlg::OnBnClickedOk() //���Ұ�ť
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	string titleEn = (CStringA)m_result; //CString -> String
	List<Node<PictureRecord>*> titleList; //������title��ͬ��ͼƬ��List
	if(picListptr->searchByTitle(titleEn,titleList)==success )
	{
		  //�õ����е��ļ���
		  Node<PictureRecord> *p;
		  PictureRecord pr;
		  for (int k=0; k<titleList.size(); k++)
		  {
			 if(titleList.retrieve(k,p)==success)
			 {
				 pr=p->entry;
				 filenames[k]=pr.the_key().c_str(); //string ->String
				 filenames[k]=basePath+filenames[k];
			 }
		  }

	   currentPage=0;
	   count =titleList.size(); //���ҵ���ͼƬ������
	   CRect rect;

       GetDlgItem(IDC_Pic1)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

       GetDlgItem(IDC_Pic2)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

       GetDlgItem(IDC_Pic3)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 
      
      GetDlgItem(IDC_Pic4)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 	
      }	
      else
          MessageBox(_T("The Word is not exist!"));
}

void CSearchDlg::drawPicture(CStatic* m_Pic/*�ؼ�����*/, int no/*�ؼ����0-n-1*/)
{

    	CRect rectPic;
        (*m_Pic).GetClientRect(&rectPic);   
		//m_pictureΪPicture Control�ؼ���������ÿؼ����������
        CDC* pDC = m_Pic->GetWindowDC();    
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
		}
		else
		{
		  m_Pic->ShowWindow(SW_HIDE);          
		}

		UpdateData(TRUE);
}		

void CSearchDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CSearchDlg::OnEnChangeEdit2()  //��ѯ�༭��
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	 
	 UpdateData(TRUE);//��������ֵ�ĸ��±����ڱ�����
	 CRect rect;
     GetDlgItem(IDC_EDIT2)->GetWindowRect(&rect);
     ScreenToClient(rect);
     InvalidateRect(&rect); 

}

BOOL CSearchDlg::OnInitDialog()
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
   ((CButton *)GetDlgItem(IDOK))->SetBitmap(hBitmap);

    HBITMAP   hBitmap_1;   
    hBitmap_1 = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP12)); 
   ((CButton *)GetDlgItem(IDCANCEL))->SetBitmap(hBitmap_1);
		 // IDB_BITMAP12Ϊ��ԴͼƬID 

	HBITMAP   hBitmap_2;   
    hBitmap_2 = LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP13)); 
   ((CButton *)GetDlgItem(IDC_BUTTON1))->SetBitmap(hBitmap_2);

    HBITMAP   hBitmap_3;   
    hBitmap_3= LoadBitmap(AfxGetInstanceHandle(),   
	MAKEINTRESOURCE(IDB_BITMAP14)); 
   ((CButton *)GetDlgItem(IDC_BUTTON2))->SetBitmap(hBitmap_3);

   	CEdit *m_edit = (CEdit*)GetDlgItem(IDC_EDIT2);
	CFont *m_font = new CFont;
	m_font->CreatePointFont(200, CString("����"), NULL);
	m_edit->SetFont(m_font, TRUE);//�ı�༭����������
	
	CEdit *m_edit_1 = (CEdit*)GetDlgItem(IDC_EDIT1);
	CFont *m_font_1 = new CFont;
	m_font_1->CreatePointFont(170, CString("����"), NULL);
	m_edit_1->SetFont(m_font_1, TRUE);//�ı�༭����������



    return TRUE;  // return TRUE  unless you set the focus to a contro
}

void CSearchDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (currentPage > 0)
	{
	  currentPage--;   
      if(m_Pic1.IsWindowVisible()== false)
         m_Pic1.ShowWindow(SW_SHOW);  
	  if(m_Pic2.IsWindowVisible() == false)
         m_Pic2.ShowWindow(SW_SHOW); 
	  if(m_Pic3.IsWindowVisible() == false)
         m_Pic3.ShowWindow(SW_SHOW); 
	   if(m_Pic4.IsWindowVisible() == false)
         m_Pic4.ShowWindow(SW_SHOW); 

	   
        CRect rect;

       GetDlgItem(IDC_Pic1)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

	   GetDlgItem(IDC_Pic2)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

       GetDlgItem(IDC_Pic3)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

	   GetDlgItem(IDC_Pic4)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 
	   //InvalidateRect(CRect(109,14,165,75), true);//ǿ��ˢ��
	}
	else
		MessageBox(_T("�Ѿ��ǵ�һ���ˣ�"));
}

void CSearchDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	//CDialog::OnPaint();
	
		  CPaintDC  dc(this);   
          CRect  rect;   
          GetClientRect(&rect);   
          CDC  dcMem;   
          dcMem.CreateCompatibleDC(&dc);   
          CBitmap  bmpBackground;   
          bmpBackground.LoadBitmap(IDB_BITMAP17);   
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
		drawPicture(&m_Pic1, 0);
		drawPicture(&m_Pic2, 1);
		drawPicture(&m_Pic3, 2);
		drawPicture(&m_Pic4, 3);
	//������Ƭ

}

void CSearchDlg::OnBnClickedButton1()  //NextPage
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (currentPage < count/numInPages)
	{
		currentPage++;
      
	   CRect rect;

       GetDlgItem(IDC_Pic1)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

	   GetDlgItem(IDC_Pic2)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

       GetDlgItem(IDC_Pic3)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

	   GetDlgItem(IDC_Pic4)->GetWindowRect(&rect);
       ScreenToClient(rect);
       InvalidateRect(&rect); 

	    //InvalidateRect(CRect(109,14,165,75), true);//ǿ��ˢ��
	}
	else 
		MessageBox(_T("�Ѿ������һ���ˣ�"));
}

void CSearchDlg::OnStnClickedPic1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

HBRUSH CSearchDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}