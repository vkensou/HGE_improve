#include "StdAfx.h"
#include "hgeSkeleton.h"

int hgeBone::cid::nid = 0;

void hgeLinePoint::UpdatePosition(bool w)
{
	if(true == tra)a = r * line->GetLength();
	if(k)
	{
		x = line->GetHeadX() + a * cos(line->GetRotate());
		y = line->GetHeadY() + a * sin(line->GetRotate());
	}
	else
	{
		x = line->GetTailX() - a * cos(line->GetRotate());
		y = line->GetTailY() - a * sin(line->GetRotate());
	}
	if(w)
		PositionChanged();
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

void hgeBindPoint::PositionChanged()
{
	if(part)
	{
		part->SetPosition(GetX(),GetY());
		part->SetRotation(rotate+line->GetRotate());
	}
}

void hgeBindPoint::SetScale(float _h, float _v)
{
	hscale = _h;vscale = _v;
	if(part)
		part->SetScale(hscale,vscale);
}

void hgeBindPoint::SetRotation(float rot)
{
	rotate = rot;
	if(part)
		part->SetRotation(line->GetRotate()+rotate);
}

void hgeJoint::PositionChanged()
{
	if(bindbone)
	{
		bindjoint->SetXY(x,y);
		bindbone->SetPositionByJoint(bindjoint);
	}
}

void hgeJoint::ReleaseBind()
{
	if(bindbone)
	{
		bindjoint->bindbone = 0;
		bindjoint->bindjoint = 0;
		bindjoint->angle = 0;
		bindbone = 0;
		bindjoint = 0;
		angle = 0;
	}
}

float hgeLine::NeedRotateFrom(hgeLine *line)
{
	//float jj= abs(rotate - line->rotate);
	//float x = (line->dx * dy) - (line->dy - dx);
	//if(x<=0)
	//	jj = M_2PI - jj;
	//while(jj<0)jj+=M_2PI;
	//while(jj>M_2PI)jj-=M_2PI;
	//return jj;
	float jj = rotate - line->rotate;
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


hgeBone::~hgeBone()
{
	std::vector<hgeJoint*>::iterator itor;
	for(itor = joints.begin();itor != joints.end();itor++)
	{
		delete *itor;
	}
	joints.clear();
}

void hgeBone::SetPosition(float x,float y,int v)
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
	PositionChanged(v);
	return ;
}

void hgeBone::SetRotate(float r,int v,float s)
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
	PositionChanged(v,s);
	return ;
}

void hgeBone::SetRotateE(float r)
{
	if(animindex >-1 && frameindex >-1)
	{
		anims[animindex].at(frameindex) = r;
		SetRotate(r,2);
	}
}

float hgeBone::GetRotateE()
{
	if(animindex >-1 && frameindex >-1)
	{
		return anims[animindex].at(frameindex);
	}
	return 0;
}

