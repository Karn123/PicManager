#pragma once
#include "Graph.h"
#include "GraphSeries.h"

// TimeTestDlg 对话框

class TimeTestDlg : public CDialog
{
	DECLARE_DYNAMIC(TimeTestDlg)

public:
	TimeTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TimeTestDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();

	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();

private:
	 CGraph* testGraph;
public:
	afx_msg void OnBnClickedButton9();
};
