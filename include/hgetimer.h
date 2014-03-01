#pragma once

#include "hge.h"

class hgeTimer
{
public:
	hgeTimer(void);
	~hgeTimer(void){hge->Release();}
	void Start(void);
	void Pause(void);
	void Resume(void);
	void Stop(void);
	float Now(void);
	void Set(float aa);
	void SetBaseTimer(hgeTimer* b);
	//数越大，时间流逝的越快；反之则越小。为0则时间停止，为负数时间倒流。小于等于0时未测试
	void SetSpeed(float speed);
	float GetSpeed(){return _speed;}
protected:
	static HGE	*hge;

	hgeTimer* t;//父时间类

	float lastnow,lasttick,_speed,temp;
	bool UTick,ZT;
private:
	inline float GetTempTick();
};

inline float hgeTimer::GetTempTick()
{
	if(t)
		return t->Now();
	else
		return hge->Timer_GetTime();
}