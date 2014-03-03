#include "hge.h"
#include "showpicture.h"
#include "showframe.h"
#include "showanimation.h"
#include "hgeskeleton.h"
#include "hgefont2.h"

using namespace Show;

HGE *hge=0;

HTEXTURE tex=0;
Picture *pic=0;
HTEXTURE tex2=0;
PictureData *dat2=0;
Picture *pic2=0;
HTEXTURE tex3=0;
PictureData *dat3=0;
Frame *frame=0;
Animation *anim=0;
HTEXTURE tex4=0;
PictureData *dat4=0;
hgeSkeleton *skt=0;
HTEXTURE tex5=0;
PictureData *dat5=0;
Animation *anim2=0;


hgeFont2 *fnt = 0;

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
	pic2->Render();
	frame->Render();
	anim->Update(hge->Timer_GetDelta());
	anim->Render();
	skt->Update();
	skt->Render();
	anim2->Update(hge->Timer_GetDelta());
	anim2->Render();
	fnt->Print(0,0,0,L"fps:%d",hge->Timer_GetFPS());
	hge->Gfx_EndScene();
	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Get HGE interface
	
	hge = hgeCreate(HGE_VERSION);

	// Set up log file, frame function, render function and window title
	hge->System_SetState(HGE_LOGFILE, L"hge_tut_show.log");
	EventListener listener;
	hge->System_SetState(HGE_EVENTLISTENER, &listener);
	hge->System_SetState(HGE_TITLE, L"HGEV Show库用法展示");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_HIDEMOUSE, false);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_FPS, HGEFPS_VSYNC);
	if(hge->System_Initiate())
	{
		tex = hge->Texture_Load(L"texture.jpg");
		pic = new Picture(tex,0,0,hge->Texture_GetWidth(tex),hge->Texture_GetHeight(tex),true);
		tex2 = hge->Texture_Load(L"twohead.png");
		dat2 = new PictureData(L"twohead.dat",tex2,true);
		pic2 = new Picture(dat2,0,true);
		pic2->SetPosition(200,200);

		tex3 = hge->Texture_Load(L"绫里千寻正面.png");
		dat3 = new PictureData(L"绫里千寻正面.dat",tex3);
		frame = new Frame(dat3,0);
		frame->SetScale(3.125f);
		frame->SetPosition(0,0);
		anim = new Animation(dat3,0);
		anim->SetPosition(400,300);
		anim->SetRotation(1);
		anim->SetScale(-1,1);
		anim->Play();
		
		tex4 = hge->Texture_Load(L"剪刀.png");
		skt = new hgeSkeleton();
		skt->dat->LoadData(L"剪刀.dat");
		skt->dat->SetTexture(tex4,true);
		skt->Load(L"test.skt");
		skt->Rec();
		skt->SetAnimIndex(0);
		skt->SetPosition(200,200);
		skt->SetRotate(1);
		skt->Play();
		tex5 = hge->Texture_Load(L"manstand.png");
		dat5 = new PictureData(0,tex5,true);
		float w5=hge->Texture_GetWidth(tex5,true),h5=hge->Texture_GetHeight(tex5,true);
		dat5->SetAnimation(4,100,SHOWANIM_LOOP,w5/4,h5,w5/8,h5);
		anim2 = new Animation(dat5,0,true);
		anim2->Play();
		anim2->SetPosition(400,300);
		fnt = new hgeFont2(L"宋体",12);
		hge->System_Start();
	}
	else 
		MessageBox(NULL, hge->System_GetErrorMessage(), L"Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

	//hge->Texture_Free(tex);
	delete pic;
	delete pic2;
	delete frame;
	hge->Texture_Free(tex3);
	delete dat3;
	delete anim;
	delete skt;
	delete anim2;
	delete fnt;
	hge->System_Shutdown();
	hge->Release();
	return 0;
}
