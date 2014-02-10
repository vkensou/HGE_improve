#pragma once

#include "resource.h"
#include "leftview.h"
#include "leftview2.h"
#include "downview.h"
#include "rightview.h"
#include "AnimationEdView.h"
#include "globaldata_animall.h"
#include "bindshow.h"

extern CAnimationEdView *g_animview;
extern CLeftView *g_leftview;
extern CLeftView2 *g_leftview2;
extern CDownView *g_downview;
extern CRightView *g_rightview;
extern CBindShow *g_bindshow;

extern int mode;//模式，0-普通，1-关节绑定模式

void SelectBone(int index,bool s = false);

void SelectJoint(int index,bool s = false);
