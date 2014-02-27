/*!
	@file
	@author		Losev Vasiliy aka bool
	@date		06/2009
*/

#ifndef __MYGUI_HGE_VERTEX_BUFFER_H__
#define __MYGUI_HGE_VERTEX_BUFFER_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_IVertexBuffer.h"
#include "MyGUI_HGERenderManager.h"

#include "hge.h"

struct IDirect3DDevice8;
struct IDirect3DVertexBuffer8;

namespace MyGUI
{

	class HGEVertexBuffer : public IVertexBuffer
	{
	public:
		HGEVertexBuffer(HGERenderManager* _pRenderManager);
		virtual ~HGEVertexBuffer();

		virtual void setVertexCount(size_t _count);
		virtual size_t getVertexCount();

		virtual Vertex* lock();
		virtual void unlock();

	/*internal:*/
		virtual bool setToStream(size_t stream);

	private:
		bool create();
		void destroy();
		void resize();

	private:
		HGE* mpHGE;
		Vertex* mpBuffer;
		HGERenderManager* pRenderManager;

		size_t mVertexCount;
		size_t mNeedVertexCount;
	};

} // namespace MyGUI

#endif // __MYGUI_HGE_VERTEX_BUFFER_H__
