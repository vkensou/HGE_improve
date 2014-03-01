#pragma once

#include "showframe.h"
#include "hgetimer.h"

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
	class Animation:public Frame
	{
	public:
		Animation();
		Animation(PictureData *data,int index=-1,bool autodel=false);
		virtual ~Animation(){};

		virtual void SetIndex(int index);
		virtual int GetIndex(){return _aidx;}
		virtual void SetFrameIndex(int index){};
		virtual int GetFrameIndex(){return m_frame;}

		void Play();
		void Stop(){ bPlaying=false;time.Pause(); }
		void Resume(){ bPlaying=true;time.Resume(); }
		void Update();
		bool IsPlaying() const { return bPlaying; }
		void SetSpeed(float speed);
		float GetSpeed(){return time.GetSpeed();}
		void SetMode(int mode);
		int GetMode(){return _mode;}
	protected:
		int _aidx;
		int m_frame,m_frame2;
		bool bPlaying;
		hgeTimer time;
		int times;
		int _mode;
	};
}