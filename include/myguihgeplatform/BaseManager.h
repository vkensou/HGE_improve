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
		public input::InputManager,
		public input::PointerManager,
		public HGEEventListener
	{
	public:
		BaseManager();
		virtual ~BaseManager();

		virtual void prepare() = 0; // инициализация коммандной строки
		bool create(); // создае?начальну?точк?каркас?приложен?
		void destroy(); // очищае?вс?параметр?каркас?приложен?
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
		virtual bool Frame();
	protected:
		virtual void createScene() { }
		virtual void destroyScene() { }

		virtual void setupResources();

		virtual void injectMouseMove(int _absx, int _absy, int _absz);
		virtual void injectMousePress(int _absx, int _absy, MyGUI::MouseButton _id);
		virtual void injectMouseRelease(int _absx, int _absy, MyGUI::MouseButton _id);
		virtual void injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text);
		virtual void injectKeyRelease(MyGUI::KeyCode _key);

	private:
		void createGui();
		void destroyGui();

		void windowAdjustSettings(HWND hWnd, int width, int height, bool fullScreen);
		void updateFPS();

		void resizeRender(int _width, int _height);
		bool createRender(int _width, int _height, bool _windowed);
		void drawOneFrame();
		void destroyRender();

	private:
		MyGUI::Gui* mGUI;
		MyGUI::HGEPlatform* mPlatform;
		diagnostic::StatisticInfo* mInfo;
		diagnostic::InputFocusInfo* mFocusInfo;

		HWND hWnd;
		HINSTANCE hInstance;

		bool mExit;

		std::string mRootMedia;
		std::string mResourceFileName;
		bool mIsDeviceLost;
	protected:
		HGE* hge;
	};

} // namespace base

#endif // __BASE_MANAGER_H__
