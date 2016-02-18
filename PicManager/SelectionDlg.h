#pragma once

#include"PicInfoList.h"
// SelectionDlg �Ի���

class SelectionDlg : public CDialog
{
	DECLARE_DYNAMIC(SelectionDlg)

public:
	SelectionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	SelectionDlg(CWnd* pParent , PictureInfoList * picLibraryPtr_,
	List<Node<PictureRecord>*>  *my_foot_list_);
	virtual ~SelectionDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_Selection };
private:
	PictureInfoList *picLibraryPtr;
	List<Node<PictureRecord>*>  *my_foot_list;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	afx_msg void OnPaint();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
};
