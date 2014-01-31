#pragma once
#include "hge.h"
#include <vector>
#include <list>
#include <cmath>

class hgePoint
{
public:
	float x,y;
	hgePoint(float _x,float _y){x = _x;y = _y;}
	hgePoint(){x = y = 0;};
	float GetDistanceToPoint(float _x,float _y){return sqrt((x-_x)*(x-_x)+(y-_y)*(y-_y));}
	float GetDistanceToPoint(hgePoint point){return GetDistanceToPoint(point.x,point.y);};
};
//�����߶Σ�ͷβ�ڵ㣬���ȣ����
class hgeLine
{
public:
	hgeLine(){head = tail = hgePoint(0,0);length = 0;}
	hgeLine(float x1,float y1,float x2,float y2){SetPosition(x1,y1,x2,y2);}
	hgeLine(hgePoint point1,hgePoint point2){SetPosition(point1,point2);}
	void SetPosition(float x1,float y1,float x2,float y2)
	{
		head.x = x1;head.y = y1;
		tail.x = x2;tail.y = y2;
		float lx = tail.x - head.x,ly = tail.y - head.y;
		length = sqrt(lx * lx + ly * ly);
		if(lx!=0)
		{
			rotate = atan(ly/lx);
			//�ڵ�һ��������
			if(lx > 0)
			{
				if(ly < 0)rotate += 2 * M_PI;
			}
			//�ڵڶ���������
			else rotate += M_PI;
		}
		else
		{
			if(ly>0)rotate = M_PI_2;
			else if(ly<0)rotate = M_PI_4 * 3;
			else rotate = 0;
		}
	}
	void SetPosition(hgePoint point1,hgePoint point2){SetPosition(point1.x,point1.y,point2.x,point2.y);};
	void SetHead(float x1,float y1){SetPosition(x1,y1,tail.x,tail.y);};
	void SetHead(hgePoint point){SetHead(point.x,point.y);};
	void SetTail(float x2,float y2){SetPosition(head.x,head.y,x2,y2);};
	void SetTail(hgePoint point){SetTail(point.x,point.y);};
	hgePoint GetHead(){return head;};
	float GetHeadX(){return head.x;};
	float GetHeadY(){return head.y;};
	hgePoint GetTail(){return tail;};
	float GetTailX(){return tail.x;};
	float GetTailY(){return tail.y;};
	float GetLength(){return length;};
	float GetRotate(){return rotate;};
	float GetDistanceFromPoint(float _x,float _y);
	float GetDistanceFromPoint(hgePoint point){return GetDistanceFromPoint(point.x,point.y);};

protected:
	hgePoint head,tail;
	float length;
	float rotate;
};

class hgeLinePoint:public hgePoint
{
public:
	float r,a;//r�����λ�ã�a�Ǿ���λ��
	bool k;//��ʾλ���Ǹ���ͷ���(true)����β���(false)����
	bool tra;//Ŀǰʹ�õ������λ��(true)���Ǿ���λ��(false)
	hgeLinePoint():hgePoint(){r = a = 0;k = tra = true;};
};
class hgeBone;
class hgeJoint:public hgeLinePoint
{
public:
	hgeJoint(hgeBone *father):hgeLinePoint(){bone = father;bindbone = 0;bindjoint = 0;};
	~hgeJoint(){};
	float GetX();
	float GetY();
	hgeBone *bone;//���������Ĺ�ͷ
	hgeBone *bindbone;//�󶨵Ĺؽ������Ĺ�ͷ
	hgeJoint *bindjoint;//�󶨵Ĺؽ�
	float rotate;//������ͷ�ļн�
};

class hgeBone:public hgeLine
{
public:
	hgeBone():hgeLine(){bx = by = 0;};
	hgeBone(float x1,float y1,float x2,float y2):hgeLine(x1,y1,x2,y2){bx = by = 0;};
	hgeBone(hgePoint point1,hgePoint point2):hgeLine(point1,point2){bx = by = 0;};
	~hgeBone(){};
	hgePoint bind;//���ڰ�ͼƬ�Ľڵ�
	float bx,by;//�󶨵�ͼƬ��ƫ����
	hgeLinePoint control;
	void SetPosition(float x,float y);
	void SetPosition(hgePoint point){SetPosition(point.x,point.y);};
	float GetX();
	float GetY();
	//���ÿ��Ƶ����λ��
	void SetControlRelative(float r);
	//���ÿ��Ƶ����λ��
	void SetControlAbsolute(float a);
	//���ÿ��Ƶ������ͷ��㻹��β���
	void SetControlBasis(bool);
	float GetControlRelative(){return control.r;}
	float GetControlAbsolute(){return control.a;}
	bool GetControlBasis(){return control.k;}
	void SetRotate(float r);
	std::vector<hgeJoint*> joints;
	//���ùؽ����λ��
	void SetJointRelative(hgeJoint *joint, float r);
	//���ùؽھ���λ��
	void SetJointAbsolute(hgeJoint *joint,float a);
	//���ùؽ������ͷ��㻹��β���
	void SetJointBasis(hgeJoint *joint,bool);
	float GetJointRelative(hgeJoint *joint){return joint->r;}
	float GetJointAbsolute(hgeJoint *joint){return joint->a;}
	bool GetJointBasis(hgeJoint *joint){return joint->k;}
	float GetJointX(hgeJoint *joint);
	float GetJointY(hgeJoint *joint);
	//ͨ���ؽ����ù�ͷλ��
	void SetPositionByJoint(hgeJoint *joint);
	bool BoneBinded(hgeBone *bone,hgeJoint* s = 0);
private:
	void MoveBindBone(hgeJoint* s=0);
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
