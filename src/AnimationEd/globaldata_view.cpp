#include "stdafx.h"

#include "globaldata_view.h"

CAnimationEdView *g_animview = 0;
CLeftView *g_leftview = 0;
CLeftView2 *g_leftview2 = 0;
CDownView *g_downview = 0;
CRightView *g_rightview = 0;

void SelectBone(UINT index,bool s)
{
	if(index<0 || index>=bones.size())return ;
	//g_leftview->RefreshBoneList();
	if(s)
		g_leftview->SetIndex(index);
	hotbone = bones[index];
	hotjoint = 0;
	g_leftview2->RefreshJointList();
	g_rightview->SetPropertyPage(1);
	g_rightview->RefreshProperty();
}

void SelectJoint(UINT index,bool s)
{
	if(index<0 || index>=hotbone->joints.size()+4)return ;
	//g_leftview->RefreshBoneList();
	if(s)
		g_leftview2->SetIndex(index);
	hotjoint = 0;
	//ͷ���
	if(index ==0)
		g_rightview->SetPropertyPage(2);
	//β���
	else if(index ==1)
		g_rightview->SetPropertyPage(3);
	//�󶨽��
	else if(index == 2)
		g_rightview->SetPropertyPage(4);
	//���ƽ��
	else if(index == 3)
		g_rightview->SetPropertyPage(5);
	//�ؽ�
	else 
	{
		hotjoint = hotbone->joints[index -4];
		g_rightview->SetPropertyPage(6);
	}
	g_rightview->RefreshProperty();
}