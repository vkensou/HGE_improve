#pragma once

//Show��Ļ����࣬�Ǵ����࣬������������̬ͼƬ�ࣨPicture����֡�����ࣨAnimation������Ƭ�����ࣨSlicedAnimation���������ࣨParticle��
#include "hge.h"

namespace Show
{
	enum  ShowType
	{
		BASE = 0,
		PICTURE = 1,
		SLICEDPICTURE = 2,
		SLICEDFRAME = 3,
		//ǰ��ļ������Ǿ�̬�ģ�����ҪUpdate
		FRAMEANIMATION = 4,
		SLICEDANIMATION = 5,
	};
	class Base
	{
	public:
		Base(){hge=hgeCreate(HGE_VERSION);_x = _y = 0;_rot = 0;_hscale = _vscale = 1.f;_alpha = 0xff;_type = BASE;};
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
		ShowType GetType(){return _type;}
	protected:
		float _x,_y;
		float _rot;
		float _hscale,_vscale;
		BYTE _alpha;
		ShowType _type;
		static HGE	*hge;
	};
}