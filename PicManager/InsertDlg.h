#pragma once
#include"PdfJpeg.h"


#include"PicInfoList.h"
// CInsertDlg �Ի���

class CInsertDlg : public CDialog
{
	DECLARE_DYNAMIC(CInsertDlg)

public:
	CInsertDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CInsertDlg(CWnd* pParent ,PictureInfoList *picIptr_,List<Node<PictureRecord>*> *x_list_);
	virtual ~CInsertDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Insert };
private:
	PictureInfoList *picIptr;
	List<Node<PictureRecord>*> *x_list;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	COleDateTime m_creatTime;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	CString m_FileName;
};
