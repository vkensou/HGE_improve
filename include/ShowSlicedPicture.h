#pragma once

#include "showpicture.h"
#include "showpicturedata.h"

namespace Show
{
	class SlicedPicture:public Picture
	{
	public:
		SlicedPicture():Picture(){_data = 0;_sidx = 0;};
		SlicedPicture(PictureData *data,UINT index=0);
		virtual ~SlicedPicture(){};
		void SetPictureData(PictureData *data);
		//序号从1开始，0表示无图像
		void SetSliceIndex(UINT index=0);
		PictureData *GetData(){return _data;}
		UINT GetSliceIndex(){return _sidx;}
	protected:
		PictureData *_data;
		UINT _sidx;
	};
}