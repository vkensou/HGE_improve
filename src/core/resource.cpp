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
#include <algorithm>
#include <list>
#include <set>


struct ZipFileInfo
{
	wchar_t path[_MAX_PATH];
	int size;
	int offset;
	int flag;
	bool operator<(const ZipFileInfo& dest)const 
	{
		return wcscmp(path,dest.path)<0;
	}
	bool operator==(const ZipFileInfo& dest)const 
	{
		return wcscmp(path,dest.path)==0;
	}
};

struct ZipInfo
{
	ZipInfo():zip(0){}
	~ZipInfo();

	wchar_t path[_MAX_PATH];
	wchar_t password[64];
	std::set<ZipFileInfo>files;
	int LoadZip(char* file);
	int GetFileCount(){return files.size();}

	bool operator<(const ZipInfo &item) const
	{
		return wcscmp(path,item.path) <0;
	} 
	bool operator==(const ZipInfo &item) const
	{
		return wcscmp(path,item.path) ==0;
	} 
	unzFile zip;
};

ZipInfo::~ZipInfo()
{
	files.clear();
	if(zip)unzClose(zip);
}

int ZipInfo::LoadZip(char* file)
{
	zip=unzOpen(file);
	if(zip)
	{
		int done;
		unz_file_info file_info;
		done = unzGoToFirstFile(zip);
		char tp[_MAX_PATH];
		//pHGE->System_Log(L"pack %s",path);
		while(done==UNZ_OK)
		{
			unzGetCurrentFileInfo(zip, &file_info, tp, sizeof(tp), NULL, 0, NULL, 0);
			if(tp[file_info.size_filename-1]!='/')
			{
				ZipFileInfo *file = new ZipFileInfo();
				C2W(tp,file->path,_MAX_PATH-1);
				wcsupr(file->path);
				file->size = file_info.uncompressed_size;
				file->offset = unzGetOffset(zip);
				file->flag = file_info.flag;
				//pHGE->System_Log(L"file %s, size %d, offset %d",file->path,file->size,file->offset);
				files.insert(*file);
			}
			done=unzGoToNextFile(zip);
		}
		return files.size();
	}
	else
		return 0;
}

struct find_in_res
{
	find_in_res(wchar_t *p):path(p){}
	bool operator()(ZipInfo *z) 
	{ 
		return wcscmp(z->path,path)==0; 
	} 
	wchar_t *path;
};

bool CALL HGE_Impl::Resource_AttachPack(const wchar_t *filename, const wchar_t *password)
{
	wchar_t *szName;
	char Path[_MAX_PATH];
	ZipInfo *zip;

	szName=Resource_MakePath(filename);
	System_Log(L"Attach pack:%s",szName);

	wcsupr(szName);

	std::list<ZipInfo*>::iterator iter = std::find_if(res.begin(),res.end(),find_in_res(szName));
	if(iter != res.end())
	{
		swprintf(szName, L"Pack has been attached:%s", filename);
		_PostError(szName);
		return false;
	}

	zip = new ZipInfo;
	W2C(szName,Path,_MAX_PATH-1);
	wcscpy(zip->path, szName);
	if(zip->LoadZip(Path)==0)return false;
	if(password)
		wcscpy(zip->password ,password);
	else
		zip->password[0]=0;
	res.push_front(zip);
	return true;
}

void CALL HGE_Impl::Resource_RemovePack(const wchar_t *filename)
{
	wchar_t *szName;
	//CResourceList *resItem=res, *resPrev=0;

	szName=Resource_MakePath(filename);
	wcsupr(szName);

	std::list<ZipInfo*>::iterator iter = std::find_if(res.begin(),res.end(),find_in_res(szName));
	if(iter != res.end())
		return;

	delete *iter;
	System_Log(L"Remove pack:%s",szName);
	res.erase(iter);
}

void CALL HGE_Impl::Resource_RemoveAllPacks()
{
	std::list<ZipInfo*>::iterator iter;
	for(iter = res.begin();iter != res.end();iter++)
		delete *iter;
	res.clear();
	System_Log(L"Remove all packs");
}

void* CALL HGE_Impl::Resource_Load(const wchar_t *filename, DWORD *size)
{
	static wchar_t *res_err=L"Can't load resource: %s";

	wchar_t szName[_MAX_PATH];
	char Path[_MAX_PATH];
	int i;
	void *ptr;
	HANDLE hF;

	if(filename[0]==L'\\' || filename[0]==L'/' || filename[1]==L':') goto _fromfile; // skip absolute paths

	// Load from pack

	ZipInfo* zipi=0;
	ZipFileInfo zipfile;
	wcscpy(zipfile.path,filename);
	for(i=0; zipfile.path[i]; i++) { if(zipfile.path[i]==L'/') zipfile.path[i]=L'\\'; }
	wcsupr(zipfile.path);

	//System_Log(L"Load file %s",zipfile.path);
	for(std::list<ZipInfo*>::iterator iter = res.begin();iter != res.end();iter++)
	{
		//System_Log(L"Load file find in pack");
		zipi = *iter;
		std::set<ZipFileInfo>::iterator iter2;
		iter2 = zipi->files.find(zipfile);
		if(iter2!=zipi->files.end())
		{
			ZipFileInfo* file =&*iter2;
			unzSetOffset(zipi->zip,file->offset);
			//System_Log(L"file name %s ,size %d, offset %d",file->path ,file->size ,file->offset );
			W2C(zipi->password, Path, _MAX_PATH-1);
			if(unzOpenCurrentFilePassword(zipi->zip, 0==Path[0] ? 0 : Path) != UNZ_OK)
			{
				swprintf(szName, res_err, filename);
				_PostError(szName);
				return 0;
			}

			ptr = malloc(file->size);
			if(!ptr)
			{
				unzCloseCurrentFile(zipi->zip);
				swprintf(szName, res_err, filename);
				_PostError(szName);
				return 0;
			}

			if(unzReadCurrentFile(zipi->zip, ptr, file->size) < 0)
			{
				unzCloseCurrentFile(zipi->zip);
				free(ptr);
				swprintf(szName, res_err, filename);
				_PostError(szName);
				return 0;
			}
			unzCloseCurrentFile(zipi->zip);
			if(size) *size=file->size;
			return ptr;
		}
	}
	// Load from file
_fromfile:
	//System_Log(L"Load file find file");
	unz_file_info file_info;
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
