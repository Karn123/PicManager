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

	//myFile.open("info.txt");  //1809��
 	myFile.open("info.csv");//3575��
	
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
		//����Ļ�����ʾ��Ϣ
		cout<<'.';
		i++;
	}

    cout<<i<<endl;
	//cout<<endl;
	MyList=whole_list;  //MyListΪ�㼣����
	this->insert(whole_list);//��ͼƬ��ϢList���뵽����
	this->insert_1(whole_list);//��ͼƬ��ϢList���뵽��1��
	this->insert_2(whole_list);//��ͼƬ��ϢList���뵽��2��
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
	}//�жϹؼ����Ƿ����

	this->Remove(data.the_key());
	//keyΨһ�������ǿ���ÿ���ڵ�Listֻ��һ�����ݣ�
	//����ֻҪ����key�����ҵ����㽫���ɾ��
	this->Remove_1(data); 
	this->Remove_2(data);//��������������
	return success;
}


Error_code PictureInfoList::replace(const PictureRecord &data)  
{	   
	//�жϹؼ����Ƿ����
	PictureRecord m;
	if(searchByKey(data.the_key(),m) == notPresent) 
	{
		cout<<"This picLibrary is not present!"<<endl<<endl;
		return notPresent;
	}
    
	//����������������޸�detail��title����ͼ��λ�ã���������Ϣ������ô����
	//�������������OthersType��������һ�����캯�����������������������޸ĵı�������
	this->Replace(data);
	this->Replace_1(data);
	this->Replace_2(data);
	return success;
}



Error_code PictureInfoList::searchByTitle(string title,List<Node<PictureRecord>*> &list_title)
{
	return  this->search_1(title,list_title);
}



Error_code PictureInfoList::searchByLocation(string location, List<Node<PictureRecord>*> &list_location /*��Ӧ��¼��ָ���ַ����*/)
{
	return  this->search_2(location,list_location);
}


Error_code PictureInfoList::searchByKey(string &filename,PictureRecord &r)  
{
	return this->search(filename,r);
}

//�㼣ͳ��

Error_code PictureInfoList::searchByFootmark(LocationGraph<600> &map)
{
	
   if(MyList.size()==0) 
   {
		return notPresent;
	}
    
    map.ClearPicPtr();
	//����ͼ������ԭ�еĽڵ���ͼƬ�Ĺ�ϵ��գ�Ȼ���ٽ����µĵ�ַ��Ӧ��ϵ��

	Node<PictureRecord>  *ptr;
  
	//���� 
	int n=0;
	for(int i=0;i<MyList.size();i++)
	{
		if(MyList.retrieve(i,ptr)==success)
	    {
			if (ptr->entry.the_map()==map.the_name()) 
			{
             if(map.InserPicPtr(ptr->entry.the_location(),ptr) == notPresent)
				 cout<<ptr->entry.the_key()<<"foot mark fail!"<<endl; 
			 //˵��ͼƬ�ϼ�¼�ĵص��ڵ�ͼ�ڵ��в����ڣ��ʱ���
			 else
				 n++;
			}      		
			else if(ptr->entry.the_hmap()==map.the_name())
			{
			 if(map.InserPicPtr(ptr->entry.the_hlocation(),ptr)==notPresent) //˵��ͼƬ�ϼ�¼�ĵص��ڵ�ͼ�ڵ��в����ڣ��ʱ���
				 cout<<ptr->entry.the_key()<<"foot mark fail!"<<endl; 
			 else
				 n++;
			}
		}
	}

	if(n>0) return success;
	else return notPresent;
}

//info�ļ���ͼƬ���е�ͼƬ��Ϣһһ��Ӧ��ϵ����������֤
Error_code  PictureInfoList::integrationCheck(string filename)
{
	ifstream inFile;	
	inFile.open(filename.c_str());
	if(!inFile)
	{
	    cout<<"Open picture name files error!"<<endl;
		return notPresent;
	}

	//�����е�ͼƬ�ļ����ƶ��뵽picNames��List��
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
	
	//������е�ͼƬ�ļ��Ƿ���info�д��ڣ�����������������ļ���
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
	//���info��¼��ͼƬ��Ϣ�Ƿ��ж�Ӧ��ͼƬ�ļ����ڣ�����������������ļ���
   
	outFile.open("infoNoPicture.txt");
    int count=0;
	for(int j=0;j<picNamesList.size();j++)
	{
	    picNamesList.retrieve(j,picNames);
		Error_code Result=this->search(picNames,m);
        //�����Ƿ����ҵ�ͼƬ

        //��û�ж�Ӧ��ͼƬ�ļ�
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
	
	this->inorder();   //����ͼƬ��filename��ӡ

	outFile.close();
}

void PictureInfoList::clear()
{
	root=NULL;
	root_1=NULL;
	root_2=NULL;
}