#include "StdAfx.h"
#include "hgeSkeleton.h"

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
