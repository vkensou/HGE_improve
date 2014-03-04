#pragma once

#include "showframe.h"
#include "ShowAnimBase.h"

namespace Show
{
	enum AnimMode
	{
		SHOWANIM_NOLOOP = 0,
		SHOWANIM_LOOP = 1,
		SHOWANIM_FWD = 0,
		SHOWANIM_REV = 2,
		SHOWANIM_NOPINGPONG = 0,
		SHOWANIM_PINGPONG = 4,
		SHOWANIM_TIME = 0,
		SHOWANIM_FRAME = 8,
	};
	class Animation:
		public Frame,public AnimBase
	{
	public:
		Animation();
		Animation(PictureData *data,int index=-1,bool autodel=false);
		virtual ~Animation(){};

		virtual void SetIndex(int index);
		virtual int GetIndex(){return _aidx;}
		virtual void SetFrameIndex(int index){};
		virtual int GetFrameIndex(){return m_frame;}

		virtual void Play();
		virtual void Stop(){ bPlaying=false; }
		virtual void Resume(){ bPlaying=true; }
		virtual void Update(float delta);
		bool IsPlaying() const { return bPlaying; }
		void SetSpeed(float speed);
		float GetSpeed(){return 1.0;}
		void SetMode(int mode);
		int GetMode(){return _mode;}
	protected:
		int _aidx;
		int m_frame,m_frame2;
		bool bPlaying;
		float _time;
		int times;
		int _mode;
	};
}