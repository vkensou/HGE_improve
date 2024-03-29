#include "hge.h"
#include "showpicturedata.h"

namespace Show
{
	PictureData::PictureData(const wchar_t* file,HTEXTURE tex,bool autodel)
	{
		LoadData(file);
		SetTexture(tex,autodel);
	}
	int PictureData::LoadData(const wchar_t* file)
	{
		if(!file)return -1;
		HGE *hge = hgeCreate(HGE_VERSION);
		void *dat;
		char *zz;
		int offset = 0;
		int temp = 0;
		dat = hge->Resource_Load(file);
		zz = (char*)dat;
		if(!dat)
		{
			hge->Release();
			return -1;
		}
		int mn = 0,n = 0,mm = 0,m = 0;
		SliceInfo nqp;
		SliceData npg;
		FrameInfo nfm;
		FrameData nfme;
		AnimationInfo nan;

		memcpy(&mn, zz + offset, sizeof(mn));
		offset+=sizeof(mn);
		for(n = 0; n<mn;n++)
		{
			memcpy(&nqp, zz + offset, sizeof(nqp));
			offset+=sizeof(nqp);
			slices.push_back(nqp);
		}
		memcpy(&mn, zz + offset, sizeof(mn));
		offset+=sizeof(mn);
		for(n = 0; n<mn;n++)
		{
			nfm.slices.clear();
			memcpy(&mm, zz + offset, sizeof(mm));
			offset+=sizeof(mm);
			for(m = 0; m<mm;m++)
			{
				memcpy(&npg, zz + offset, sizeof(npg));
				offset+=sizeof(npg);
				npg.index--;
				nfm.slices.push_back(npg);
			}
			frames.push_back(nfm);
		}
		memcpy(&mn, zz + offset, sizeof(mn));
		offset+=sizeof(mn);
		for(n = 0; n<mn;n++)
		{
			nan.frames.clear();
			memcpy(&mm, zz + offset, sizeof(mm));
			offset+=sizeof(mm);
			for(m = 0; m<mm;m++)
			{
				memcpy(&nfme.index, zz + offset, sizeof(nfme.index));
				offset+=sizeof(nfme.index);
				memcpy(&temp, zz + offset, sizeof(temp));
				offset+=sizeof(temp);
				nfme.time = (float)temp / 1000.f;
				memcpy(&nfme.x, zz + offset, sizeof(nfme.x));
				offset+=sizeof(nfme.x);
				memcpy(&nfme.y, zz + offset, sizeof(nfme.y));
				offset+=sizeof(nfme.y);
				nfme.index --;
				nan.frames.push_back(nfme);
			}
			memcpy(&nan.mode, zz + offset, sizeof(nan.mode));
			offset+=sizeof(nan.mode);
			animations.push_back(nan);
		}
		hge->Resource_Free(dat);
		hge->Release();
		return 0;
	}

	void PictureData::SetTexture(HTEXTURE _tex,bool autodel)
	{
		tex = _tex;
		_autodel = autodel;
	}

	PictureData::~PictureData()
	{
		if(_autodel)
			if(tex)
			{
				HGE *hge = hgeCreate(HGE_VERSION);
				hge->Texture_Free(tex);
				hge->Release();
			}
	}

	bool PictureData::SetAnimation(int nframes, float DeltaTime, int mode, float w, float h, float x, float y)
	{
		if(0==tex)return false;
		HGE *hge = hgeCreate(HGE_VERSION);
		animations.clear();
		frames.clear();
		slices.clear();
		float tw = (float)hge->Texture_GetWidth(tex,true),th=(float)hge->Texture_GetHeight(tex,true);
		int xn =tw/w,yn=th/h;;
		DeltaTime/=1000.f;
		SliceInfo *slice;
		FrameInfo *frame;
		SliceData *slicedata;
		AnimationInfo *anim;
		FrameData *framedata;
		animations.push_back(AnimationInfo());
		anim = &animations.back();
		anim->mode = mode;
		anim->w = w;anim->h = h;
		for(int i = 0;i<nframes;i++)
		{
			slices.push_back(SliceInfo());
			slice = &slices.back();
			slice->x = x;slice->y = y;
			slice->left = (i % xn) * w;
			slice->top = (i / xn) * h;
			slice->width = w;
			slice->height = h;
			frames.push_back(FrameInfo());
			frame = &frames.back();
			frame->w = slice->width;frame->h = slice->height;
			frame->slices.push_back(SliceData());
			slicedata=&frame->slices.back();
			slicedata->index=i;
			slicedata->x=0;
			slicedata->y=0;
			anim->frames.push_back(FrameData());
			framedata=&anim->frames.back();
			framedata->index=i;
			framedata->time = DeltaTime;
			framedata->x = 0;framedata->y = 0;
		}

		hge->Release();
		return true;
	}
}