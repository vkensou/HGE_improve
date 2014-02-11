#pragma once
#include "hge.h"
#include "showbase.h"
#include <vector>
#include <list>
#include <cmath>
#include <map>

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
				if(ly < 0)rotate += M_2PI;
			}
			//�ڵڶ���������
			else rotate += M_PI;
		}
		else
		{
			if(ly>0)rotate = M_PI_2;
			else if(ly<0)rotate = M_PI_2 * 3;
			else rotate = 0;
		}
		dx = tail.x - head.x ;
		dy = tail.y - head.y;
		PositionChanged();
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
	//��ȡ��ֱƽ�����ϵ�һ��
protected:
	virtual void PositionChanged(){};
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
	void UpdatePosition(bool w= true);
	float GetX(){return x;};
	float GetY(){return y;};
	//�˺���һ�㲻����
	void SetXY(float _x,float _y){x = _x;y = _y;}

	hgeLinePoint(hgeLine *hostline){r = a = 0;k = tra = true;line = hostline;};
protected:
	float x,y;
	float r,a;//r�����λ�ã�a�Ǿ���λ��
	bool k;//��ʾλ���Ǹ���ͷ���(true)����β���(false)����
	bool tra;//Ŀǰʹ�õ������λ��(true)���Ǿ���λ��(false)
	hgeLine *line;
	virtual void PositionChanged(){};
};

class hgeBone;
class hgeJoint:public hgeLinePoint
{
public:
	hgeJoint(hgeBone *father):hgeLinePoint((hgeLine*)father){bone = father;bindbone = 0;bindjoint = 0;angle = 0;bidx = jidx = -1;};
	~hgeJoint(){ReleaseBind();};
	hgeBone *bone;//���������Ĺ�ͷ
	hgeBone *bindbone;//�󶨵Ĺؽ������Ĺ�ͷ
	hgeJoint *bindjoint;//�󶨵Ĺؽ�
	int bidx,jidx;
	float angle;//������ͷ�ļн�
	void ReleaseBind();
protected:
	void PositionChanged();
};

class hgeBindPoint:public hgeLinePoint
{
public:
	hgeBindPoint(hgeLine *hostline):hgeLinePoint(hostline){part = 0;hscale = vscale = 1.f;rotate = 0;}
	~hgeBindPoint(){delete part;}
	hgeBone *bone;//���������Ĺ�ͷ
	void SetScale(float hscale=1.0f, float vscale=0.0f);
	void SetRotation(float rot =0);
	float GetRotation(){return rotate;}
	float GetHScale(){return hscale;}
	float GetVScale(){return vscale;}
	void Update(){}
	void Render()
	{
		if(part)
		{
			part->Render();
		}
	}
	Base *part;
	void PositionChanged();
protected:
	float hscale,vscale;//����ϵ���������ھ���
	float ox,oy;//ƫ��
	float rotate;//��ת
};

class hgeBone:public hgeLine
{
public:
	hgeBone():hgeLine(),bind(this),control(this){bind.bone = this;bind.UpdatePosition();control.UpdatePosition();father = -1;ftrb = 0;};
	hgeBone(float x1,float y1,float x2,float y2):hgeLine(x1,y1,x2,y2),bind(this),control(this){bind.bone = this;bind.UpdatePosition();control.UpdatePosition();father = -1;ftrb = 0;};
	hgeBone(hgePoint point1,hgePoint point2):hgeLine(point1,point2),bind(this),control(this){bind.bone = this;bind.UpdatePosition();control.UpdatePosition();father = -1;ftrb = 0;};
	hgeBone(int id):hgeLine(),bind(this),control(this),mid(id){bind.bone = this;bind.UpdatePosition();control.UpdatePosition();father = -1;ftrb = 0;};
	~hgeBone();
	hgeBindPoint bind;//���ڰ�ͼƬ�Ľڵ�
	hgeLinePoint control;
	void SetPosition(float x,float y);
	void SetPosition(hgePoint point){SetPosition(point.x,point.y);};
	void SetLength(float l){length = l;SetPosition(control.GetX(),control.GetY());};
	void SetRotate(float r);
	float GetX(){return control.GetX();};
	float GetY(){return control.GetY();};
	hgeLinePoint& ControlPoint(){return control;}
	hgeBindPoint& BindPoint(){return bind;}
	std::vector<hgeJoint*> joints;
	hgeJoint* AddJoint();
	bool DelJoint(hgeJoint* joint);
	int GetJointIndex(hgeJoint* joint);
	void SetPositionByJoint(hgeJoint *joint);
	bool BoneBinded(hgeBone *bone,hgeJoint* s = 0);
	int GetID(){return mid.getid();}
	bool SetFather(int index,hgeBone* fabone);
	void SetFatherID(int index){father = index;}
	int GetFather(){return father;}
	hgePoint GetOtherPoint();
protected:
	void PositionChanged();
	int father;
	hgeBone* ftrb;
	bool fathered(hgeBone*);
private:
	void MoveBindBone(hgeJoint* s=0);
	class cid
	{
	public:
		cid(int id){_id = id;nid =_id+1;}
		cid():_id(nid++){};
		virtual ~cid(){};
		int getid(){return _id;}
	private:
		static int nid;//�����õ��ı��
		int _id;
	};
	cid mid;
};



//������
class hgeSkeleton
{
public:
	hgeSkeleton(void){mainbone = 0;x = y = 0;rotate = 0;ox = oy = 0;newestbi = -1;};
	virtual ~hgeSkeleton(void){};
	int AddBone();
	bool DelBone(hgeBone* bone);
	//std::map<int,hgeBone*>bones;
	std::list<hgeBone*>bones;
	hgeBone* GetBoneFromID(int id);
	bool BoneTop(hgeBone* bone);
	bool BoneUp(hgeBone* bone);
	bool BoneDown(hgeBone* bone);
	bool BoneBottom(hgeBone* bone);
	bool Save(const wchar_t* path);
	bool Load(const wchar_t* path);
	hgeBone *mainbone;//����ͷ
	//�������ĵ��λ��
	float x,y;
	float rotate;
	//����ͷ�Ŀ��Ƶ������ĵ��ƫ����
	float ox,oy;
	int newestbi;
};
