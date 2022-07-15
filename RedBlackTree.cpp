#include "RedBlackTree.h"


RedBlackTree::RedBlackTree()
{
	root = nullptr;
}

void RedBlackTree::insertRoot(int value)
{
	if (!root)
	{
		root = new Node(value, 'b');
	}
}

void RedBlackTree::insert(int value)
{
	if (root)
	{
		Node* newNode = nullptr;
		Node* temp = root;
		Node* prev = root;
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
		}
		if (value > prev->data)
		{
			prev->right = new Node(value, 'r');
			prev->right->parrent = prev;
			newNode = prev->right;
		}
		else
		{
			prev->left = new Node(value, 'r');
			prev->left->parrent = prev;
			newNode = prev->left;
		}
		propertyFix(newNode);
	}
	else
	{
		insertRoot(value);
	}
}

void RedBlackTree::propertyFix(Node* nd)
{
	if (nd->parrent)
	{
		while (nd->parrent->color == 'r')
		{
			Node* parent = nd->parrent;

			if (parent->parrent->left == parent)
			{
				char clr = 'b';
				Node* uncle = nullptr;
				if (parent->parrent->right)
				{
					uncle = parent->parrent->right;
					clr = parent->parrent->right->color;
				}
				if (clr == 'r')
				{
					colorFix(parent, uncle);
					if (parent->parrent->color == 'r' && parent->color == 'r')
						nd = parent;
					else if (parent->parrent->color == 'r' && parent->parrent->parrent->color == 'r')
						nd = parent->parrent;
				}
				else
				{
					if (parent->right == nd)
					{
						leftRightRotate(nd);
						afterRotateColorFix(nd, 'd');
					}
					else
					{
						rotateRight(parent);
						afterRotateColorFix(nd, 's');
					}
				}
			}
			else if (parent->parrent->right == parent)
			{
				char clr = 'b';
				Node* uncle = nullptr;
				if (parent->parrent->left)
				{
					uncle = parent->parrent->left;
					clr = parent->parrent->left->color;
				}
				if (clr == 'r')
				{
					colorFix(parent, uncle);
					if (parent->parrent->color == 'r' && parent->color == 'r')
						nd = parent;
					else if (parent->parrent->color == 'r' && parent->parrent->parrent->color == 'r')
						nd = parent->parrent;
				}
				else
				{
					if (parent->right == nd)
					{
						rotateLeft(parent);
						afterRotateColorFix(nd, 's');
					}
					else
					{
						RightLeftRotate(nd);
						afterRotateColorFix(nd, 'd');
					}
				}
			}
			if (!nd->parrent)
				break;
		}
	}
}

void RedBlackTree::deleteFix(Node* nd)
{
	while (nd != root && nd->color == 'b')
	{
		if (nd->parrent == nullptr)
			break;
		if (nd->parrent->left == nd)
		{
			Node* sibling = nd->parrent->right;
			if (sibling->color == 'r')
			{
				sibling->color = 'b';
				nd->parrent->color = 'r';
				rotateLeft(nd->parrent);
				sibling = nd->parrent->right;
			}
			char clr1 = 'b';
			if (sibling->left)
				clr1 = sibling->left->color;
			char clr2 = 'b';
			if (sibling->right)
				clr2 = sibling->right->color;
			if (clr1 == 'b' && clr2 == 'b')
			{
				sibling->color = 'r';
				nd = nd->parrent;
			}
			else
			{
				if (clr2 == 'b')
				{
					if (sibling->left)
						sibling->left->color = 'b';
					sibling->color = 'r';
					rotateRight(sibling);
					if (nd->parrent->right)
						sibling = nd->parrent->right;
					else
						sibling = nullptr;
				}
				sibling->color = nd->parrent->color;
				nd->parrent->color = 'b';
				if (sibling->right)
					sibling->right->color = 'b';
				rotateLeft(nd->parrent);
				nd = root;
			}
		}
		else if (nd->parrent->right == nd)
		{
			Node* sibling = nd->parrent->left;
			if (sibling->color == 'r')
			{
				sibling->color = 'b';
				nd->parrent->color = 'r';
				rotateRight(nd->parrent);
				sibling = nd->parrent->left;
			}
			char clr1 = 'b';
			if (sibling->right)
				clr1 = sibling->right->color;
			char clr2 = 'b';
			if (sibling->left)
				clr2 = sibling->left->color;
			if (clr1 == 'b' && clr2 == 'b')
			{
				sibling->color = 'r';
				nd = nd->parrent;
			}
			else
			{
				if (clr2 == 'b')
				{
					if (sibling->right)
						sibling->right->color = 'b';
					sibling->color = 'r';
					rotateLeft(sibling);
					if (nd->parrent->left)
						sibling = nd->parrent->left;
					else
						sibling = nullptr;
				}
				sibling->color = nd->parrent->color;
				nd->parrent->color = 'b';
				if (sibling->left)
					sibling->left->color = 'b';
				rotateRight(nd->parrent);
				nd = root;
			}
		}
		break;
	}
	nd->color = 'b';
}

