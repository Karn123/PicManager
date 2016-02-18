#pragma once
#include <string.h>
#include <stdio.h>
#pragma warning(disable: 4244)

class PdfJpeg
{
public:
	PdfJpeg(void);
	~PdfJpeg(void);
	PdfJpeg( char *filename):
	weidth(0),height(0),buffer(NULL),length(0),file(filename?filename:NULL),name(NULL){}
private:
	//jpeg宽度
	int weidth; 
	//jpeg高度
	int height; 
	 //jpeg数据
	unsigned char *buffer;
	//jpeg数据长度
	long length; 
	//jpeg文件名和路径
	char *file;  
	//jpeg文件名
	char *name;  
	PdfJpeg& operator=(const PdfJpeg &j);
	//获取jpeg图片尺寸
	int GetSize(unsigned char * buffer,long length);
	float inline JepgSize(int x)
	{
		return x!=2?1:2.56;
	}
	//垂直像素点
	float hpx;
	//水平像素点
	float wpx;
public:
	//读取jpeg文件,失败返回-1,成功返回1
	int ReadImage();
	int inline GetWidth() const
	{
		return weidth;
	}

	int inline GetHeight() const
	{
		return height;
	}

	unsigned char inline *GetData() const
	{
		return buffer;
	}

	long inline GetDataLength() const
	{
		return length;
	}

	char * GetFileName() const
	{
		return name;
	}

	float inline GetHDpi()
	{
		return hpx;
	}

	float inline GetWDpi()
	{
		return wpx;
	}

};
