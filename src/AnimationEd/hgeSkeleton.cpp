#include "StdAfx.h"
#include "hgeSkeleton.h"

void hgeLinePoint::UpdatePosition()
{
	float l = tra ==true ? r * line->GetLength() :a;
	if(k)
	{
		x = line->GetHeadX() + l * cos(line->GetRotate());
		y = line->GetHeadY() + l * sin(line->GetRotate());
	}
	else
	{
		x = line->GetTailX() - l * cos(line->GetRotate());
		y = line->GetTailY() - l * sin(line->GetRotate());
	}
}

void hgeLinePoint::SetRelative(float _r)
{
	r = _r;
	a = line->GetLength() * r;
	tra = true;
	UpdatePosition();
	return ;
}

void hgeLinePoint::SetAbsolute(float _a)
{
	a = _a;
	if(line->GetLength() !=0)
		r = a / line->GetLength();
	else
		r = 0;
	tra = false;
	UpdatePosition();
}

void hgeLinePoint::SetBasis(bool _k)
{
	if(k != _k)
	{
		k = _k;
		r = 1 - r;
		a = line->GetLength() * r;
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
	bind.UpdatePosition();
	control.UpdatePosition();
	MoveBindBone();
	return ;
}

void hgeBone::SetRotate(float r)
{
	if(rotate != r)
	{
		rotate = r;
		if(control.GetBasis()== true)
		{
			head.x = control.GetX() - control.GetAbsolute() * cos(rotate);
			head.y = control.GetY() - control.GetAbsolute() * sin(rotate);
			tail.x = head.x + length * cos(rotate);
			tail.y = head.y + length * sin(rotate);
		}
		else
		{
			tail.x = control.GetX() + control.GetAbsolute() * cos(rotate);
			tail.y = control.GetY() + control.GetAbsolute() * sin(rotate);
			head.x = tail.x - length * cos(rotate);
			head.y = tail.y - length * sin(rotate);
		}
	}
	MoveBindBone();
	return ;
}

void hgeBone::SetPositionByJoint(hgeJoint *joint)
{
	if(!joint)return;
	rotate=joint->bindbone->rotate + joint->angle ;
	if(joint->GetBasis()== true)
	{
		head.x = joint->GetX() - joint->GetAbsolute() * cos(rotate);
		head.y = joint->GetY() - joint->GetAbsolute() * sin(rotate);
		tail.x = head.x + length * cos(rotate);
		tail.y = head.y + length * sin(rotate);
	}
	else
	{
		tail.x = joint->GetX() + joint->GetAbsolute() * cos(rotate);
		tail.y = joint->GetY() + joint->GetAbsolute() * sin(rotate);
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
		joints[i]->UpdatePosition();
		if(joints[i]->bindbone != 0 && joints[i]!=s)
		{	
			joints[i]->bindjoint->SetXY(joints[i]->GetX(),joints[i]->GetY());
			joints[i]->bindbone->SetPositionByJoint(joints[i]->bindjoint);
			//joints[i]->bindbone->SetRotate(bone->GetRotate()+joints[i]->angle);
		}
	}
}

hgeJoint* hgeBone::AddJoint()
{
	hgeJoint* nj = new hgeJoint(this);
	joints.push_back(nj);
	nj->UpdatePosition();
	return nj;
}