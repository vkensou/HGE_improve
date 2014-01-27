/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: timer
*/


#include "hge_impl.h"


float CALL HGE_Impl::Timer_GetTime()
{
	return fTime;
}

float CALL HGE_Impl::Timer_GetDelta()
{
	return fDeltaTime;
}


int CALL HGE_Impl::Timer_GetFPS()
{
	return nFPS;
}


void CALL HGE_Impl::Timer_StartTick(void)
{
	Timer_StopTick();
	JZTick = GetTickCount();
	UTick = true;
	ZT = false;
}
void CALL HGE_Impl::Timer_PauseTick(void)
{
	if((UTick == true) &&(ZT == false))
	{
		ZtTime = Timer_NowTick();
		YanChiA = GetTickCount();
		ZT = true;
	}
}
void CALL HGE_Impl::Timer_GoonTick(void)
{
	if((UTick == true) &&(ZT == true))
	{
		TempTick = GetTickCount();
		YanChi = TempTick - YanChiA + YanChi;
		ZT = false;
	}
}
void CALL HGE_Impl::Timer_StopTick(void)
{
	JZTick = TempTick = NowTick1 = YanChi = YanChiA = 0;
	UTick = false;
	ZT = true;
	ZtTime = 0;
}
int CALL HGE_Impl::Timer_NowTick(void)
{
	if(UTick == false)return 0;
	if(ZT == false)
	{
		TempTick = GetTickCount();
		NowTick1 = TempTick - JZTick - YanChi;
		return NowTick1;
	}
	else
		return ZtTime;
}
void CALL HGE_Impl::Timer_SetTick(int aa)
{
	if(UTick == false)return ;
	if(ZT == false)
	{
		TempTick = GetTickCount();
		YanChi = TempTick - JZTick - aa;
	}
	else
	{
		Timer_GoonTick() ;
		Timer_SetTick(aa) ;
		Timer_PauseTick() ;
	}
}
