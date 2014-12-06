// ReadPictureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReadPicture.h"
#include "ReadPictureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



HBITMAP LoadAnImage(const unsigned char *data, unsigned long len)
{
	HGLOBAL hG;
	IStream *s;
	IPicture *p;
	HBITMAP hB, hBB;

	hG = GlobalAlloc(GPTR, len);
	if(!hG)
	{
		return NULL;
	}

	memcpy(hG, data, len);

	if(CreateStreamOnHGlobal(hG, FALSE, &s) != S_OK)
	{
		GlobalFree(hG);
		return NULL;
	}

	if(OleLoadPicture(s, 0, FALSE, IID_IPicture, (void **)&p) != S_OK)
	{
		s->Release();
		GlobalFree(hG);
		return NULL;
	}

	s->Release();
	GlobalFree(hG);

	p->get_Handle((OLE_HANDLE *)&hB);
	hBB = (HBITMAP)CopyImage(hB, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG);
	p->Release();

	return hBB;
}
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CReadPictureDlg 对话框




CReadPictureDlg::CReadPictureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadPictureDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReadPictureDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CReadPictureDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CReadPictureDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CReadPictureDlg 消息处理程序

BOOL CReadPictureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CReadPictureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CReadPictureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CReadPictureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReadPictureDlg::showpicture(CString&str)
{

	unsigned char *p;
	unsigned long len;
	FILE *fp;
	fp = fopen((LPCTSTR)str, "rb");
	if(fp==NULL) 
	{
		AfxMessageBox("建立文件出错!");
		return;
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	p = new unsigned char[len];
	fread(p, 1, len, fp);
	fclose(fp);
	//DeleteFile("~me.bmp");
	m_hB = LoadAnImage(p, len);
	delete [] p;
	if(m_hB)
	{
		GetDlgItem(IDC_STATIC)->Invalidate();
		GetDlgItem(IDC_STATIC)->UpdateWindow();
	}
}


void CReadPictureDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString lpstrName;
	CString	strFilePath;
	char cLocalDir[1000];
	GetModuleFileName(NULL,   cLocalDir,   sizeof(cLocalDir));	//get local folder path
	CFileDialog	dlgFile(TRUE, NULL, NULL,  OFN_HIDEREADONLY, "JPG Files (*.jpg)|*.jpg|All Files (*.*)|*.*|| ", NULL);

	dlgFile.m_ofn.lpstrInitialDir = cLocalDir ;
	dlgFile.m_ofn.lpstrTitle =_T("请选择图片");

	if (dlgFile.DoModal() == IDOK)
	{
		lpstrName =  dlgFile.GetPathName( ); 
		char PathName[1024  + 1]={0};
		memcpy(PathName,lpstrName,strlen(lpstrName));	//store file path 
        strFilePath.Format((char *)PathName);	//change format
        showpicture(strFilePath);
	}else   
	{ 
		SetDlgItemText(IDC_STATIC,"");
	}
}

HBRUSH CReadPictureDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if(m_hB && (pWnd->GetDlgCtrlID() == IDC_STATIC))
	{
		CRect r;
		GetDlgItem(IDC_STATIC)->GetClientRect(&r);
		CDC dcMem;
		dcMem.CreateCompatibleDC(pDC);
		dcMem.SelectObject(m_hB);
		BITMAP bm;
		GetObject(m_hB, sizeof(bm), &bm);

		pDC->StretchBlt(0, 0, r.Width(), r.Height(), &dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		//pDC->BitBlt(0,0,r.Width(),r.Height(),&dcMem,0,0,SRCCOPY);
	}
	// TODO: Return a different brush if the default is not des
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CReadPictureDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}
