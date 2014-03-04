/*!
@file
@author		Albert Semenov
@date		08/2008
*/

#ifndef __BASE_MANAGER_H__
#define __BASE_MANAGER_H__

#include <MyGUI.h>
#include "StatisticInfo.h"
#include "InputFocusInfo.h"

#include "InputManager.h"
#include "PointerManager.h"

#include "hge.h"

namespace MyGUI
{
	class HGEPlatform;
}

struct HWND__;
typedef HWND__* HWND;
struct HINSTANCE__;
typedef HINSTANCE__* HINSTANCE;

namespace base
{

	class BaseManager :
		//public input::InputManager,
		public input::PointerManager,
		public HGEEventListener
	{
	public:
		BaseManager();
		virtual ~BaseManager();

		virtual void prepare() = 0;
		bool create();
		void destroy();
		void run();
		void quit();

		void setWindowCaption(const std::wstring& _text);
		void createDefaultScene() { }

		const std::string& getRootMedia();
		void setResourceFilename(const std::string& _flename);
		void addResourceLocation(const std::string& _name, bool _recursive = false);

		diagnostic::StatisticInfo* getStatisticInfo();
		diagnostic::InputFocusInfo* getFocusInput();

		/*internal:*/
		void _windowResized();
		
		bool GetInputEvent(hgeInputEvent* event);
	protected:
		virtual void createScene() { }
		virtual void destroyScene() { }

		virtual void setupResources();

		//virtual void injectMouseMove(int _absx, int _absy, int _absz);
		//virtual void injectMousePress(int _absx, int _absy, MyGUI::MouseButton _id);
		//virtual void injectMouseRelease(int _absx, int _absy, MyGUI::MouseButton _id);
		//virtual void injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text);
		//virtual void injectKeyRelease(MyGUI::KeyCode _key);
		void drawOneFrame();

	private:
		void createGui();
		void destroyGui();

		void windowAdjustSettings(HWND hWnd, int width, int height, bool fullScreen);

		void resizeRender(int _width, int _height);
		bool createRender(int _width, int _height, bool _windowed);
		void destroyRender();

	private:
		diagnostic::StatisticInfo* mInfo;
		diagnostic::InputFocusInfo* mFocusInfo;

		HWND hWnd;
		HINSTANCE hInstance;

		bool mExit;

		std::string mRootMedia;
		bool mIsDeviceLost;
	protected:
		MyGUI::Gui* mGUI;
		MyGUI::HGEPlatform* mPlatform;
		HGE* hge;
		std::string mResourceFileName;
		bool GUIAccessInput;
	};

} // namespace base

#endif // __BASE_MANAGER_H__

