#pragma once


#include"PicInfoList.h"
#include<fstream>
#include "afxwin.h"
using namespace std;

// CSearchDlg �Ի���

class CSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchDlg)

public:
	CSearchDlg(CWnd* pParent = NULL);   // ��׼���캯��

	//CSearchDlg(CWnd* pParent,CString m_result_,CString m_result_1_);
	
	CSearchDlg(CWnd* pParent,PictureInfoList * picListptr_,List<Node<PictureRecord>*>  *r_list_);  

	virtual ~CSearchDlg();
	
// �Ի�������
	enum { IDD = IDD_DIALOG_SearchByTitle };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
    void drawPicture(CStatic *m_Pic/*�ؼ�����*/, int no/*�ؼ����0-count-1*/);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CString m_result;   //������󶨵ı���

	
	afx_msg void OnEnChangeEdit4();
private:
	PictureInfoList *picListptr;
	List<Node<PictureRecord>*>  *r_list;//ͼƬ��ַ
	
	CString filenames[4000];//��Ҫ��ʾ�������ļ�����
	CString basePath;//picLibrary��·��
	int currentPage;//��ǰҳ��
	int numInPages;//ÿҳ��ͼƬ��Ŀ
	int count;//�ܵ�ͼƬ��Ŀ

public:
	afx_msg void OnEnChangeEdit2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	CStatic m_Pic1;
	CStatic m_Pic2;
	CStatic m_Pic3;
	CStatic m_Pic4;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnStnClickedPic1();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
