/*!
	@file
	@author		Losev Vasiliy aka bool
	@date		06/2009
*/

#include "MyGUI_HGEVertexBuffer.h"
#include "MyGUI_VertexData.h"
#include "MyGUI_HGEDiagnostic.h"

namespace MyGUI
{

	const size_t VERTEX_IN_QUAD = 6;
	const size_t RENDER_ITEM_STEEP_REALLOCK = 5 * VERTEX_IN_QUAD;

	HGEVertexBuffer::HGEVertexBuffer(HGERenderManager* _pRenderManager) :
		mNeedVertexCount(0),
		mVertexCount(RENDER_ITEM_STEEP_REALLOCK),
		pRenderManager(_pRenderManager),
		mpBuffer(NULL)
	{
		mpHGE = hgeCreate(HGE_VERSION);
	}

	HGEVertexBuffer::~HGEVertexBuffer()
	{
		destroy();
		mpHGE->Release();
	}

	void HGEVertexBuffer::setVertexCount(size_t _count)
	{
		if (_count != mNeedVertexCount)
		{
			mNeedVertexCount = _count;
			resize();
		}
	}

	size_t HGEVertexBuffer::getVertexCount()
	{
		return mNeedVertexCount;
	}

	Vertex* HGEVertexBuffer::lock()
	{
		return mpBuffer;
	}

	void HGEVertexBuffer::unlock()
	{
	}

	bool HGEVertexBuffer::setToStream(size_t stream)
	{
		return false;
	}

	bool HGEVertexBuffer::create()
	{
		mpBuffer = new Vertex[mNeedVertexCount];
		memset(mpBuffer,0,mNeedVertexCount*sizeof(Vertex));
		if (mpBuffer) return true;
		return false;
	}

	void HGEVertexBuffer::destroy()
	{
		if (mpBuffer)
		{
			delete mpBuffer;
			mpBuffer = nullptr;
		}
	}

	void HGEVertexBuffer::resize()
	{
		if (mpBuffer)
			destroy();
		create();
	}

} // namespace MyGUI
