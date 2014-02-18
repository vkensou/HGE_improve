#pragma once

#include "showslicedpicture.h"

namespace Show
{
	class SlicedFrame:public SlicedPicture
	{
	public:
		SlicedFrame():SlicedPicture(){_fidx = 0;_fx = _fy = 0;_type = SLICEDFRAME;};
		SlicedFrame(PictureData *data,UINT index=0);
		virtual ~SlicedFrame(){};

		virtual void Render();
		
		virtual void SetPosition(float x,float y);
		void SetFrameIndex(UINT index);
		UINT GetFrameIndex(){return _fidx;}
	protected:
		float _fx,_fy;
		UINT _fidx;
	};
}