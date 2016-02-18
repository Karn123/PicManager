#include "PicRecord.h"


PictureRecord::PictureRecord()
{
   key = "none";
}

PictureRecord::PictureRecord(string k, OthersType others)
{
   key = k;
   info = others;
}
	
string PictureRecord::the_key() const
{
   return key;
}

int PictureRecord::the_height() const
{
   return info.height;
}

int PictureRecord::the_width() const
{
   return info.width;
}

int PictureRecord::the_size() const
{
   return info.size;
}

long PictureRecord ::the_time() const
{
   return info.time;
}

string PictureRecord ::the_detail() const
{
   return info.detail;
}

string PictureRecord::the_titleEn() const
{
   return info.titleEn;
}

string PictureRecord::the_map() const
{
   return info.map;
}

string PictureRecord ::the_location() const
{
   return info.location;
}

string PictureRecord ::the_hmap() const
{
   return info.hmap;
}

string PictureRecord ::the_hlocation() const
{
   return info.hlocation;
}

string PictureRecord ::the_owner() const
{
   return info.owner;
}

OthersType PictureRecord ::the_others() const
{
   return info;
}


bool operator > (const PictureRecord  &x, const PictureRecord  &y)
{
	return x.the_key()>y.the_key();
}

bool operator < (const PictureRecord  &x, const PictureRecord  &y)
{
	return x.the_key()<y.the_key();
}

bool operator <= (const PictureRecord  &x, const PictureRecord  &y)
{
	return x.the_key()<=y.the_key();
}

bool operator >= (const PictureRecord  &x, const PictureRecord  &y)
{
	return x.the_key()>=y.the_key();
}

bool operator ==(const PictureRecord  &x, const PictureRecord  &y)
{
	return x.the_titleEn()==y.the_titleEn();//!!!注意此处不是比较the_key()
}

ostream & operator << (ostream &output, PictureRecord  &x)
{
	output<<x.the_key()<<", "<<x.the_height()<<", "<<x.the_width()
		 <<", "<<x.the_size()<<", "<<x.the_time()<<", "<<x.the_detail()
		 <<", "<<x.the_titleEn()<<", "<<x.the_map()<<", "<<x.the_location()
		 <<", "<<x.the_hmap()<<", "<<x.the_hlocation()<<", "<<x.the_owner();
	output<<endl<<endl;
	return output;
}

