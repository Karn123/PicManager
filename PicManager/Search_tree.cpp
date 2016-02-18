#include"Search_tree.h"

//****************************************************************************//
//****************************************************************************//
//*************************Search_Tree_By_Key*********************************//
//****************************************************************************//
//****************************************************************************//

template <class Entry> 
Error_code Search_tree_By_Key<Entry>::search(string &Key,PictureRecord &x) 
{
   	Error_code result=success; 
	Node<PictureRecord> *s;
   	Binary_node<List<Node<PictureRecord>*>> *found=search_for_node(root,Key); 
	if(found==NULL)  result=notPresent; 
	else
	{
		found->data.retrieve(0,s);
		x=s->entry;
		result=success;
	}
		return result; 
}

template <class Entry> 
Binary_node<List<Node<PictureRecord>*>>  *Search_tree_By_Key<Entry>::search_for_node
(Binary_node<List<Node<PictureRecord>*>> *&sub_root,string &Key)const 
{ 
	if(sub_root==NULL||sub_root->KEY==Key)
		return sub_root;
	else if(sub_root->KEY<Key) 
	return search_for_node(sub_root->right,Key); 
	else return search_for_node(sub_root->left,Key);  
}

template <class Entry> 
Error_code Search_tree_By_Key<Entry>::insert(const List<Node<PictureRecord>*> &new_data)
{
	Node<PictureRecord>* r;
	Error_code result;
	for(int i=0;i<new_data.size();i++)
	{
		new_data.retrieve(i, r);
		result=search_and_insert(root,r);
	}
	return result;
}

template <class Entry> 
Error_code Search_tree_By_Key<Entry>::insert_pic(Node<PictureRecord> *&new_data)
{
	return search_and_insert(root,new_data);
}

template <class Entry> 
Error_code Search_tree_By_Key<Entry>::search_and_insert(Binary_node<List<Node<PictureRecord>*>> 
*&sub_root /*inout*/, Node<PictureRecord>* &new_data/*in*/) 
{ //递归找到待插结点，记录Tree的待插结点KEY值

	if(sub_root==NULL) 
	{
	  sub_root=new Binary_node<List<Node<PictureRecord>*>>;
	  sub_root->data.insert(0,new_data);
	  sub_root->KEY=new_data->entry.the_key();
	  return success; 
	} 	
	else if(new_data->entry.the_key()<sub_root->KEY) 
	return search_and_insert(sub_root->left,new_data); 
	else if(new_data->entry.the_key()>sub_root->KEY)
	return search_and_insert(sub_root->right,new_data); 
	else  
	{
		cout<<"Failed!The PictureRecord has already been inserted!"<<endl;
		return duplicateKey;
	}
}

template <class Entry> 
Error_code Search_tree_By_Key<Entry>::Replace(const PictureRecord &new_data)
{
	Binary_node<List<Node<PictureRecord>*>> *find_target=search_for_node(root,new_data.the_key());
	if(find_target!=NULL)
	{
		Node<PictureRecord> *p;
		find_target->data.retrieve(0,p);
		p->entry=new_data;
		return success;
	//因为key是唯一的，所以List里只有1个
	}
	else return notPresent;
}

template <class Entry> 
Error_code Search_tree_By_Key<Entry>::Remove(string &Key)
{
	return search_and_destroy(root,Key);  
}

template <class Entry> 
Error_code Search_tree_By_Key<Entry>::search_and_destroy(Binary_node<List<Node<PictureRecord>*>>* &sub_root,
														 string &Key)
{
	if (sub_root==NULL||sub_root->KEY==Key)	
	return  remove_root(sub_root);
	else if (Key<sub_root->KEY) 
	return search_and_destroy(sub_root->left,Key); 
	else return search_and_destroy(sub_root->right,Key);
}

template <class Entry> 
Error_code Search_tree_By_Key<Entry>::remove_root(Binary_node<List<Node<PictureRecord>*>>* &sub_root) 
{ //将PictureRecord删掉，在这里由于key是唯一的，所以也就是删除Binary_node的一个结点
	//对指针进行操作，需要用到List的等号操作符重载，代码基本与二分查找树相同
	
	if(sub_root==NULL) return notPresent; 
	Binary_node<List<Node<PictureRecord>*>>  *to_delete=sub_root; 

	if(sub_root->right==NULL) 
	sub_root=sub_root->left; 
	else if(sub_root->left==NULL) 
	sub_root=sub_root->right; 
	else 
	{ 
	  to_delete=sub_root->left;  
	  Binary_node<List<Node<PictureRecord>*>> *parent=sub_root; 
	  while(to_delete->right != NULL) 
	  { 
	    parent=to_delete; 
		to_delete=to_delete->right; 
	  } 
	  sub_root->data=to_delete->data;  //List等号操作符已经重载 
	
	  if(parent==sub_root) 
	  sub_root->left=to_delete->left; 
	  else parent->right=to_delete->left; 
	} 
		delete to_delete;
		return success; 
}

