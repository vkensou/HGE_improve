#pragma once

#include "showbase.h"
#include "showpicturedata.h"

namespace Show
{
	class Picture:public Base
	{
	public:
		Picture();
		Picture(HTEXTURE texture, float x, float y, float w, float h,bool autodel=false);
		Picture(PictureData *data,int index = -1, bool autodel=false);
		virtual ~Picture();

		virtual void Render(){if(quad.tex)hge->Gfx_RenderQuad(&quad);};

		virtual void SetTexture(HTEXTURE tex, bool autodel=false);
		virtual HTEXTURE GetTexture(){return quad.tex;}
		void SetTextureRect(float x, float y, float w, float h);
		void GetTextureRect(float *x, float *y, float *w, float *h){};

		virtual void SetPosition(float x,float y);
		void SetCenterPoint(float x,float y);
		virtual void SetRotation(float rot =0);
		virtual void SetScale(float hscale=1.0f, float vscale=0.0f);
		virtual void SetEx(float x,float y,float cx =0.f,float cy=0.f,float rot =0,float hscale=1.f, float vscale=0.f);

		virtual void SetColor(DWORD col, int i=-1);
		virtual DWORD GetColor(int i=0){return quad.v[i].col;};

		virtual void SetAlpha(BYTE alpha, int i=-1);
		virtual BYTE GetAlpha(int i=0){return GETA(quad.v[i].col);};
	
		virtual void SetBlendMode(int blend){quad.blend = blend;};
		virtual int GetBlendMode(){return quad.blend;};

		virtual float GetWidth(){return width;};
		virtual float GetHeight(){return height;};

		void SetPictureData(PictureData *data, bool autodel=false);
		PictureData *GetData(){return _data;}

		void SetIndex(int index);
		UINT GetIndex(){return _sidx;}

	protected:
		Picture(ShowType st);
		void _init();
		void SetXYOffset();

		hgeQuad		quad;
		float		tx, ty, width, height;//图片显示的区域
		float		tex_width, tex_height;//图片的大小
		float		_cx, _cy;//锚点
		float		rcos, rsin;//临时变量
		float		x1o,y1o,x2o,y2o,x3o,y3o,x4o,y4o;
		PictureData *_data;
		int			_sidx;
		bool		_autodel,_autodelt;
	};
}