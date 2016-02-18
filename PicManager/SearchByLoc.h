#pragma once

#include<string>
#include<cstring>
#include"PicInfoList.h"
#include "afxwin.h"
// CSearchByLoc 对话框

class CSearchByLoc : public CDialog
{
	DECLARE_DYNAMIC(CSearchByLoc)

public:
	CSearchByLoc(CWnd* pParent = NULL);   // 标准构造函数
	CSearchByLoc(CWnd* pParent,PictureInfoList * picListptr_,List<Node<PictureRecord>*>  *r_list_);  
	virtual ~CSearchByLoc();

// 对话框数据
	enum { IDD = IDD_DIALOG_SearchByLoc };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void drawPicture(CStatic *m_Picture/*控件名称*/, int no/*控件编号0-count-1*/);
	DECLARE_MESSAGE_MAP()

private:
	PictureInfoList *picListptr;
	List<Node<PictureRecord>*>  *r_list;//图片地址
	
	CString filenames[4000];//需要显示的所有文件名称
	CString basePath;//picLibrary的路径
	int currentPage;//当前页面
	int numInPages;//每页的图片数目
	int count;//总的图片数目


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
