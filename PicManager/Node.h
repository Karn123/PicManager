enum Error_code{underflow, overflow, rangeError, duplicateKey,success,notPresent};
template <class Node_entry>
struct Node 
{
	Node_entry entry;
	Node<Node_entry> *next;
	Node();
	Node(Node_entry item, Node<Node_entry> *link = NULL);
};