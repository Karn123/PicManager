#pragma once


#include "afxwin.h"
#include "PicInfoList.h"


// CPicExplorerDlg �Ի���

class CPicExplorerDlg : public CDialog
{
	DECLARE_DYNAMIC(CPicExplorerDlg)

public:
	CPicExplorerDlg(CWnd* pParent = NULL);   // ��׼���캯��
    CPicExplorerDlg(CWnd* pParent,PictureInfoList * picListptr_,List<Node<PictureRecord>*>  *r_list_);   
	virtual ~CPicExplorerDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Explorer };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
private:

	PictureInfoList *picListptr;//ָ��
	CString filename;
	CString basePath;//picLibrary��·��
	int current;
	int count;
	List<Node<PictureRecord>*>  *r_list;  //������ͼƬ��ַ��list
public:
	CStatic m_Pic1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonexit();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();


	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton5();
};
