#pragma once
#include "hge.h"
#include "showbase.h"
#include <vector>
#include <list>
#include <cmath>

using namespace Show;

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
	hgeLine(){head = tail = hgePoint(0,0);length = 0;dx = dy = 0;}
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
		dx = tail.x - head.x ;
		dy = tail.y - head.y;
		AfterSetPosition();
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
	//�Ӳ����߶ο�ʼ��ת
	float NeedRotateFrom(hgeLine *line);

protected:
	virtual void AfterSetPosition(){};
	hgePoint head,tail;
	float dx,dy;
	float length;
	float rotate;
};

class hgeLinePoint
{
public:
	void SetRelative(float r);
	void SetAbsolute(float a);
	void SetBasis(bool b);
	float GetRelative(){return r;}
	float GetAbsolute(){return a;}
	bool GetBasis(){return k;}
	void UpdatePosition();
	float GetX(){return x;};
	float GetY(){return y;};

	hgeLinePoint(hgeLine *hostline):hgePoint(){r = a = 0;k = tra = true;line = hostline;};
protected:
	float x,y;
	float r,a;//r�����λ�ã�a�Ǿ���λ��
	bool k;//��ʾλ���Ǹ���ͷ���(true)����β���(false)����
	bool tra;//Ŀǰʹ�õ������λ��(true)���Ǿ���λ��(false)
	hgeLine *line;
};

class hgeBone;
class hgeJoint:public hgeLinePoint
{
public:
	hgeJoint(hgeBone *father):hgeLinePoint((hgeLine*)father){bone = father;bindbone = 0;bindjoint = 0;angle = 0;};
	~hgeJoint(){};
	hgeBone *bone;//���������Ĺ�ͷ
	hgeBone *bindbone;//�󶨵Ĺؽ������Ĺ�ͷ
	hgeJoint *bindjoint;//�󶨵Ĺؽ�
	float angle;//������ͷ�ļн�
};

class hgeBindPoint:public hgeLinePoint
{
public:
	hgeBindPoint(hgeLine *hostline):hgeLinePoint(hostline){part = 0;}
	~hgeBindPoint(){delete part;}
	hgeBone *bone;//���������Ĺ�ͷ
	float scalex,scaley;//����ϵ���������ھ���
	float ox,oy;//ƫ��
	float rotate;//��ת
	void Update(){}
	void Render()
	{
		if(part)
		{
			part->SetPosition(GetX(),GetY());
			part->Render();
		}
	}
	Base *part;
};

class hgeBone:public hgeLine
{
public:
	hgeBone():hgeLine(){bind.bone = this;};
	hgeBone(float x1,float y1,float x2,float y2):hgeLine(x1,y1,x2,y2){bind.bone = this;};
	hgeBone(hgePoint point1,hgePoint point2):hgeLine(point1,point2){bind.bone = this;};
	~hgeBone(){};
	hgeBindPoint bind(this);//���ڰ�ͼƬ�Ľڵ�
	hgeLinePoint control(this);
	void SetPosition(float x,float y);
	void SetPosition(hgePoint point){SetPosition(point.x,point.y);};
	float GetX(){return control.GetX();};
	float GetY(){return control.GetY();};

	const hgeLinePoint& ControlPoint(){return control;}
	const hgeBindPoint& BindPoint(){return bind;}

	////���ÿ��Ƶ����λ��
	//void SetControlRelative(float r);
	////���ÿ��Ƶ����λ��
	//void SetControlAbsolute(float a);
	////���ÿ��Ƶ������ͷ��㻹��β���
	//void SetControlBasis(bool);
	//float GetControlRelative(){return control.r;}
	//float GetControlAbsolute(){return control.a;}
	//bool GetControlBasis(){return control.k;}


	void SetRotate(float r);
	std::vector<hgeJoint*> joints;

	////���ùؽ����λ��
	//void SetJointRelative(hgeJoint *joint, float r);
	////���ùؽھ���λ��
	//void SetJointAbsolute(hgeJoint *joint,float a);
	////���ùؽ������ͷ��㻹��β���
	//void SetJointBasis(hgeJoint *joint,bool);
	//float GetJointRelative(hgeJoint *joint){return joint->r;}
	//float GetJointAbsolute(hgeJoint *joint){return joint->a;}
	//bool GetJointBasis(hgeJoint *joint){return joint->k;}
	//float GetJointX(hgeLinePoint *joint);
	//float GetJointY(hgeLinePoint *joint);
	//ͨ���ؽ����ù�ͷλ��
	void SetPositionByJoint(hgeJoint *joint);
	bool BoneBinded(hgeBone *bone,hgeJoint* s = 0);

	////���ð󶨽ڵ����λ��
	//void SetBindRelative(float r);
	////���ð󶨽ڵ����λ��
	//void SetBindAbsolute(float a);
	////���ùؽ������ͷ��㻹��β���
	//void SetBindBasis(bool b);
	//float GetBindRelative(){return bind.r;}
	//float GetBindAbsolute(){return bind.a;}
	//bool GetBindBasis(){return bind.k;}
	//float GetBindX();
	//float GetBindY();
private:
	void MoveBindBone(hgeJoint* s=0);
};



//������
class hgeSkeleton
{
public:
	hgeSkeleton(void){};
	virtual ~hgeSkeleton(void){};
	std::list<hgeBone*>bones;
	hgeBone *mainbone;//����ͷ
	//�������ĵ��λ��
	float x,y;
	float rotate;
	//����ͷ�Ŀ��Ƶ������ĵ��ƫ����
	float ox,oy;
};
