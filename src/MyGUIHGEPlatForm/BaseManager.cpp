/*
@file
@author		Albert Semenov
@date		05/2009
*/

#include "Precompiled.h"
#include "BaseManager.h"
#include <MyGUI_HGEPlatform.h>
#include "InputConverter.h"

#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
#	include <windows.h>
#	include <winuser.h>
#endif



namespace base
{
	BaseManager::BaseManager() 
		:mGUI(nullptr),
		mPlatform(nullptr),
		mInfo(nullptr),
		mFocusInfo(nullptr),
		hWnd(0),
		hge(nullptr),
		hInstance(nullptr),
		mExit(false),
		mResourceFileName("MyGUI_Core.xml"),
		mIsDeviceLost(false),
		GUIAccessInput(true)
	{
	}

	BaseManager::~BaseManager()
	{
	}

	void BaseManager::_windowResized()
	{
		RECT rect = { 0, 0, 0, 0 };
		GetClientRect(hWnd, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		resizeRender(width, height);

		if (mPlatform)
			mPlatform->getRenderManagerPtr()->setViewSize(width, height);

		//setInputViewSize(width, height);
	}

	bool BaseManager::create()
	{
		hge = hgeCreate(HGE_VERSION);
		if (!hge)
			return false;

		prepare();

		//hge->System_SetState(HGE_WINDOWED, windowed);
		//hge->System_SetState(HGE_SCREENWIDTH, width);
		//hge->System_SetState(HGE_SCREENHEIGHT, height);
		//hge->System_SetState(HGE_USESOUND, false);
		//hge->System_SetState(HGE_HIDEMOUSE, false);
		//hge->System_SetState(HGE_SHOWSPLASH, true);
		//hge->System_SetState(HGE_FPS, 100);
		//hge->System_SetState(HGE_LOGFILE, L"hge.log");
		//hge->System_SetState(HGE_FRAMEFUNC, frame);
		hge->System_SetState(HGE_EVENTLISTENER, this);

		if (!hge->System_Initiate())
			return false;

		hWnd = hge->System_GetState(HGE_HWND);

//#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
//		char buf[MAX_PATH];
//		::GetModuleFileNameA(0, (LPCH)&buf, MAX_PATH);
//		HINSTANCE instance = ::GetModuleHandleA(buf);
//		HICON hIcon = ::LoadIcon(instance, MAKEINTRESOURCE(1001));
//		if (hIcon)
//		{
//			::SendMessageA((HWND)hWnd, WM_SETICON, 1, (LPARAM)hIcon);
//			::SendMessageA((HWND)hWnd, WM_SETICON, 0, (LPARAM)hIcon);
//		}
//#endif

		//hInstance = instance;

		//windowAdjustSettings(hWnd, width, height, !windowed);

		createRender(hge->System_GetState(HGE_SCREENWIDTH), hge->System_GetState(HGE_SCREENHEIGHT), hge->System_GetState(HGE_WINDOWED));

		createGui();

		//createInput((size_t)hWnd);

		createPointerManager((size_t)hWnd);

		createScene();

		_windowResized();

		return true;
	}

	void BaseManager::run()
	{
		hge->System_Start();
	}

	void BaseManager::destroy()
	{
		destroyScene();

		destroyPointerManager();

		//destroyInput();

		destroyGui();

		destroyRender();

		if (hge)
		{
			hge->System_Shutdown();
			hge->Release();
		}
	}

	void BaseManager::setupResources()
	{
		MyGUI::xml::Document doc;

		if (!doc.open(std::string("resources.xml")))
			doc.getLastError();

		MyGUI::xml::ElementPtr root = doc.getRoot();
		if (root == nullptr || root->getName() != "Paths")
			return;

		MyGUI::xml::ElementEnumerator node = root->getElementEnumerator();
		while (node.next())
		{
			if (node->getName() == "Path")
			{
				bool root = false;
				if (node->findAttribute("root") != "")
				{
					root = MyGUI::utility::parseBool(node->findAttribute("root"));
					if (root) mRootMedia = node->getContent();
				}
				addResourceLocation(node->getContent(), false);
			}
		}

		addResourceLocation(getRootMedia() + "/Common/Base");
	}

	void BaseManager::createGui()
	{
		mPlatform = new MyGUI::HGEPlatform();
		mPlatform->initialise();

		setupResources();

		mGUI = new MyGUI::Gui();
		mGUI->initialise(mResourceFileName);

		mInfo = new diagnostic::StatisticInfo();
		mFocusInfo = new diagnostic::InputFocusInfo();
	}

	void BaseManager::destroyGui()
	{
		if (mGUI)
		{
			if (mInfo)
			{
				delete mInfo;
				mInfo = nullptr;
			}

			if (mFocusInfo)
			{
				delete mFocusInfo;
				mFocusInfo = nullptr;
			}

			mGUI->shutdown();
			delete mGUI;
			mGUI = nullptr;
		}

		if (mPlatform)
		{
			mPlatform->shutdown();
			delete mPlatform;
			mPlatform = nullptr;
		}
	}

	void BaseManager::setWindowCaption(const std::wstring& _text)
	{
		SetWindowTextW(hWnd, _text.c_str());
	}

	void BaseManager::addResourceLocation(const std::string& _name, bool _recursive)
	{
		mPlatform->getDataManagerPtr()->addResourceLocation(_name, _recursive);
	}

	void BaseManager::windowAdjustSettings(HWND hWnd, int width, int height, bool fullScreen)
	{
		HWND hwndAfter = 0;
		unsigned long style = 0;
		unsigned long style_ex = 0;

		RECT rc = { 0, 0, width, height };

		if (fullScreen)
		{
			style = WS_POPUP | WS_VISIBLE;
			style_ex = GetWindowLong(hWnd, GWL_EXSTYLE) | (WS_EX_TOPMOST);
			hwndAfter = HWND_TOPMOST;
		}
		else
		{
			style = WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME;
			style_ex = GetWindowLong(hWnd, GWL_EXSTYLE) & (~WS_EX_TOPMOST);
			hwndAfter = HWND_NOTOPMOST;
			AdjustWindowRect(&rc, style, false);
		}

		SetWindowLong(hWnd, GWL_STYLE, style);
		SetWindowLong(hWnd, GWL_EXSTYLE, style_ex);

		int desk_width  = GetSystemMetrics(SM_CXSCREEN);
		int desk_height = GetSystemMetrics(SM_CYSCREEN);

		int w = rc.right - rc.left;
		int h = rc.bottom - rc.top;
		int x = fullScreen ? 0 : (desk_width  - w) / 2;
		int y = fullScreen ? 0 : (desk_height - h) / 2;

		SetWindowPos(hWnd, hwndAfter, x, y, w, h, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	}

	bool BaseManager::GetInputEvent(hgeInputEvent* event)
	{
		bool rel=false;
		hgeInputEvent evt;
		while(true)
		{
			if(!hge->Input_GetEvent(&evt))
				return false;
			if (mGUI && GUIAccessInput)
			{
				if(evt.type <=2)
				{

				}
				switch(evt.type)
				{
				case INPUT_KEYDOWN:
					rel = MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(input::VirtualKeyToScanCode(evt.key)), evt.chr);
					break;
				case INPUT_KEYUP:
					rel = MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(input::VirtualKeyToScanCode(evt.key)));
					break;
				case INPUT_MBUTTONDOWN:
					if(HGEK_LBUTTON==evt.key)
						rel = MyGUI::InputManager::getInstance().injectMousePress(evt.x , evt.y, MyGUI::MouseButton::Left);
					else if(HGEK_RBUTTON==evt.key)
						rel = MyGUI::InputManager::getInstance().injectMousePress(evt.x , evt.y, MyGUI::MouseButton::Right);
					else if(HGEK_MBUTTON==evt.key)
						rel = MyGUI::InputManager::getInstance().injectMousePress(evt.x , evt.y, MyGUI::MouseButton::Middle);
					break;
				case INPUT_MBUTTONUP:
					if(HGEK_LBUTTON==evt.key)
						rel = MyGUI::InputManager::getInstance().injectMouseRelease(evt.x , evt.y, MyGUI::MouseButton::Left);
					else if(HGEK_RBUTTON==evt.key)
						rel = MyGUI::InputManager::getInstance().injectMouseRelease(evt.x , evt.y, MyGUI::MouseButton::Right);
					else if(HGEK_MBUTTON==evt.key)
						rel = MyGUI::InputManager::getInstance().injectMouseRelease(evt.x , evt.y, MyGUI::MouseButton::Middle);
					break;
				case INPUT_MOUSEMOVE:
					rel = MyGUI::InputManager::getInstance().injectMouseMove(evt.x , evt.y , evt.wheel );
					break;
				case INPUT_MOUSEWHEEL:
					rel = MyGUI::InputManager::getInstance().injectMouseMove(evt.x , evt.y , evt.wheel );
					break;
				}
				if(!rel)
					break;
			}
			else
				break;
		};
		if(event)
		{
			memcpy(event, &evt, sizeof(hgeInputEvent));
			return true;
		}
		return false;
	}
	//void BaseManager::injectMouseMove(int _absx, int _absy, int _absz)
	//{
	//	if (mGUI && GUIAccessInput)
	//		MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
	//}

