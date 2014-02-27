/*!
	@file
	@author		Losev Vasiliy aka bool
	@date		06/2009
*/

#include "MyGUI_HGERenderManager.h"
#include "MyGUI_HGETexture.h"
#include "MyGUI_HGEVertexBuffer.h"
#include "MyGUI_HGEDiagnostic.h"
#include "MyGUI_Gui.h"
#include "MyGUI_Timer.h"

#define MAX_VERTEX_BUFFER	4000

namespace MyGUI
{

	HGERenderManager::HGERenderManager() :
		mIsInitialise(false),
		mpHGE(nullptr),
		mUpdate(false)
	{
	}

	void HGERenderManager::initialise()
	{
		MYGUI_PLATFORM_ASSERT(!mIsInitialise, getClassTypeName() << " initialised twice");
		MYGUI_PLATFORM_LOG(Info, "* Initialise: " << getClassTypeName());

		//MYGUI_PLATFORM_ASSERT(_hge, getClassTypeName() << " HGE pointer is null");

		mpHGE = hgeCreate(HGE_VERSION);
		setViewSize(mpHGE->System_GetState(HGE_SCREENWIDTH),
					mpHGE->System_GetState(HGE_SCREENHEIGHT));
		mVertexFormat = VertexColourType::ColourARGB;

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully initialized");
		mIsInitialise = true;
	}

	void HGERenderManager::shutdown()
	{
		MYGUI_PLATFORM_ASSERT(mIsInitialise, getClassTypeName() << " is not initialised");
		MYGUI_PLATFORM_LOG(Info, "* Shutdown: " << getClassTypeName());

		destroyAllResources();
		mpHGE->Release();

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully shutdown");
		mIsInitialise = false;
	}

	IVertexBuffer* HGERenderManager::createVertexBuffer()
	{
		return new HGEVertexBuffer(this);
	}

	void HGERenderManager::destroyVertexBuffer(IVertexBuffer* _buffer)
	{
		delete _buffer;
	}

	void HGERenderManager::doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count)
	{
		HGETexture* dxTex = static_cast<HGETexture*>(_texture);
		HGEVertexBuffer* dxVB = static_cast<HGEVertexBuffer*>(_buffer);
		MyGUI::Vertex* pVertex = dxVB->lock();
		hgeTriple Triple;
		Triple.tex = dxTex->getHGETexture();
		Triple.blend = BLEND_DEFAULT;
		//for (size_t t = 0;t<_count;t+=3)
		//{
		//	memcpy(Triple.v, pVertex+t, 3*sizeof(Vertex));
		//	Triple.v[0].y = -Triple.v[0].y;
		//	Triple.v[1].y = -Triple.v[1].y;
		//	Triple.v[2].y = -Triple.v[2].y;
		//	mpHGE->Gfx_RenderTriple(&Triple);
		//}
		int maxPrim = 0,numPrims = 0,numPrims2 = 0;
		hgeVertex *vt = mpHGE->Gfx_StartBatch(HGEPRIM_TRIPLES,dxTex->getHGETexture(),BLEND_DEFAULT,&maxPrim);
		for (size_t t = 0;t<_count;t+=3)
		{
			memcpy(vt+numPrims, pVertex+t, 3*sizeof(Vertex));
			vt[numPrims].y = - vt[numPrims].y;
			vt[numPrims+1].y = - vt[numPrims+1].y;
			vt[numPrims+2].y = - vt[numPrims+2].y;
			numPrims+=3;
			numPrims2++;
			if(numPrims2>=maxPrim)
			{
				mpHGE->Gfx_FinishBatch( numPrims2 );
				hgeVertex *vt = mpHGE->Gfx_StartBatch(HGEPRIM_TRIPLES,dxTex->getHGETexture(),BLEND_DEFAULT,&maxPrim);
				numPrims = numPrims2 = 0;
			}
		}
		mpHGE->Gfx_FinishBatch( numPrims2 );
	}

	void HGERenderManager::drawOneFrame()
	{
		Gui* gui = Gui::getInstancePtr();
		if (gui == nullptr)
			return;

		static Timer timer;
		static unsigned long last_time = timer.getMilliseconds();
		unsigned long now_time = timer.getMilliseconds();
		unsigned long time = now_time - last_time;

		onFrameEvent((float)((double)(time) / (double)1000));

		last_time = now_time;

		begin();
		onRenderToTarget(this, mUpdate);
		end();

		mUpdate = false;
	}

	void HGERenderManager::begin()
	{
		mpHGE->Gfx_SetTransform();
	}

	void HGERenderManager::end()
	{
	}

	ITexture* HGERenderManager::createTexture(const std::string& _name)
	{
		MapTexture::const_iterator item = mTextures.find(_name);
		MYGUI_PLATFORM_ASSERT(item == mTextures.end(), "Texture '" << _name << "' already exist");

		HGETexture* texture = new HGETexture(_name);
		mTextures[_name] = texture;
		return texture;
	}

	void HGERenderManager::destroyTexture(ITexture* _texture)
	{
		if (_texture == nullptr)
			return;

		MapTexture::iterator item = mTextures.find(_texture->getName());
		MYGUI_PLATFORM_ASSERT(item != mTextures.end(), "Texture '" << _texture->getName() << "' not found");

		mTextures.erase(item);
		delete _texture;
	}

	ITexture* HGERenderManager::getTexture(const std::string& _name)
	{
		MapTexture::const_iterator item = mTextures.find(_name);
		if (item == mTextures.end())
			return nullptr;
		return item->second;
	}

	bool HGERenderManager::isFormatSupported(PixelFormat _format, TextureUsage _usage)
	{
		// add by Eric.Liu 2011.9.1
		// 此处返回false会使freetype font 创建的时候使用A8R8G8B8颜色格式
		// 其他可能用到的地方需要自己调整
		return false;
	}

	void HGERenderManager::destroyAllResources()
	{
		for (MapTexture::const_iterator item = mTextures.begin(); item != mTextures.end(); ++item)
		{
			delete item->second;
		}
		mTextures.clear();
	}

	void HGERenderManager::setViewSize(int _width, int _height)
	{
		if (_height == 0)
			_height = 1;
		if (_width == 0)
			_width = 1;

		mViewSize.set(_width, _height);

		mInfo.maximumDepth = 1.f;
		mInfo.hOffset = 0.5f;
		mInfo.vOffset = 0.5f;
		mInfo.aspectCoef = float(mViewSize.width) / float(mViewSize.height);
		mInfo.pixScaleX = 0.5f;
		//mInfo.pixScaleY = -0.5f;
		mInfo.pixScaleY = 0.5f;

		onResizeView(mViewSize);

		mUpdate = true;
	}

	void HGERenderManager::deviceLost()
	{
		MYGUI_PLATFORM_LOG(Info, "device D3D lost");

		for (MapTexture::const_iterator item = mTextures.begin(); item != mTextures.end(); ++item)
		{
			static_cast<HGETexture*>(item->second)->deviceLost();
		}
	}

	void HGERenderManager::deviceRestore()
	{
		MYGUI_PLATFORM_LOG(Info, "device D3D restore");

		for (MapTexture::const_iterator item = mTextures.begin(); item != mTextures.end(); ++item)
		{
			static_cast<HGETexture*>(item->second)->deviceRestore();
		}

		mUpdate = true;
	}

} // namespace MyGUI
