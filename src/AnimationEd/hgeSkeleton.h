#pragma once
#include <vector>
#include <list>

class hgeBone;
class hgePoint
{
public:
	float x,y;
	hgePoint(float _x,float _y){x = _x;y = _y;}
	hgePoint(){x = y = 0;};
};

class hgeLinePoint:public hgePoint
{
public:
	float o;
	hgeLinePoint(float _x,float _y,float _o):hgePoint(_x,_y){o = _o;};
	hgeLinePoint(float _o):hgePoint(){o = _o;};
	hgeLinePoint():hgePoint(){o = 0;};
};

class hgeJoint:public hgeLinePoint
{
public:
	hgeJoint():hgeLinePoint(){};
	~hgeJoint(){};
	hgeBone *body;//表明所属的骨头
	hgeJoint *bind;//绑定的关节
	float rotate;//两个骨头的夹角
};

class hgeBone
{
public:
	hgeBone(){length = rotate = 0;bx = by = 0;};
	~hgeBone(){};
	float length;
	float rotate;
	hgePoint head,tail;
	hgePoint bind;//用于绑定图片的节点
	float bx,by;//绑定的图片的偏移量
	hgePoint control;
	std::list<hgeJoint*> joints;
};

//骨骼类
class hgeSkeleton
{
public:
	hgeSkeleton(void);
	virtual ~hgeSkeleton(void);
	std::list<hgeBone*>bones;
	hgeBone *mainbone;//主骨头
	//骨骼中心点的位置
	float x,y;
	float rotate;
	//主骨头的控制点与中心点的偏移量
	float ox,oy;
};
