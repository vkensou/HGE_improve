#pragma once

#include <vector>
#include "hgeSkeleton.h"
#include "showpicturedata.h"

extern std::vector<hgeBone*> bones;
//��ǰѡ���
extern hgeBone *hotbone;
extern hgeJoint *hotjoint;
//��ǰ�������λ�õ�
extern hgeBone *over;
extern hgeJoint *overj;

extern Show::PictureData *dat;