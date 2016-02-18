#pragma once


#include"PicInfoList.h"
// CFootMarkdlg �Ի���

class CFootMarkdlg : public CDialog
{
	DECLARE_DYNAMIC(CFootMarkdlg)

public:
	CFootMarkdlg(CWnd* pParent = NULL);   // ��׼���캯��
	CFootMarkdlg(CWnd* pParent, PictureInfoList * picLibraryPtr_,
	List<Node<PictureRecord>*>  *my_foot_list_); 
 
	virtual ~CFootMarkdlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FootMarkDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
