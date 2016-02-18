#pragma once

#include"PicInfoList.h"
// SelectionDlg 对话框

class SelectionDlg : public CDialog
{
	DECLARE_DYNAMIC(SelectionDlg)

public:
	SelectionDlg(CWnd* pParent = NULL);   // 标准构造函数
	SelectionDlg(CWnd* pParent , PictureInfoList * picLibraryPtr_,
	List<Node<PictureRecord>*>  *my_foot_list_);
	virtual ~SelectionDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_Selection };
private:
	PictureInfoList *picLibraryPtr;
	List<Node<PictureRecord>*>  *my_foot_list;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	afx_msg void OnPaint();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
};
