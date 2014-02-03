#pragma once
#include "showpicture.h"

namespace Show
{
	const int ANIM_FWD = 0;
	const int ANIM_REV = 1;
	const int ANIM_PINGPONG = 2;
	const int ANIM_NOPINGPONG = 0;
	const int ANIM_LOOP	= 4;
	const int ANIM_NOLOOP = 0;

	class FrameAnimation :public Picture
	{
	public:
		FrameAnimation(HTEXTURE tex, int nframes, float FPS, float x, float y, float w, float h);

		void		Play();
		void		Stop() { bPlaying=false; }
		void		Resume() { bPlaying=true; }
		void		Update(float fDeltaTime);
		bool		IsPlaying() const { return bPlaying; }

		void		SetTexture(HTEXTURE tex) { Picture::SetTexture(tex); orig_width = hge->Texture_GetWidth(tex, true); }
		void		SetTextureRect(float x1, float y1, float x2, float y2) { Picture::SetTextureRect(x1,y1,x2,y2); SetFrame(nCurFrame); }
		void		SetMode(int mode);
		void		SetSpeed(float FPS) { fSpeed=1.0f/FPS; }
		void		SetFrame(int n);
		void		SetFrames(int n) { nFrames=n; }

		int			GetMode() const { return Mode; }
		float		GetSpeed() const { return 1.0f/fSpeed; }
		int			GetFrame() const { return nCurFrame; }
		int			GetFrames() const { return nFrames; }

	private:
		FrameAnimation();

		int			orig_width;

		bool		bPlaying;

		float		fSpeed;
		float		fSinceLastFrame;

		int			Mode;
		int			nDelta;
		int			nFrames;
		int			nCurFrame;
	};
}