void hgeBone::SetPositionByJoint(hgeJoint *joint,int v,float s)
{
	if(!joint)return;

	if(v == 0)
		rotate=joint->bindbone->rotate + joint->angle ;
	else if(v==1)
	{
		if(mode || animindex == -1 || frameindex == -1)
			rotate = yrotate;
		else
			rotate = anims[animindex].at(frameindex);
	}
	else if(v==2)
	{
		rotate=joint->bindbone->rotate + joint->angle ;
		if(!mode && animindex != -1 && frameindex != -1)
			anims[animindex].at(frameindex) = rotate;
	}
	else if(v==3)
	{
		rotate = anims[animindex].at(frameindex) + s * dj;
	}
	while(rotate>M_2PI)rotate-=M_2PI;
	while(rotate<0)rotate+=M_2PI;

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
	bind.UpdatePosition();
	control.UpdatePosition();
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

void hgeBone::MoveBindBone(hgeJoint* s,int v,float x)
{
	for(UINT i = 0; i< joints.size();i++)
	{
		joints[i]->UpdatePosition(false);
		if(joints[i]->bindbone != 0 && joints[i]!=s)
		{
			if(joints[i]->bindbone == ftrb)
			{
				joints[i]->angle = NeedRotateFrom(joints[i]->bindbone);
				joints[i]->bindjoint->angle = -joints[i]->angle;
			}
			else
			{	
				joints[i]->bindjoint->SetXY(joints[i]->GetX(),joints[i]->GetY());
				joints[i]->bindbone->SetPositionByJoint(joints[i]->bindjoint,v,x);
				joints[i]->angle = NeedRotateFrom(joints[i]->bindbone);
				joints[i]->bindjoint->angle = -joints[i]->angle;
				//joints[i]->bindbone->SetRotate(bone->GetRotate()+joints[i]->angle);
			}
		}
	}
}

void hgeBone::PositionChanged()
{
	bind.UpdatePosition();
	control.UpdatePosition();
	if(mode || animindex == -1 || frameindex == -1)
	{
		yrotate = rotate;
	}
	else
	{
		anims[animindex].at(frameindex) = rotate;
	}
	std::vector<hgeJoint*>::iterator itor;
	for(itor = joints.begin();itor != joints.end();itor++)
	{
		(*itor)->UpdatePosition(false);
	}
	MoveBindBone(0,false);
};


void hgeBone::PositionChanged(int v,float s)
{
	bind.UpdatePosition();
	control.UpdatePosition();
	if(mode || animindex == -1 || frameindex == -1)
	{
		yrotate = rotate;
	}
	else
	{
		//anims[animindex].at(frameindex) = rotate;
	}
	std::vector<hgeJoint*>::iterator itor;
	for(itor = joints.begin();itor != joints.end();itor++)
	{
		(*itor)->UpdatePosition(false);
	}
	MoveBindBone(0,v,s);
};

hgePoint hgeBone::GetOtherPoint()
{
	float tt = rotate + M_PI_2;
	hgePoint other;
	other.x = control.GetX() + 8.f * cos(tt);
	other.y = control.GetY() + 8.f * sin(tt);
	return other;
}

hgeJoint* hgeBone::AddJoint()
{
	hgeJoint* nj = new hgeJoint(this);
	joints.push_back(nj);
	nj->UpdatePosition();
	return nj;
}

bool hgeBone::DelJoint(hgeJoint* joint)
{
	if(!joint)return false;
	std::vector<hgeJoint*>::iterator itor;
	for(itor = joints.begin();itor != joints.end();itor++)
	{
		if(*itor == joint)
		{
			joints.erase(itor);
			//joint->ReleaseBind();
			delete joint;
			return true;
		}
	}
	return false;
}

bool hgeBone::fathered(hgeBone* w)
{
	//没有爹
	if(!ftrb)
		return false;
	//爹正好是
	else if(ftrb == w)
		return true;
	//祖宗里有
	else if(ftrb->fathered(w))
		return true;
	else
		return false;
}

hgeBone* hgeBone::GetAcst()
{
	if(ftrb)
	{
		hgeBone* ls;
		ls = ftrb->GetAcst();
		if(ls)
			return ls;
		else
			return ftrb;
	}
	else
	{
		return 0;
	}
}

bool hgeBone::SetFather(int index,hgeBone* fabone)
{
	if(index == -1 || fabone == this)
	{
		father = -1;
		fabone = 0;
		return false;
	}
	if(!fabone->fathered(this))
	{
		father = index;
		ftrb = fabone;
		return true;
	}
	return false;
}

int hgeBone::GetJointIndex(hgeJoint* joint)
{
	for(int i = 0;i<(int)joints.size();i++)
	{
		if(joints[i] == joint)
			return i;
	}
	return -1;
}

int hgeSkeleton::AddBone()
{
	hgeBone*  nb = new hgeBone();
	bones.push_back(nb);
	newestbi = nb->GetID();
	for(int i = 0 ;i<anims.size();i++)
	{
		nb->AddAnim();
		nb->SetAnimIndex(anims.size()-1);
		nb->SetFrameNum(anims[i].frames.size());
	}
	return nb->GetID();
}

hgeBone* hgeSkeleton::GetBoneFromID(int id)
{
	if(id<0)return 0;
	std::list<hgeBone*>::iterator itor;
	hgeBone* vv;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		vv = *itor;
		if(id == vv->GetID())
			return vv;
	}
	return 0;
}

