#include "..\..\include\hgetimer.h"

HGE *hgeTimer::hge=0;

hgeTimer::hgeTimer(void)
{
	hge=hgeCreate(HGE_VERSION);
	t = 0;
	StopTick();
}

void hgeTimer::StartTick(void)
{
	StopTick();
	if(t)
		JZTick = t->NowTick ();
	else
		JZTick = hge->Timer_GetTime();
	UTick = true;
	ZT = false;
}
void hgeTimer::PauseTick(void)
{
	if((UTick == true) &&(ZT == false))
	{
		ZtTime = NowTick();
		if(t)
			YanChiA = t->NowTick ();
		else
			YanChiA = hge->Timer_GetTime();
		//YanChiA = GetTickCount();
		ZT = true;
	}
}
void hgeTimer::GoonTick(void)
{
	if((UTick == true) &&(ZT == true))
	{
		if(t)
			TempTick = t->NowTick ();
		else
			TempTick = hge->Timer_GetTime();
		//TempTick = GetTickCount();
		YanChi = TempTick - YanChiA + YanChi;
		ZT = false;
	}
}
void hgeTimer::StopTick(void)
{
	JZTick = TempTick = NowTick1 = YanChi = YanChiA = 0;
	UTick = false;
	ZT = true;
	ZtTime = 0;
}
float hgeTimer::NowTick(void)
{
	if(UTick == false)return 0;
	if(ZT == false)
	{
		if(t)
			TempTick = t->NowTick ();
		else
			TempTick = hge->Timer_GetTime();
		//TempTick = GetTickCount();
		NowTick1 = TempTick - JZTick - YanChi;
		return NowTick1;
	}
	else
		return ZtTime;
}
void hgeTimer::SetTick(int aa)
{
	if(UTick == false)return ;
	if(ZT == false)
	{
		if(t)
			TempTick = t->NowTick ();
		else
			TempTick = hge->Timer_GetTime();
		//TempTick = GetTickCount();
		YanChi = TempTick - JZTick - aa;
	}
	else
	{
		GoonTick() ;
		SetTick(aa) ;
		PauseTick() ;
	}
}

void hgeTimer::SetBaseTimer(hgeTimer* b)
{
	t = b;
}

void hgeTimer::Resume(void)
{
	if((UTick == true) &&(ZT == true))
	{
		if(t)
			TempTick = t->NowTick ();
		else
			TempTick = hge->Timer_GetTime();
		//TempTick = GetTickCount();
		YanChi = TempTick - YanChiA + YanChi;
		ZT = false;
	}
}