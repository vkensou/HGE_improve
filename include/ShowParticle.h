#pragma once

#include "hge.h"
#include "ShowPicture.h"
#include "ShowAnimBase.h"
#include "hgevector.h"
#include "hgecolor.h"
#include "hgerect.h"

const int SHOWMAXPARTICLES = 500;
namespace Show
{
	struct ParticleData
	{
		Picture*	sprite;    // texture + blend mode
		int			nEmission; // particles per sec
		float		fLifetime;

		float		fParticleLifeMin;
		float		fParticleLifeMax;

		float		fDirection;
		float		fSpread;
		bool		bRelative;

		float		fSpeedMin;
		float		fSpeedMax;

		float		fGravityMin;
		float		fGravityMax;

		float		fRadialAccelMin;
		float		fRadialAccelMax;

		float		fTangentialAccelMin;
		float		fTangentialAccelMax;

		float		fSizeStart;
		float		fSizeEnd;
		float		fSizeVar;

		float		fSpinStart;
		float		fSpinEnd;
		float		fSpinVar;

		hgeColor	colColorStart; // + alpha
		hgeColor	colColorEnd;
		float		fColorVar;
		float		fAlphaVar;
	};

	class ParticleSystem
		:public Base,public AnimBase
	{
	public:
		ParticleData info;

		ParticleSystem(const wchar_t *filename, Picture *sprite);
		ParticleSystem(ParticleData *psi);
		ParticleSystem(const ParticleSystem &ps);
		virtual ~ParticleSystem() { hge->Release(); }

		ParticleSystem&	operator= (const ParticleSystem &ps);

		virtual void Update(float fDeltaTime);
		virtual void Render();
		virtual void Play();
		virtual void Stop(/*bool bKillParticles*/);
		virtual void Resume(){Play();}

		void PlayAt(float x, float y);
		virtual void SetPosition(float x, float y);
		virtual void SetPosition(float x, float y,bool bMoveParticles);

		void				Transpose(float x, float y) { fTx=x; fTy=y; }
		void				SetScale(float scale=1.0f, float vscale=0.0f) {_hscale = _vscale = scale;}
		void				TrackBoundingBox(bool bTrack) { bUpdateBoundingBox=bTrack; }

		int					GetParticlesAlive() const { return nParticlesAlive; }
		float				GetAge() const { return fAge; }
		virtual float GetX(){return vecLocation.x;}
		virtual float GetY(){return vecLocation.y;}

		void				GetTransposition(float *x, float *y) const { *x=fTx; *y=fTy; }
		hgeRect*			GetBoundingBox(hgeRect *rect) const;

	private:
		ParticleSystem();

		static HGE			*hge;

		float				fAge;
		float				fEmissionResidue;

		hgeVector			vecPrevLocation;
		hgeVector			vecLocation;
		float				fTx, fTy;

		int					nParticlesAlive;
		hgeRect				rectBoundingBox;
		bool				bUpdateBoundingBox;

		struct Particle
		{
			hgeVector	vecLocation;
			hgeVector	vecVelocity;

			float		fGravity;
			float		fRadialAccel;
			float		fTangentialAccel;

			float		fSpin;
			float		fSpinDelta;

			float		fSize;
			float		fSizeDelta;

			hgeColor	colColor;		// + alpha
			hgeColor	colColorDelta;

			float		fAge;
			float		fTerminalAge;
		};
		Particle			particles[SHOWMAXPARTICLES];

	};

}