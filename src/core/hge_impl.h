/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Common core implementation header
*/


#ifndef HGE_IMPL_H
#define HGE_IMPL_H

#include "..\..\include\hge.h"
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
//#include <d3dx8.h>

#define DEMO

#define D3DFVF_HGEVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define VERTEX_BUFFER_SIZE 4000


typedef BOOL (WINAPI *GetSystemPowerStatusFunc)(LPSYSTEM_POWER_STATUS);


struct CRenderTargetList
{
	int					width;
	int					height;
	IDirect3DTexture9*	pTex;
	IDirect3DSurface9*	pDepth;
	CRenderTargetList*	next;
};

struct CTextureList
{
	HTEXTURE			tex;
	int					width;
	int					height;
	CTextureList*		next;
};

struct CResourceList
{
	wchar_t				filename[_MAX_PATH];
	char				password[64];
	CResourceList*		next;
};

struct CStreamList
{
	HSTREAM				hstream;
	void*				data;
	CStreamList*		next;
};

struct CInputEventList
{
	hgeInputEvent		event;
	CInputEventList*	next;
};


void DInit();
void DDone();
bool DFrame();


/*
** HGE Interface implementation
*/
class HGE_Impl : public HGE
{
public:
	virtual	void		CALL	Release();

	virtual bool		CALL	System_Initiate();
	virtual void		CALL	System_Shutdown();
	virtual bool		CALL	System_Start();
	virtual wchar_t*	CALL	System_GetErrorMessage();
	virtual	void		CALL	System_Log(const wchar_t *format, ...);
	virtual bool		CALL	System_Launch(const wchar_t *url);
	virtual void		CALL	System_Snapshot(const wchar_t *filename=0);


	virtual void		CALL	System_SetStateBool  (hgeBoolState   state, bool        value);
	virtual void		CALL	System_SetStateFunc  (hgeFuncState   state, hgeCallback value);
	virtual void		CALL	System_SetStateHwnd  (hgeHwndState   state, HWND        value);
	virtual void		CALL	System_SetStateInt   (hgeIntState    state, int         value);
	virtual void		CALL	System_SetStateString(hgeStringState state, const wchar_t *value);
	virtual bool		CALL	System_GetStateBool  (hgeBoolState   state);
	virtual hgeCallback	CALL	System_GetStateFunc  (hgeFuncState   state);
	virtual HWND		CALL	System_GetStateHwnd  (hgeHwndState   state);
	virtual int			CALL	System_GetStateInt   (hgeIntState    state);
	virtual const wchar_t*	CALL	System_GetStateString(hgeStringState state);


	virtual void*		CALL	Resource_Load(const wchar_t *filename, DWORD *size=0);
	virtual void		CALL	Resource_Free(void *res);
	virtual bool		CALL	Resource_AttachPack(const wchar_t *filename, const wchar_t *password=0);
	virtual void		CALL	Resource_RemovePack(const wchar_t *filename);
	virtual void		CALL	Resource_RemoveAllPacks();
	virtual wchar_t*	CALL	Resource_MakePath(const wchar_t *filename=0);
	virtual wchar_t*	CALL	Resource_EnumFiles(const wchar_t *wildcard=0);
	virtual wchar_t*	CALL	Resource_EnumFolders(const wchar_t *wildcard=0);

	virtual	void		CALL	Ini_SetInt(const wchar_t *section, const wchar_t *name, int value);
	virtual	int 		CALL	Ini_GetInt(const wchar_t *section, const wchar_t *name, int def_val);
	virtual	void		CALL	Ini_SetFloat(const wchar_t *section, const wchar_t *name, float value);
	virtual	float		CALL	Ini_GetFloat(const wchar_t *section, const wchar_t *name, float def_val);
	virtual	void		CALL	Ini_SetString(const wchar_t *section, const wchar_t *name, const wchar_t *value);
	virtual	wchar_t*	CALL	Ini_GetString(const wchar_t *section, const wchar_t *name, const wchar_t *def_val);

