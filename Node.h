#pragma once
class Node
{
public:
	Node* left;
	Node* right;
	Node* parrent;
	char color;
	int data;
	Node();
	Node(int value, char clr);
	Node(const Node& obj);
	~Node();
};


