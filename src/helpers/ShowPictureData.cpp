#include "hge.h"
#include "showpicturedata.h"

namespace Show
{
	int PictureData::LoadData(const wchar_t* file)
	{
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
}