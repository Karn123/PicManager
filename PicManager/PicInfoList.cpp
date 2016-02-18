#pragma once

#include"PicInfoList.h"
#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
using namespace std;

PictureInfoList::PictureInfoList()
{	

}

PictureRecord getOnePicRecorder(ifstream & myFile)
{
 	string picname;
	OthersType ot;
	char ch;
	
    //filename;
	picname="";
	myFile.get(ch);
	while(ch!=',') {
		picname=picname+ch;
		myFile.get(ch);
	}

	myFile>>ot.height;
	myFile.get();
	
	myFile>>ot.width;
	myFile.get();

	myFile>>ot.size;
	myFile.get();

	myFile>>ot.time;
	myFile.get();

	//detail;
	ot.detail = "";
	myFile.get(ch);
	while(ch!=',') {
		ot.detail=ot.detail+ch;
		myFile.get(ch);
	}

	//title;
	ot.titleEn = "";
	myFile.get(ch);
	while(ch!=',') {
		ot.titleEn=ot.titleEn+ch;
		myFile.get(ch);
	}
    
	//map;
	ot.map= "";
	myFile.get(ch);
	while(ch!=',') 
	{
		ot.map=ot.map+ch;
		myFile.get(ch);
	}
	
	//location;
	ot.location= "";
	myFile.get(ch);
	while(ch!=',') {
		ot.location=ot.location+ch;
		myFile.get(ch);
	}
	//hmap;
	ot.hmap= "";
	myFile.get(ch);
	while(ch!=',') {
		ot.hmap=ot.hmap+ch;
		myFile.get(ch);
	}
	//hlocation;
	ot.hlocation= "";
	myFile.get(ch);
	while(ch!=',') 
	{
		ot.hlocation=ot.hlocation+ch;
		myFile.get(ch);
	}
	
	getline(myFile,ot.owner);

	PictureRecord item(picname,ot);
    return item;
}

Error_code PictureInfoList::initialization(List<Node<PictureRecord>*> &whole_list)
{
	ifstream myFile;
	int number;

	//myFile.open("info.txt");  //1809张
 	myFile.open("info.csv");//3575张
	
	if(!myFile)
	{
		cout<<"open file failed!"<<endl;
		return notPresent;
	}

	myFile>>number;
	if (myFile)
	{
	    
	}
    
	int i=0;
	while(myFile) 
	{
		myFile.get();

        PictureRecord  item=getOnePicRecorder(myFile);
		Node<PictureRecord> *p=new Node<PictureRecord>;
		p->entry=item;
		whole_list.insert(whole_list.size(),p);
        myFile>>number;	
		//在屏幕输出提示信息
		cout<<'.';
		i++;
	}

    cout<<i<<endl;
	//cout<<endl;
	MyList=whole_list;  //MyList为足迹服务
	this->insert(whole_list);//将图片信息List插入到树中
	this->insert_1(whole_list);//将图片信息List插入到树1中
	this->insert_2(whole_list);//将图片信息List插入到树2中
	return success;
}

Error_code PictureInfoList::Insert(const PictureRecord &data)
{
	PictureRecord m;
	Node<PictureRecord> *p=new Node<PictureRecord>;
	p->entry=data;
	
	if(this->insert_pic(p)==success)
	{
		this->insert_1_pic(p);
		this->insert_2_pic(p);
		return success;
	}
	else return notPresent;
}

Error_code PictureInfoList::remove(PictureRecord &data)
{
	PictureRecord m;
	if(searchByKey(data.the_key(),m)==notPresent) 
	{
		cout<<"This picLibrary is not present!"<<endl<<endl;
		return notPresent;
	}//判断关键码是否存在

	this->Remove(data.the_key());
	//key唯一，所以那棵树每个节点List只有一个数据，
	//所以只要根据key便能找到结点便将结点删除
	this->Remove_1(data); 
	this->Remove_2(data);//更新另外两棵树
	return success;
}


