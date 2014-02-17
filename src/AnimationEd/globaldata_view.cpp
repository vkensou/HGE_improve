#include "stdafx.h"

#include "globaldata_view.h"

CAnimationEdView *g_animview = 0;
CLeftView *g_leftview = 0;
CLeftView2 *g_leftview2 = 0;
CDownView *g_downview = 0;
CRightView *g_rightview = 0;
CBindShow *g_bindshow = 0;

int mode=0;
bool editmode=true;

float ox=0.f,oy=0.f,os=1.f;

void SelectBone(int index,bool s)
{
	if(editmode)
	{
		if(mode == 0)
		{
			if(index == -1)
			{
				if(s)
					g_leftview->SetIndex(index);
				hotbone = 0;
				hotjoint = 0;
				g_leftview2->RefreshJointList();
				g_rightview->SetPropertyPage(0);
				g_rightview->RefreshProperty();
				g_bindshow->ResfreshData(index);
			}
			else
			{
				//g_leftview->RefreshBoneList();
				hotbone = nowskt->GetBoneFromID(index);
				if(0 == hotbone)return;
				if(s)
					g_leftview->SetIndex(index);
				hotjoint = 0;
				g_leftview2->RefreshJointList();
				g_rightview->SetPropertyPage(1);
				g_rightview->RefreshProperty();
				g_bindshow->ResfreshData(index);
			}
		}
	}
	else
	{
		if(index == -1)
		{
			if(s)
				g_leftview->SetIndex(index);
			hotbone = 0;
			hotjoint = 0;
			g_leftview2->RefreshJointList();
			g_rightview->SetPropertyPage(0);
			g_rightview->RefreshProperty();
		}
		else
		{
			hotbone = nowskt->GetBoneFromID(index);
			if(0 == hotbone)return;
			if(s)
				g_leftview->SetIndex(index);
			hotjoint = 0;
			g_leftview2->RefreshJointList();
			g_rightview->SetPropertyPage(1);
			g_rightview->RefreshProperty();
		}
	}
}

void SelectJoint(int index,bool s)
{
	if(mode ==0 )
	{
		if(index<0 || index>=(int)hotbone->joints.size()+4)return ;
		//g_leftview->RefreshBoneList();
		if(s)
			g_leftview2->SetIndex(index);
		hotjoint = 0;
		//头结点
		if(index ==0)
			g_rightview->SetPropertyPage(2);
		//尾结点
		else if(index ==1)
			g_rightview->SetPropertyPage(3);
		//绑定结点
		else if(index == 2)
			g_rightview->SetPropertyPage(4);
		//控制结点
		else if(index == 3)
			g_rightview->SetPropertyPage(5);
		//关节
		else 
		{
			hotjoint = hotbone->joints[index -4];
			g_rightview->SetPropertyPage(6);
		}
		g_rightview->RefreshProperty();
	}
	else if(mode ==1)
	{
		if(over!=hotbone && overj!=hotjoint)
		{
			if(!overj->bindbone && !hotbone->BoneBinded(over))
			{
				//禁止添加成闭环
				hotjoint->SetXY(overj->GetX(),overj->GetY());
				hotjoint->bindbone = over;
				hotjoint->bindjoint = overj;
				hotjoint->angle = hotbone->NeedRotateFrom((hgeLine*)over);
				overj->bindbone = hotbone;
				overj->bindjoint = hotjoint;
				overj->angle = -hotjoint->angle;
				hotbone->SetPositionByJoint(hotjoint);
			}
		}
		mode = 0;
	}
}
