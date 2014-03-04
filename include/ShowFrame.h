#pragma once

#include "showpicture.h"

namespace Show
{
	class Frame:public Picture
	{
	public:
		Frame();
		Frame(PictureData *data,int index=-1,bool autodel=false);
		virtual ~Frame(){};

		virtual void Render();
		
		virtual void SetPosition(float x,float y);
		virtual float GetX(){return _fx;}
		virtual float GetY(){return _fy;}

		void SetIndex(int index);
		int GetIndex(){return _fidx;}
	protected:
		Frame(ShowType st);
		float _fx,_fy;
		int _fidx;
	};
}