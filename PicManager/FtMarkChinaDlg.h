#pragma once


// CFtMarkChinaDlg �Ի���
#include"PicInfoList.h"

class CFtMarkChinaDlg : public CDialog
{
	DECLARE_DYNAMIC(CFtMarkChinaDlg)

public:
	CFtMarkChinaDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CFtMarkChinaDlg(CWnd* pParent, PictureInfoList * picLibraryPtr_,
	List<Node<PictureRecord>*>  *my_foot_list_); 
	virtual ~CFtMarkChinaDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FootMarkDlgChina };


private:
	LocationGraph<600> ecnuMap;
    PictureInfoList *picLibraryPtr;
	List<Node<PictureRecord>*>  *my_foot_list;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