template <class Entry>
void Search_tree_By_Key<Entry>::inorder()
{
	recursive_inorder(root);
}

template <class Entry>
void Search_tree_By_Key<Entry>::recursive_inorder(Binary_node<List<Node<PictureRecord>*>> *sub_root)
{
	if(sub_root!=NULL)
	{
		recursive_inorder(sub_root->left);
		print_node(sub_root);
		recursive_inorder(sub_root->right);
	} 
}



template <class Entry>
void Search_tree_By_Key<Entry>::print_node(Binary_node<List<Node<PictureRecord>*>> *sub_root)
{
	Node<PictureRecord> *p;
	for(int i=0;i<sub_root->data.size();i++)
	{
		if(sub_root->data.retrieve(i,p)==success)
			cout<<p->entry;
	}
}



//****************************************************************************//
//****************************************************************************//
//************************Search_tree_By_Title********************************//
//****************************************************************************//
//****************************************************************************//


template <class Entry> 
Error_code Search_tree_By_Title<Entry>::search_1(string &Title,
List<Node<PictureRecord>*> &titleList/*out*/) 
{
   	Error_code result=success; 
   	Binary_node<List<Node<PictureRecord>*>> *found=search_for_node_1(root_1,Title); 
	if(found==NULL) result=notPresent;
	else 	titleList=found->data;
	return result; 
}

template <class Entry> 
Binary_node<List<Node<PictureRecord>*>>  *Search_tree_By_Title<Entry>::search_for_node_1
(Binary_node<List<Node<PictureRecord>*>> *&sub_root,string &Title) const 
{ 
	if(sub_root==NULL||sub_root->KEY==Title)
		return sub_root;
	else if(sub_root->KEY<Title) 
	return search_for_node_1(sub_root->right,Title); 
	else return search_for_node_1(sub_root->left,Title);  
}

template <class Entry> 
Error_code Search_tree_By_Title<Entry>::insert_1(const List<Node<PictureRecord>*> &new_data)
{
	Node<PictureRecord>* r;
	Error_code result;
	for(int i=0;i<new_data.size();i++)
	{
		new_data.retrieve(i,r);
		result=search_and_insert_1(root_1,r);
	}
	return result;
}

template <class Entry> 
Error_code Search_tree_By_Title<Entry>::insert_1_pic(Node<PictureRecord> *&new_data)
{
	return search_and_insert_1(root_1,new_data);
}

template <class Entry> 
Error_code Search_tree_By_Title<Entry>::search_and_insert_1(Binary_node<List<Node<PictureRecord>*>> 
*&sub_root /*inout*/, Node<PictureRecord>* &new_data/*in*/) 
{ //递归找到待插结点，记录Tree的待插结点KEY值

	if(sub_root==NULL) 
	{
	  sub_root=new Binary_node<List<Node<PictureRecord>*>>;
	  sub_root->data.insert(0,new_data);
	  sub_root->KEY=new_data->entry.the_titleEn();
	  return success; 
	} 	

	else if(new_data->entry.the_titleEn()<sub_root->KEY) 
	return search_and_insert_1(sub_root->left,new_data); 
	else if(new_data->entry.the_titleEn()>sub_root->KEY)
	return search_and_insert_1(sub_root->right,new_data); 
	else  
	{
		sub_root->data.insert(sub_root->data.size(),new_data);
		sub_root->KEY=new_data->entry.the_titleEn();
	}
	return success;
}

template <class Entry> 
Error_code Search_tree_By_Title<Entry>::Replace_1(const PictureRecord &new_data)
{
	Binary_node<List<Node<PictureRecord>*>> *find_target=search_for_node_1(root_1,new_data.the_titleEn());
	Node<PictureRecord> *p;
	if(find_target!=NULL)
	{
		for(int i=0;i<find_target->data.size();i++)
		{
			if(find_target->data.retrieve(i,p)==success)
			{
				if(p->entry.the_key()==new_data.the_key())
				{
					p->entry=new_data;
					return success;
				}	//因为只有key才是唯一的
			}
		}
		return notPresent;
	}
	else return notPresent;
}

template <class Entry> 
Error_code Search_tree_By_Title<Entry>::Remove_1(PictureRecord &new_data)
{
	string title_name=new_data.the_titleEn();
	return search_and_destroy_1(root_1,title_name,new_data);  
}

