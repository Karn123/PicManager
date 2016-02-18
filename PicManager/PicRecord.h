#ifndef PIC_RECORD
#define PIC_RECORD

#include<iostream>
#include<string>
using namespace std;

struct OthersType
{	
	OthersType(){}
    int height;
	int width;
	int size;
	long time;//不能晚于2038年1月18日19时14分07秒
	string detail;//详细描述
	string titleEn;//英文title
    string map;//所属地图
	string location;//地图中的位置
	string hmap;//所属上级地图
	string hlocation;//hmap中的位置
	string owner;//属主
};

class PictureRecord {
public:
	PictureRecord();
	PictureRecord(string k, OthersType others);
	string the_key() const;
	int the_height() const;
	int the_width() const;
	int the_size() const;
	long the_time() const;
	string the_detail() const;
	string the_titleEn() const;
	string the_map() const;
	string the_location() const;
	string the_hmap() const;
	string the_hlocation() const;
	string the_owner() const;
    OthersType the_others() const;
	OthersType info;//see defintion of OthersType
private:
	string key; //filename
	
};

bool operator > (const PictureRecord  &x, const PictureRecord  &y);
bool operator < (const PictureRecord  &x, const PictureRecord  &y);
bool operator <= (const PictureRecord  &x, const PictureRecord  &y);
bool operator >= (const PictureRecord  &x, const PictureRecord  &y);
bool operator == (const PictureRecord  &x, const PictureRecord  &y);
ostream & operator << (ostream &output, PictureRecord  &x);


#endif