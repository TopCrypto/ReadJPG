// ReadPictureDlg.h : ͷ�ļ�
//

#pragma once


// CReadPictureDlg �Ի���
class CReadPictureDlg : public CDialog
{
// ����
public:
	CReadPictureDlg(CWnd* pParent = NULL);	// ��׼���캯��
    HBITMAP m_hB;




// �Ի�������
	enum { IDD = IDD_READPICTURE_DIALOG };

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
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	void showpicture(CString&str);
};
