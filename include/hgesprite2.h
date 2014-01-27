#pragma once

#include "hge.h"
#include "hgerect.h"

class hgeSprite2
{
public:
	hgeSprite2(HTEXTURE tex, float x, float y, float w, float h);
	hgeSprite2(const hgeSprite2 &spr);
	~hgeSprite2() { hge->Release(); }

	void Render();

	void SetRenderPosition(float,float,bool = false);
	void SetCenterPoint(float x,float y);
	void SetRotation(float rot =0);
	void SetZoom(float hscale=1.0f, float vscale=0.0f);
	void SetAlpha(unsigned char alpha);

	void SetTexture(HTEXTURE tex);
	void SetTextureRect(float x, float y, float w, float h, bool adjSize = true);
	void SetZ(float z, int i=-1);
	void SetBlendMode(int blend) { quad.blend=blend; }
	void SetFlip(bool bX, bool bY, bool bHotSpot = false);

	void GetFlip(bool *bX, bool *bY) const { *bX=bXFlip; *bY=bYFlip; }
	float GetWidth() const { return width; }
	float GetHeight() const { return height; }
	int GetBlendMode() const { return quad.blend; }
	char GetAlpha(){return m_alphaz;}
protected:
	void SetXYOffset();
	hgeSprite2();
	static HGE	*hge;

	hgeQuad		quad;
	float		tx, ty, width, height;
	float		tex_width, tex_height;
	float		rx,ry;
	float		centerX, centerY;
	float		rr, rcos, rsin, rh, rv;
	float		x1o,y1o,x2o,y2o,x3o,y3o,x4o,y4o;
	bool		bXFlip, bYFlip, bHSFlip;
	unsigned char		m_alphaz;
};