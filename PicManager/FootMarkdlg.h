#pragma once


#include"PicInfoList.h"
// CFootMarkdlg 对话框

class CFootMarkdlg : public CDialog
{
	DECLARE_DYNAMIC(CFootMarkdlg)

public:
	CFootMarkdlg(CWnd* pParent = NULL);   // 标准构造函数
	CFootMarkdlg(CWnd* pParent, PictureInfoList * picLibraryPtr_,
	List<Node<PictureRecord>*>  *my_foot_list_); 
 
	virtual ~CFootMarkdlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_FootMarkDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

private:
	LocationGraph<600> ecnuMap;
    PictureInfoList *picLibraryPtr;
	List<Node<PictureRecord>*>  *my_foot_list;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
