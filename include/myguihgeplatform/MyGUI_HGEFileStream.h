#pragma once

#include "MyGUI_Prerequest.h"
#include "MyGUI_DataStream.h"
#include <sstream>

namespace MyGUI
{
	class HGEFileStream:
		public DataStream
	{
	public:
		HGEFileStream();
		HGEFileStream(std::stringstream* _stream);
		virtual ~HGEFileStream();
		
		//virtual bool eof();
		//virtual size_t size();
		//virtual void readline(std::string& _source, Char _delim);
		//virtual size_t read(void* _buf, size_t _count);
	private:
		//size_t mSize;
		std::stringstream* mStream;
	};
}