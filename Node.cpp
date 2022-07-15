#include "Node.h"


Node::Node()
{
	left = nullptr;
	right = nullptr;
	parrent = nullptr;
}

Node::Node(int value, char clr)
{
	data = value;
	color = clr;
	left = nullptr;
	right = nullptr;
	parrent = nullptr;
}


Node::Node(const Node& obj)
{
	data = obj.data;
	right = obj.right;
	left = obj.left;
	parrent = obj.parrent;
	color = obj.color;
}

Node::~Node()
{
	if (left)
		delete left;
	if (right)
		delete right;
	if (parrent)
		delete parrent;
	left = nullptr;
	parrent = nullptr;
	right = nullptr;
}