	//void BaseManager::injectMousePress(int _absx, int _absy, MyGUI::MouseButton _id)
	//{
	//	if (mGUI && GUIAccessInput)
	//		MyGUI::InputManager::getInstance().injectMousePress(_absx, _absy, _id);
	//}

	//void BaseManager::injectMouseRelease(int _absx, int _absy, MyGUI::MouseButton _id)
	//{
	//	if (mGUI && GUIAccessInput)
	//		MyGUI::InputManager::getInstance().injectMouseRelease(_absx, _absy, _id);
	//}

	//void BaseManager::injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text)
	//{
	//	if (mGUI && GUIAccessInput)
	//		MyGUI::InputManager::getInstance().injectKeyPress(_key, _text);
	//}

	//void BaseManager::injectKeyRelease(MyGUI::KeyCode _key)
	//{
	//	if (mGUI && GUIAccessInput)
	//		MyGUI::InputManager::getInstance().injectKeyRelease(_key);
	//}

	void BaseManager::resizeRender(int _width, int _height)
	{
	}

	bool BaseManager::createRender(int _width, int _height, bool _windowed)
	{
		return true;
	}

	bool mIsDeviceLost = false;

	void BaseManager::drawOneFrame()
	{
		//hge->Gfx_BeginScene();
		//hge->Gfx_Clear(0);
		mPlatform->getRenderManagerPtr()->drawOneFrame();
		//hge->Gfx_EndScene();
	}

	void BaseManager::destroyRender()
	{
	}

	void BaseManager::quit()
	{
		mExit = true;
	}

	const std::string& BaseManager::getRootMedia()
	{
		return mRootMedia;
	}

	void BaseManager::setResourceFilename(const std::string& _flename)
	{
		mResourceFileName = _flename;
	}

	diagnostic::StatisticInfo* BaseManager::getStatisticInfo()
	{
		return mInfo;
	}

	diagnostic::InputFocusInfo* BaseManager::getFocusInput()
	{
		return mFocusInfo;
	}

} // namespace base
