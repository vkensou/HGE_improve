#include "StdAfx.h"
#include "hgeSkeleton.h"

float hgeLine::NeedRotateFrom(hgeLine *line)
{
	float jj= rotate - line->rotate;
	float x = (line->dx * dy) - (line->dy - dx);
	if(x<=0)
		jj = M_2PI - jj;
	return jj;
}

hgeSkeleton::hgeSkeleton(void)
{
}

hgeSkeleton::~hgeSkeleton(void)
{
}

void hgeBone::SetPosition(float x,float y)
{
	if(control.k== true)
	{
		head.x = x - control.a * cos(rotate);
		head.y = y - control.a * sin(rotate);
		tail.x = head.x + length * cos(rotate);
		tail.y = head.y + length * sin(rotate);
	}
	else
	{
		tail.x = x + control.a * cos(rotate);
		tail.y = y + control.a * sin(rotate);
		head.x = tail.x - length * cos(rotate);
		head.y = tail.y - length * sin(rotate);
	}
	control.x = x;
	control.y = y;
	MoveBindBone();
	return ;
}

float hgeBone::GetX()
{
	float l = control.tra ==true ? control.r * length :control.a;
	if(control.k== true)
	{
		control.x = head.x + l * cos(rotate);
	}
	else
	{
		control.x = tail.x - l * cos(rotate);
	}
	return control.x;
}

float hgeBone::GetY()
{
	float l = control.tra ==true ? control.r * length :control.a;
	if(control.k== true)
	{
		control.y = head.y + l * sin(rotate);
	}
	else
	{
		control.y = tail.y - l * sin(rotate);
	}
	return control.y;
}

void hgeBone::SetControlRelative(float r)
{
	control.r = r;
	control.a = length * control.r;
	control.tra = true;
	return ;
}

void hgeBone::SetControlAbsolute(float a)
{
	control.a = a;
	if(length !=0)
		control.r = a / length;
	else
		control.r = 0;
	control.tra = false;
}

void hgeBone::SetControlBasis(bool k)
{
	if(control.k != k)
	{
		control.k = k;
		control.r = 1 - control.r;
		control.a = length * control.r;
	}
	return ;
}

void hgeBone::SetRotate(float r)
{
	if(rotate != r)
	{
		rotate = r;
		if(control.k== true)
		{
			head.x = control.x - control.a * cos(rotate);
			head.y = control.y - control.a * sin(rotate);
			tail.x = head.x + length * cos(rotate);
			tail.y = head.y + length * sin(rotate);
		}
		else
		{
			tail.x = control.x + control.a * cos(rotate);
			tail.y = control.y + control.a * sin(rotate);
			head.x = tail.x - length * cos(rotate);
			head.y = tail.y - length * sin(rotate);
		}
	}
	MoveBindBone();
	return ;
}

void hgeBone::SetJointRelative(hgeJoint *joint,float r)
{
	joint->r = r;
	joint->a = length * joint->r;
	joint->tra = true;
	return ;
}

void hgeBone::SetJointAbsolute(hgeJoint *joint,float a)
{
	joint->a = a;
	if(length !=0)
		joint->r = a / length;
	else
		joint->r = 0;
	joint->tra = false;
}

void hgeBone::SetJointBasis(hgeJoint *joint,bool k)
{
	if(joint->k != k)
	{
		joint->k = k;
		joint->r = 1 - joint->r;
		joint->a = length * joint->r;
	}
	return ;
}

float hgeBone::GetJointX(hgeJoint *joint)
{
	float l = joint->tra ==true ? joint->r * length :joint->a;
	if(joint->k== true)
	{
		joint->x = head.x + l * cos(rotate);
	}
	else
	{
		joint->x = tail.x - l * cos(rotate);
	}
	return joint->x;
}

float hgeBone::GetJointY(hgeJoint *joint)
{
	float l = joint->tra ==true ? joint->r * length :joint->a;
	if(joint->k== true)
	{
		joint->y = head.y + l * sin(rotate);
	}
	else
	{
		joint->y = tail.y - l * sin(rotate);
	}
	return joint->y;
}

float hgeLine::GetDistanceFromPoint(float _x,float _y)
{
	float r = (tail.x - head.x) * (_x - head.x) + (tail.y - head.y) * (_y - head.y);
	r /= length * length;
	if(r<0)
		return head.GetDistanceToPoint(_x,_y);
	else if(r>1)
		return tail.GetDistanceToPoint(_x,_y);
	hgePoint d(tail.x - head.x,tail.y - head.y);
	d.x *= r;
	d.y *= r;
	d.x += head.x ;
	d.y += head.y ;
	return d.GetDistanceToPoint(_x,_y);
}

void hgeBone::SetPositionByJoint(hgeJoint *joint)
{
	if(!joint)return;
	rotate=joint->bindbone->rotate + joint->angle ;
	if(joint->k== true)
	{
		head.x = joint->x - joint->a * cos(rotate);
		head.y = joint->y - joint->a * sin(rotate);
		tail.x = head.x + length * cos(rotate);
		tail.y = head.y + length * sin(rotate);
	}
	else
	{
		tail.x = joint->x + joint->a * cos(rotate);
		tail.y = joint->y + joint->a * sin(rotate);
		head.x = tail.x - length * cos(rotate);
		head.y = tail.y - length * sin(rotate);
	}
	MoveBindBone(joint);
	return ;
}

float hgeJoint::GetX()
{
	return bone->GetJointX(this);
}
float hgeJoint::GetY()
{
	return bone->GetJointY(this);
}

bool hgeBone::BoneBinded(hgeBone *bone,hgeJoint* s)
{
	for(UINT i = 0;i<joints.size();i++)
	{
		if(joints[i]->bindbone!=0 && joints[i]!=s)
		{
			if(joints[i]->bindbone == bone)
				return true;
			else if(joints[i]->bindbone->BoneBinded(bone,joints[i]->bindjoint))
				return true;
		}
	}
	return false;
}

void hgeBone::MoveBindBone(hgeJoint* s)
{
	for(UINT i = 0; i< joints.size();i++)
	{
		if(joints[i]->bindbone != 0 && joints[i]!=s)
		{
			joints[i]->bindjoint->x = joints[i]->GetX();
			joints[i]->bindjoint->y = joints[i]->GetY();
			joints[i]->bindbone->SetPositionByJoint(joints[i]->bindjoint);
			//joints[i]->bindbone->SetRotate(bone->GetRotate()+joints[i]->angle);
		}
	}
}