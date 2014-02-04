#include "StdAfx.h"
#include "hgeSkeleton.h"

void hgeLinePoint::UpdatePosition()
{
	float l = tra ==true ? r * line->length :a;
	if(k)
	{
		x = line->head.x + l * cos(line->rotate);
		y = line->head.y + l * sin(line->rotate);
	}
	else
	{
		x = line->tail.x - l * cos(line->rotate);
		y = line->tail.y - l * sin(line->rotate);
	}
}

void hgeLinePoint::SetControlRelative(float _r)
{
	r = _r;
	a = line->length * r;
	tra = true;
	return ;
}

void hgeLinePoint::SetControlAbsolute(float _a)
{
	a = _a;
	if(line->length !=0)
		r = a / line->length;
	else
		r = 0;
	tra = false;
}

void hgeLinePoint::SetControlBasis(bool _k)
{
	if(k != _k)
	{
		k = _k;
		r = 1 - r;
		a = line->length * r;
	}
	return ;
}

float hgeLine::NeedRotateFrom(hgeLine *line)
{
	float jj= rotate - line->rotate;
	float x = (line->dx * dy) - (line->dy - dx);
	if(x<=0)
		jj = M_2PI - jj;
	return jj;
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

void hgeBone::SetPosition(float x,float y)
{
	if(control.GetBasis())
	{
		head.x = x - control.GetAbsolute() * cos(rotate);
		head.y = y - control.GetAbsolute() * sin(rotate);
		tail.x = head.x + length * cos(rotate);
		tail.y = head.y + length * sin(rotate);
	}
	else
	{
		tail.x = x + control.GetAbsolute() * cos(rotate);
		tail.y = y + control.GetAbsolute() * sin(rotate);
		head.x = tail.x - length * cos(rotate);
		head.y = tail.y - length * sin(rotate);
	}
	control.UpdatePosition();
	MoveBindBone();
	return ;
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

float hgeBone::GetJointX(hgeLinePoint *joint)
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

float hgeBone::GetJointY(hgeLinePoint *joint)
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

float hgeBindPoint::GetX()
{
	return bone->GetJointX(this);
}
float hgeBindPoint::GetY()
{
	return bone->GetJointY(this);
}

void hgeBone::SetBindRelative(float r)
{
	bind.r = r;
	bind.a = length * bind.r;
	bind.tra = true;
	return ;
}

void hgeBone::SetBindAbsolute(float a)
{
	bind.a = a;
	if(length !=0)
		bind.r = a / length;
	else
		bind.r = 0;
	bind.tra = false;
}

void hgeBone::SetBindBasis(bool k)
{
	if(bind.k != k)
	{
		bind.k = k;
		bind.r = 1 - bind.r;
		bind.a = length * bind.r;
	}
	return ;
}

float hgeBone::GetBindX()
{
	float l = bind.tra ==true ? bind.r * length :bind.a;
	if(bind.k== true)
	{
		bind.x = head.x + l * cos(rotate);
	}
	else
	{
		bind.x = tail.x - l * cos(rotate);
	}
	return bind.x;
}

float hgeBone::GetBindY()
{
	float l = bind.tra ==true ? bind.r * length :bind.a;
	if(bind.k== true)
	{
		bind.y = head.y + l * sin(rotate);
	}
	else
	{
		bind.y = tail.y - l * sin(rotate);
	}
	return bind.y;
}
