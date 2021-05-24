#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{}
    
template <class T>
Stack<T>::Stack(Stack<T>& otherStack)
{
	shared_ptr<ListItem<T>> temp;
	temp = otherStack.list.getTail();
	if (temp == NULL)
	{
		return;
	}
	while (temp != NULL)
	{
		this->push(temp->value);
		temp = temp->prev;
	}
}

template <class T>
Stack<T>::~Stack()
{}

template <class T>
void Stack<T>::push(T item)
{
	list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
	shared_ptr<ListItem<T>> temp=list.getHead();
	T val= temp->value;
	return val;
}

template <class T>
T Stack<T>::pop()
{
	shared_ptr<ListItem<T>> temp= list.getHead();
	T val=temp->value;
	list.deleteHead();
	return val;
}

template <class T>
int Stack<T>::length()
{
	int len=list.length();
	return len;
}

template <class T>
bool Stack<T>::isEmpty()
{
	int len=list.length();
	if(len==0)
	{
		return false;
	}
	else {
		return true;
	}
}

#endif
