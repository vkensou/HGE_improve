/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: resources management
*/


#include "hge_impl.h"

#define NOCRYPT
//#define NOUNCRYPT
#include "ZLIB\unzip.h"


bool CALL HGE_Impl::Resource_AttachPack(const wchar_t *filename, const wchar_t *password)
{
	wchar_t *szName;
	char Path[_MAX_PATH];
	CResourceList *resItem=res;
	unzFile zip;

	szName=Resource_MakePath(filename);
	wcsupr(szName);

	while(resItem)
	{
		if(!wcscmp(szName,resItem->filename)) return false;
		resItem=resItem->next;
	}
	W2C(szName, Path, _MAX_PATH-1);
	zip=unzOpen(Path);
	if(!zip) return false;
	unzClose(zip);

	resItem=new CResourceList;
	wcscpy(resItem->filename, szName);
	if(password){
		W2C(password, Path, _MAX_PATH-1);
		strcpy(resItem->password, Path);
	}
	else resItem->password[0]=0;
	resItem->next=res;
	res=resItem;

	return true;
}

void CALL HGE_Impl::Resource_RemovePack(const wchar_t *filename)
{
	wchar_t *szName;
	CResourceList *resItem=res, *resPrev=0;

	szName=Resource_MakePath(filename);
	wcsupr(szName);

	while(resItem)
	{
		if(!wcscmp(szName,resItem->filename))
		{
			if(resPrev) resPrev->next=resItem->next;
			else res=resItem->next;
			delete resItem;
			break;
		}

		resPrev=resItem;
		resItem=resItem->next;
	}
}

void CALL HGE_Impl::Resource_RemoveAllPacks()
{
	CResourceList *resItem=res, *resNextItem;

	while(resItem)
	{
		resNextItem=resItem->next;
		delete resItem;
		resItem=resNextItem;
	}

	res=0;
}

void* CALL HGE_Impl::Resource_Load(const wchar_t *filename, DWORD *size)
{
	static wchar_t *res_err=L"Can't load resource: %s";

	CResourceList *resItem=res;
	wchar_t szName[_MAX_PATH];
	wchar_t szZipName[_MAX_PATH];
	char Path[_MAX_PATH];
	unzFile zip;
	unz_file_info file_info;
	int done, i;
	void *ptr;
	HANDLE hF;

	if(filename[0]==L'\\' || filename[0]==L'/' || filename[1]==L':') goto _fromfile; // skip absolute paths

	// Load from pack
 
	wcscpy(szName,filename);
	wcsupr(szName);
	for(i=0; szName[i]; i++) { if(szName[i]==L'/') szName[i]=L'\\'; }

	while(resItem)
	{
		W2C(resItem->filename, Path, _MAX_PATH-1);
		zip=unzOpen(Path);
		done=unzGoToFirstFile(zip);
		while(done==UNZ_OK)
		{
			unzGetCurrentFileInfo(zip, &file_info, Path, sizeof(szZipName), NULL, 0, NULL, 0);
			C2W(Path, szZipName, _MAX_PATH-1);
			wcsupr(szZipName);
			for(i=0; szZipName[i]; i++)	{ if(szZipName[i]==L'/') szZipName[i]=L'\\'; }
			if(!wcscmp(szName,szZipName))
			{
				if(unzOpenCurrentFilePassword(zip, resItem->password[0] ? resItem->password : 0) != UNZ_OK)
				{
					unzClose(zip);
					swprintf(szName, res_err, filename);
					_PostError(szName);
					return 0;
				}

				ptr = malloc(file_info.uncompressed_size);
				if(!ptr)
				{
					unzCloseCurrentFile(zip);
					unzClose(zip);
					swprintf(szName, res_err, filename);
					_PostError(szName);
					return 0;
				}

				if(unzReadCurrentFile(zip, ptr, file_info.uncompressed_size) < 0)
				{
					unzCloseCurrentFile(zip);
					unzClose(zip);
					free(ptr);
					swprintf(szName, res_err, filename);
					_PostError(szName);
					return 0;
				}
				unzCloseCurrentFile(zip);
				unzClose(zip);
				if(size) *size=file_info.uncompressed_size;
				return ptr;
			}
			
			done=unzGoToNextFile(zip);
		}
		
		unzClose(zip);
		resItem=resItem->next;
	}

	// Load from file
_fromfile:

	hF = CreateFile(Resource_MakePath(filename), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, NULL);
	if(hF == INVALID_HANDLE_VALUE)
	{
		swprintf(szName, res_err, filename);
		_PostError(szName);
		return 0;
	}
	file_info.uncompressed_size = GetFileSize(hF, NULL);
	ptr = malloc(file_info.uncompressed_size);
	if(!ptr)
	{
		CloseHandle(hF);
		swprintf(szName, res_err, filename);
		_PostError(szName);
		return 0;
	}
	if(ReadFile(hF, ptr, file_info.uncompressed_size, &file_info.uncompressed_size, NULL ) == 0)
	{
		CloseHandle(hF);
		free(ptr);
		swprintf(szName, res_err, filename);
		_PostError(szName);
		return 0;
	}
	
	CloseHandle(hF);
	if(size) *size=file_info.uncompressed_size;
	return ptr;
}


void CALL HGE_Impl::Resource_Free(void *res)
{
	if(res) free(res);
}


wchar_t* CALL HGE_Impl::Resource_MakePath(const wchar_t *filename)
{
	int i;

	if(!filename)
		wcscpy(szTmpFilename, szAppPath);
	else if(filename[0]==L'\\' || filename[0]==L'/' || filename[1]==L':')
		wcscpy(szTmpFilename, filename);
	else
	{
		wcscpy(szTmpFilename, szAppPath);
		if(filename) wcscat(szTmpFilename, filename);
	}

	for(i=0; szTmpFilename[i]; i++) { if(szTmpFilename[i]==L'/') szTmpFilename[i]=L'\\'; }
	return szTmpFilename;
}

wchar_t* CALL HGE_Impl::Resource_EnumFiles(const wchar_t *wildcard)
{
	if(wildcard)
	{
		if(hSearch) { FindClose(hSearch); hSearch=0; }
		hSearch=FindFirstFile(Resource_MakePath(wildcard), &SearchData);
		if(hSearch==INVALID_HANDLE_VALUE) { hSearch=0; return 0; }

		if(!(SearchData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) return SearchData.cFileName;
		else return Resource_EnumFiles();
	}
	else
	{
		if(!hSearch) return 0;
		for(;;)
		{
			if(!FindNextFile(hSearch, &SearchData))	{ FindClose(hSearch); hSearch=0; return 0; }
			if(!(SearchData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) return SearchData.cFileName;
		}
	}
}

wchar_t* CALL HGE_Impl::Resource_EnumFolders(const wchar_t *wildcard)
{
	if(wildcard)
	{
		if(hSearch) { FindClose(hSearch); hSearch=0; }
		hSearch=FindFirstFile(Resource_MakePath(wildcard), &SearchData);
		if(hSearch==INVALID_HANDLE_VALUE) { hSearch=0; return 0; }

		if((SearchData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
		   wcscmp(SearchData.cFileName,L".") && wcscmp(SearchData.cFileName,L".."))
				return SearchData.cFileName;
		else return Resource_EnumFolders();
	}
	else
	{
		if(!hSearch) return 0;
		for(;;)
		{
			if(!FindNextFile(hSearch, &SearchData))	{ FindClose(hSearch); hSearch=0; return 0; }
			if((SearchData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			   wcscmp(SearchData.cFileName,L".") && wcscmp(SearchData.cFileName,L".."))
					return SearchData.cFileName;
		}
	}
}
