#include"Node.h"
#include<iostream>
using namespace std;
template<class Node_entry>
Node<Node_entry>::Node()
{
	next = NULL;
}

template<class Node_entry>
Node<Node_entry>::Node(Node_entry item, Node<Node_entry> *add_on)
{
	entry = item;
	next = add_on;
}