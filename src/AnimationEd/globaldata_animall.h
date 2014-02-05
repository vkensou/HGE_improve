#pragma once

#include <vector>
#include "hgeSkeleton.h"
#include "showpicturedata.h"

extern std::vector<hgeBone*> bones;
//当前选择的
extern hgeBone *hotbone;
extern hgeJoint *hotjoint;
//当前鼠标所在位置的
extern hgeBone *over;
extern hgeJoint *overj;

extern Show::PictureData *dat;