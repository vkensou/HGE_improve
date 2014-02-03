#pragma once

//Show库的基础类，是纯虚类，由其衍生出静态图片类（Picture），帧动画类（Animation），切片动画类（SlicedAnimation），粒子类（Particle）
#include "hge.h"

namespace Show
{
	class Base
	{
	public:
		Base(){hge=hgeCreate(HGE_VERSION);_x = _y = 0;_rot = 0;_hscale = _vscale = 1.f;_alpha = 0xff;};
		virtual ~Base(){hge->Release();};
		virtual void Render()=0;
		virtual void SetPosition(float x,float y){};
		virtual void SetRotation(float rot =0){};
		virtual void SetScale(float hscale=1.0f, float vscale=0.0f){};
		virtual void SetColor(DWORD col, int i=-1){};
		virtual void SetAlpha(BYTE col, int i=-1){};

		float GetX(){return _x;}
		float GetY(){return _y;}
		float GetRotation(){return _rot;}
		float GetHScale(){return _hscale;}
		float GetVScale(){return _vscale;}
		virtual DWORD GetColor(int i=0){return 0;}
		virtual BYTE GetAlpha(int i=0){return 0;}
	protected:
		float _x,_y;
		float _rot;
		float _hscale,_vscale;
		BYTE _alpha;

		static HGE	*hge;
	};
}