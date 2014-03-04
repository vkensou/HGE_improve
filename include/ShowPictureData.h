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
		PictureData(){tex = 0;_autodel = false;}
		PictureData(const wchar_t* file,HTEXTURE tex = 0,bool autodel = false);
		~PictureData();
		HTEXTURE tex;
		std::vector<SliceInfo> slices;
		std::vector<FrameInfo> frames;
		std::vector<AnimationInfo> animations;
		int LoadData(const wchar_t* file);
		void SetTexture(HTEXTURE tex,bool autodel = false);
		//�˺�������������򵥵Ķ������һ�����Ѿ���ǰ���еĸ�����Ϣ��
		//��ǰ����������������
		//DeltaTime��λ���룬�ڲ���ת��Ϊ��
		bool SetAnimation(int nframes, float DeltaTime, int mode, float w, float h, float x=0, float y=0);
	private:
		bool _autodel;
	};
}