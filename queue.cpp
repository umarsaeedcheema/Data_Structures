#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{

}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue)//:list(otherQueue.list) 
{

	shared_ptr<ListItem<T>> temp = otherQueue.list.getHead();
	
	if (temp == NULL)
	{
		return;
	}
	while (temp != NULL)
	{
		this->enqueue(temp->value);
		temp = temp->next;
	}
}

template <class T>
Queue<T>::~Queue()
{

	
}

template <class T>
void Queue<T>::enqueue(T item)
{
	list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
	shared_ptr<ListItem<T>> temp=list.getHead();
	T val=temp->value;
	return val;
}

template <class T>
T Queue<T>::dequeue()
{
	shared_ptr<ListItem<T>> temp=list.getHead();
	T val = temp->value;
	list.deleteHead();
	return val;
}

template <class T>
int Queue<T>::length()
{
	int len = list.length();
	return len;
}

template <class T>
bool Queue<T>::isEmpty()
{
	int len=list.length();
	if (len==0)
	{
		return false;
	}
	else {
		return true;
	}
}


#endif
