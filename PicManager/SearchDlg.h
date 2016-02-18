#pragma once


#include"PicInfoList.h"
#include<fstream>
#include "afxwin.h"
using namespace std;

// CSearchDlg 对话框

class CSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchDlg)

public:
	CSearchDlg(CWnd* pParent = NULL);   // 标准构造函数

	//CSearchDlg(CWnd* pParent,CString m_result_,CString m_result_1_);
	
	CSearchDlg(CWnd* pParent,PictureInfoList * picListptr_,List<Node<PictureRecord>*>  *r_list_);  

	virtual ~CSearchDlg();
	
// 对话框数据
	enum { IDD = IDD_DIALOG_SearchByTitle };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
    void drawPicture(CStatic *m_Pic/*控件名称*/, int no/*控件编号0-count-1*/);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CString m_result;   //搜索框绑定的变量

	
	afx_msg void OnEnChangeEdit4();
private:
	PictureInfoList *picListptr;
	List<Node<PictureRecord>*>  *r_list;//图片地址
	
	CString filenames[4000];//需要显示的所有文件名称
	CString basePath;//picLibrary的路径
	int currentPage;//当前页面
	int numInPages;//每页的图片数目
	int count;//总的图片数目

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
