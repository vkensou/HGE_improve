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
	//��Խ��ʱ�����ŵ�Խ�죻��֮��ԽС��Ϊ0��ʱ��ֹͣ��Ϊ����ʱ�䵹����С�ڵ���0ʱδ����
	void SetSpeed(float speed);
	float GetSpeed(){return _speed;}
protected:
	static HGE	*hge;

	hgeTimer* t;//��ʱ����

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