bool hgeSkeleton::BoneTop(hgeBone* bone)
{
	if(!bone)return false;
	std::list<hgeBone*>::iterator itor;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		if(*itor == bone)
		{
			bones.erase(itor);
			bones.push_front(bone);
			return true;
		}
	}
	return false;
}

bool hgeSkeleton::BoneUp(hgeBone* bone)
{
	if(!bone)return false;
	std::list<hgeBone*>::iterator itor;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		if(*itor == bone)
		{
			if(itor != bones.begin())
			{
				itor = bones.erase(itor);
				itor--;
				itor = bones.insert(itor,bone);
			}
			return true;
		}
	}
	return false;
}

bool hgeSkeleton::BoneDown(hgeBone* bone)
{
	if(!bone)return false;
	std::list<hgeBone*>::iterator itor;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		if(*itor == bone)
		{
			itor = bones.erase(itor);
			if(itor == bones.end())
			{
				bones.push_back(bone);
				return true;
			}
			itor++;
			if(itor == bones.end())
			{
				bones.push_back(bone);
				return true;
			}
			bones.insert(itor,bone);
			return true;
		}
	}
	return false;
}

bool hgeSkeleton::BoneBottom(hgeBone* bone)
{
	if(!bone)return false;
	std::list<hgeBone*>::iterator itor;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		if(*itor == bone)
		{
			bones.erase(itor);
			bones.push_back(bone);
			return true;
		}
	}
	return false;
}

bool hgeSkeleton::DelBone(hgeBone* bone)
{
	if(!bone)return false;
	std::list<hgeBone*>::iterator itor;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		if(*itor == bone)
		{
			bones.erase(itor);
			delete bone;
			return true;
		}
	}
	return false;
}

