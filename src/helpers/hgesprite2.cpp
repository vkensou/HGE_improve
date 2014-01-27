#include "..\..\include\hgesprite2.h"
#include <math.h>

HGE *hgeSprite2::hge=0;

hgeSprite2::hgeSprite2(HTEXTURE texture, float texx, float texy, float w, float h)
{
	float texx1, texy1, texx2, texy2;

	hge=hgeCreate(HGE_VERSION);
	
	tx=texx; ty=texy;
	width=w; height=h;

	if(texture)
	{
		tex_width = (float)hge->Texture_GetWidth(texture);
		tex_height = (float)hge->Texture_GetHeight(texture);
	}
	else
	{
		tex_width = 1.0f;
		tex_height = 1.0f;
	}

	centerX=0;
	centerY=0;
	bXFlip=false;
	bYFlip=false;
	bHSFlip=false;
	quad.tex=texture;

	texx1=texx/tex_width;
	texy1=texy/tex_height;
	texx2=(texx+w)/tex_width;
	texy2=(texy+h)/tex_height;


	rr = 0.f;rcos = cosf(rr); rsin = sinf(rr);
	rh = 1.f;rv = 1.f;
	centerX = centerY = 0;
	SetXYOffset();

	quad.v[0].tx = texx1; quad.v[0].ty = texy1;
	quad.v[1].tx = texx2; quad.v[1].ty = texy1;
	quad.v[2].tx = texx2; quad.v[2].ty = texy2;
	quad.v[3].tx = texx1; quad.v[3].ty = texy2;

	quad.v[0].z = 
	quad.v[1].z = 
	quad.v[2].z = 
	quad.v[3].z = 0.5f;
	
	quad.v[0].col = 
	quad.v[1].col = 
	quad.v[2].col = 
	quad.v[3].col = 0xffffffff;
	m_alphaz = 0xff;

	quad.blend=BLEND_DEFAULT;
}

hgeSprite2::hgeSprite2(const hgeSprite2 &spr)
{
	memcpy(this, &spr, sizeof(hgeSprite2));
	hge=hgeCreate(HGE_VERSION);
}

void hgeSprite2::Render()
{
	if(quad.tex)
		hge->Gfx_RenderQuad(&quad);
}

void hgeSprite2::SetRenderPosition(float x,float y,bool force)
{
	if(rx != x)
	{
		rx = x;
		quad.v[0].x = rx + x1o;	
		quad.v[1].x = rx + x2o;	
		quad.v[2].x = rx + x3o;	
		quad.v[3].x = rx + x4o;	
	}
	if(ry != y)
	{
		ry = y;
		quad.v[0].y = ry + y1o;	
		quad.v[1].y = ry + y2o;	
		quad.v[2].y = ry + y3o;	
		quad.v[3].y = ry + y4o;	
	}
}

void hgeSprite2::SetCenterPoint(float x,float y)
{
	if(centerX != x || centerY != y)
	{
		centerX = x;centerY = y;
		SetXYOffset();
	}
}

void hgeSprite2::SetRotation(float rot)
{
	if(rr!=rot)
	{
		rr = rot;
		rcos = cosf(rr); rsin = sinf(rr);
		SetXYOffset();
	}
}

void hgeSprite2::SetZoom(float hscale, float vscale)
{
	if(vscale==0) vscale=hscale;
	if(rh != hscale || rv != vscale)
	{
		rh = hscale; rv = vscale;
		SetXYOffset();
	}
}

void hgeSprite2::SetXYOffset()
{
	float tx1, ty1, tx2, ty2;
	tx1 = x1o = x4o = -centerX*rh;
	tx2 = x2o = x3o = (width-centerX)*rh;
	ty1 = y1o = y2o = -centerY*rv;
	ty2 = y3o = y4o = (height-centerY)*rv;
	if(rr!=0)
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
	quad.v[0].x = rx + x1o;	
	quad.v[1].x = rx + x2o;	
	quad.v[2].x = rx + x3o;	
	quad.v[3].x = rx + x4o;	
	quad.v[0].y = ry + y1o;	
	quad.v[1].y = ry + y2o;	
	quad.v[2].y = ry + y3o;	
	quad.v[3].y = ry + y4o;	
}

