#include "..\..\include\hgetimer.h"

HGE *hgeTimer::hge=0;

hgeTimer::hgeTimer(void)
{
	hge=hgeCreate(HGE_VERSION);
	t = 0;
	_speed = 1.f;
	Stop();
}

void hgeTimer::Start(void)
{
	Stop();
	lastnow = GetTempTick();
	UTick = true;
	ZT = false;
}

void hgeTimer::Pause(void)
{
	if((UTick == true) &&(ZT == false))
	{
		ZT = true;
	}
}

void hgeTimer::Resume(void)
{
	if((UTick == true) &&(ZT == true))
	{
		lastnow = GetTempTick();
		ZT = false;
	}
}

void hgeTimer::Stop(void)
{
	lastnow = lasttick = 0.f;
	UTick = false;
	ZT = true;
}
float hgeTimer::Now(void)
{
	if(UTick == false)return 0;
	if(ZT == false)
	{
		temp = GetTempTick();
		lasttick = (temp - lastnow ) * _speed + lasttick;
		lastnow = temp;
		return lasttick;
	}
	else
		return lasttick;
}

void hgeTimer::Set(float aa)
{
	if(UTick == false)return ;
	lasttick = aa;
	if(ZT == false)
		lastnow = GetTempTick();
}

void hgeTimer::SetSpeed(float speed)
{
	_speed = speed;
}

void hgeTimer::SetBaseTimer(hgeTimer* b)
{
	if(b == this || t == b)return;
	t = b;
}

