#pragma once
#include <iostream>
#include "Node.h"
#include "Queue.cpp"
using namespace std;
class RedBlackTree
{
public:
	RedBlackTree();
	void insertRoot(int value);
	void insert(int value);
	void deleteItem(int value);
	void trav();
	void displayBreadthFirst();
	void displayDepthFirst();
	void print();
	bool search(int value);
	~RedBlackTree();

private:
	Node* root;
	void displayDepthFirstHelper(Node* root)
	{
		if (root)
		{
			displayDepthFirstHelper(root->left);
			cout << root->data << " ";
			displayDepthFirstHelper(root->right);
		}
	}
	void displayBreadthFirstHelper(Node* root)
	{
		if (root)
		{
			Queue<Node*> obj;
			obj.enqueue(root);
			Node* nl = nullptr;
			obj.enqueue(nl);
			while (!obj.isempty())
			{
				Node* temp = obj.dequeue();
				if (temp == nullptr)
				{
					cout << endl;
					if (!obj.isempty())
						obj.enqueue(nl);
				}
				else
				{
					cout << temp->data << " ";
					if (temp->left)
						obj.enqueue(temp->left);
					if (temp->right)
						obj.enqueue(temp->right);
				}
			}
		}
	}
	void rotateLeft(Node* nd);
	void rotateRight(Node* nd);
	void leftRightRotate(Node* nd);
	void RightLeftRotate(Node* nd);
	void propertyFix(Node* nd);
	void deleteFix(Node* x);
	void printHelper(Node* root, string indent, bool last) {
		if (root != nullptr) {
			cout << indent;
			if (last) {
				cout << "R----";
				indent += "   ";
			}
			else {
				cout << "L----";
				indent += "|  ";
			}

			char sColor = root->color;
			cout << root->data << "(" << sColor << ")" << endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}
	void afterRotateColorFix(Node*& nd, char rotation)
	{
		if (rotation == 'd')
		{
			if (nd->left)                         /// this is for double rotation
			{
				if (nd->color == 'r' && nd->left->color == 'r')
				{
					nd->color = 'b';
					if (nd->right)
					{
						if (nd->right->color == 'r')
							nd->right->color = 'b';
						else
							nd->right->color = 'r';
					}
				}
				else if (nd->color == 'r' && nd->right->color == 'r')
				{
					nd->color = 'b';
					if (nd->left)
					{
						if (nd->left->color == 'r')
							nd->left->color = 'b';
						else
							nd->left->color = 'r';
					}
				}
			}
			else if (nd->right)
			{
				if (nd->color == 'r' && nd->right->color == 'r')
				{
					nd->color = 'b';
					if (nd->left)
					{
						if (nd->left->color == 'r')
							nd->left->color = 'b';
						else
							nd->left->color = 'r';
					}
				}
				else if (nd->color == 'r' && nd->left->color == 'r')
				{
					nd->color = 'b';
					if (nd->right)
					{
						if (nd->right->color == 'r')
							nd->right->color = 'b';
						else
							nd->right->color = 'r';
					}
				}
			}
		}
		else if (rotation == 's')
		{
			if (nd->parrent->color == 'r' && nd->color == 'r') // this is for single rotation
			{
				nd->parrent->color = 'b';
				if (nd->parrent->right == nd)
				{
					if (nd->parrent->left)
					{
						if (nd->parrent->left->color == 'r')
							nd->parrent->left->color = 'b';
						else
							nd->parrent->left->color = 'r';
					}
				}
				else if (nd->parrent->left == nd)
				{
					if (nd->parrent->right)
					{
						if (nd->parrent->right->color == 'r')
							nd->parrent->right->color = 'b';
						else
							nd->parrent->right->color = 'r';
					}
				}
			}
		}
		if (nd == root)
			nd->color = 'b';
	}
	void colorFix(Node*& parent, Node*& uncle)
	{
		if (parent->color == 'b')
			parent->color = 'r';
		else
			parent->color = 'b';

		if (parent->parrent->color == 'r')
			parent->parrent->color = 'b';
		else
			parent->parrent->color = 'r';

		if (uncle->color == 'b')
			uncle->color = 'r';
		else
			uncle->color = 'b';

		if (parent->parrent == root)
			parent->parrent->color = 'b';
	}
	void deleteCase1(Node*& prev, Node*& dest)
	{
		if (dest == root)
			root = '\0';
		else
		{
			if (prev->right == dest)
				prev->right = '\0';
			else if (prev->left == dest)
				prev->left = '\0';
		}
	}
	void deleteCase2(Node * &prev, Node * it)
	{
		if (it != root)
		{
			if (prev->right == it)
			{
				if (it->right != '\0')
				{
					prev->right = it->right;
					prev->right->parrent = prev;
				}
				else
				{
					prev->right = it->left;
					prev->right->parrent = prev;
				}
			}
			else if (prev->left == it)
			{
				if (it->right != '\0')
				{
					prev->left = it->right;
					prev->left->parrent = prev;
				}
				else
				{
					prev->left = it->left;
					prev->left->parrent = prev;
				}
			}
		}
		else if (it == root)
		{
			if (it->left)
			{
				root = it->left;
				root->parrent = nullptr;
			}
			else
			{
				root = it->right;
				root->parrent = nullptr;
			}
		}
	}
	void deleteCase3(Node * it)
	{
		Node* temp = it->right;
		while (temp->left != '\0') {
			temp = temp->left;
		}
		int dat = temp->data;
		char clr = temp->color;
		deleteItem(dat);
		it->data = dat;
		it->color = clr;
		
	}
	void getSearch(Node*& prev, Node*& temp, int value)
	{
		temp = root;
		prev = root;
		while (1)
		{
			if (value > temp->data)
			{
				prev = temp;
				temp = temp->right;
			}
			else if (value < temp->data)
			{
				prev = temp;
				temp = temp->left;
			}
			if (!temp)
				break;
			else if (temp->data == value)
			{
				break;
			}
		}
	}
};

