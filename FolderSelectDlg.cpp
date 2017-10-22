// FolderSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FolderSelectDlg.h"
#include "afxdialogex.h"


// FolderSelectDlg dialog

IMPLEMENT_DYNAMIC(FolderSelectDlg, CDialog)

FolderSelectDlg::FolderSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_FOLDER_SELECT, pParent)
{

}

FolderSelectDlg::~FolderSelectDlg()
{
}

void FolderSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DROPBOX_TREE, _dropboxTree);
}


BEGIN_MESSAGE_MAP(FolderSelectDlg, CDialog)
END_MESSAGE_MAP()


// FolderSelectDlg message handlers
