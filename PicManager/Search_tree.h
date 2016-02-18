#pragma once

#include"LinkedList.cpp"
#include"Binary_node.cpp"
#include"PicRecord.h"

template<class Entry>
class Search_tree_By_Key
{
public:
		Search_tree_By_Key()
		{
			root=NULL;
		} //Constructor
		
		//Search_tree_By_Key(const List<Node<PictureRecord>*> &list);
		Error_code insert(const List<Node<PictureRecord>*> &new_data);
			//向树中插入一个List结点
		Error_code insert_pic(Node<PictureRecord> *&new_data);
		//向树中插入一个PictureRecord
		Error_code Remove(string &Key);	
		Error_code search(string &Key,PictureRecord &x) ;
		Error_code Replace(const PictureRecord &new_data);
		void inorder();
		void print_node(Binary_node<List<Node<PictureRecord>*>> *sub_root);
private:
	void recursive_inorder(Binary_node<List<Node<PictureRecord>*>> *sub_root);
    
	Binary_node<List<Node<PictureRecord>*>> *search_for_node(Binary_node<List<Node<PictureRecord>*>>* &sub_root,string &Key) const; 
	
	Error_code search_and_destroy(Binary_node<List<Node<PictureRecord>*>>* &sub_root,
	  string &Key);
	
    Error_code search_and_insert(Binary_node<List<Node<PictureRecord>*>> *&sub_root,
	 Node<PictureRecord>* &new_data);
	
	Error_code remove_root(Binary_node<List<Node<PictureRecord>*>>* &sub_root);
protected:
	Binary_node<List<Node<PictureRecord>*>>  *root;
};



template<class Entry>
class Search_tree_By_Title
{
public:
		Search_tree_By_Title()
		{
			root_1=NULL;
		} //Constructor
		
		//Search_tree_By_Title(const List<Node<PictureRecord>*> &list);
		Error_code insert_1(const List<Node<PictureRecord>*> &new_data);
			//向树中插入一个List结点
		Error_code insert_1_pic(Node<PictureRecord> *&new_data);
		//向树中插入一个PictureRecord
		Error_code Remove_1(PictureRecord &new_data);	
		Error_code search_1(string &Title,List<Node<PictureRecord>*> &titleList/*out*/);
		Error_code Replace_1(const PictureRecord &new_data);
		void inorder_1();
		void print_node_1(Binary_node<List<Node<PictureRecord>*>> *sub_root);
private:
	void recursive_inorder_1(Binary_node<List<Node<PictureRecord>*>> *sub_root);
    
	Binary_node<List<Node<PictureRecord>*>> *search_for_node_1(Binary_node<List<Node<PictureRecord>*>>* &sub_root,string &Title) const; 
	
	Error_code search_and_destroy_1(Binary_node<List<Node<PictureRecord>*>>* &sub_root,
	  string &Title,PictureRecord &new_data);
	
    Error_code search_and_insert_1(Binary_node<List<Node<PictureRecord>*>> *&sub_root,
	 Node<PictureRecord>* &new_data);
	
	Error_code remove_root_1(Binary_node<List<Node<PictureRecord>*>>* &sub_root,
							PictureRecord &new_data);
protected:
	Binary_node<List<Node<PictureRecord>*>>  *root_1;
};


template<class Entry>
class Search_tree_By_Location
{
public:
		Search_tree_By_Location()
		{
			root_2=NULL;
		} //Constructor
		
		//Search_tree_By_Title(const List<Node<PictureRecord>*> &list);
		Error_code insert_2(const List<Node<PictureRecord>*> &new_data);
			//向树中插入一个List结点
		Error_code insert_2_pic(Node<PictureRecord> *&new_data);
		Error_code Remove_2(PictureRecord &new_data);	
		Error_code search_2(string &Location,List<Node<PictureRecord>*> &locationList/*out*/);
		Error_code Replace_2(const PictureRecord &new_data);
		void inorder_2();
		void print_node_2(Binary_node<List<Node<PictureRecord>*>> *sub_root);
private:
	void recursive_inorder_2(Binary_node<List<Node<PictureRecord>*>> *sub_root);
    
	Binary_node<List<Node<PictureRecord>*>> *search_for_node_2(Binary_node<List<Node<PictureRecord>*>>* &sub_root,
		string &Location) const; 
	
	Error_code search_and_destroy_2(Binary_node<List<Node<PictureRecord>*>>* &sub_root,
	  string &Location,PictureRecord &new_data);

    Error_code search_and_insert_2(Binary_node<List<Node<PictureRecord>*>> *&sub_root,
	 Node<PictureRecord>* &new_data);
	
	Error_code remove_root_2(Binary_node<List<Node<PictureRecord>*>>* &sub_root,
							PictureRecord &new_data);
protected:
	Binary_node<List<Node<PictureRecord>*>>  *root_2;
};