// MainUIDlg.h : ͷ�ļ�
//

#pragma once
#include "PicInfoList.h" //����ͷ�ļ�
#include"SearchDlg.h"
#include"SearchByLoc.h"
#include"SelectionDlg.h"
#include"InsertDlg.h"
#include"TimeTestDlg.h"
// CMainUIDlg �Ի���
class CMainUIDlg : public CDialog
{
// ����
public:
	CMainUIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAINUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSearchbytitle();
	afx_msg void OnBnClickedButtonexplore();
	afx_msg void OnBnClickedButtonTrack();

private:
	PictureInfoList picLibrary; //�����µĶ���
	List<Node<PictureRecord>*>  list_trans;//�����µĶ���
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonSearchbyloc();
	afx_msg void OnBnClickedButtonReplace();
	afx_msg void OnBnDoubleclickedButtonTrack();
	afx_msg void OnBnClickedButtonTesting();
};
