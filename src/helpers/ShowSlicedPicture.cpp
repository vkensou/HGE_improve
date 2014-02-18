#include "showslicedpicture.h"

namespace Show
{
	SlicedPicture::SlicedPicture(PictureData *data,UINT index)
		:Picture()
	{
		_type = SLICEDPICTURE;
		SetPictureData(data);
		SetSliceIndex(index);
	}
	
	void SlicedPicture::SetPictureData(PictureData *data)
	{
		_data = data;
		Picture::SetTexture(_data->tex);
		_sidx = 0;
		Picture::SetTextureRect(0,0,0,0);
		Picture::SetCenterPoint(0,0);
	}

	void SlicedPicture::SetSliceIndex(UINT index)
	{
		if(_data ==0 )return ;
		if(index >_data->slices.size())return ;
		_sidx = index;
		if(_sidx>0)
		{
			SliceInfo slice = _data->slices[_sidx-1];
			Picture::SetTextureRect(slice.left,slice.top,slice.width,slice.height);
			Picture::SetCenterPoint(slice.x,slice.y);
		}
		else
		{
			Picture::SetTextureRect(0,0,0,0);
			Picture::SetCenterPoint(0,0);
		}
	}
}