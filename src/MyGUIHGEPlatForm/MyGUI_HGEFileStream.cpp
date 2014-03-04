#include "mygui_hgefilestream.h"

namespace MyGUI
{
	HGEFileStream::HGEFileStream()
		:DataStream()
		,mStream(nullptr)
	{
	}

	HGEFileStream::HGEFileStream(std::stringstream* _stream)
		:DataStream(_stream)
		,mStream(_stream)
	{
	}

	HGEFileStream::~HGEFileStream()
	{
		if (mStream != nullptr)
		{
			mStream->clear();
			delete mStream;
			mStream = nullptr;
		}
	}

	//size_t HGEFileStream::size()
	//{
	//	if (mStream == nullptr) return 0;
	//	if (mSize == (size_t) - 1)
	//	{
	//		mStream->seekg (0, std::ios::end);
	//		mSize = (size_t)mStream->tellg();
	//		mStream->seekg (0, std::ios::beg);
	//	}
	//	return mSize;
	//}

	//bool HGEFileStream::eof()
	//{
	//	return mStream == nullptr ? true : mStream->eof();
	//}

	//void HGEFileStream::readline(std::string& _source, Char _delim)
	//{
	//	if (mStream == nullptr) return;
	//	std::getline(*mStream, _source, (char)_delim);
	//}

	//size_t HGEFileStream::read(void* _buf, size_t _count)
	//{
	//	if (mStream == nullptr) return 0;
	//	size_t count = std::min(size(), _count);
	//	mStream->read((char*)_buf, count);
	//	return count;
	//}

}