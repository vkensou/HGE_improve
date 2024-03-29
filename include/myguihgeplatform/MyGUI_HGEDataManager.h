/*!
	@file
	@author		Losev Vasiliy aka bool
	@date		06/2009
*/

#ifndef __MYGUI_OGRE_DATA_MANAGER_H__
#define __MYGUI_OGRE_DATA_MANAGER_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_DataManager.h"
#include "hge.h"

namespace MyGUI
{

	class HGEDataManager :
		public DataManager
	{
	public:
		HGEDataManager();

		void initialise();
		void shutdown();

		static HGEDataManager& getInstance()
		{
			return *getInstancePtr();
		}
		static HGEDataManager* getInstancePtr()
		{
			return static_cast<HGEDataManager*>(DataManager::getInstancePtr());
		}

		/** @see DataManager::getData(const std::string& _name) */
		virtual IDataStream* getData(const std::string& _name);

		/** @see DataManager::isDataExist(const std::string& _name) */
		virtual bool isDataExist(const std::string& _name);

		/** @see DataManager::getDataListNames(const std::string& _pattern) */
		virtual const VectorString& getDataListNames(const std::string& _pattern);

		/** @see DataManager::getDataPath(const std::string& _name) */
		virtual const std::string& getDataPath(const std::string& _name);

	/*internal:*/
		void addResourceLocation(const std::string& _name, bool _recursive);

	private:
		HGE* mpHGE;
		struct ArhivInfo
		{
			std::wstring name;
			bool recursive;
		};
		typedef std::vector<ArhivInfo> VectorArhivInfo;
		VectorArhivInfo mPaths;

		bool mIsInitialise;
	};

} // namespace MyGUI

#endif // __MYGUI_OGRE_DATA_MANAGER_H__