bool hgeSkeleton::Save(const wchar_t* path)
{
	FILE *f = _wfopen(path,L"w");
	UINT sz = bones.size(),sz3,sz4;
	int t;bool bt;float ft;
	fwrite(&sz,sizeof(sz),1,f);

	std::list<hgeBone*>::iterator itor;
	hgeBone *tb;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		tb = *itor;
		t = tb->GetID();
		//存ID
		fwrite(&t,sizeof(t),1,f);
		//存控制点信息
		bt = tb->ControlPoint().GetBasis();
		fwrite(&bt,sizeof(bt),1,f);
		bt = tb->ControlPoint().GetTra();
		fwrite(&bt,sizeof(bt),1,f);
		if(bt)
		{
			ft = tb->ControlPoint().GetRelative();
		}
		else
		{
			ft = tb->ControlPoint().GetAbsolute();
		}
		fwrite(&ft,sizeof(ft),1,f);

		//存绑定点信息
		bt = tb->BindPoint().GetBasis();
		fwrite(&bt,sizeof(bt),1,f);
		bt = tb->BindPoint().GetTra();
		fwrite(&bt,sizeof(bt),1,f);
		if(bt)
		{
			ft = tb->BindPoint().GetRelative();
		}
		else
		{
			ft = tb->BindPoint().GetAbsolute();
		}
		fwrite(&ft,sizeof(ft),1,f);
		bt = tb->BindPoint().part != 0;
		fwrite(&bt,sizeof(bt),1,f);
		if(bt)
		{
			ft = tb->BindPoint().GetHScale();
			fwrite(&ft,sizeof(ft),1,f);
			ft = tb->BindPoint().GetVScale();
			fwrite(&ft,sizeof(ft),1,f);
			ft = tb->BindPoint().GetRotation();
			fwrite(&ft,sizeof(ft),1,f);
			SlicedPicture* p = (SlicedPicture*)tb->BindPoint().part;
			t = p->GetSliceIndex();
			fwrite(&t,sizeof(t),1,f);
		}
		ft = tb->GetHeadX();
		fwrite(&ft,sizeof(ft),1,f);
		ft = tb->GetHeadY();
		fwrite(&ft,sizeof(ft),1,f);
		ft = tb->GetTailX();
		fwrite(&ft,sizeof(ft),1,f);
		ft = tb->GetTailY();
		fwrite(&ft,sizeof(ft),1,f);
		t = tb->GetFather();
		fwrite(&t,sizeof(t),1,f);
		sz = tb->joints.size();
		fwrite(&sz,sizeof(sz),1,f);
		for(UINT i = 0;i<tb->joints.size();i++)
		{
			bt = tb->joints[i]->GetBasis();
			fwrite(&bt,sizeof(bt),1,f);
			bt = tb->joints[i]->GetTra();
			fwrite(&bt,sizeof(bt),1,f);
			if(bt)
			{
				ft = tb->joints[i]->GetRelative();
			}
			else
			{
				ft = tb->joints[i]->GetAbsolute();
			}
			fwrite(&ft,sizeof(ft),1,f);
			if(tb->joints[i]->bindbone)
			{
				t = tb->joints[i]->bindbone->GetID();
				fwrite(&t,sizeof(t),1,f);
				t = tb->joints[i]->bindbone->GetJointIndex(tb->joints[i]->bindjoint);
				fwrite(&t,sizeof(t),1,f);
				ft = tb->joints[i]->angle;
				fwrite(&ft,sizeof(ft),1,f);
			}
			else
			{
				t = -1;
				fwrite(&t,sizeof(t),1,f);
			}
		}
		sz3 = tb->anims.size();
		fwrite(&sz3,sizeof(sz3),1,f);
		for(UINT k = 0;k<sz3;k++)
		{
			sz4 = tb->anims[k].size();
			fwrite(&sz4,sizeof(sz4),1,f);
			for(UINT j = 0;j<sz4;j++)
			{
				ft = tb->anims[k].at(j);
				fwrite(&ft,sizeof(ft),1,f);
			}
		}
	}
	sz3 = anims.size();
	fwrite(&sz3,sizeof(sz3),1,f);
	for(UINT k = 0;k<sz3;k++)
	{
		ft = anims[k].fps ;
		fwrite(&ft,sizeof(ft),1,f);
		sz4 = anims[k].frames.size();
		fwrite(&sz4,sizeof(sz4),1,f);
		for(UINT j = 0;j<sz4;j++)
		{
			ft = anims[k].frames[j].first ;
			fwrite(&ft,sizeof(ft),1,f);
			ft = anims[k].frames[j].second ;
			fwrite(&ft,sizeof(ft),1,f);
		}
	}
	t = -1;
	if(mainbone)
		t = mainbone->GetID();
	fwrite(&t,sizeof(t),1,f);
	fclose(f);
	return true;
}

