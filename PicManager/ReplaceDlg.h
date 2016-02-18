#pragma once

#include"PicInfoList.h"
// CReplaceDlg 对话框


class CReplaceDlg : public CDialog
{
	DECLARE_DYNAMIC(CReplaceDlg)

public:
	CReplaceDlg(CWnd* pParent = NULL);   // 标准构造函数
	CReplaceDlg(CWnd* pParent,PictureInfoList * pInfoptr_,List<Node<PictureRecord>*>  *rp_list_);
	virtual ~CReplaceDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_Replace};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
