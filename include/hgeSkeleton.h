#pragma once
#include "hge.h"
#include "showbase.h"
#include "hgetimer.h"
#include <vector>
#include <list>
#include <cmath>
#include "showpicturedata.h"
#include "showslicedpicture.h"

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
//有向线段，头尾节点，长度，倾角
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
			//在第一、四象限
			if(lx > 0)
			{
				if(ly < 0)rotate += M_2PI;
			}
			//在第二、三象限
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
	//从参数线段开始旋转
	float NeedRotateFrom(hgeLine *line);
	//获取垂直平分线上的一点
	float scale;
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
	bool GetTra(){return tra;}
	float GetRelative(){return r;}
	float GetAbsolute(){return a;}
	bool GetBasis(){return k;}
	void UpdatePosition(bool w= true);
	float GetX(){return x;};
	float GetY(){return y;};
	//此函数一般不可用
	void SetXY(float _x,float _y){x = _x;y = _y;}

	hgeLinePoint(hgeLine *hostline){r = a = 0;k = tra = true;line = hostline;};
protected:
	float x,y;
	float r,a;//r是相对位置，a是绝对位置
	bool k;//表示位置是根据头结点(true)还是尾结点(false)决定
	bool tra;//目前使用的是相对位置(true)还是绝对位置(false)
	hgeLine *line;
	virtual void PositionChanged(){};
};

class hgeBone;
class hgeJoint:public hgeLinePoint
{
public:
	hgeJoint(hgeBone *father):hgeLinePoint((hgeLine*)father){bone = father;bindbone = 0;bindjoint = 0;angle = 0;bidx = jidx = -1;};
	~hgeJoint(){ReleaseBind();};
	hgeBone *bone;//表明所属的骨头
	hgeBone *bindbone;//绑定的关节所属的骨头
	hgeJoint *bindjoint;//绑定的关节
	int bidx,jidx;
	float angle;//两个骨头的夹角
	void ReleaseBind();
protected:
	void PositionChanged();
};

class hgeBindPoint:public hgeLinePoint
{
public:
	hgeBindPoint(hgeLine *hostline):hgeLinePoint(hostline){part = 0;hscale = vscale = 1.f;rotate = 0;hscale2 = vscale2 = 1.f;}
	~hgeBindPoint(){delete part;}
	hgeBone *bone;//表明所属的骨头
	void SetScale(float hscale=1.0f, float vscale=0.0f);
	void SetRotation(float rot =0);
	float GetRotation(){return rotate;}
	float GetHScale(){return hscale;}
	float GetVScale(){return vscale;}

	void SetScale2(float hscale=1.0f, float vscale=0.0f);
	float GetHScale2(){return hscale2;}
	float GetVScale2(){return vscale2;}

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
	UINT ls;
protected:
	float hscale,vscale;//缩放系数，可用于镜像
	float ox,oy;//偏移
	float rotate;//旋转
	float hscale2,vscale2;//缩放系数，可用于镜像
};

