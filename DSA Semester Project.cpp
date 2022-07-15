// DSA SEMESTER PROJECT
// ABDUL MOIZ L1F20BSCS0712
// MUGHEEZ ASIF L1F20BSCS0539


#include <iostream>
#include "RedBlackTree.h"
using namespace std;

void menu();
void afterMenu(int choise, int*& data, int counter, RedBlackTree& obj);

int main()
{
	menu();

	return 0;
}

void menu()
{
	RedBlackTree obj;
	int* data = new int[100];
	int counter = 0;
	while (1)
	{
		int user;
		cout << endl;
		cout << "************************************" << endl;
		cout << "Press 1 to insert values in the tree" << endl;
		cout << "Press 2 for searching a value from the tree" << endl;
		cout << "Press 3 for depth first search" << endl;
		cout << "Press 4 for breadth first search" << endl;
		cout << "Press 5 for traversal" << endl;
		cout << "Press 6 for display complete tree" << endl;
		cout << "Press 7 for delete a value" << endl;

		cout << "Press 8 to EXIT" << endl;
		cout << endl << "Your Choise : ";
		cin >> user;
		while (user > 8 || user < 1)
		{
			cout << "Wrong choise. Enter again : ";
			cin >> user;
		}
		cout << endl;
		if (user == 8)
			break;
		else
		{
			afterMenu(user, data, counter, obj);
		}
	}
}
void afterMenu(int choise, int*& data,int counter, RedBlackTree& obj)
{
	if (choise == 1)
	{
		int value;
		cout << "Enter a value : ";
		cin >> value;
		bool flag = true;
		for (int i = 0; i < counter; i++)
		{
			if (data[i] == value)
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			obj.insert(value);
			data[counter] = value;
			counter++;
		}
		else
		{
			cout << "The value is alredy entered. Try another value!" << endl;
		}
	}
	else if (choise == 2)
	{
		int value;
		cout << "Enter a Value : ";
		cin >> value;
		if (obj.search(value))
		{
			cout << "Value exists" << endl;
		}
		else
		{
			cout << "Value does not exists" << endl;
		}
	}
	else if (choise == 3)
	{
		obj.displayDepthFirst();
	}
	else if (choise == 4)
	{
		obj.displayBreadthFirst();
	}
	else if (choise == 5)
	{
		obj.trav();
	}
	else if (choise == 6)
	{
		obj.print();
	}
	else if (choise == 7)
	{
		int value;
		cout << "Enter a value : ";
		cin >> value;
		bool flag = true;
		for (int i = 0; i < counter; i++)
		{
			if (data[i] == value)
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			obj.deleteItem(value);
			for (int i = 0; i < counter - 1; i++)
			{
				if (value == data[i])
				{
					for (int j = i; j < counter - 1; j++)
						data[j] = data[j + 1];
					break;
				}
			}
			counter--;
		}
		else
		{
			cout << "The value is not present in the tree. Try another value!" << endl;
		}
	}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