	virtual void		CALL	Random_Seed(int seed=0);
	virtual int			CALL	Random_Int(int min, int max);
	virtual float		CALL	Random_Float(float min, float max);

	virtual float		CALL	Random_Guss(float avrgvalue ,float standdeviation);

	virtual float		CALL	Timer_GetTime();
	virtual float		CALL	Timer_GetDelta();
	virtual int			CALL	Timer_GetFPS();

	virtual HEFFECT		CALL	Effect_Load(const wchar_t *filename, DWORD size=0);
	virtual void		CALL	Effect_Free(HEFFECT eff);
	virtual HCHANNEL	CALL 	Effect_Play(HEFFECT eff);
	virtual HCHANNEL	CALL 	Effect_PlayEx(HEFFECT eff, int volume=100, int pan=0, float pitch=1.0f, bool loop=false);

	virtual HMUSIC		CALL 	Music_Load(const wchar_t *filename, DWORD size=0);
	virtual void		CALL	Music_Free(HMUSIC mus);
	virtual HCHANNEL	CALL 	Music_Play(HMUSIC mus, bool loop, int volume = 100, int order = 0, int row = 0);
	virtual void		CALL	Music_SetAmplification(HMUSIC music, int ampl);
	virtual int			CALL	Music_GetAmplification(HMUSIC music);
	virtual int			CALL	Music_GetLength(HMUSIC music);
	virtual void		CALL	Music_SetPos(HMUSIC music, int order, int row);
	virtual bool		CALL	Music_GetPos(HMUSIC music, int *order, int *row);
	virtual void		CALL	Music_SetInstrVolume(HMUSIC music, int instr, int volume);
	virtual int			CALL	Music_GetInstrVolume(HMUSIC music, int instr);
	virtual void		CALL	Music_SetChannelVolume(HMUSIC music, int channel, int volume);
	virtual int			CALL	Music_GetChannelVolume(HMUSIC music, int channel);

	virtual HSTREAM		CALL	Stream_Load(const wchar_t *filename, DWORD size=0);
	virtual void		CALL	Stream_Free(HSTREAM stream);
	virtual HCHANNEL	CALL	Stream_Play(HSTREAM stream, bool loop, int volume = 100);

	virtual void		CALL 	Channel_SetPanning(HCHANNEL chn, int pan);
	virtual void		CALL 	Channel_SetVolume(HCHANNEL chn, int volume);
	virtual void		CALL 	Channel_SetPitch(HCHANNEL chn, float pitch);
	virtual void		CALL 	Channel_Pause(HCHANNEL chn);
	virtual void		CALL 	Channel_Resume(HCHANNEL chn);
	virtual void		CALL 	Channel_Stop(HCHANNEL chn);
	virtual void		CALL 	Channel_PauseAll();
	virtual void		CALL 	Channel_ResumeAll();
	virtual void		CALL 	Channel_StopAll();
	virtual bool		CALL	Channel_IsPlaying(HCHANNEL chn);
	virtual float		CALL	Channel_GetLength(HCHANNEL chn);
	virtual float		CALL	Channel_GetPos(HCHANNEL chn);
	virtual void		CALL	Channel_SetPos(HCHANNEL chn, float fSeconds);
	virtual void		CALL	Channel_SlideTo(HCHANNEL channel, float time, int volume, int pan = -101, float pitch = -1);
	virtual bool		CALL	Channel_IsSliding(HCHANNEL channel);

	virtual void		CALL	Input_GetMousePos(float *x, float *y);
	virtual void		CALL	Input_SetMousePos(float x, float y);
	virtual int			CALL	Input_GetMouseWheel();
	virtual bool		CALL	Input_IsMouseOver();
	virtual bool		CALL	Input_KeyDown(int key);
	virtual bool		CALL	Input_KeyUp(int key);
	virtual bool		CALL	Input_GetKeyState(int key);
	virtual wchar_t*	CALL	Input_GetKeyName(int key);
	virtual int			CALL	Input_GetKey();
	virtual int			CALL	Input_GetChar();
	virtual bool		CALL	Input_GetEvent(hgeInputEvent *event);

