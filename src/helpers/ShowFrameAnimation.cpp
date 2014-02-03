#include "showframeanimation.h"

namespace Show
{
	FrameAnimation::FrameAnimation(HTEXTURE tex, int nframes, float FPS, float x, float y, float w, float h)
		: Picture(tex, x, y, w, h)
	{
		orig_width = hge->Texture_GetWidth(tex, true);

		fSinceLastFrame=-1.0f;
		fSpeed=1.0f/FPS;
		bPlaying=false;
		nFrames=nframes;

		Mode=ANIM_FWD | ANIM_LOOP;
		nDelta=1;
		SetFrame(0);
	}

	void FrameAnimation::SetMode(int mode)
	{
		Mode=mode;

		if(mode & ANIM_REV)
		{
			nDelta = -1;
			SetFrame(nFrames-1);
		}
		else
		{
			nDelta = 1;
			SetFrame(0);
		}
	}


	void FrameAnimation::Play()
	{
		bPlaying=true;
		fSinceLastFrame=-1.0f;
		if(Mode & ANIM_REV)
		{
			nDelta = -1;
			SetFrame(nFrames-1);
		}
		else
		{
			nDelta = 1;
			SetFrame(0);
		}
	}


	void FrameAnimation::Update(float fDeltaTime)
	{
		if(!bPlaying) return;

		if(fSinceLastFrame == -1.0f)
			fSinceLastFrame=0.0f;
		else
			fSinceLastFrame += fDeltaTime;

		while(fSinceLastFrame >= fSpeed)
		{
			fSinceLastFrame -= fSpeed;

			if(nCurFrame + nDelta == nFrames)
			{
				switch(Mode)
				{
				case ANIM_FWD:
				case ANIM_REV | ANIM_PINGPONG:
					bPlaying = false;
					break;

				case ANIM_FWD | ANIM_PINGPONG:
				case ANIM_FWD | ANIM_PINGPONG | ANIM_LOOP:
				case ANIM_REV | ANIM_PINGPONG | ANIM_LOOP:
					nDelta = -nDelta;
					break;
				}
			}
			else if(nCurFrame + nDelta < 0)
			{
				switch(Mode)
				{
				case ANIM_REV:
				case ANIM_FWD | ANIM_PINGPONG:
					bPlaying = false;
					break;

				case ANIM_REV | ANIM_PINGPONG:
				case ANIM_REV | ANIM_PINGPONG | ANIM_LOOP:
				case ANIM_FWD | ANIM_PINGPONG | ANIM_LOOP:
					nDelta = -nDelta;
					break;
				}
			}

			if(bPlaying) SetFrame(nCurFrame+nDelta);
		}
	}

	void FrameAnimation::SetFrame(int n)
	{
		float tx1, ty1, tx2, ty2;
		int ncols = int(orig_width) / int(width);


		n = n % nFrames;
		if(n < 0) n = nFrames + n;
		nCurFrame = n;

		// calculate texture coords for frame n
		ty1 = ty;
		tx1 = tx + n*width;

		if(tx1 > orig_width-width)
		{
			n -= int(orig_width-tx) / int(width);
			tx1 = width * (n%ncols);
			ty1 += height * (1 + n/ncols);
		}

		tx2 = tx1 + width;
		ty2 = ty1 + height;

		tx1 /= tex_width;
		ty1 /= tex_height;
		tx2 /= tex_width;
		ty2 /= tex_height;

		quad.v[0].tx=tx1; quad.v[0].ty=ty1;
		quad.v[1].tx=tx2; quad.v[1].ty=ty1;
		quad.v[2].tx=tx2; quad.v[2].ty=ty2;
		quad.v[3].tx=tx1; quad.v[3].ty=ty2;
	}



}