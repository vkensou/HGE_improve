#pragma once

#include "Box2D.h"
#include "hge.h"
#include "hgevector.h"
#include "hgecolor.h"

class hgeBox2dDraw :
	public b2Draw
{
private:
	HGE* hge;
public:
	hgeBox2dDraw(){hge=hgeCreate(HGE_VERSION);};
	~hgeBox2dDraw(){hge->Release();};

	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	virtual void DrawTransform(const b2Transform& xf);
};
