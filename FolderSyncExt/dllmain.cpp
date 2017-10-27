// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "FolderSync_i.h"
#include "dllmain.h"

CFolderSyncModule _AtlModule;

class CFolderSyncApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CFolderSyncApp, CWinApp)
END_MESSAGE_MAP()

CFolderSyncApp theApp;

BOOL CFolderSyncApp::InitInstance()
{
	return CWinApp::InitInstance();
}

int CFolderSyncApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
