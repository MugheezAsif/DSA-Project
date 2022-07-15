#pragma once
#include <iostream>
#include <string>
using namespace std;
template <class T>
class Queue
{
	T* arr;
	int size;
	int maxSize;
public:
	Queue();
	Queue(Queue& obj);
	Queue& operator=(Queue& obj);
	void enqueue(T a);
	T dequeue();
	void display();
	T peek();
	int length();
	bool isempty();
	bool isfull();
	~Queue();
};