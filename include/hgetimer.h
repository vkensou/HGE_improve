#pragma once

#include "hge.h"

class hgeTimer
{
public:
	hgeTimer(void);
	~hgeTimer(void){hge->Release();}
	void StartTick(void);
	void PauseTick(void);
	void GoonTick(void);
	void Resume(void);
	void StopTick(void);
	int NowTick(void);
	void SetTick(int aa);
	void SetBaseTimer(hgeTimer* b);
protected:
	static HGE	*hge;

	hgeTimer* t;
	int JZTick,TempTick,NowTick1,YanChi,YanChiA;
	bool UTick,ZT;
	int ZtTime;

};