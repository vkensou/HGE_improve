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
		PictureData(){tex = 0;_autodel = false;}
		PictureData(const wchar_t* file,HTEXTURE tex = 0,bool autodel = false);
		~PictureData();
		HTEXTURE tex;
		std::vector<SliceInfo> slices;
		std::vector<FrameInfo> frames;
		std::vector<AnimationInfo> animations;
		int LoadData(const wchar_t* file);
		void SetTexture(HTEXTURE tex,bool autodel = false);
		//此函数仅仅生成最简单的动画，且会清除已经当前已有的各种信息。
		//当前已设置纹理才有用
		//DeltaTime单位毫秒，内部会转换为秒
		bool SetAnimation(int nframes, float DeltaTime, int mode, float w, float h, float x=0, float y=0);
	private:
		bool _autodel;
	};
}