#include "showframe.h"

namespace Show
{
	Frame::Frame()
		:Picture(FRAME)
	{
		_fx = _fy = 0.f;
		_fidx = -1;
	}

	Frame::Frame(PictureData *data,int index,bool autodel)
		:Picture(FRAME)
	{
		_fx = _fy = 0;
		Picture::SetPictureData(data,autodel);
		SetIndex(index);
	}

	Frame::Frame(ShowType st)
		:Picture(FRAME)
	{
		_fx = _fy = 0.f;
		_fidx = -1;
	}

	void Frame::SetIndex(int index)
	{
		if(!_data || index <-1 || index >(int)_data->frames.size()-1)
		{
			_fidx = -1;
			return ;
		}
		_fidx = index;
		Picture::SetTextureRect(0,0,0,0);
		Picture::SetCenterPoint(0,0);
	}

	void Frame::Render()
	{
		if(!_data || !quad.tex || _fidx<0 || _fidx >(int)_data->frames.size()-1)return ;

		FrameInfo* frame = &(_data->frames[_fidx]);
		SliceInfo* slice=0;
		for(UINT i=0;i<frame->slices.size();i++)
		{
			slice = &(_data->slices[frame->slices[i].index]);
			Picture::SetTextureRect(slice->left,slice->top,slice->width,slice->height);
			Picture::SetEx(_fx,_fy,slice->x - frame->slices[i].x,slice->y - frame->slices[i].y,_rot,_hscale,_vscale);
			hge->Gfx_RenderQuad(&quad);
		}
	}

	void Frame::SetPosition(float x,float y)
	{
		_fx = x;
		_fy = y;
	}
}