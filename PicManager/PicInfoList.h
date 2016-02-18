
#pragma once

#include"LocationGraph.cpp"
#include"Search_tree.cpp"

class PictureInfoList: public Search_tree_By_Key<List<Node<PictureRecord>*>>,
					   public Search_tree_By_Title<List<Node<PictureRecord>*>>,
					   public Search_tree_By_Location<List<Node<PictureRecord>*>>
{//ӵ��Search_tree�����ԺͲ���
public:
	PictureInfoList();
	Error_code initialization(List<Node<PictureRecord>*> &whole_list);//������ɲ��빦��
	Error_code Insert(const PictureRecord &data);
	Error_code remove(PictureRecord &data);
	Error_code replace(const PictureRecord &data); 
	Error_code searchByTitle(string title,List<Node<PictureRecord>*> &list_title );
	Error_code searchByLocation(string location,List<Node<PictureRecord>*> &list_location);
	Error_code searchByFootmark(LocationGraph<600> &map/*inout*/);
    Error_code integrationCheck(string filename);
	void clear();
	//void sort();  �����ʹ���ĸ߶����ߣ����Բ�ʹ��
	void print();
	Error_code searchByKey(string &filename,PictureRecord &r);
private:
	//���Ҹ�������
	
	List<Node<PictureRecord>*> MyList;
};