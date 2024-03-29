/*!
	@file
	@author		Albert Semenov
	@date		12/2009
*/

#include "MyGUI_HGERTTexture.h"
#include "MyGUI_HGERenderManager.h"

namespace MyGUI
{

	HGERTTexture::HGERTTexture(HTEXTURE _texture) :
		mpTexture(_texture)
	{
		//mpTexture->GetSurfaceLevel(0, &mpRenderSurface);

		//D3DSURFACE_DESC info;
		//mpTexture->GetLevelDesc(0, &info);
		//int width = info.Width;
		//int height = info.Height;

		//mRenderTargetInfo.maximumDepth = 0.0f;
		//mRenderTargetInfo.hOffset = -0.5f / float(width);
		//mRenderTargetInfo.vOffset = -0.5f / float(height);
		//mRenderTargetInfo.aspectCoef = float(height) / float(width);
		//mRenderTargetInfo.pixScaleX = 1.0f / float(width);
		//mRenderTargetInfo.pixScaleY = 1.0f / float(height);
		mpHGE = hgeCreate(HGE_VERSION);
	}

	HGERTTexture::~HGERTTexture()
	{
		//if (mpRenderSurface != nullptr)
		//{
		//	mpRenderSurface->Release();
		//	mpRenderSurface = nullptr;
		//}
		mpHGE->Release();
	}

	void HGERTTexture::begin()
	{
		//mpD3DDevice->GetRenderTarget(0, &mpBackBuffer);

		//mpD3DDevice->SetRenderTarget(0, mpRenderSurface);
		//mpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET,
		//	D3DCOLOR_RGBA(0, 0, 0, 0), 1, 0);

		//mpD3DDevice->BeginScene();
	}

	void HGERTTexture::end()
	{
		//mpD3DDevice->EndScene();

		//mpD3DDevice->SetRenderTarget(0, mpBackBuffer);
		//mpBackBuffer->Release();
	}

	void HGERTTexture::doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count)
	{
		HGERenderManager::getInstance().doRender(_buffer, _texture, _count);
	}

} // namespace MyGUI