	//virtual int			CALL	Gfx_GetD3d9Device(){return (int)pD3DDevice;};
	virtual bool		CALL	Gfx_BeginScene(HTARGET target=0);
	virtual void		CALL	Gfx_EndScene();
	virtual void		CALL	Gfx_Clear(DWORD color);
	virtual void		CALL	Gfx_RenderLine(float x1, float y1, float x2, float y2, DWORD color=0xFFFFFFFF, float z=0.5f);
	virtual void		CALL	Gfx_RenderTriple(const hgeTriple *triple);
	virtual void		CALL	Gfx_RenderQuad(const hgeQuad *quad);
	virtual hgeVertex*	CALL	Gfx_StartBatch(int prim_type, HTEXTURE tex, int blend, int *max_prim);
	virtual void		CALL	Gfx_FinishBatch(int nprim);
	virtual void		CALL	Gfx_SetClipping(int x=0, int y=0, int w=0, int h=0);
	virtual void		CALL	Gfx_SetTransform(float x=0, float y=0, float dx=0, float dy=0, float rot=0, float hscale=0, float vscale=0); 
	virtual void		CALL	Gfx_RenderDone();

	virtual HTARGET		CALL	Target_Create(int width, int height, bool zbuffer);
	virtual void		CALL	Target_Free(HTARGET target);
	virtual HTEXTURE	CALL	Target_GetTexture(HTARGET target);

	virtual HTEXTURE	CALL	Texture_Create(int width, int height);
	virtual HTEXTURE	CALL	Texture_Load(const wchar_t *filename, DWORD size=0, bool bMipmap=false);
	virtual void		CALL	Texture_Free(HTEXTURE tex);
	virtual int			CALL	Texture_GetWidth(HTEXTURE tex, bool bOriginal=false);
	virtual int			CALL	Texture_GetHeight(HTEXTURE tex, bool bOriginal=false);
	virtual DWORD*		CALL	Texture_Lock(HTEXTURE tex, bool bReadOnly=true, int left=0, int top=0, int width=0, int height=0);
	virtual void		CALL	Texture_Unlock(HTEXTURE tex);

	virtual bool		CALL	Shader_CreatePixelShader( const wchar_t *psFileName, const char *mainFunc, const char *virsion, HPIXSHADER* pixHandle, HCONSTTABLE* tableHandle );
	virtual bool		CALL	Shader_SetPixelShader( HPIXSHADER pixHandle );
	virtual void		CALL	Shader_FreePixelShader( HPIXSHADER pixHandle );
	virtual void		CALL	Shader_FreeConstTable( HCONSTTABLE tableHandle );
	virtual void		CALL	Shader_SetParaValue( HCONSTTABLE tableHandle, const char* name, float val );
	virtual void		CALL	Shader_SetParaValue( HCONSTTABLE tableHandle, const char* name, int val );
	virtual void		CALL	Shader_SetParaValue( HCONSTTABLE tableHandle, const char* name, bool val );

	//jcweiran加入的时间模块
	virtual void		CALL	Timer_StartTick(void);
	virtual void		CALL	Timer_PauseTick(void);
	virtual void		CALL	Timer_GoonTick(void);
	virtual void		CALL	Timer_StopTick(void);
	virtual int			CALL	Timer_NowTick(void);
	virtual void		CALL	Timer_SetTick(int);




	//////// Implementation ////////

	static HGE_Impl*	_Interface_Get();
	void				_FocusChange(bool bAct);
	void				_PostError(wchar_t *error);


	HINSTANCE			hInstance;
	HWND				hwnd;

	bool				bActive;
	wchar_t				szError[256];
	wchar_t				szAppPath[_MAX_PATH];
	wchar_t				szIniString[256];


