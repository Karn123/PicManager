#include "PdfJpeg.h"

PdfJpeg::PdfJpeg(void):weidth(0),height(0),buffer(NULL),length(0),file(NULL),name(NULL)
{
}

PdfJpeg::~PdfJpeg(void)
{
	delete[]buffer;
}

int PdfJpeg::ReadImage()
{
	if(file==NULL)
		return -1;
	if(strrchr(file,'.'))
		name=strrchr(file,'.')+1;
	if(!strcmp(name,".jpg")||!strcmp(name,".JPG"))
	{
		printf("%s文件,未被支持格式 \n" ,file);
		return -1;
	}
	//获取文件名
	if(strrchr(file,'\\'))
		name=strrchr(file,'\\')+1;
	else
		name=file;
	//读取jpeg数据
	FILE *filejpeg;
	//errno_t err=fopen_s(&filejpeg,file,"rb");
	 filejpeg=fopen(file,"rb");
	if(NULL == filejpeg)
	{
		printf("读取%s文件,产生错误\n" ,file);
		return -1;
	}
	fseek(filejpeg,0,SEEK_END);
	length=ftell(filejpeg);
	buffer=new unsigned char[length];
	fseek(filejpeg,0,SEEK_SET);
	fread(buffer,length,1,filejpeg);
	fclose(filejpeg);
	return GetSize(buffer,length);
}

int PdfJpeg::GetSize(unsigned char * buffer,long length)
{
	if(!buffer)
		return -1;
	unsigned char * temp=buffer+length,*temp1=buffer;
	unsigned char ff,type=0xff;
	int m_ret=-1,m_pos=0,m_hpx=0,m_wpx=0,uits=0;
	if(*buffer++!=0xff||*buffer++!=0xd8)
	{
		printf("此非jepg图片\n");
		return -1;
	}
	while(temp>buffer&&type!=0xDA)
	{
		do 
		{
			ff=*buffer++;
		} while (ff!=0xff);
		do 
		{
			type=*buffer++;
		} while (type==0xff);
		switch(type)
		{
		case 0x00:
		case 0x01:
		case 0xD0:
		case 0xD1:
		case 0xD2:
		case 0xD3:
		case 0xD4:
		case 0xD5:
		case 0xD6:
		case 0xD7:
			break;
		case 0xC0://SOF0段
			temp1=buffer;
			m_pos=(*buffer++)<<8;
			m_pos+=*buffer++;
			buffer++; //舍弃精度值
			height=(*buffer++)<<8;
			height+=*buffer++;
			weidth=(*buffer++)<<8;
			weidth+=*buffer;
			m_ret++;
			break;
		case 0xE0: //APP0段
			temp1=buffer;
			m_pos=(*buffer++)<<8;
			m_pos+=*buffer++;
			buffer=buffer+7;        //丢弃APP0标记(5bytes)以及主版本号(1bytes)及次版本号(1bytes)
			uits=*buffer++;  //0: 无单位,units=1:点数/英寸,units=2:点数/厘米
			m_wpx=(*buffer++)<<8;
			m_wpx+=*buffer++;
			m_hpx=(*buffer++)<<8;
			m_hpx+=*buffer++;
			hpx=m_hpx*JepgSize(uits);
			wpx=m_wpx*JepgSize(uits);
			m_ret++;
			break;
		default:
			temp1=buffer;
			m_pos=(*buffer++)<<8;
			m_pos+=*buffer++;
			break;
		}
		buffer=temp1+m_pos;
	}
	return m_ret;
}