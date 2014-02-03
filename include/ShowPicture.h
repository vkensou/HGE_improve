#pragma once

#include "showbase.h"

namespace Show
{
	class Picture:public Base
	{
	public:
		Picture();
		Picture(HTEXTURE texture, float x, float y, float w, float h);
		virtual ~Picture(){}

		virtual void Render(){if(quad.tex)hge->Gfx_RenderQuad(&quad);};

		void SetTexture(HTEXTURE tex);
		void SetTextureRect(float x, float y, float w, float h);
		virtual void SetPosition(float x,float y);
		virtual void SetCenterPoint(float x,float y);
		virtual void SetRotation(float rot =0);
		virtual void SetScale(float hscale=1.0f, float vscale=0.0f);
		virtual void SetColor(DWORD col, int i=-1);
		virtual void SetAlpha(BYTE alpha, int i=-1);

		virtual DWORD GetColor(int i=0){return quad.v[i].col;};
		virtual BYTE GetAlpha(int i=0){return ((quad.v[i].col & 0xff)>>24);};
	protected:
		void SetXYOffset();

		hgeQuad		quad;
		float		tx, ty, width, height;//ͼƬ��ʾ������
		float		tex_width, tex_height;//ͼƬ�Ĵ�С
		float		_cx, _cy;//ê��
		float		rcos, rsin;//��ʱ����
		float		x1o,y1o,x2o,y2o,x3o,y3o,x4o,y4o;
	private:
		void _init();
	};
}