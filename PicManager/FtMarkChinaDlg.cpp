// FtMarkChinaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MainUI.h"
#include "FtMarkChinaDlg.h"


// CFtMarkChinaDlg �Ի���

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


// CFtMarkChinaDlg ��Ϣ�������

void CFtMarkChinaDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CDialog::OnPaint();
				//��ʾ����ͼ��ʼ
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
	
	 //�����㼣��Ϣ    
	int count = ecnuMap.get_verterxCount();
	VertexRecord vr; //ͼ�нڵ��¼
	const List<const Node<PictureRecord>*>* trackListPtr=NULL;//ͼ�е��Ӧ����Ƭ����
	//���λ��Ƶ�ͼ��ÿ���ڵ����Ƭ���� 
    for(int i=0; i<count; i++)
	{
	 ecnuMap.get_trackByIndex(i,vr,trackListPtr);
	  if(trackListPtr!=NULL&&trackListPtr->size()>0)
	  {
	    dc.Ellipse(vr.the_x()-10, vr.the_y()-10, vr.the_x()+10, vr.the_y()+10);//Χ�����ĵ㻭��Բ�Σ�
		dc.SetTextColor(RGB(255,0,0));
        
		CString tmp;
		tmp.Format(_T("%d"),trackListPtr->size());//��������
	    dc.TextOut(vr.the_x()-8,vr.the_y() , tmp);	
	  }	
	}

}

BOOL CFtMarkChinaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
		//����ͼ�������ʾͼ�Ρ�
	CRect   temprect(0,0,800,667);   
    CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE); 

	if(ecnuMap.Initialize("�й�","China")==success)
	   MessageBox(_T("OK,Now map is initialized."));
	else
	   MessageBox(_T("error,map load failed."));
         //���ҵõ��㼣
	picLibraryPtr->searchByFootmark(ecnuMap);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CFtMarkChinaDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnLButtonDown(nFlags, point);

	int no,index;
	//�ҵ��û����λ�ö�Ӧ�ĵ�ͼ�еĽڵ���no�ʹ洢�±�index
	ecnuMap.positionToNum(point.x,point.y,index,no);

	VertexRecord vr; //ͼ�нڵ��¼
	const List <const Node<PictureRecord>*> *trackListPtr=NULL;
	//ͼ�е��Ӧ����Ƭ����
	//��øýڵ��Ӧ����Ƭ��Ϣ
	ecnuMap.get_trackByIndex(index,vr,trackListPtr);
	CString tmp(vr.the_location().c_str());
	
    CString str_x;//X����
	CString str_y;//Y����
	str_x.Format(_T("%d"),point.x);//ת��point.x��str_x
	str_y.Format(_T("%d"),point.y); //ת��point.y��str_y
    
    tmp =str_x+_T(",")+str_y+_T(",")+tmp;
	CString imageNames("");
	const Node<PictureRecord >* cptr;//��Ƭ��¼��ָ��

	for (int i=0;i<trackListPtr->size();i++)
	{
		trackListPtr->retrieve(i,cptr);
		CString tmpName(cptr->entry.the_key().c_str());
		imageNames = imageNames+ _T(",")+tmpName;	
	}
	MessageBox(tmp + imageNames);
	CDialog::OnLButtonDown(nFlags, point);

}
