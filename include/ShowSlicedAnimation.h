#pragma once

#include "showslicedframe.h"
#include "hgetimer.h"

namespace Show
{
	class SlicedAnimation:public SlicedFrame
	{
	public:
		SlicedAnimation():SlicedFrame(){_aidx = 0;_ax = _ay = 0;bPlaying = false;time.StopTick();};
		SlicedAnimation(PictureData *data,UINT index=0);
		virtual ~SlicedAnimation(){};

		virtual void SetPosition(float x,float y);
		void SetAnimationIndex(UINT index);
		UINT GetAnimationIndex(){return _aidx;}

		void Play();
		void Stop(){ bPlaying=false;time.PauseTick(); }
		void Resume(){ bPlaying=true;time.Resume(); }
		void Update(float fDeltaTime);
		bool IsPlaying() const { return bPlaying; }

	protected:
		float _ax,_ay;
		UINT _aidx;
		UINT m_frame,m_frame2;
		bool bPlaying;
		hgeTimer time;
	};
}