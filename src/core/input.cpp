/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: input
*/


#include "hge_impl.h"


wchar_t *KeyNames[] =
{
 L"?",
 L"Left Mouse Button", L"Right Mouse Button", L"?", L"Middle Mouse Button",
 L"?", L"?", L"?", L"Backspace", L"Tab", L"?", L"?", L"?", L"Enter", L"?", L"?",
 L"Shift", L"Ctrl", L"Alt", L"Pause", L"Caps Lock", L"?", L"?", L"?", L"?", L"?", L"?",
 L"Escape", L"?", L"?", L"?", L"?",
 L"Space", L"Page Up", L"Page Down", L"End", L"Home",
 L"Left Arrow", L"Up Arrow", L"Right Arrow", L"Down Arrow",
 L"?", L"?", L"?", L"?", L"Insert", L"Delete", L"?",
 L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9",
 L"?", L"?", L"?", L"?", L"?", L"?", L"?",
 L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M",
 L"N", L"O", L"P", L"Q", L"R", L"S", L"T", L"U", L"V", L"W", L"X", L"Y", L"Z",
 L"Left Win", L"Right Win", L"Application", L"?", L"?",
 L"NumPad 0", L"NumPad 1", L"NumPad 2", L"NumPad 3", L"NumPad 4",
 L"NumPad 5", L"NumPad 6", L"NumPad 7", L"NumPad 8", L"NumPad 9",
 L"Multiply", L"Add", L"?", L"Subtract", L"Decimal", L"Divide",
 L"F1", L"F2", L"F3", L"F4", L"F5", L"F6", L"F7", L"F8", L"F9", L"F10", L"F11", L"F12",
 L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?",
 L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?",
 L"Num Lock", L"Scroll Lock",
 L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?",
 L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?",
 L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?",
 L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?",
 L"Semicolon", L"Equals", L"Comma", L"Minus", L"Period", L"Slash", L"Grave",
 L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?",
 L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?",
 L"?", L"?", L"?", L"?", L"?", L"?",
 L"Left bracket", L"Backslash", L"Right bracket", L"Apostrophe",
 L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?",
 L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?",
 L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?", L"?",
 L"?", L"?", L"?"
};


bool CALL HGE_Impl::Input_GetEvent(hgeInputEvent *event)
{
	CInputEventList *eptr;

	if(queue)
	{
		eptr=queue;
		memcpy(event, &eptr->event, sizeof(hgeInputEvent));
		queue=eptr->next;
		delete eptr;
		return true;
	}
	
	return false;
}

void CALL HGE_Impl::Input_GetMousePos(float *x, float *y)
{
	*x=Xpos; *y=Ypos;
}


void CALL HGE_Impl::Input_SetMousePos(float x, float y)
{
	POINT pt;
	pt.x=(long)x; pt.y=(long)y;
	ClientToScreen(hwnd, &pt);
	SetCursorPos(pt.x,pt.y);
}

int CALL HGE_Impl::Input_GetMouseWheel()
{
	return Zpos;
}

bool CALL HGE_Impl::Input_IsMouseOver()
{
	return bMouseOver;
}

bool CALL HGE_Impl::Input_GetKeyState(int key)
{
	return ((GetKeyState(key) & 0x8000) != 0);
}

bool CALL HGE_Impl::Input_KeyDown(int key)
{
	return (keyz[key] & 1) != 0;
}

bool CALL HGE_Impl::Input_KeyUp(int key)
{
	return (keyz[key] & 2) != 0;
}

wchar_t* CALL HGE_Impl::Input_GetKeyName(int key)
{
	return KeyNames[key];
}

int CALL HGE_Impl::Input_GetKey()
{
	return VKey;
}

int CALL HGE_Impl::Input_GetChar()
{
	return Char;
}


//////// Implementation ////////


void HGE_Impl::_InputInit()
{
	POINT	pt;
	GetCursorPos(&pt);
	ScreenToClient(hwnd, &pt);
	Xpos = (float)pt.x;
	Ypos = (float)pt.y;

	memset(&keyz, 0, sizeof(keyz));
}

