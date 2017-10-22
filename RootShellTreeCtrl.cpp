#include "stdafx.h"
#include "RootShellTreeCtrl.h"


RootShellTreeCtrl::RootShellTreeCtrl()
{
}


RootShellTreeCtrl::~RootShellTreeCtrl()
{
}

void RootShellTreeCtrl::SetRootPath(const CString& rootPath)
{
	_rootPath = rootPath;
}

HRESULT RootShellTreeCtrl::EnumObjects(HTREEITEM hParentItem, LPSHELLFOLDER pParentFolder, LPITEMIDLIST pidlParent)
{
	ASSERT_VALID(this);
	ASSERT_VALID(afxShellManager);

	LPENUMIDLIST pEnum = NULL;

	HRESULT hr = pParentFolder->EnumObjects(NULL, m_dwFlags, &pEnum);
	if (FAILED(hr) || pEnum == NULL)
	{
		return hr;
	}

	LPITEMIDLIST pidlTemp;
	DWORD dwFetched = 1;

	// Enumerate the item's PIDLs:
	while (SUCCEEDED(pEnum->Next(1, &pidlTemp, &dwFetched)) && dwFetched)
	{
		TVITEM tvItem;
		ZeroMemory(&tvItem, sizeof(tvItem));

		// Fill in the TV_ITEM structure for this item:
		tvItem.mask = TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN;

		// AddRef the parent folder so it's pointer stays valid:
		pParentFolder->AddRef();

		// Put the private information in the lParam:
		LPAFX_SHELLITEMINFO pItem = (LPAFX_SHELLITEMINFO)GlobalAlloc(GPTR, sizeof(AFX_SHELLITEMINFO));
		ENSURE(pItem != NULL);

		pItem->pidlRel = pidlTemp;
		pItem->pidlFQ = afxShellManager->ConcatenateItem(pidlParent, pidlTemp);

		pItem->pParentFolder = pParentFolder;
		tvItem.lParam = (LPARAM)pItem;

		CString strItem = OnGetItemText(pItem);
		tvItem.pszText = strItem.GetBuffer(strItem.GetLength());
		tvItem.iImage = OnGetItemIcon(pItem, FALSE);
		tvItem.iSelectedImage = OnGetItemIcon(pItem, TRUE);

		// Determine if the item has children:
		DWORD dwAttribs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER | SFGAO_DISPLAYATTRMASK | SFGAO_CANRENAME | SFGAO_FILESYSANCESTOR;

		pParentFolder->GetAttributesOf(1, (LPCITEMIDLIST*)&pidlTemp, &dwAttribs);
		tvItem.cChildren = (dwAttribs & (SFGAO_HASSUBFOLDER | SFGAO_FILESYSANCESTOR));

		// Determine if the item is shared:
		if (dwAttribs & SFGAO_SHARE)
		{
			tvItem.mask |= TVIF_STATE;
			tvItem.stateMask |= TVIS_OVERLAYMASK;
			tvItem.state |= INDEXTOOVERLAYMASK(1); //1 is the index for the shared overlay image
		}

		// Fill in the TV_INSERTSTRUCT structure for this item:
		TVINSERTSTRUCT tvInsert;

		tvInsert.item = tvItem;
		tvInsert.hInsertAfter = TVI_LAST;
		tvInsert.hParent = hParentItem;

		InsertItem(&tvInsert);
		dwFetched = 0;
	}

	pEnum->Release();
	return S_OK;
}

