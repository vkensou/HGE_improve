#include "hge.h"
#include "showpicture.h"
#include "showslicedpicture.h"
#include "showframeanimation.h"
#include "showslicedframe.h"
#include "showslicedanimation.h"
#include "hgeskeleton.h"
using namespace Show;

HGE *hge=0;
Picture *pic=0;
SlicedPicture *spic=0;
SlicedPicture *spic2=0;
FrameAnimation *fanim=0;
SlicedFrame *sframe=0;
SlicedAnimation *sanim=0;
HTEXTURE tex = 0;
HTEXTURE tex2 = 0;
HTEXTURE tex3 = 0;
HTEXTURE tex4 = 0;
HTEXTURE tex5 = 0;
HTEXTURE tex6 = 0;
PictureData *data;
PictureData *data2;
hgeSkeleton *skt;
hgeSkeleton *skt2;
bool FrameFunc()
{
	return false;
}

bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);

	pic->Render();

	spic->Render();
	spic2->Render();

	fanim->Update(hge->Timer_GetDelta());
	fanim->Render();

	sframe->Render();

	sanim->Update(hge->Timer_GetDelta());
	sanim->Render();
	
	skt->Update();
	skt->Render();

	skt2->Update();
	skt2->Render();

	hge->Gfx_EndScene();
	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Get HGE interface
	hge = hgeCreate(HGE_VERSION);

	// Set up log file, frame function, render function and window title
	hge->System_SetState(HGE_LOGFILE, L"hge_tut_show.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, L"HGEV Show库用法展示");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_HIDEMOUSE, false);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	if(hge->System_Initiate())
	{
		tex = hge->Texture_Load(L"texture.jpg");
		pic = new Picture();
		pic->SetTexture(tex);
		pic->SetTextureRect (0,0,(float)hge->Texture_GetWidth(tex),(float)hge->Texture_GetHeight(tex));

		tex2 = hge->Texture_Load(L"twohead.png");
		data = new PictureData();
		data->LoadData(L"twohead.dat");
		data->tex = tex2;
		spic = new SlicedPicture(data);
		spic->SetSliceIndex(1);
		spic->SetPosition(200,300);

		spic2 = new SlicedPicture(data);
		spic2->SetSliceIndex(2);
		spic2->SetPosition(600,300);

		tex3 = hge->Texture_Load(L"fish.png");
		fanim = new FrameAnimation(tex3,20,20,0,0,139,91);
		fanim->SetMode(ANIM_LOOP);
		fanim->Play();

		tex4 = hge->Texture_Load(L"绫里千寻正面.png");
		data2 = new PictureData();
		data2->LoadData(L"绫里千寻正面.dat");
		data2->tex = tex4;
		sframe = new SlicedFrame(data2,2);
		sframe->SetPosition(400,0);
		sframe->SetScale(2.f,2.f);
		sframe->SetRotation(0.5);

		sanim = new SlicedAnimation(data2,1);
		sanim->SetPosition(400,0);
		sanim->SetScale(-2.f,2.f);
		sanim->SetRotation(-0.5);
		sanim->Play();

		skt = new hgeSkeleton();
		skt->Load(L"test.skt");
		skt->dat->LoadData(L"剪刀.dat");
		tex5 = hge->Texture_Load(L"剪刀.png");
		skt->dat->tex = tex5;
		skt->Rec();
		skt->SetPosition(200,300);
		skt->SetRotate(2);
		skt->SetScale(1,1);
		skt->SetAnimIndex(0);	
		skt->Play();

		skt2 = new hgeSkeleton();
		skt2->Load(L"man.skt");
		skt2->dat->LoadData(L"man.dat");
		tex6 = hge->Texture_Load(L"man.png");
		skt2->dat->tex = tex6;
		skt2->Rec();
		skt2->SetPosition(600,500);
		skt2->SetScale(0.5,0.5);
		skt2->SetAnimIndex(0);	
		skt2->Play();

		hge->System_Start();
	}
	else MessageBox(NULL, hge->System_GetErrorMessage(), L"Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

	hge->Texture_Free(tex);
	hge->Texture_Free(tex2);
	hge->Texture_Free(tex3);
	hge->Texture_Free(tex4);
	hge->Texture_Free(tex5);
	hge->Texture_Free(tex6);

	delete data;
	delete data2;
	delete pic;
	delete spic;
	delete spic2;
	delete sframe;
	delete sanim;
	delete skt;
	delete skt2;

	hge->System_Shutdown();
	hge->Release();
	return 0;
}
