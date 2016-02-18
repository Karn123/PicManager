#include "LocationGraph.h"
#include <fstream>
#include <cmath>
#include<iostream>
using namespace std;

template <int graph_size>
LocationGraph<graph_size>::LocationGraph()
{
   count =0;
   name="none";
}

template <int graph_size>
void LocationGraph<graph_size>::get_trackByIndex(int index,
VertexRecord& vr/*out*/, const List<const Node<PictureRecord>*> *&trackListPtr/*out*/) const
{
	vertexList.retrieve(index,vr);
	trackListPtr = &picInfoPtrs[index];
}

template <int graph_size>
void LocationGraph<graph_size>::ClearPicPtr()
{
    for(int i=0; i<count; i++)
	{     
		picInfoPtrs[i].clear(); //清空每个节点对应的图片地址信息，以便重新建立相关的关系。
	}
}

template <int graph_size>
void LocationGraph<graph_size>::positionToNum(int x, int y,
int& index, int& no) const
{
	double mindis=100;
	no=-1;
	index=-1;

	for(int i=0;i<count;i++)
	{
	   //取出第i个点
	   VertexRecord tmp ;
	   vertexList.retrieve(i,tmp);
	   //计算第i个点到鼠标的距离
	   double value=(tmp.the_x()-x)*(tmp.the_x()-x)+(tmp.the_y()-y)*(tmp.the_y()-y);
	   double d= sqrt(value);

	   if(d<mindis)
	   {
	       no = tmp.the_no();
		   index = i;
		   mindis =d;
	   }
	
	}

	return;
}
 
 template <int graph_size>
 int LocationGraph<graph_size>::get_verterxCount() const
 {//即count
   return count;
 }

  template <int graph_size>
 string LocationGraph<graph_size>::the_name() const
 {
   return name;
 }

template <int graph_size>
Error_code LocationGraph<graph_size>::Initialize(string mapname,string mappath)
{//读取graphVertex.txt，读取introuction.txt
    name = mapname;

	if(readVertexXY(mappath) == success)
	   return readVertexInfo(mappath);
   else
	   return notPresent;

}	

template <int graph_size>
Error_code LocationGraph<graph_size>::InserPicPtr(string location, const Node<PictureRecord>  *cptr)
{//增加地点与pic的对应关系
    int pos;
	VertexRecord vr;
	SearchByLocation(location,pos,vr);//查询是否存在；

	if(pos>=0)
	{
	     return picInfoPtrs[pos].insert(picInfoPtrs[pos].size(),cptr);
		 	
	}else{
	     return notPresent;
	}

}


template <int graph_size>
void LocationGraph<graph_size>::Print()
{//输出节点信息，及其节点与地点的对应关系信息；
	VertexRecord tmpVR;
	const Node<PictureRecord >* cptr;
	PictureRecord precord;
	for(int i=0; i<count; i++ )
	{
	if(picInfoPtrs[i].size()>0)
	{
	   vertexList.retrieve(i,tmpVR);
	   cout<<tmpVR.the_no()<<" "<<tmpVR.the_x()<<"  "<<tmpVR.the_y()<<" "
		   <<tmpVR.the_location()<<"  "<<picInfoPtrs[i].size()<<" ";
	   for(int j=0; j<picInfoPtrs[i].size();j++)
	   {
	      picInfoPtrs[i].retrieve(j,cptr);
	      precord = cptr->entry;
		  cout<<precord.the_key()<<"  ";
	   }
	   cout<<endl;
	}
	   
  }   		
}

template <int graph_size>
Error_code  LocationGraph<graph_size>::readVertexXY(string mappath)
{ //读取节点的x，y轴信息。called by Initialize
  ifstream infile;
  string filename = ".\\"+mappath+"\\"+"graphVertex.txt"; 
  infile.open(filename.c_str());
  
  if(!infile){
	  cout<<"Open graphVertex.txt file error!!"<<endl;
	  return notPresent;
  }

  int no,x,y;

  infile>>no>>x>>y;
  while(infile){
     VertexRecord vt(no,x,y,"",""); //默认情况下，地点名称和地点描述为空
	 vertexList.insert(vertexList.size(),vt);
	 count++;
	 infile>>no>>x>>y;
  }
  return success;
}

template <int graph_size>
Error_code LocationGraph<graph_size>::readVertexInfo(string mappath)
{//读取节点的详细信息。called by Initialize
  ifstream infile;
  string filename = ".\\"+mappath+"\\"+"introduction.txt";
  infile.open(filename.c_str());
   
  if(!infile)
  {
	  cout<<"Open introduction.txt file error!!"<<endl;
	  return notPresent;
  }
  
  int no,pos;
  string location,detail;
  VertexRecord vr;

  infile>>no>>location>>detail;
  while(infile)
  {
     SearchByNo(no, pos, vr);//查询是否存在；

	 if (pos >= 0 ){//若存在
	   vr.set_location(location);
	   vr.set_detail(detail);
       vertexList.replace (pos,vr);//更新name和detail	    
	 }
	 else{
	    cout<<"Becareful: veretex"<<no<<" doesn't exist."<<endl;
		return notPresent;
	 }
     	 
	  infile>>no>>location>>detail;
  }  

  return success;
}

template <int graph_size>
Error_code LocationGraph<graph_size>::SearchByNo(int no,int&pos,VertexRecord& vr)
{    
	VertexRecord tmpVR;
	pos = -1;
	if(vertexList.size()==0) 
	{
		return notPresent;
	}
	
	for (int i=0; i<vertexList.size();i++){
	    vertexList.retrieve(i,tmpVR);

		if(tmpVR.the_no() == no)
		{
			vr = tmpVR;
			pos = i;
		    return success;
		}
	}
	
	//至此，表示no的编号不存在
	return notPresent;
}

template <int graph_size>
Error_code LocationGraph<graph_size>::SearchByLocation(string location, int&pos, VertexRecord& vr)
{
    
	VertexRecord tmpVR;
	pos = -1;

	if(vertexList.size() == 0)
	{
		return notPresent;
	}
	
	for (int i=0; i<vertexList.size();i++)
	{
	    vertexList.retrieve(i,tmpVR);

		if(tmpVR.the_location() == location)
		{
			vr = tmpVR;
			pos = i;
		    return success;
		}
	}
	
	//至此，表示no的编号不存在
	return notPresent;
}