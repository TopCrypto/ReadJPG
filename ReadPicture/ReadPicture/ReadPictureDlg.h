// ReadPictureDlg.h : 头文件
//

#pragma once


// CReadPictureDlg 对话框
class CReadPictureDlg : public CDialog
{
// 构造
public:
	CReadPictureDlg(CWnd* pParent = NULL);	// 标准构造函数
    HBITMAP m_hB;




// 对话框数据
	enum { IDD = IDD_READPICTURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
