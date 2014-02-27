/*!
	@file
	@author		Losev Vasiliy aka bool
	@date		06/2009
*/

#include "MyGUI_HGETexture.h"
#include "MyGUI_HGEDataManager.h"
#include "MyGUI_HGERTTexture.h"
#include "MyGUI_HGEDiagnostic.h"
#include "MYGUI_UString.h"

namespace MyGUI
{

	HGETexture::HGETexture(const std::string& _name) :
		mName(_name),
		mpTexture(NULL),
		mNumElemBytes(0),
		mLock(false),
		mRenderTarget(nullptr),
		//mInternalPool(D3DPOOL_MANAGED),
		//mInternalFormat(D3DFMT_UNKNOWN),
		mInternalUsage(0)
	{
		mpHGE = hgeCreate(HGE_VERSION);
	}

	HGETexture::~HGETexture()
	{
		destroy();
		mpHGE->Release();
	}

	const std::string& HGETexture::getName() const
	{
		return mName;
	}

	void HGETexture::createManual(int _width, int _height, TextureUsage _usage, PixelFormat _format)
	{
		destroy();
		mpTexture = mpHGE->Texture_Create( _width, _height );
		mSize.set(_width, _height);
	}

	void HGETexture::loadFromFile(const std::string& _filename)
	{
		destroy();
		//MyGUI::UString path = HGEDataManager::getInstance().getDataPath(_filename);
		MyGUI::UString path = _filename;
		void* fptr = 0;
		DWORD size = 0;
		fptr = mpHGE->Resource_Load(path.asWStr().c_str(),&size);
		if(!size)return ;
		mpTexture = mpHGE->Texture_Load( (wchar_t*)fptr,size);
		//mpTexture = mpHGE->Texture_Load( path.asWStr().c_str());
		if (!mpTexture) return;
		mSize.set( mpHGE->Texture_GetWidth(mpTexture), mpHGE->Texture_GetHeight(mpTexture) );
	}

	void HGETexture::destroy()
	{
		if (mRenderTarget != nullptr)
		{
			delete mRenderTarget;
			mRenderTarget = nullptr;
		}

		if (mpTexture != nullptr)
		{
			mpHGE->Texture_Free( mpTexture );
			mpTexture = nullptr;
		}
	}

	int HGETexture::getWidth()
	{
		return mSize.width;
	}

	int HGETexture::getHeight()
	{
		return mSize.height;
	}

	void* HGETexture::lock(TextureUsage _access)
	{
		DWORD* lockbits = mpHGE->Texture_Lock( mpTexture );
		mLock = true;
		return (void*)lockbits;
	}

	void HGETexture::unlock()
	{
		mpHGE->Texture_Unlock( mpTexture );
		mLock = false;
	}

	bool HGETexture::isLocked()
	{
		return mLock;
	}

	PixelFormat HGETexture::getFormat()
	{
		return mPixelFormat;
	}

	size_t HGETexture::getNumElemBytes()
	{
		return mNumElemBytes;
	}

	TextureUsage HGETexture::getUsage()
	{
		return mTextureUsage;
	}

	IRenderTarget* HGETexture::getRenderTarget()
	{
		if (mpTexture == nullptr)
			return nullptr;

		if (mRenderTarget == nullptr)
			mRenderTarget = new HGERTTexture(mpTexture);

		return mRenderTarget;
	}

	void HGETexture::deviceLost()
	{
		//if (mInternalPool == D3DPOOL_DEFAULT)
		//{
			//destroy();
		//}
	}

	void HGETexture::deviceRestore()
	{
	}

} // namespace MyGUI
