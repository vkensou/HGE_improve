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
	g_leftview2->RefreshJointList();
	g_rightview->RefreshProperty();
}