bool hgeSkeleton::Load(const wchar_t* path)
{
	FILE *f = _wfopen(path,L"r");
	UINT sz,sz2,sz3,sz4;
	int t;bool bt;float ft,ft2;
	fread(&sz,sizeof(sz),1,f);
	bones.clear();
	hgeBone *tb;hgeJoint *tj;
	for(int i = 0;i<sz;i++)
	{
		fread(&t,sizeof(t),1,f);
		tb = new hgeBone(t);
		bones.push_back(tb);
		fread(&bt,sizeof(bt),1,f);
		tb->ControlPoint().SetBasis(bt);
		fread(&bt,sizeof(bt),1,f);
		fread(&ft,sizeof(ft),1,f);
		if(bt)
			tb->ControlPoint().SetRelative(ft);
		else
			tb->ControlPoint().SetAbsolute(ft);
		fread(&bt,sizeof(bt),1,f);
		tb->BindPoint().SetBasis(bt);
		fread(&bt,sizeof(bt),1,f);
		fread(&ft,sizeof(ft),1,f);
		if(bt)
			tb->BindPoint().SetRelative(ft);
		else
			tb->BindPoint().SetAbsolute(ft);
		fread(&bt,sizeof(bt),1,f);
		if(bt)
		{
			fread(&ft,sizeof(ft),1,f);
			fread(&ft2,sizeof(ft2),1,f);
			tb->BindPoint().SetScale(ft,ft2);
			fread(&ft,sizeof(ft),1,f);
			tb->BindPoint().SetRotation(ft);
			fread(&t,sizeof(t),1,f);
			tb->BindPoint().part = new SlicedPicture();
			SlicedPicture* p = (SlicedPicture*)tb->bind.part;
			p->SetPictureData(dat);
			tb->BindPoint().ls = t;
		}
		fread(&ft,sizeof(ft),1,f);
		fread(&ft2,sizeof(ft2),1,f);
		tb->SetHead(ft,ft2);
		fread(&ft,sizeof(ft),1,f);
		fread(&ft2,sizeof(ft2),1,f);
		tb->SetTail(ft,ft2);
		fread(&t,sizeof(t),1,f);
		tb->SetFatherID(t);
		fread(&sz2,sizeof(sz2),1,f);
		for(int j = 0;j<sz2;j++)
		{
			tj = new hgeJoint(tb);
			tb->joints.push_back(tj);
			fread(&bt,sizeof(bt),1,f);
			tj->SetBasis(bt);
			fread(&bt,sizeof(bt),1,f);
			fread(&ft,sizeof(ft),1,f);
			if(bt)
				tj->SetRelative(ft);
			else
				tj->SetAbsolute(ft);
			fread(&t,sizeof(t),1,f);
			if(t!=-1)
			{
				tj->bidx = t;
				fread(&t,sizeof(t),1,f);
				tj->jidx = t;
				fread(&ft,sizeof(ft),1,f);
				tj->angle = ft;
			}
		}
		fread(&sz3,sizeof(sz3),1,f);
		for(UINT k = 0;k<sz3;k++)
		{
			tb->AddAnim();
			tb->SetAnimIndex(tb->anims.size()-1);
			fread(&sz4,sizeof(sz4),1,f);
			tb->SetFrameNum(sz4);
			for(UINT j = 0;j<sz4;j++)
			{
				fread(&ft,sizeof(ft),1,f);
				tb->anims[k].at(j) = ft;
			}
		}
	}

	fread(&sz3,sizeof(sz3),1,f);
	for(UINT k = 0;k<sz3;k++)
	{
		anims.push_back(hgeSkeleton::anim());
		animindex = anims.size()-1;
		fread(&ft,sizeof(ft),1,f);
		anims[k].fps = ft;
		fread(&sz4,sizeof(sz4),1,f);
		for(UINT j = 0;j<sz4;j++)
		{
			anims[k].frames.push_back(std::pair<float,float>(0.f,0.f));
			fread(&ft,sizeof(ft),1,f);
			anims[k].frames[j].first = ft;
			fread(&ft,sizeof(ft),1,f);
			anims[k].frames[j].second = ft;

		}
	}


	fread(&t,sizeof(t),1,f);
	mbidx = t;

	fclose(f);

	std::list<hgeBone*>::iterator itor;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		tb = *itor;
		tb->SetFather(tb->GetFather(),GetBoneFromID(tb->GetFather()));
		for(UINT i = 0;i<tb->joints.size();i++)
		{
			if(tb->joints[i]->bidx>-1)
			{
				tb->joints[i]->bindbone = GetBoneFromID(tb->joints[i]->bidx);
				tb->joints[i]->bindjoint = tb->joints[i]->bindbone->joints[tb->joints[i]->jidx];
			}
		}
	}
	if(mbidx>-1)
		mainbone = GetBoneFromID(mbidx);
	return true;
}

