#pragma once
#include <vector>

namespace Show
{
	struct SliceInfo
	{
		//切片的中心，是相对位置
		float x,y;
		//切片在图片上的位置
		float left,top,width,height;
	};

	struct SliceData
	{
		int index;
		//切片的偏移值
		int x,y;
	};

	struct FrameInfo
	{
		std::vector<SliceData> slices;
		float w,h;
	};

	struct FrameData
	{
		int index;
		float time;
		//帧的偏移值，目前尚没有用
		int x ,y;
	};

	struct AnimationInfo
	{
		std::vector<FrameData> frames;
		int mode;
		float w,h;
	};

	class PictureData
	{
	public:
		PictureData(){tex = 0;};
		HTEXTURE tex;
		std::vector<SliceInfo> slices;
		std::vector<FrameInfo> frames;
		std::vector<AnimationInfo> animations;
		int LoadData(const wchar_t* file);
	};
}