void HGE_Impl::_UpdateMouse()
{
	POINT	pt;
	RECT	rc;

	GetCursorPos(&pt);
	GetClientRect(hwnd, &rc);
	MapWindowPoints(hwnd, NULL, (LPPOINT)&rc, 2);

	if(bCaptured || (PtInRect(&rc, pt) && WindowFromPoint(pt)==hwnd))
		bMouseOver=true;
	else
		bMouseOver=false;
}

void HGE_Impl::_BuildEvent(int type, int key, int scan, int flags, int x, int y)
{
	CInputEventList *last, *eptr=new CInputEventList;
	unsigned char kbstate[256];
	POINT pt;

	eptr->event.type=type;
	eptr->event.chr=0;
	pt.x=x; pt.y=y;

	GetKeyboardState(kbstate);
	if(type==INPUT_KEYDOWN)
	{
		if((flags & HGEINP_REPEAT) == 0) keyz[key] |= 1;
		ToAscii(key, scan, kbstate, (unsigned short *)&eptr->event.chr, 0);
	}
	if(type==INPUT_KEYUP)
	{
		keyz[key] |= 2;
		ToAscii(key, scan, kbstate, (unsigned short *)&eptr->event.chr, 0);
	}
	if(type==INPUT_MOUSEWHEEL)
	{
		eptr->event.key=0; eptr->event.wheel=key;
		ScreenToClient(hwnd,&pt);
	}
	else { eptr->event.key=key; eptr->event.wheel=0; }

	if(type==INPUT_MBUTTONDOWN)
	{
		keyz[key] |= 1;
		SetCapture(hwnd);
		bCaptured=true;
	}
	if(type==INPUT_MBUTTONUP)
	{
		keyz[key] |= 2;
		ReleaseCapture();
		Input_SetMousePos(Xpos, Ypos);
		pt.x=(int)Xpos; pt.y=(int)Ypos;
		bCaptured=false;
	}
	
	if(kbstate[VK_SHIFT] & 0x80) flags|=HGEINP_SHIFT;
	if(kbstate[VK_CONTROL] & 0x80) flags|=HGEINP_CTRL;
	if(kbstate[VK_MENU] & 0x80) flags|=HGEINP_ALT;
	if(kbstate[VK_CAPITAL] & 0x1) flags|=HGEINP_CAPSLOCK;
	if(kbstate[VK_SCROLL] & 0x1) flags|=HGEINP_SCROLLLOCK;
	if(kbstate[VK_NUMLOCK] & 0x1) flags|=HGEINP_NUMLOCK;
	eptr->event.flags=flags;

	if(pt.x==-1) { eptr->event.x=Xpos;eptr->event.y=Ypos; }
	else
	{
		if(pt.x<0) pt.x=0;
		if(pt.y<0) pt.y=0;
		if(pt.x>=nScreenWidth) pt.x=nScreenWidth-1;
		if(pt.y>=nScreenHeight) pt.y=nScreenHeight-1;

		eptr->event.x=(float)pt.x;
		eptr->event.y=(float)pt.y;
	}

	eptr->next=0; 

	if(!queue) queue=eptr;
	else
	{
		last=queue;
		while(last->next) last=last->next;
		last->next=eptr;
	}

	if(eptr->event.type==INPUT_KEYDOWN || eptr->event.type==INPUT_MBUTTONDOWN)
	{
		VKey=eptr->event.key;Char=eptr->event.chr;
	}
	else if(eptr->event.type==INPUT_MOUSEMOVE)
	{
		Xpos=eptr->event.x;Ypos=eptr->event.y;
	}
	else if(eptr->event.type==INPUT_MOUSEWHEEL)
	{
		Zpos+=eptr->event.wheel;
	}
}

void HGE_Impl::_ClearQueue()
{
	CInputEventList *nexteptr, *eptr=queue;

	memset(&keyz, 0, sizeof(keyz));
	
	while(eptr)
	{
		nexteptr=eptr->next;
		delete eptr;
		eptr=nexteptr;
	}

	queue=0; VKey=0; Char=0; Zpos=0;
}
