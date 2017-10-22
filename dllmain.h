// dllmain.h : Declaration of module class.

class CFolderSyncModule : public ATL::CAtlDllModuleT< CFolderSyncModule >
{
public :
	DECLARE_LIBID(LIBID_FolderSyncLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FOLDERSYNC, "{17B9B9F4-5C9E-4D48-A545-46BB756CFF85}")
};

extern class CFolderSyncModule _AtlModule;