template <class Entry> 
Error_code Search_tree_By_Title<Entry>::search_and_destroy_1(Binary_node<List<Node<PictureRecord>*>>* &sub_root,
										string &Title,PictureRecord &new_data)
{
	if (sub_root==NULL||sub_root->KEY==Title)	
	return  remove_root_1(sub_root,new_data);
	else if (Title<sub_root->KEY) 
	return search_and_destroy_1(sub_root->left,Title,new_data); 
	else return search_and_destroy_1(sub_root->right,Title,new_data);
}

template <class Entry> 
Error_code Search_tree_By_Title<Entry>::remove_root_1(Binary_node<List<Node<PictureRecord>*>>* &sub_root,
													  PictureRecord &new_data) 
{ //将指定的PictureRecord删掉，

	if(sub_root==NULL) return notPresent; 
	Node<PictureRecord> *p;
	for(int i=0;i<sub_root->data.size();i++)
	{
	  if(sub_root->data.retrieve(i,p)==success &&p->entry.the_key()==new_data.the_key())
		{
			if(sub_root->data.size()>1) 
			{
				sub_root->data.remove(i,p);
				return success;   
			} //若结点的List的大小>1，则直接删除

				//若等于1，则需要调整树的结构，保证其中序遍历是有序的
			else
			{
				Binary_node<List<Node<PictureRecord>*>>  *to_delete=sub_root; 
				if(sub_root->right==NULL) 
				sub_root=sub_root->left; 
				else if(sub_root->left==NULL) 
				sub_root=sub_root->right; 
				else 
				{ 
					to_delete=sub_root->left;  
					Binary_node<List<Node<PictureRecord>*>> *parent=sub_root; 
					while(to_delete->right != NULL) 
					{ 
						parent=to_delete; 
						to_delete=to_delete->right; 
					} 
					sub_root->data=to_delete->data;  //List等号操作符已经重载 
	
					if(parent==sub_root) 
					sub_root->left=to_delete->left; 
					else parent->right=to_delete->left; 
				} 
				delete to_delete;
				return success; 
			}
		}
	}
	return notPresent;
}



template <class Entry>
void Search_tree_By_Title<Entry>::inorder_1()
{
	recursive_inorder_1(root_1);
}

template <class Entry>
void Search_tree_By_Title<Entry>::recursive_inorder_1(Binary_node<List<Node<PictureRecord>*>> *sub_root)
{
	if(sub_root!=NULL)
	{
		recursive_inorder_1(sub_root->left);
		print_node_1(sub_root);
		recursive_inorder_1(sub_root->right);
	} 
}

template <class Entry>
void Search_tree_By_Title<Entry>::print_node_1(Binary_node<List<Node<PictureRecord>*>> *sub_root)
{
	Node<PictureRecord> *p;
	for(int i=0;i<sub_root->data.size();i++)
	{
		if(sub_root->data.retrieve(i,p)==success)
			cout<<p->entry;
	}

}




//****************************************************************************//
//****************************************************************************//
//************************Search_tree_By_Location*****************************//
//****************************************************************************//
//****************************************************************************//

template <class Entry> 
Error_code Search_tree_By_Location<Entry>::search_2(string &Location,
List<Node<PictureRecord>*> &locationList/*out*/) 
{
   	Error_code result=success; 
   	Binary_node<List<Node<PictureRecord>*>> *found=search_for_node_2(root_2,Location); 
	if(found==NULL) result=notPresent;
   	else locationList=found->data;
	return result; 
}

template <class Entry> 
Binary_node<List<Node<PictureRecord>*>>  *Search_tree_By_Location<Entry>::search_for_node_2
(Binary_node<List<Node<PictureRecord>*>> *&sub_root,string &Location) const 
{ 
	if(sub_root==NULL||sub_root->KEY==Location)
		return sub_root;
	else if(sub_root->KEY<Location) 
	return search_for_node_2(sub_root->right,Location); 
	else return search_for_node_2(sub_root->left,Location);  
}

template <class Entry> 
Error_code Search_tree_By_Location<Entry>::insert_2(const List<Node<PictureRecord>*> &new_data)
{
	Node<PictureRecord>* r;
	Error_code result;
	for(int i=0;i<new_data.size();i++)
	{
		new_data.retrieve(i,r);
		result=search_and_insert_2(root_2,r);
	}
	return result;
}

template <class Entry> 
Error_code Search_tree_By_Location<Entry>::insert_2_pic(Node<PictureRecord> *&new_data)
{
	return search_and_insert_2(root_2,new_data);
}

