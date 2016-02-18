#pragma once

#include<string>

template<class Entry>
struct Binary_node
{
   	Binary_node();
	Binary_node(const std::string &Key);
	Binary_node<Entry> *left;
	Binary_node<Entry> *right;
	std::string KEY; 
	Entry data; 
};