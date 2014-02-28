#pragma once
#include <vector>

namespace Show
{
	struct SliceInfo
	{
		//��Ƭ�����ģ������λ��
		float x,y;
		//��Ƭ��ͼƬ�ϵ�λ��
		float left,top,width,height;
	};

	struct SliceData
	{
		int index;
		//��Ƭ��ƫ��ֵ
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
		//֡��ƫ��ֵ��Ŀǰ��û����
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