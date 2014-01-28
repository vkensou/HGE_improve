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
	hgeBone *body;//���������Ĺ�ͷ
	hgeJoint *bind;//�󶨵Ĺؽ�
	float rotate;//������ͷ�ļн�
};

class hgeBone
{
public:
	hgeBone(){length = rotate = 0;bx = by = 0;};
	~hgeBone(){};
	float length;
	float rotate;
	hgePoint head,tail;
	hgePoint bind;//���ڰ�ͼƬ�Ľڵ�
	float bx,by;//�󶨵�ͼƬ��ƫ����
	hgePoint control;
	std::list<hgeJoint*> joints;
};

//������
class hgeSkeleton
{
public:
	hgeSkeleton(void);
	virtual ~hgeSkeleton(void);
	std::list<hgeBone*>bones;
	hgeBone *mainbone;//����ͷ
	//�������ĵ��λ��
	float x,y;
	float rotate;
	//����ͷ�Ŀ��Ƶ������ĵ��ƫ����
	float ox,oy;
};
