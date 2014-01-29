#pragma once

#include "resource.h"
#include "leftview.h"
#include "leftview2.h"
#include "downview.h"
#include "rightview.h"
#include "AnimationEdView.h"
#include "globaldata_animall.h"

extern CAnimationEdView *g_animview;
extern CLeftView *g_leftview;
extern CLeftView2 *g_leftview2;
extern CDownView *g_downview;
extern CRightView *g_rightview;

void SelectBone(UINT index,bool s = false);