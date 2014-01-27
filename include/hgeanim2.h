#pragma once

#include "hgesprite2.h"
#include "hgetimer.h"
#include <vector>

struct tagqp
{
	//��Ƭ�����ģ������λ��
	float x,y;
	//��Ƭ��ͼƬ�ϵ�λ��
	float left,top,width,height;
};

struct tagpge
{
	int index;
	//��Ƭ��ƫ��ֵ
	int x,y;
};

struct tagfm
{
	std::vector<tagpge> qps;
	float w,h;
};

struct tagfme
{
	int index;
	int time;
	//֡��ƫ��ֵ��Ŀǰ��û����
	int x ,y;
};

struct tagan
{
	std::vector<tagfme> fms;
	int mode;
	float w,h;
};

class CAnimDate
{
public:
	CAnimDate(){};
	HTEXTURE tex;
	std::vector<tagqp> qps;
	std::vector<tagfm> fms;
	std::vector<tagan> ans;
	int LoadDate(const wchar_t* file);
};


class hgeAnimation2:public hgeTimer //: public hgeSprite2
{
public:
	hgeAnimation2();
	//~hgeAnimation2() { hge->Release(); }

	void Play();
	void Stop() { bPlaying=false; }
	void Resume() { bPlaying=true; }
	void Update(float fDeltaTime);
	void Render(float,float);
	void RenderEx(float,float);//���Ҿ�����Ⱦ���д���չ
	bool IsPlaying() const { return bPlaying; }
	void SetAnimData(CAnimDate*);
	void SetAnim(int);
	void SetAnimFrame(int);
	void SetFrame(int);
	void SetZoom(float zoom){m_z = zoom;}
	float GetZoom(){return m_z;}
	unsigned int GetAnim(){return m_anim;}
	unsigned int GetFrame(){return m_frame;}
	hgeSprite2* spr;
	//void SetPosition (float a,float b){x = a;y = b;}
private:
	//static HGE	*hge;
	bool bPlaying;
	CAnimDate* m_data;
	int m_anim,m_frame,m_frame2;
	int mode;
	float fSinceLastFrame;
	float m_z;
	//float x ,y ;
};