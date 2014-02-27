/*!
	@file
	@author		Albert Semenov
	@date		12/2009
*/

#ifndef __MYGUI_HGE_RTTEXTURE_H__
#define __MYGUI_HGE_RTTEXTURE_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_ITexture.h"
#include "MyGUI_RenderFormat.h"
#include "MyGUI_IRenderTarget.h"

#include "hge.h"

namespace MyGUI
{

	class HGERTTexture :
		public IRenderTarget
	{
	public:
		HGERTTexture(HTEXTURE _texture);
		virtual ~HGERTTexture();

		virtual void begin();
		virtual void end();

		virtual void doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count);

		virtual const RenderTargetInfo& getInfo()
		{
			return mRenderTargetInfo;
		}

	private:
		HGE* mpHGE;
		HTEXTURE mpTexture;
		RenderTargetInfo mRenderTargetInfo;
	};

} // namespace MyGUI

#endif // __MYGUI_HGE_RTTEXTURE_H__