Error_code PictureInfoList::replace(const PictureRecord &data)  
{	   
	//判断关键码是否存在
	PictureRecord m;
	if(searchByKey(data.the_key(),m) == notPresent) 
	{
		cout<<"This picLibrary is not present!"<<endl<<endl;
		return notPresent;
	}
    
	//考虑如果仅仅允许修改detail，title，地图，位置，属主等信息，该怎么做？
	//解决方案：可在OthersType里面声明一个构造函数，参数仅仅有上述允许修改的变量即可
	this->Replace(data);
	this->Replace_1(data);
	this->Replace_2(data);
	return success;
}



Error_code PictureInfoList::searchByTitle(string title,List<Node<PictureRecord>*> &list_title)
{
	return  this->search_1(title,list_title);
}



Error_code PictureInfoList::searchByLocation(string location, List<Node<PictureRecord>*> &list_location /*对应记录的指针地址链表*/)
{
	return  this->search_2(location,list_location);
}


Error_code PictureInfoList::searchByKey(string &filename,PictureRecord &r)  
{
	return this->search(filename,r);
}

//足迹统计

Error_code PictureInfoList::searchByFootmark(LocationGraph<600> &map)
{
	
   if(MyList.size()==0) 
   {
		return notPresent;
	}
    
    map.ClearPicPtr();
	//将地图对象中原有的节点与图片的关系清空，然后再建立新的地址对应关系。

	Node<PictureRecord>  *ptr;
  
	//查找 
	int n=0;
	for(int i=0;i<MyList.size();i++)
	{
		if(MyList.retrieve(i,ptr)==success)
	    {
			if (ptr->entry.the_map()==map.the_name()) 
			{
             if(map.InserPicPtr(ptr->entry.the_location(),ptr) == notPresent)
				 cout<<ptr->entry.the_key()<<"foot mark fail!"<<endl; 
			 //说明图片上记录的地点在地图节点中不存在，故报错
			 else
				 n++;
			}      		
			else if(ptr->entry.the_hmap()==map.the_name())
			{
			 if(map.InserPicPtr(ptr->entry.the_hlocation(),ptr)==notPresent) //说明图片上记录的地点在地图节点中不存在，故报错
				 cout<<ptr->entry.the_key()<<"foot mark fail!"<<endl; 
			 else
				 n++;
			}
		}
	}

	if(n>0) return success;
	else return notPresent;
}

//info文件与图片库中的图片信息一一对应关系的完整性验证
Error_code  PictureInfoList::integrationCheck(string filename)
{
	ifstream inFile;	
	inFile.open(filename.c_str());
	if(!inFile)
	{
	    cout<<"Open picture name files error!"<<endl;
		return notPresent;
	}

	//将所有的图片文件名称读入到picNames的List中
	List<string> picNamesList;
    PictureRecord tmpPR;

	string picNames;
	getline(inFile,picNames);
	//inFile>>picNames;

	while(inFile)
	{
		picNamesList.insert(picNamesList.size(),picNames);
        getline(inFile,picNames);
	}
	
	//检查所有的图片文件是否在info中存在，若不存在则输出该文件名
	ofstream outFile;	
	outFile.open("pictureNoInfo.txt");
	PictureRecord m;
	for(int i=0; i<picNamesList.size();i++)
	{
		picNamesList.retrieve(i,picNames);
        
		if(searchByKey(picNames,m)==notPresent)
		{
			cout<<picNames<<endl;
			outFile<<picNames<<endl;
		}
	
	}

	outFile.close();

	cout<<"***********************************"<<endl;
	//检查info记录的图片信息是否有对应的图片文件存在，若不存在则输出该文件名
   
	outFile.open("infoNoPicture.txt");
    int count=0;
	for(int j=0;j<picNamesList.size();j++)
	{
	    picNamesList.retrieve(j,picNames);
		Error_code Result=this->search(picNames,m);
        //看看是否能找到图片

        //若没有对应的图片文件
		if (Result==notPresent)
		{
			count++;
			//cout<<count<<":"<<tmpPR.the_key()<<endl;
			outFile<<j<<":"<<picNames<<endl;
		}
	
	}
	
	outFile.close();

	return success;

}


void PictureInfoList::print()
{
	ofstream outFile;	
	outFile.open("MyInfo.txt");
	
	this->inorder();   //按照图片的filename打印

	outFile.close();
}

void PictureInfoList::clear()
{
	root=NULL;
	root_1=NULL;
	root_2=NULL;
}