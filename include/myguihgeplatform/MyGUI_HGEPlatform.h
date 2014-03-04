/*!
	@file
	@author		Losev Vasiliy aka bool
	@date		06/2009
*/

#ifndef __MYGUI_HGE_PLATFORM_H__
#define __MYGUI_HGE_PLATFORM_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_HGERenderManager.h"
#include "MyGUI_HGEDataManager.h"
#include "MyGUI_HGETexture.h"
#include "MyGUI_HGEVertexBuffer.h"
#include "MyGUI_HGEDiagnostic.h"
#include "MyGUI_LogManager.h"

namespace MyGUI
{

	class HGEPlatform
	{
	public:
		HGEPlatform() :
			mIsInitialise(false)
		{
			mLogManager = new LogManager();
			mRenderManager = new HGERenderManager();
			mDataManager = new HGEDataManager();
		}

		~HGEPlatform()
		{
			assert(!mIsInitialise);
			delete mRenderManager;
			delete mDataManager;
			delete mLogManager;
		}

		void initialise(const std::string& _logName = MYGUI_PLATFORM_LOG_FILENAME)
		{
			assert(!mIsInitialise);
			mIsInitialise = true;

			if (!_logName.empty())
				LogManager::getInstance().createDefaultSource(_logName);

			mRenderManager->initialise();
			mDataManager->initialise();
		}

		void shutdown()
		{
			assert(mIsInitialise);
			mIsInitialise = false;

			mRenderManager->shutdown();
			mDataManager->shutdown();
		}

		HGERenderManager* getRenderManagerPtr()
		{
			assert(mIsInitialise);
			return mRenderManager;
		}

		HGEDataManager* getDataManagerPtr()
		{
			assert(mIsInitialise);
			return mDataManager;
		}

	private:
		bool mIsInitialise;
		HGERenderManager* mRenderManager;
		HGEDataManager* mDataManager;
		LogManager* mLogManager;

	};

} // namespace MyGUI

#endif // __MYGUI_HGE_PLATFORM_H__