template <class Entry> 
Error_code Search_tree_By_Location<Entry>::search_and_insert_2(Binary_node<List<Node<PictureRecord>*>> 
*&sub_root /*inout*/, Node<PictureRecord>* &new_data/*in*/) 
{ //递归找到待插结点，记录Tree的待插结点KEY值

	if(sub_root==NULL) 
	{
	  sub_root=new Binary_node<List<Node<PictureRecord>*>>;
	  sub_root->data.insert(0,new_data);
	  sub_root->KEY=new_data->entry.the_location();
	  return success; 
	} 	

	else if(new_data->entry.the_location()<sub_root->KEY) 
	return search_and_insert_2(sub_root->left,new_data); 
	else if(new_data->entry.the_location()>sub_root->KEY)
	return search_and_insert_2(sub_root->right,new_data); 
	else sub_root->data.insert(sub_root->data.size(),new_data);
	return success;
}

template <class Entry> 
Error_code Search_tree_By_Location<Entry>::Replace_2(const PictureRecord &new_data)
{
	Binary_node<List<Node<PictureRecord>*>> *find_target=search_for_node_2(root_2,new_data.the_location());
	Node<PictureRecord> *p;
	if(find_target!=NULL)
	{
		for(int i=0;i<find_target->data.size();i++)
		{
			if(find_target->data.retrieve(i,p)==success)
			{
				if(p->entry.the_key()==new_data.the_key())
				{
					p->entry=new_data;
					return success;
				}	//因为只有key才是唯一的
			}
		}
		return notPresent;
	}
	else return notPresent;
}

template <class Entry> 
Error_code Search_tree_By_Location<Entry>::Remove_2(PictureRecord &new_data)
{
	string location_name=new_data.the_location();
	return search_and_destroy_2(root_2,location_name,new_data);  
}

template <class Entry> 
Error_code Search_tree_By_Location<Entry>::search_and_destroy_2(Binary_node<List<Node<PictureRecord>*>>* &sub_root,
string &Location,PictureRecord &new_data)
{
	if (sub_root==NULL||sub_root->KEY==Location)	
	return  remove_root_2(sub_root,new_data);
	else if (Location<sub_root->KEY) 
	return search_and_destroy_2(sub_root->left,Location,new_data); 
	else return search_and_destroy_2(sub_root->right,Location,new_data);
}

template <class Entry> 
Error_code Search_tree_By_Location<Entry>::remove_root_2(Binary_node<List<Node<PictureRecord>*>>* &sub_root,
													  PictureRecord &new_data) 
{ //将指定的PictureRecord删掉，

	if(sub_root==NULL) return notPresent; 
	Node<PictureRecord> *p;
	for(int i=0;i<sub_root->data.size();i++)
	{
	  if(sub_root->data.retrieve(i,p)==success && p->entry.the_key()==new_data.the_key())
		{
			if(sub_root->data.size()>1) 
			{
				sub_root->data.remove(i,p);
				return success;   
			} //若结点的List的大小>1，则直接删除

				//若等于1，则需要调整树的结构，保证其中序遍历是有序的
			else
			{
				Binary_node<List<Node<PictureRecord>*>>  *to_delete=sub_root; 
				if(sub_root->right==NULL) 
				sub_root=sub_root->left; 
				else if(sub_root->left==NULL) 
				sub_root=sub_root->right; 
				else 
				{ 
					to_delete=sub_root->left;  
					Binary_node<List<Node<PictureRecord>*>> *parent=sub_root; 
					while(to_delete->right != NULL) 
					{ 
						parent=to_delete; 
						to_delete=to_delete->right; 
					} 
					sub_root->data=to_delete->data;  //List等号操作符已经重载 
	
					if(parent==sub_root) 
					sub_root->left=to_delete->left; 
					else parent->right=to_delete->left; 
				} 
				delete to_delete;
				return success; 
			}

		}
	}
	return notPresent;
}



template <class Entry>
void Search_tree_By_Location<Entry>::inorder_2()
{
	recursive_inorder_2(root_2);
}

template <class Entry>
void Search_tree_By_Location<Entry>::recursive_inorder_2(Binary_node<List<Node<PictureRecord>*>> *sub_root)
{
	if(sub_root!=NULL)
	{
		recursive_inorder_2(sub_root->left);
		print_node_2(sub_root);
		recursive_inorder_2(sub_root->right);
	} 
}

template <class Entry>
void Search_tree_By_Location<Entry>::print_node_2(Binary_node<List<Node<PictureRecord>*>> *sub_root)
{
	Node<PictureRecord> *p;
	for(int i=0;i<sub_root->data.size();i++)
	{
		if(sub_root->data.retrieve(i,p)==success)
			cout<<p->entry;
	}

}