class hgeBone:public hgeLine
{
public:
	hgeBone():hgeLine(),bind(this),control(this){bind.bone = this;bind.UpdatePosition();control.UpdatePosition();father = -1;ftrb = 0;mode = true;frameindex = -1;yrotate = 0;animindex = -1;dj = 0.f;er = 0;scale = 1;hflip = vflip = true;};
	hgeBone(float x1,float y1,float x2,float y2):hgeLine(x1,y1,x2,y2),bind(this),control(this){bind.bone = this;bind.UpdatePosition();control.UpdatePosition();father = -1;ftrb = 0;mode = true;frameindex = -1;yrotate = 0;animindex = -1;dj = 0.f;er = 0;scale = 1;hflip = vflip = true;};
	hgeBone(hgePoint point1,hgePoint point2):hgeLine(point1,point2),bind(this),control(this){bind.bone = this;bind.UpdatePosition();control.UpdatePosition();father = -1;ftrb = 0;mode = true;frameindex = -1;yrotate = 0;animindex = -1;dj = 0.f;er = 0;scale = 1;hflip = vflip = true;};
	hgeBone(int id):hgeLine(),bind(this),control(this),mid(id){bind.bone = this;bind.UpdatePosition();control.UpdatePosition();father = -1;ftrb = 0;mode = true;frameindex = -1;yrotate = 0;animindex = -1;dj = 0.f;er = 0;scale = 1;hflip = vflip = true;};
	~hgeBone();
	hgeBindPoint bind;//用于绑定图片的节点
	hgeLinePoint control;
	void SetPosition(float x,float y,int v = 0);
	void SetPosition(hgePoint point){SetPosition(point.x,point.y);};
	void SetLength(float l){length = l;SetPosition(control.GetX(),control.GetY());};
	void SetRotate(float r,int v = 0,float s = 0);
	void SetRotateE(float r);
	float GetRotateE();
	float GetX(){return control.GetX();};
	float GetY(){return control.GetY();};
	hgeLinePoint& ControlPoint(){return control;}
	hgeBindPoint& BindPoint(){return bind;}
	std::vector<hgeJoint*> joints;
	hgeJoint* AddJoint();
	bool DelJoint(hgeJoint* joint);
	int GetJointIndex(hgeJoint* joint);
	void SetPositionByJoint(hgeJoint *joint,int v = 0,float s = 0);
	bool BoneBinded(hgeBone *bone,hgeJoint* s = 0);
	int GetID(){return mid.getid();}
	bool SetFather(int index,hgeBone* fabone);
	void SetFatherID(int index){father = index;}
	int GetFather(){return father;}
	hgePoint GetOtherPoint();
	hgeBone* GetAcst();//获取祖宗
	void SetMode(bool mode);
	float yrotate;
	void AddAnim();
	void DelAnim(int index);
	void SetAnimIndex(int index);
	int GetAnimIndex(){return animindex;}
	int animindex;
	typedef std::vector<float> frames;
	std::vector<frames>anims;
	void SetFrameNum(UINT num);
	int frameindex;
	void SetFrameIndex(int index);
	int GetFrameIndex(){return frameindex;}
	void Reload();
	void Update(float p);
	//void Render();
	void SetRotateX(float rot);
	void SetScaleX(float h,float v);

protected:
	void PositionChanged(int v = 0,float s = 0);
	void PositionChanged();
	int father;
	hgeBone* ftrb;
	bool fathered(hgeBone*);
private:
	void MoveBindBone(hgeJoint* s=0,int v = 0,float x = 0);
	class cid
	{
	public:
		cid(int id){_id = id; if(_id >= nid)nid = _id+1;}
		cid():_id(nid++){};
		virtual ~cid(){};
		int getid(){return _id;}
	private:
		static int nid;//现在用到的编号
		int _id;
	};
	cid mid;
	bool mode;
	float dj;
	float er;
	bool hflip,vflip;
};



//骨骼类
class hgeSkeleton
{
public:
	hgeSkeleton(void){mainbone = 0;x = y = 0;rotate = 0;hscale = vscale = 1; ox = oy = 0;newestbi = -1;mbidx = -1;mode = true;frameindex = -1;animindex = -1;bplaying =false;dat = new PictureData();dox = doy = 0;};
	virtual ~hgeSkeleton(void);
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
	bool CheckReady();
	hgeBone *mainbone;//主骨头
	int mbidx;
	//骨骼中心点的位置
	float x,y;
	//主骨头的控制点与中心点的偏移量
	float ox,oy;
	int newestbi;
	class anim
	{
	public:
		anim(){fps = 0;}
		std::vector<std::pair<float,float>>frames;
		UINT fps;
	};
	std::vector<anim> anims;
	//UINT framesnum;
	void SetFps(UINT fps);
	UINT GetFps(){if(animindex == -1)return 0;else return anims[animindex].fps;}
	float time;
	int animindex;
	int frameindex;
	bool mode;
	void SetMode(bool mode);
	int AddAnim();
	void DelAnim(int index);
	void SetAnimIndex(int index);
	int GetAnimIndex(){return animindex;}
	void SetFrameNum(UINT num);
	UINT GetFrameNum(){if(animindex == -1)return 0;else return anims[animindex].frames.size();}
	void SetFrameIndex(int index);
	int GetFrameIndex(){return frameindex;}
	void SetPosition(float x,float y);
	void SetPosition();
	float GetX(){return x;};
	float GetY(){return y;};
	void SetOffset(float x,float y);
	float GetOX();
	float GetOY();
	void Render();
	void Play();
	void Stop();
	void Update();
	bool IsPlaying(){return bplaying;}
	PictureData *dat;
	void Rec();
	void SetRotate(float rot);
	void SetScale(float h,float v);
	float GetRotate(){return rotate;}
	float GetHScale(){return hscale;}
	float GetVScale(){return vscale;}
private:
	bool bplaying;
	hgeTimer timer;
	float dox,doy;
	float rotate;
	float hscale,vscale;
};
