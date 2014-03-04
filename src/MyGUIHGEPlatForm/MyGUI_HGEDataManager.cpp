/*!
	@file
	@author		Losev Vasiliy aka bool
	@date		06/2009
*/

#include "MyGUI_HGEDataManager.h"
#include "MyGUI_HGEDiagnostic.h"
#include "MyGUI_DataFileStream.h"
#include "MyGUI_HGEFileStream.h"
#include "FileSystemInfo/FileSystemInfo.h"
#include <fstream>

namespace MyGUI
{

	HGEDataManager::HGEDataManager() :
		mIsInitialise(false)
	{
	}

	void HGEDataManager::initialise()
	{
		MYGUI_PLATFORM_ASSERT(!mIsInitialise, getClassTypeName() << " initialised twice");
		MYGUI_PLATFORM_LOG(Info, "* Initialise: " << getClassTypeName());

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully initialized");
		mIsInitialise = true;
		mpHGE = hgeCreate(HGE_VERSION);
	}

	void HGEDataManager::shutdown()
	{
		MYGUI_PLATFORM_ASSERT(mIsInitialise, getClassTypeName() << " is not initialised");
		MYGUI_PLATFORM_LOG(Info, "* Shutdown: " << getClassTypeName());

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully shutdown");
		mIsInitialise = false;
		mpHGE->Release();
	}

	IDataStream* HGEDataManager::getData(const std::string& _name)
	{
		void* ptr;DWORD size=0;
		MyGUI::UString path = "MyGUI_Media\\" + _name;

		ptr = mpHGE->Resource_Load(path.asWStr().c_str(),&size);

		if(!size)
			return nullptr;

		std::stringstream *stream = new std::stringstream;
		stream->write((const char*)ptr,size);

		mpHGE->Resource_Free(ptr);

		return new HGEFileStream(stream);



		//std::string filepath = getDataPath(_name);
		//if (filepath.empty())
		//	return nullptr;

		//std::ifstream* stream = new std::ifstream();

		//stream->open(path.c_str(), std::ios_base::binary);
		
		//if (!stream->is_open())
		//{
		//	delete stream;
		//	return nullptr;
		//}

		//DataFileStream* data = new DataFileStream(stream);

		//return data;
	}

	bool HGEDataManager::isDataExist(const std::string& _name)
	{
		return true;
		const VectorString& files = getDataListNames(_name);
		return files.size() == 1;
	}

	const VectorString& HGEDataManager::getDataListNames(const std::string& _pattern)
	{
		static VectorString result;
		common::VectorWString wresult;
		result.clear();

		for (VectorArhivInfo::const_iterator item = mPaths.begin(); item != mPaths.end(); ++item)
		{
			common::scanFolder(wresult, (*item).name, (*item).recursive, MyGUI::UString(_pattern).asWStr(), false);
		}

		for (common::VectorWString::const_iterator item = wresult.begin(); item != wresult.end(); ++item)
		{
			result.push_back(MyGUI::UString(*item).asUTF8());
		}

		return result;
	}

	const std::string& HGEDataManager::getDataPath(const std::string& _name)
	{
		static std::string path;
		VectorString result;
		common::VectorWString wresult;

		for (VectorArhivInfo::const_iterator item = mPaths.begin(); item != mPaths.end(); ++item)
		{
			common::scanFolder(wresult, (*item).name, (*item).recursive, MyGUI::UString(_name).asWStr(), true);
		}

		for (common::VectorWString::const_iterator item = wresult.begin(); item != wresult.end(); ++item)
		{
			result.push_back(MyGUI::UString(*item).asUTF8());
		}

		path = result.size() == 1 ? result[0] : "";
		return path;
	}

	void HGEDataManager::addResourceLocation(const std::string& _name, bool _recursive)
	{
		ArhivInfo info;
		info.name = MyGUI::UString(_name).asWStr();
		info.recursive = _recursive;
		mPaths.push_back(info);
	}

} // namespace MyGUI