void RedBlackTree::deleteItem(int value)
{
	if (root)
	{
		Node* it = root;
		Node* prev = root;
		getSearch(prev, it, value);
		char clr = it->color;
		if (it->right == '\0' && it->left == '\0')
		{
			deleteCase1(prev, it);
		}
		else if (it->right != '\0' && it->left != '\0')
		{
			deleteCase3(it);
		}
		else
		{
			deleteCase2(prev, it);
		}
		if (clr == 'b')
			deleteFix(it);
	}

}

void RedBlackTree::rotateLeft(Node* nd)
{
	Node* parent = nd->parrent;
	parent->right = nd->left;
	if (nd->left != nullptr)
		nd->left->parrent = parent;
	nd->parrent = parent->parrent;
	if (parent->parrent == nullptr)
		root = nd;
	else if (parent->parrent->left->data == parent->data)
		parent->parrent->left = nd;
	else if (parent->parrent->right->data == parent->data)
		parent->parrent->right = nd;
	nd->left = parent;
	parent->parrent = nd;
}

void RedBlackTree::rotateRight(Node* nd)
{
	Node* parent = nd->parrent;
	parent->left = nd->right;
	if (nd->right != nullptr)
		nd->right->parrent = parent;
	nd->parrent = parent->parrent;
	if (parent->parrent == nullptr)
		root = nd;
	else if (parent->parrent->left->data == parent->data)
		parent->parrent->left = nd;
	else if (parent->parrent->right->data == parent->data)
		parent->parrent->right = nd;
	nd->right = parent;
	parent->parrent = nd;	
}

void RedBlackTree::leftRightRotate(Node* nd)
{
	rotateLeft(nd);
	rotateRight(nd);
}
void RedBlackTree::RightLeftRotate(Node* nd)
{
	rotateRight(nd);
	rotateLeft(nd);
}

void RedBlackTree::print()
{
	if (root) {
		printHelper(this->root, "", true);
	}
	else
		cout << "Tree is empty";
	cout << endl;
}

void RedBlackTree::displayDepthFirst()
{
	if (root)
	{
		displayDepthFirstHelper(root);
	}
	else
	{
		cout << "Tree is empty" << endl;
	}
}

void RedBlackTree::displayBreadthFirst()
{
	if (root)
	{
		displayBreadthFirstHelper(root);
	}
	else
	{
		cout << "Tree is empty" << endl;
	}
}

void RedBlackTree::trav()
{
	if (root)
	{
		Queue<Node*> q;
		if (root) {
			q.enqueue(root);
			cout << root->data << " ";
		}
		while (!q.isempty()) {
			Node* temp = q.dequeue();

			if (temp->left) {
				q.enqueue(temp->left);
				cout << temp->left->data << " ";
			}


			if (temp->right) {
				q.enqueue(temp->right);
				cout << temp->right->data << " ";
			}
		}
	}
	else
		cout << "Tree is empty" << endl;
}

bool RedBlackTree::search(int value)
{
	if (root)
	{
		Node* temp = root;
		bool flag = false;
		while (1)
		{
			if (value > temp->data)
				temp = temp->right;
			else if (value < temp->data)
				temp = temp->left;
			if (!temp)
				break;
			else if (temp->data == value)
			{
				flag = true;
				break;
			}
		}
		return flag;
	}
}

RedBlackTree::~RedBlackTree()
{
	if (!root)
	{
		delete root;
	}
	root = nullptr;
}
