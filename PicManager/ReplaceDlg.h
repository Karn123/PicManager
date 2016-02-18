#pragma once

#include"PicInfoList.h"
// CReplaceDlg �Ի���


class CReplaceDlg : public CDialog
{
	DECLARE_DYNAMIC(CReplaceDlg)

public:
	CReplaceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CReplaceDlg(CWnd* pParent,PictureInfoList * pInfoptr_,List<Node<PictureRecord>*>  *rp_list_);
	virtual ~CReplaceDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Replace};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	PictureInfoList  *pInfoptr;
	List<Node<PictureRecord>*>   *rp_list;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_fileName;
	CString m_Title;
	CString m_loc;
	CString m_map;
	
	afx_msg void OnBnClickedOk();
	int m_height;
	int m_width;
	afx_msg void OnEnChangeEdit7();

	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg void OnStnClicked7();
};
