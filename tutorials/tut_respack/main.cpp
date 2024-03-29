#include "hge.h"
#include "showpicture.h"
#include "hgeresource.h"
#include "hgesprite.h"

using namespace Show;

HGE *hge=0;
HTEXTURE tex=0;
Picture *pic=0;
hgeResourceManager *rm=0;
hgeSprite *spr = 0;

class EventListener:public HGEEventListener
{
public:
	EventListener(){};
	virtual ~EventListener(){};
	virtual bool Frame();
	virtual bool Render();
};

bool EventListener::Frame()
{
	return false;
}

bool EventListener::Render()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);

	pic->Render();

	spr->Render(200,200);
	hge->Gfx_EndScene();
	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Get HGE interface
	
	hge = hgeCreate(HGE_VERSION);

	// Set up log file, frame function, render function and window title
	hge->System_SetState(HGE_LOGFILE, L"hge_tut_respack.log");
	EventListener listener;
	hge->System_SetState(HGE_EVENTLISTENER, &listener);
	hge->System_SetState(HGE_TITLE, L"HGEV Zip压缩包使用");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_HIDEMOUSE, false);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	if(hge->System_Initiate())
	{
		hge->Resource_AttachPack(L"1.zip");
		hge->Resource_AttachPack(L"2.zip");
		//优先读取后面添加的资源包中的资源，即1.zip和2.zip里面都有1.jpg。但2.zip是后添加的，所以优先度更高，所以读取的是2.zip里的1.jpg
		tex = hge->Texture_Load(L"1.jpg");
		pic = new Picture(tex,0,0,(float)hge->Texture_GetWidth(tex),(float)hge->Texture_GetHeight(tex));

		rm = new hgeResourceManager(L"res.txt");
		spr = rm->GetSprite(L"spr1");
		hge->System_Start();
	}
	else MessageBox(NULL, hge->System_GetErrorMessage(), L"Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

	hge->Texture_Free(tex);

	delete pic;
	rm->Purge();
	delete rm;
	hge->System_Shutdown();
	hge->Release();
	return 0;
}
