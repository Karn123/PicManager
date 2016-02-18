
#pragma once

#include"LocationGraph.cpp"
#include"Search_tree.cpp"

class PictureInfoList: public Search_tree_By_Key<List<Node<PictureRecord>*>>,
					   public Search_tree_By_Title<List<Node<PictureRecord>*>>,
					   public Search_tree_By_Location<List<Node<PictureRecord>*>>
{//拥有Search_tree的属性和操作
public:
	PictureInfoList();
	Error_code initialization(List<Node<PictureRecord>*> &whole_list);//负责完成插入功能
	Error_code Insert(const PictureRecord &data);
	Error_code remove(PictureRecord &data);
	Error_code replace(const PictureRecord &data); 
	Error_code searchByTitle(string title,List<Node<PictureRecord>*> &list_title );
	Error_code searchByLocation(string location,List<Node<PictureRecord>*> &list_location);
	Error_code searchByFootmark(LocationGraph<600> &map/*inout*/);
    Error_code integrationCheck(string filename);
	void clear();
	//void sort();  排序会使树的高度增高，所以不使用
	void print();
	Error_code searchByKey(string &filename,PictureRecord &r);
private:
	//查找辅助函数
	
	List<Node<PictureRecord>*> MyList;
};