bool hgeSkeleton::CheckReady()
{
	if(!mainbone)return false;
	std::list<hgeBone*>::iterator itor;
	hgeBone* nn;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		nn = *itor;
		if(nn == mainbone)
		{
			//主骨头不能有父骨头
			if(nn->GetFather()!=-1)
				return false;
		}
		else
		{
			//除主骨头外的所有骨头的祖宗必须是主骨头
			if(nn->GetAcst()!=mainbone)
				return false;
		}
	}

	return true;
}

void hgeSkeleton::SetMode(bool _md)
{
	mode = _md;
	std::list<hgeBone*>::iterator itor;
	hgeBone* nn;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		nn = *itor;
		nn->SetMode(mode);
	}
	if(mainbone)
		mainbone->Reload();
}

void hgeBone::SetMode(bool _md)
{
	mode = _md;
}

void hgeSkeleton::SetFrameNum(UINT num)
{
	if(animindex<0)return;

	if(num==anims[animindex].frames.size())return;
	if(num>anims[animindex].frames.size())
	{
		int w = num - anims[animindex].frames.size();
		for(UINT i=0;i<w;i++)
		{
			anims[animindex].frames.push_back(std::pair<float,float>(0.f,0.f));
		}
	}
	else
	{
		int w = anims[animindex].frames.size()-num;
		for(UINT i=0;i<w;i++)
		{
			anims[animindex].frames.pop_back();
		}
	}

	std::list<hgeBone*>::iterator itor;
	hgeBone* nn;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		nn = *itor;
		nn->SetFrameNum(anims[animindex].frames.size());
	}
}

void hgeBone::SetFrameNum(UINT num)
{
	if(num==anims[animindex].size())return;
	if(num>anims[animindex].size())
	{
		int w = num - anims[animindex].size();
		for(UINT i=0;i<w;i++)
		{
			anims[animindex].push_back(yrotate);
		}
	}
	else
	{
		int w = anims[animindex].size()-num;
		for(UINT i=0;i<w;i++)
		{
			anims[animindex].pop_back();
		}
	}
}

void hgeSkeleton::SetFrameIndex(int index)
{
	if(index <-1 || index >=anims[animindex].frames.size())
		index = -1;
	frameindex = index;
	std::list<hgeBone*>::iterator itor;
	hgeBone* nn;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		nn = *itor;
		nn->SetFrameIndex(index);
	}
	if(mainbone)
		mainbone->Reload();
	if(frameindex>-1)
	{
		int v = frameindex + 1 >=anims[animindex].frames.size()?0:frameindex + 1;
		ox = anims[animindex].frames[frameindex].first;
		oy = anims[animindex].frames[frameindex].second;
		dox = anims[animindex].frames[v].first - anims[animindex].frames[frameindex].first;
		doy = anims[animindex].frames[v].second - anims[animindex].frames[frameindex].second;
	}
}

void hgeBone::SetFrameIndex(int index)
{
	frameindex = index;
	if(animindex != -1 && frameindex!=-1)
	{
		UINT v = frameindex + 1;
		if(v+1>anims[animindex].size())v = 0;
		dj = anims[animindex].at(v) - anims[animindex].at(frameindex);
	}
	else
		dj = 0.f;
}

void hgeBone::Update(float p)
{
	SetRotate(anims[animindex].at(frameindex) + p * dj,3,p);
}

void hgeBone::Reload()
{
	float r;
	if(mode || animindex == -1 || frameindex == -1)
		r = yrotate;
	else
		r = anims[animindex].at(frameindex);
	SetRotate(r,1);
}

int hgeSkeleton::AddAnim()
{
	anims.push_back(hgeSkeleton::anim());
	std::list<hgeBone*>::iterator itor;
	hgeBone* nn;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		nn = *itor;
		nn->AddAnim();
	}
	return anims.size()-1;
}

void hgeSkeleton::DelAnim(int idx)
{
	std::list<hgeBone*>::iterator itor;
	hgeBone* nn;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		nn = *itor;
		nn->DelAnim(idx);
	}
	std::vector<anim>::const_iterator itor2 = anims.begin();
	itor2 += idx;
	anims.erase(itor2);
}

