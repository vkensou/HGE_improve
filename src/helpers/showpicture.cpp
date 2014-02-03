#include "showpicture.h"

#include <math.h>

namespace Show
{
	void Picture::_init()
	{
		quad.tex = 0;
		tx = ty = width = height = 0.f;
		tex_width = tex_height = 1.f;
		_cx=_cy=0.f;
		rcos = 1.f; rsin = 0.f;
		x1o = y1o = x2o = y2o = x3o = y3o = x4o = y4o = 0.f;
		quad.v[0].z = 
			quad.v[1].z = 
			quad.v[2].z = 
			quad.v[3].z = 0.5f;

		quad.v[0].col = 
			quad.v[1].col = 
			quad.v[2].col = 
			quad.v[3].col = 0xffffffff;
		_alpha = 0xff;

		quad.blend=BLEND_DEFAULT;
	}

	Picture::Picture()
		:Base()
	{
		_init();
	}

	Picture::Picture(HTEXTURE texture, float x, float y, float w, float h)
		:Base()
	{
		_init();
		SetTexture(texture);
		SetTextureRect(x,y,w,h);
	}

	void Picture::SetTexture(HTEXTURE tex)
	{
		if(quad.tex == tex)return;
		quad.tex=tex;

		if(tex)
		{
			tex_width = (float)hge->Texture_GetWidth(tex);
			tex_height = (float)hge->Texture_GetHeight(tex);
		}
		else
		{
			tex_width = 1.0f;
			tex_height = 1.0f;
		}
	}

	void Picture::SetTextureRect(float x, float y, float w, float h)
	{
		float tx1, ty1, tx2, ty2;

		tx=x;
		ty=y;

		width=w;
		height=h;

		tx1=tx/tex_width; ty1=ty/tex_height;
		tx2=(tx+w)/tex_width; ty2=(ty+h)/tex_height;

		quad.v[0].tx=tx1; quad.v[0].ty=ty1; 
		quad.v[1].tx=tx2; quad.v[1].ty=ty1; 
		quad.v[2].tx=tx2; quad.v[2].ty=ty2; 
		quad.v[3].tx=tx1; quad.v[3].ty=ty2; 
		SetXYOffset();
	}

	void Picture::SetPosition(float x,float y)
	{
		if(_x != x)
		{
			_x = x;
			quad.v[0].x = _x + x1o;	
			quad.v[1].x = _x + x2o;	
			quad.v[2].x = _x + x3o;	
			quad.v[3].x = _x + x4o;	
		}
		if(_y != y)
		{
			_y = y;
			quad.v[0].y = _y + y1o;	
			quad.v[1].y = _y + y2o;	
			quad.v[2].y = _y + y3o;	
			quad.v[3].y = _y + y4o;	
		}
	}

	void Picture::SetCenterPoint(float x,float y)
	{
		if(_cx != x || _cy != y)
		{
			_cx = x;_cy = y;
			SetXYOffset();
		}
	}

	void Picture::SetRotation(float rot)
	{
		if(_rot!=rot)
		{
			_rot = rot;
			rcos = cos(_rot); rsin = sin(_rot);
			SetXYOffset();
		}
	}

	void Picture::SetScale(float hscale, float vscale)
	{
		if(vscale==0) vscale=hscale;
		if(_hscale != hscale || _vscale != vscale)
		{
			_hscale = hscale; _vscale = vscale;
			SetXYOffset();
		}
	}

	void Picture::SetXYOffset()
	{
		float tx1, ty1, tx2, ty2;
		tx1 = x1o = x4o = -_cx*_hscale;
		tx2 = x2o = x3o = (width-_cx)*_hscale;
		ty1 = y1o = y2o = -_cy*_vscale;
		ty2 = y3o = y4o = (height-_cy)*_vscale;
		if(_rot!=0)
		{
			x1o = tx1*rcos - ty1*rsin;
			y1o = tx1*rsin + ty1*rcos;

			x2o = tx2*rcos - ty1*rsin;
			y2o = tx2*rsin + ty1*rcos;

			x3o = tx2*rcos - ty2*rsin;
			y3o = tx2*rsin + ty2*rcos;	

			x4o = tx1*rcos - ty2*rsin;
			y4o = tx1*rsin + ty2*rcos;	
		}
		quad.v[0].x = _x + x1o;	
		quad.v[1].x = _x + x2o;	
		quad.v[2].x = _x + x3o;	
		quad.v[3].x = _x + x4o;	
		quad.v[0].y = _y + y1o;	
		quad.v[1].y = _y + y2o;	
		quad.v[2].y = _y + y3o;	
		quad.v[3].y = _y + y4o;	
	}

	void Picture::SetColor(DWORD col, int i)
	{
		if(i != -1)
			quad.v[i].col = col;
		else
			quad.v[0].col = quad.v[1].col = quad.v[2].col = quad.v[3].col = col;
	}

	void Picture::SetAlpha(BYTE alpha, int i)
	{
		_alpha = alpha;
		if(i!=-1)
			quad.v[i].col = ((_alpha & 0xff) << 24) | 0xffffff;
		else
			quad.v[0].col = 
			quad.v[1].col = 
			quad.v[2].col = 
			quad.v[3].col = ((_alpha & 0xff) << 24) | 0xffffff;
	}
}