#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include <memory>
#include "LinkedList.h"
using namespace std;

template <class T>
LinkedList<T>::LinkedList()
{
	 head = NULL;
	 tail = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
	shared_ptr<ListItem<T>> temp;
	temp = otherLinkedList.head;
	if (temp == NULL)
	{
		return;
	}
	while (temp != NULL)
	{
		this->insertAtTail(temp->value);
		temp = temp->next;
	}
	head->prev=NULL;
	tail->next=NULL;
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
	//creating a new node
	shared_ptr<ListItem<T>> temp (new ListItem<T>(item));
	//case 1 when list is empty
	if (head == NULL)
	{
		head = temp;
		tail = temp;
	}
	//case 2 when list is not empty
	else {
		temp->next = head;
		head->prev = temp;
		head = temp;
	}

}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
	//creating a new node
	shared_ptr<ListItem<T>> temp (new ListItem<T>(item));
	//case 1 when list is empty
	if (tail == NULL)
	{
		head = temp;
		tail = temp;
	}
	//case 2 when list is not empty
	else {
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
	//creating a new node
	shared_ptr<ListItem<T>> temp (new ListItem<T>(toInsert));
	//creating a temp ptr
	shared_ptr<ListItem<T>> temp_ptr = searchFor(afterWhat);
	/*shared_ptr<ListItem<T>> temp_ptr ;
	while(temp_ptr->value != afterWhat)
		{
			temp_ptr = temp_ptr->next;
		}*/
	if (head == NULL)
	{
		return;
	}
	else if (temp_ptr->value == tail->value)
	{
		insertAtTail(toInsert);
	}
	else {

		temp->prev = temp_ptr;
		temp_ptr->next-> prev = temp;
		temp->next = temp_ptr->next;
		temp_ptr->next = temp;

	}
}


template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::getHead()
{
	return head;
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::getTail()
{
	return tail;
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::searchFor(T item)
{
	shared_ptr<ListItem<T>> temp_ptr = head;
	if (head == NULL)
	{
		return NULL;
	}
	else
	{
		while (temp_ptr->value != item ) {
			temp_ptr = temp_ptr->next;
			if(temp_ptr== NULL)
			{
				return NULL;
			}
			
		}
		if (temp_ptr->value == item)
		{
			return temp_ptr;
		}
		/*else {
			return NULL;
		}*/

	}
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{

	shared_ptr<ListItem<T>> temp;
	temp = searchFor(item);
	if (head == NULL)
	{
		return;
	}
	else if (item==head->value)
	{
		deleteHead();
	}
	else if(item==tail->value){
		deleteTail();
	}


}

template <class T>
void LinkedList<T>::deleteHead()
{
	shared_ptr<ListItem<T>> temp = head;
	if (head== NULL)
	{
		return ;
	}
	else if (head==tail)
	{
		head=NULL;
		tail=NULL;
	}
	else{
		head=head->next;
		head->prev = NULL;	
	}
	

}

template <class T>
void LinkedList<T>::deleteTail()
{
	shared_ptr<ListItem<T>> temp = tail;
	if (tail== NULL)
	{
		return ;
	}
	else if(tail == head)
	{
		tail=NULL;
		head=NULL;
	}
	else{
		tail=tail->prev;
		tail->next = NULL;
	}
	

}

template <class T>
int LinkedList<T>::length()
{
	shared_ptr<ListItem<T>> temp_ptr = head;
	int count = 0;
	//if list is empty
	if (head == NULL)
	{
		return count;
	}
	else {
		while (temp_ptr != NULL)
		{
			count++;
			temp_ptr = temp_ptr->next;

		}
		
	}
	return count;

}

#endif