void hgeSprite2::SetTexture(HTEXTURE tex)
{
	float tx1,ty1,tx2,ty2;
	float tw,th;
	if(quad.tex == tex)return;
	quad.tex=tex;

	if(tex)
	{
		tw = (float)hge->Texture_GetWidth(tex);
		th = (float)hge->Texture_GetHeight(tex);
	}
	else
	{
		tw = 1.0f;
		th = 1.0f;
	}

	if(tw!=tex_width || th!=tex_height)
	{
		tx1=quad.v[0].tx*tex_width;
		ty1=quad.v[0].ty*tex_height;
		tx2=quad.v[2].tx*tex_width;
		ty2=quad.v[2].ty*tex_height;

		tex_width=tw;
		tex_height=th;

		tx1/=tw; ty1/=th;
		tx2/=tw; ty2/=th;

		quad.v[0].tx=tx1; quad.v[0].ty=ty1; 
		quad.v[1].tx=tx2; quad.v[1].ty=ty1; 
		quad.v[2].tx=tx2; quad.v[2].ty=ty2; 
		quad.v[3].tx=tx1; quad.v[3].ty=ty2; 
	}
	SetXYOffset();
}

void hgeSprite2::SetTextureRect(float x, float y, float w, float h, bool adjSize)
{
	float tx1, ty1, tx2, ty2;
	bool bX,bY,bHS;

	tx=x;
	ty=y;
	
	if(adjSize)
	{
		width=w;
		height=h;
	}

	tx1=tx/tex_width; ty1=ty/tex_height;
	tx2=(tx+w)/tex_width; ty2=(ty+h)/tex_height;

	quad.v[0].tx=tx1; quad.v[0].ty=ty1; 
	quad.v[1].tx=tx2; quad.v[1].ty=ty1; 
	quad.v[2].tx=tx2; quad.v[2].ty=ty2; 
	quad.v[3].tx=tx1; quad.v[3].ty=ty2; 
	SetXYOffset();
	bX=bXFlip; bY=bYFlip; bHS=bHSFlip;
	bXFlip=false; bYFlip=false;
	SetFlip(bX,bY,bHS);
}

void hgeSprite2::SetZ(float z, int i)
{
	if(i != -1)
		quad.v[i].z = z;
	else
		quad.v[0].z = quad.v[1].z = quad.v[2].z = quad.v[3].z = z;
}

void hgeSprite2::SetFlip(bool bX, bool bY, bool bHotSpot)
{
	float tx, ty;

	if(bHSFlip && bXFlip) centerX = width - centerX;
	if(bHSFlip && bYFlip) centerY = height - centerY;

	bHSFlip = bHotSpot;
	
	if(bHSFlip && bXFlip) centerX = width - centerX;
	if(bHSFlip && bYFlip) centerY = height - centerY;

	if(bX != bXFlip)
	{
		tx=quad.v[0].tx; quad.v[0].tx=quad.v[1].tx; quad.v[1].tx=tx;
		ty=quad.v[0].ty; quad.v[0].ty=quad.v[1].ty; quad.v[1].ty=ty;
		tx=quad.v[3].tx; quad.v[3].tx=quad.v[2].tx; quad.v[2].tx=tx;
		ty=quad.v[3].ty; quad.v[3].ty=quad.v[2].ty; quad.v[2].ty=ty;

		bXFlip=!bXFlip;
	}

	if(bY != bYFlip)
	{
		tx=quad.v[0].tx; quad.v[0].tx=quad.v[3].tx; quad.v[3].tx=tx;
		ty=quad.v[0].ty; quad.v[0].ty=quad.v[3].ty; quad.v[3].ty=ty;
		tx=quad.v[1].tx; quad.v[1].tx=quad.v[2].tx; quad.v[2].tx=tx;
		ty=quad.v[1].ty; quad.v[1].ty=quad.v[2].ty; quad.v[2].ty=ty;

		bYFlip=!bYFlip;
	}
}

void hgeSprite2::SetAlpha(unsigned char alpha)
{
	m_alphaz = alpha;
	quad.v[0].col = 
	quad.v[1].col = 
	quad.v[2].col = 
	quad.v[3].col = ((m_alphaz & 0xff) << 24) | 0xffffff;
}
