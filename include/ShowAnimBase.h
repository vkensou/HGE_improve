#pragma once

namespace Show
{
	class AnimBase
	{
	public:
		virtual ~AnimBase(){};
		virtual void Play(){};
		virtual void Stop(){};
		virtual void Resume(){};
		virtual void Update(float fDeltaTime){};
	};
}