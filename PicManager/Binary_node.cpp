#include"Binary_node.h"
#include<iostream>
using namespace std;

template<class Entry>
Binary_node<Entry>::Binary_node()
{
	KEY="";
	left=NULL;
	right=NULL;
}

template<class Entry>
Binary_node<Entry>::Binary_node(/*Entry x,*/const string &Key)
{
	data=Entry;
	KEY=Key;
	left=NULL;
	right=NULL;
} 