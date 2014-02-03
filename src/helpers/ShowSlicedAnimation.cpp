#include "showslicedanimation.h"

namespace Show
{
	SlicedAnimation::SlicedAnimation(PictureData *data,UINT index)
		:SlicedFrame(data,0)
	{
		SetAnimationIndex(index);
		_ax = _ay = 0;
		bPlaying = false;
		time.StopTick();
	}

	void SlicedAnimation::Play()
	{
		if(_data && _aidx>0 && _aidx <= _data->animations.size() && _data->animations[_aidx-1].frames.size() > 0)
		{
			bPlaying = true;
			m_frame = 0;
			m_frame2 = _data->animations[_aidx-1].frames[m_frame].index;
			SlicedFrame::SetFrameIndex(m_frame2+1);
			time.StartTick();
		}
		else
		{
			_aidx = m_frame = m_frame2 = 0;
		}
	}

	void SlicedAnimation::Update(float fDeltaTime)
	{
		if(!bPlaying)return ;
		if(time.NowTick()>= _data->animations[_aidx-1].frames[m_frame].time)
		{
			m_frame++;
			time.StartTick();

			if(m_frame == _data->animations[_aidx-1].frames.size())
			{
				switch(_data->animations[_aidx-1].mode)
				{
				case 0:
					bPlaying = false;
					time.StopTick();
					m_frame--;
					break;
				case 1:
					m_frame=0;
					break;
				}
			}
			m_frame2 = _data->animations[_aidx-1].frames[m_frame].index;
			SlicedFrame::SetFrameIndex(m_frame2+1);
		}
	}


	void SlicedAnimation::SetPosition(float x,float y)
	{
		_ax = x;
		_ay = y;
		SlicedFrame::SetPosition(_ax,_ay);
	}

	void SlicedAnimation::SetAnimationIndex(UINT index)
	{
		if(!_data || index >_data->animations.size())
		{
			_aidx = 0;
		}
		else
		{
			_aidx = index;
			m_frame = 0;
			m_frame2 = _data->animations[_aidx-1].frames[m_frame].index;
			SlicedFrame::SetFrameIndex(m_frame2+1);
		}
		bPlaying = false;
		time.StopTick();
	}
}