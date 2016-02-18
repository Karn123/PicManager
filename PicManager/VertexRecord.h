#ifndef VERTEXRECORD
#define VERTEXRECORD
#include <string>
#include<iostream>
using namespace std;

class VertexRecord
{
private:
	//½Úµã±àºÅ
	int no;
	
	int x;
	int y;
	string location;
	string detail;
public:
	VertexRecord()
	{
	   no=x=y=0;
	   location = detail = "";
	}

	VertexRecord(int n,int x1, int y1, string location1, string detail1)
	{
	
	   no = n;
	   x = x1;
	   y = y1;
	   location = location1; 
	   detail = detail1;
	}

	int the_no(){ return no;}
	int the_x(){return x;}
	int the_y(){return y;}
	string the_location(){return location;}
	string the_detail(){return detail;}

	void set_location(string loc){location = loc;}
	void set_detail(string del){detail =del;}
};

#endif