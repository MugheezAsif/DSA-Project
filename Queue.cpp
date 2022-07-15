#include "Queue.h"
template <class T>
Queue<T>::Queue()
{
	arr = new T[100];
	maxSize = 100;
	size = 0;
}
template <class T>
Queue<T>::Queue(Queue& obj)
{
	if (arr != nullptr)
		delete[]arr;
	arr = new T[obj.maxSize];
	for (int i = 0; i < obj.size; i++)
		arr[i] = obj.arr[i];
	size = obj.size;
	maxSize = obj.maxSize;
}
template <class T>
Queue<T> & Queue<T>::operator=(Queue & obj)
{
	if (arr != nullptr)
		delete[]arr;
	arr = new T[obj.maxSize];
	for (int i = 0; i < obj.size; i++)
		arr[i] = obj.arr[i];
	size = obj.size;
	maxSize = obj.maxSize;
	return *this;
}
template <class T>
Queue<T>::~Queue()
{
	delete[] arr;
	arr = nullptr;
}
template <class T>
void Queue<T>::enqueue(T a)
{
	arr[size++] = a;
}
template <class T>
T Queue<T>::dequeue()
{
	T temp = arr[0];
	for (int i = 0; i < size - 1; i++)
		arr[i] = arr[i + 1];
	size--;
	return temp;
}
template <class T>
void Queue<T>::display()
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
}
template <class T>
T Queue<T>::peek()
{
	return arr[0];
}
template <class T>
int Queue<T>::length()
{
	return size + 1;
}
template <class T>
bool Queue<T>::isempty()
{
	if (size == 0)
		return 1;
	return 0;
}
template <class T>
bool Queue<T>::isfull()
{
	if (maxSize == size)
		return 1;
	return 0;
}