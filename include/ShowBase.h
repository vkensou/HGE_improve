#pragma once

//Show库的基础类，是纯虚类，由其衍生出静态图片类（Picture），帧类（Frame），动画类（Animation），粒子类（Particle），骨骼类（Skeleton）
#include "hge.h"

namespace Show
{
	enum  ShowType
	{
		BASE = 0,
		PICTURE = 1,
		FRAME = 2,
		ANIMATION = 3,
		PARTICAL = 4,
		SKELETON = 5,
	};
	class Base
	{
	public:
		Base():_type(BASE){_init();}
		Base(ShowType st):_type(st){_init();}
		virtual ~Base(){hge->Release();};

		virtual void Render()=0;

		virtual void SetPosition(float x,float y){};
		virtual float GetX(){return _x;}
		virtual float GetY(){return _y;}

		virtual void SetRotation(float rot =0){};
		float GetRotation(){return _rot;}

		virtual void SetScale(float hscale=1.f, float vscale=0.f){};
		float GetHScale(){return _hscale;}
		float GetVScale(){return _vscale;}

		virtual void SetEx(float x,float y,float cx =0.f,float cy=0.f,float rot =0,float hscale=1.f, float vscale=0.f){};

		virtual void SetZ(float z, int i=-1){};
		virtual float GetZ(int i=0){return 0;}

		virtual void SetColor(DWORD col, int i=-1){};
		virtual DWORD GetColor(int i=0){return 0;}

		virtual void SetAlpha(BYTE col, int i=-1){};
		virtual BYTE GetAlpha(int i=0){return 0;}

		virtual void SetBlendMode(int blend){};
		virtual int GetBlendMode(){return 0;};

		virtual void SetTexture(HTEXTURE tex){};
		virtual HTEXTURE GetTexture(){return 0;}

		virtual float GetWidth(){return 0;};
		virtual float GetHeight(){return 0;};

		virtual void GetBoundingBox(float *x1,float *y1, float *x2,float *y2){}
		//virtual void GetCenterSpot(float *x,float *y){};		//不确定是否加入该函数
		ShowType GetType(){return _type;}

	protected:
		float _x,_y;
		float _rot;
		float _hscale,_vscale;
		const ShowType _type;
		static HGE	*hge;
	private:
		void _init(){hge=hgeCreate(HGE_VERSION);_x = _y = 0;_rot = 0;_hscale = _vscale = 1.f;}
	};
}