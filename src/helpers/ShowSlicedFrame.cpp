#include "showslicedframe.h"

namespace Show
{
	SlicedFrame::SlicedFrame(PictureData *data,UINT index)
		:SlicedPicture(data,0)
	{
		_fx = _fy = 0;
		SetFrameIndex(index);
	}

	void SlicedFrame::SetFrameIndex(UINT index)
	{
		if(!_data || index >_data->frames.size())
		{
			_fidx = 0;
			return ;
		}
		_fidx = index;
		Picture::SetTextureRect(0,0,0,0);
		Picture::SetCenterPoint(0,0);
	}

	float sgn(float num){return num>=0?1.f:-1.f;}

	void SlicedFrame::Render()
	{
		if(!_data || !quad.tex || !_fidx)return ;

		FrameInfo* frame = &(_data->frames[_fidx-1]);
		SliceInfo* slice=0;
		for(UINT i=0;i<frame->slices.size();i++)
		{
			slice = &(_data->slices[frame->slices[i].index]);
			Picture::SetTextureRect(slice->left,slice->top,slice->width,slice->height);
			//Picture::SetCenterPoint(slice->x - sgn(_hscale) * frame->slices[i].x,slice->y - sgn(_vscale) * frame->slices[i].y);
			Picture::SetCenterPoint(slice->x - frame->slices[i].x,slice->y - frame->slices[i].y);
			Picture::SetPosition(_fx , _fy );
			hge->Gfx_RenderQuad(&quad);
		}
	}

	void SlicedFrame::SetPosition(float x,float y)
	{
		_fx = x;
		_fy = y;
	}
}