#pragma once
#include "RootShellTreeCtrl.h"


// FolderSelectDlg dialog

class FolderSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(FolderSelectDlg)

public:
	FolderSelectDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~FolderSelectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FOLDER_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	RootShellTreeCtrl _dropboxTree;
};
