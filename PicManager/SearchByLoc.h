#pragma once

#include<string>
#include<cstring>
#include"PicInfoList.h"
#include "afxwin.h"
// CSearchByLoc �Ի���

class CSearchByLoc : public CDialog
{
	DECLARE_DYNAMIC(CSearchByLoc)

public:
	CSearchByLoc(CWnd* pParent = NULL);   // ��׼���캯��
	CSearchByLoc(CWnd* pParent,PictureInfoList * picListptr_,List<Node<PictureRecord>*>  *r_list_);  
	virtual ~CSearchByLoc();

// �Ի�������
	enum { IDD = IDD_DIALOG_SearchByLoc };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void drawPicture(CStatic *m_Picture/*�ؼ�����*/, int no/*�ؼ����0-count-1*/);
	DECLARE_MESSAGE_MAP()

private:
	PictureInfoList *picListptr;
	List<Node<PictureRecord>*>  *r_list;//ͼƬ��ַ
	
	CString filenames[4000];//��Ҫ��ʾ�������ļ�����
	CString basePath;//picLibrary��·��
	int currentPage;//��ǰҳ��
	int numInPages;//ÿҳ��ͼƬ��Ŀ
	int count;//�ܵ�ͼƬ��Ŀ


public:
	afx_msg void OnBnClickedButton1();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedPre();
	afx_msg void OnBnClickedButton2();
	CStatic m_Picture1;
	CStatic m_Picture2;
	CStatic m_Picture3;
	CStatic m_Picture4;
	CString m_result;

	afx_msg void OnPaint();
	afx_msg void OnEnChangeEdit1();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
