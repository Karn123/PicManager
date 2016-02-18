
#pragma once

#include"LinkedList.cpp"
#include"VertexRecord.h"
#include"PicRecord.h"


template <int graph_size>
class LocationGraph 
{
public:
	LocationGraph();

	Error_code Initialize(string mapname,string mappath);//读取graphVertex.txt，读取introuction.txt
	Error_code InserPicPtr(string location, const Node<PictureRecord >  * cptr);//增加地点与pic的对应关系
	void Print();//输出节点信息，及其节点与地点的对应关系信息；
	void ClearPicPtr();
	
	string the_name() const;
	void set_name(string name);

		//index为节点编号，vr为节点的基本信息，trackListPtr为该节点对应的照片列表；
    void get_trackByIndex(int index,VertexRecord& vr, const List <const Node<PictureRecord >  *>*& trackListPtr) const;
	int get_verterxCount() const; //即count
	void positionToNum(int x, int y,int& index, int& no) const;
private:

	Error_code  readVertexXY(string mappath); //读取节点的x，y轴信息。called by Initialize
	Error_code  readVertexInfo(string mappath);//读取节点的详细信息。called by Initialize
	Error_code SearchByNo(int no, int&pos, VertexRecord& vr) ;//查找指定编号no在list中的详细信息

	Error_code SearchByLocation(string location, int&pos, VertexRecord& vr) ;
    

	int count; //包含的节点数目；
	string name;//地图名称，如华师大，中国等
	//记录每个节点对应的图片的内存地址；
	List <const Node<PictureRecord>*>  picInfoPtrs[graph_size];
	//记录结点信息
	List<VertexRecord> vertexList; 
};