	// System States
	bool				(*procFrameFunc)();
	bool				(*procRenderFunc)();
	bool				(*procFocusLostFunc)();
	bool				(*procFocusGainFunc)();
	bool				(*procGfxRestoreFunc)();
	bool				(*procExitFunc)();
	bool				(*procResizeFunc)();
	const wchar_t*		szIcon;
	wchar_t				szWinTitle[256];
	int					nScreenWidth;
	int					nScreenHeight;
	int					nScreenBPP;
	bool				bWindowed;
	bool				bZBuffer;
	bool				bTextureFilter;
	wchar_t				szIniFile[_MAX_PATH];
	wchar_t				szLogFile[_MAX_PATH];
	bool				bUseSound;
	int					nSampleRate;
	int					nFXVolume;
	int					nMusVolume;
	int					nHGEFPS;
	bool				bHideMouse;
	bool				bDontSuspend;
	HWND				hwndParent;

	#ifdef DEMO
	bool				bDMO;
	#endif


	// Power
	int							nPowerStatus;
	HMODULE						hKrnl32;
	GetSystemPowerStatusFunc	lpfnGetSystemPowerStatus;

	void				_InitPowerStatus();
	void				_UpdatePowerStatus();
	void				_DonePowerStatus();


	// Graphics
	D3DPRESENT_PARAMETERS*  d3dpp;

	D3DPRESENT_PARAMETERS   d3dppW;
	RECT					rectW;
	LONG					styleW;

	D3DPRESENT_PARAMETERS   d3dppFS;
	RECT					rectFS;
	LONG					styleFS;

	IDirect3D9*				pD3D;
	IDirect3DDevice9*		pD3DDevice;
	IDirect3DVertexBuffer9*	pVB;
	IDirect3DIndexBuffer9*	pIB;

	IDirect3DSurface9*	pScreenSurf;
	IDirect3DSurface9*	pScreenDepth;
	CRenderTargetList*	pTargets;
	CRenderTargetList*	pCurTarget;

	D3DXMATRIX			matView;
	D3DXMATRIX			matProj;

	CTextureList*		textures;
	hgeVertex*			VertArray;

	int					nPrim;
	int					CurPrimType;
	int					CurBlendMode;
	HTEXTURE			CurTexture;



	//LPD3DXSPRITE       pSprite;

	bool				_GfxInit();
	void				_GfxDone();
	bool				_GfxRestore();
	void				_AdjustWindow();
	void				_Resize(int width, int height);
	bool				_init_lost();
	void				_render_batch(bool bEndScene=false);
	int					_format_id(D3DFORMAT fmt);
	void				_SetBlendMode(int blend);
	void				_SetProjectionMatrix(int width, int height);
	

	// Audio
	HINSTANCE			hBass;
	bool				bSilent;
	CStreamList*		streams;
	bool				_SoundInit();
	void				_SoundDone();
	void				_SetMusVolume(int vol);
	void				_SetFXVolume(int vol);


	// Input
	int					VKey;
	int					Char;
	int					Zpos;
	float				Xpos;
	float				Ypos;
	bool				bMouseOver;
	bool				bCaptured;
	char				keyz[256];
	CInputEventList*	queue;
	void				_UpdateMouse();
	void				_InputInit();
	void				_ClearQueue();
	void				_BuildEvent(int type, int key, int scan, int flags, int x, int y);


	// Resources
	wchar_t				szTmpFilename[_MAX_PATH];
	CResourceList*		res;
	HANDLE				hSearch;
	WIN32_FIND_DATA		SearchData;


	// Timer
	float				fTime;
	float				fDeltaTime;
	DWORD				nFixedDelta;
	int					nFPS;
	DWORD				t0, t0fps, dt;
	int					cfps;

	bool				shaderChanged;

	int JZTick,TempTick,NowTick1,YanChi,YanChiA;
	bool UTick,ZT;
	int ZtTime;

private:
	HGE_Impl();
};

extern HGE_Impl*		pHGE;

#endif

