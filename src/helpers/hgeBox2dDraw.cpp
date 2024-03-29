#include "hgeBox2dDraw.h"

void hgeBox2dDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	if(!hge) return;

	for(int i=0;i<vertexCount-1;i++)
		hge->Gfx_RenderLine(tx(vertices[i].x), ty(vertices[i].y), tx(vertices[i+1].x), ty(vertices[i+1].y), ARGB(255,color.r*255,color.g*255,color.b*255));

	hge->Gfx_RenderLine(tx(vertices[vertexCount-1].x), ty(vertices[vertexCount-1].y), tx(vertices[0].x), ty(vertices[0].y), ARGB(255,color.r*255,color.g*255,color.b*255));
}

void hgeBox2dDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	if(!hge) return;

	for(int i=0;i<vertexCount-1;i++)
		hge->Gfx_RenderLine(tx(vertices[i].x), ty(vertices[i].y), tx(vertices[i+1].x), ty(vertices[i+1].y), ARGB(255,color.r*255,color.g*255,color.b*255));

	hge->Gfx_RenderLine(tx(vertices[vertexCount-1].x), ty(vertices[vertexCount-1].y), tx(vertices[0].x), ty(vertices[0].y), ARGB(255,color.r*255,color.g*255,color.b*255));
}

void hgeBox2dDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	if(!hge) return;

	float r = M_2PI/10;

	for(int i = 0;i<10;i++)
		hge->Gfx_RenderLine(tx(center.x + radius * cos(r * i)) ,ty(center.y + radius * sin(r * i)), tx(center.x + radius * cos(r * i + r)) ,ty(center.y + radius * sin(r * i + r)), ARGB(255,color.r*255,color.g*255,color.b*255));
}

void hgeBox2dDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	if(!hge) return;

	float r = M_2PI/10;

	for(int i = 0;i<10;i++)
		hge->Gfx_RenderLine(tx(center.x + radius * cos(r * i)) ,ty(center.y + radius * sin(r * i)), tx(center.x + radius * cos(r * i + r)) ,ty(center.y + radius * sin(r * i + r)), ARGB(255,color.r*255,color.g*255,color.b*255));
}

void hgeBox2dDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	if(!hge) return;

	float adjustW = hge->System_GetState(HGE_SCREENWIDTH)/2.0f;
	float adjustH = hge->System_GetState(HGE_SCREENHEIGHT)/2.0f;

	hge->Gfx_RenderLine(tx(p1.x), ty(p1.y), tx(p2.x), ty(p2.y), ARGB(255,color.r*255,color.g*255,color.b*255));
}

void hgeBox2dDraw::DrawTransform(const b2Transform& xf)
{
	//if(!hge) return;

	//float adjustW = hge->System_GetState(HGE_SCREENWIDTH)/2.0f;
	//float adjustH = hge->System_GetState(HGE_SCREENHEIGHT)/2.0f;

	//b2Vec2 p1 = xf.position, p2;
	//const float32 k_axisScale = 0.4f;

	//p2 = p1 + k_axisScale * xf.R.col1;
	//hge->Gfx_RenderLine(adjustW + p1.x, adjustH - p1.y, adjustW + p2.x, adjustH - p2.y, ARGB(255,255,0,0));

	//p2 = p1 + k_axisScale * xf.R.col2;
	//hge->Gfx_RenderLine(adjustW + p1.x, adjustH - p1.y, adjustW + p2.x, adjustH - p2.y, ARGB(255,0,255,0));

}

void hgeBox2dDraw::SetTransform(float TransX,float TransY,float HScale,float VScale)
{
	_dx = TransX;_dy = TransY;
	_hs = HScale;_vs = VScale;
}