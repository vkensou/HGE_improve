#include "showanimation.h"

namespace Show
{
	Animation::Animation()
		:Frame(ANIMATION)
	{
		_aidx = 0;bPlaying = false;time.Stop();
	};

	Animation::Animation(PictureData *data,int index,bool autodel)
		:Frame(ANIMATION)
	{
		Picture::SetPictureData(data,autodel);
		SetIndex(index);
		bPlaying = false;
		time.Stop();
	}

	void Animation::Play()
	{
		if(_data && _aidx>-1 && _aidx <= (int)_data->animations.size()-1 && _data->animations[_aidx].frames.size() > 0)
		{
			bPlaying = true;
			m_frame = 0;
			m_frame2 = _data->animations[_aidx].frames[m_frame].index;
			Frame::SetIndex(m_frame2);
			time.Start();
		}
		else
		{
			_aidx = m_frame = m_frame2 = 0;
		}
	}

	void Animation::Update()
	{
		if(!bPlaying)return ;
		if(!(_mode & SHOWANIM_FRAME))
		{
			if(time.Now()>= _data->animations[_aidx].frames[m_frame].time)
			{
				m_frame++;
				time.Start();

				if(m_frame == _data->animations[_aidx].frames.size())
				{
					if(_mode & SHOWANIM_LOOP)
					{
						m_frame=0;
					}
					else
					{
						bPlaying = false;
						time.Stop();
						m_frame--;
					}
				}
				m_frame2 = _data->animations[_aidx].frames[m_frame].index;
				Frame::SetIndex(m_frame2);
			}
		}
	}

	void Animation::SetIndex(int index)
	{
		if(!_data || index < -1 || index >(int)_data->animations.size()-1)
		{
			_aidx = -1;
		}
		else
		{
			_aidx = index;
			m_frame = 0;
			m_frame2 = _data->animations[_aidx].frames[m_frame].index;
			Frame::SetIndex(m_frame2);
		}
		bPlaying = false;
		time.Stop();
		_mode = _data->animations[_aidx].mode;
	}

	void Animation::SetSpeed(float speed)
	{
		time.SetSpeed(speed);
	}
}