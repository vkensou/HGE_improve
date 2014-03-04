#include "showanimation.h"

namespace Show
{
	Animation::Animation()
		:Frame(ANIMATION)
	{
		_aidx = 0;bPlaying = false;_time =0;
	};

	Animation::Animation(PictureData *data,int index,bool autodel)
		:Frame(ANIMATION)
	{
		Picture::SetPictureData(data,autodel);
		SetIndex(index);
		bPlaying = false;
		_time =0;
	}

	void Animation::Play()
	{
		if(_data && _aidx>-1 && _aidx <= (int)_data->animations.size()-1 && _data->animations[_aidx].frames.size() > 0)
		{
			bPlaying = true;
			m_frame = 0;
			m_frame2 = _data->animations[_aidx].frames[m_frame].index;
			Frame::SetIndex(m_frame2);
			_time = 0;
		}
		else
		{
			_aidx = m_frame = m_frame2 = 0;
		}
	}

	void Animation::Update(float delta)
	{
		if(!bPlaying)return ;
		if(!(_mode & SHOWANIM_FRAME))
		{
			_time += delta;
			if(_time>= _data->animations[_aidx].frames[m_frame].time)
			{
				m_frame++;
				_time = 0;

				if(m_frame == _data->animations[_aidx].frames.size())
				{
					if(_mode & SHOWANIM_LOOP)
					{
						m_frame=0;
					}
					else
					{
						bPlaying = false;
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
		_time = 0;
		_mode = _data->animations[_aidx].mode;
	}

	void Animation::SetSpeed(float speed)
	{
		//time.SetSpeed(speed);
	}
}