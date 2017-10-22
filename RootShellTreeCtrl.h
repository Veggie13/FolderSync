#pragma once
#include <afxshelltreectrl.h>

class RootShellTreeCtrl :
	public CMFCShellTreeCtrl
{
public:
	RootShellTreeCtrl();
	~RootShellTreeCtrl();

	void SetRootPath(const CString& rootPath);

protected:
	virtual HRESULT EnumObjects(HTREEITEM hParentItem, LPSHELLFOLDER pParentFolder, LPITEMIDLIST pidlParent);

private:
	CString _rootPath;
};