void hgeSkeleton::SetAnimIndex(int index)
{
	animindex = index;
	frameindex = -1;
	std::list<hgeBone*>::iterator itor;
	hgeBone* nn;
	for(itor = bones.begin();itor != bones.end();itor++)
	{
		nn = *itor;
		nn->SetAnimIndex(index);
		nn->SetFrameIndex(-1);
	}

	if(animindex>-1 && anims[animindex].fps>0)
		time = 1000.f / (float)anims[animindex].fps;
	else
		time = 99999999999.f;

}

void hgeBone::AddAnim()
{
	anims.push_back(hgeBone::frames());
}

void hgeBone::DelAnim(int index)
{
	std::vector<frames>::const_iterator itor = anims.begin();
	itor += index;
	anims.erase(itor);
}

void hgeBone::SetAnimIndex(int index)
{
	animindex = index;
}

void hgeSkeleton::SetPosition(float _x,float _y)
{
	x = _x;y = _y;
	if(mainbone)
	{
		if(animindex == -1 || frameindex == -1)
			mainbone->SetPosition(0,0,2);
		else
			mainbone->SetPosition(x + ox,y + oy,2);
	}
}

void hgeSkeleton::SetOffset(float _x,float _y)
{
	if(animindex == -1 || frameindex == -1)return;

	anims[animindex].frames[frameindex].first = _x;
	anims[animindex].frames[frameindex].second = _y;

	ox = _x;oy = _y;
	if(mainbone)
		mainbone->SetPosition(x + anims[animindex].frames[frameindex].first,y + anims[animindex].frames[frameindex].second,2);
}

float hgeSkeleton::GetOX()
{
	if(animindex > -1 && frameindex > -1)
		return anims[animindex].frames[frameindex].first;
	else
		return 0;
}

float hgeSkeleton::GetOY()
{
	if(animindex > -1 && frameindex > -1)
		return anims[animindex].frames[frameindex].second;
	else
		return 0;
}

void hgeSkeleton::SetFps(UINT _fps)
{
	if(animindex == -1)return;
	anims[animindex].fps = _fps;
	if(anims[animindex].fps>0)
		time = 1000.f / (float)anims[animindex].fps;
	else
		time = 99999999999.f;
}

void hgeSkeleton::Render()
{
	std::list<hgeBone*>::reverse_iterator ritor;
	hgeBone* vv;
	for(ritor = bones.rbegin();ritor != bones.rend();ritor++)
	{
		vv = *ritor;
		vv->BindPoint().Render();
	}
}

void hgeSkeleton::Play()
{
	if(animindex!=-1 && GetFrameNum()>0)
	{
		bplaying = true;
		timer.StartTick();
		SetFrameIndex(0);
	}
	else
	{
		bplaying = false;
		timer.StopTick();
	}
}

void hgeSkeleton::Stop()
{
	bplaying = false;
	timer.StopTick();
	dox = doy = 0;
}

void hgeSkeleton::Update()
{
	if(!bplaying)return;
	float t = (float)timer.NowTick();
	if(t>time)
	{
		if(GetFrameIndex() + 1 >= GetFrameNum())
			SetFrameIndex(0);
		else
			SetFrameIndex(GetFrameIndex()+1);
		timer.StartTick();
		t = 0;
	}
		
	if(mainbone)
		mainbone->Update(t/time);
	ox = anims[animindex].frames[frameindex].first + dox * (t/time) ;
	oy = anims[animindex].frames[frameindex].second + doy * (t/time);
	SetPosition(x,y);
}

void hgeSkeleton::Rec()
{
	std::list<hgeBone*>::reverse_iterator ritor;
	hgeBone* vv;
	for(ritor = bones.rbegin();ritor != bones.rend();ritor++)
	{
		vv = *ritor;
		if(vv->BindPoint().part)
		{
			SlicedPicture* p = (SlicedPicture*)vv->BindPoint().part;
			p->SetPictureData(dat);
			p->SetSliceIndex(vv->BindPoint().ls);
		}
	}
}