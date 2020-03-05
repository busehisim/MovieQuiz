#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST
#include<iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>
using namespace std;

template<class T>
class DLLNode {
public:
    DLLNode() {
        next = prev = 0;
    }
    DLLNode(const T& el, DLLNode<T> *n = 0, DLLNode<T> *p = 0) {
        info = el; next = n; prev = p;
    }
    T info;
    DLLNode<T> *next, *prev;
};

template<class T>
class DoublyLinkedList {
public:
    DoublyLinkedList() {
        head = tail = 0;
    }
    void addToDLLTail(const T&);
    T deleteFromDLLTail();
    ~DoublyLinkedList() {
        clear();
    }
    bool isEmpty() const {
        return head == 0;
    }
    void clear();
    void setToNull() {
        head = tail = 0;
    }
    void addToDLLHead(const T&);
    T deleteFromDLLHead();
    T& firstEl();
    T* find(const int) const;
	//std::string getString();
    void printAll() const;
    void deleteNode(string el);
    bool isInList(string) const;

protected:
    DLLNode<T> *head, *tail;
    friend ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll) {
        for (DLLNode<T> *tmp = dll.head; tmp != 0; tmp = tmp->next)
            out << tmp->info << ' ' << endl;
        return out;
    }
};

template<class T>
void DoublyLinkedList<T>::addToDLLHead(const T& el) {
    if (head != 0) {
         head = new DLLNode<T>(el,head,0);
         head->next->prev = head;
    }
    else head = tail = new DLLNode<T>(el);
}

template<class T>
void DoublyLinkedList<T>::addToDLLTail(const T& el) {
    if (tail != 0) {
         tail = new DLLNode<T>(el,0,tail);
         tail->prev->next = tail;
    }
    else head = tail = new DLLNode<T>(el);
}

template<class T>
T DoublyLinkedList<T>::deleteFromDLLHead() {
    T el = head->info;
    if (head == tail) { // if only one DLLNode on the list;
         delete head;
         head = tail = 0;
    }
    else {              // if more than one DLLNode in the list;
         head = head->next;
         delete head->prev;
         head->prev = 0;
    }
    return el;
}

template<class T>
T DoublyLinkedList<T>::deleteFromDLLTail() {
    T el = tail->info;
    if (head == tail) { // if only one DLLNode on the list;
         delete head;
         head = tail = 0;
    }
    else {              // if more than one DLLNode in the list;
         tail = tail->prev;
         delete tail->next;
         tail->next = 0;
    }
    return el;
}

template <class T>
T* DoublyLinkedList<T>::find(const int num) const {
    DLLNode<T> * tmp = head;
    for (int i = 0; tmp != NULL; i++, tmp = tmp->next)
    {
        if (i == num)
            return &tmp->info;
    }

    return NULL;
}

template<class T>
T& DoublyLinkedList<T>::firstEl() {
    return head->info;
}

template<class T>
void DoublyLinkedList<T>::clear() {
    for (DLLNode<T> *tmp; head != 0; ) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}
/*template<class T>
std::string DoublyLinkedList<T>::getString()   //turns bigInt into a string
{
	std::string a;
	for (DLLNode<T> *tmp = head; tmp != NULL; tmp = tmp->next)
		a.push_back(tmp->info + '0');
	return a;
}*/
template<class T>
void DoublyLinkedList<T>::printAll() const
{
    for (DLLNode<T> *tmp = head; tmp != 0; tmp = tmp->next)
        std::cout << tmp->info << endl;
	std::cout << std::endl;

}
template<class T>
void DoublyLinkedList<T>::deleteNode(string el)
{

    if (head != 0)  // if non-empty list;
    {
         if (head == tail && el == head->info) { // if only one
              delete head;                       // node on the list;
              head = tail = 0;
         }
         else if (el == head->info) {  // if more than one node on the list
              DLLNode<T>*tmp = head;
              head = head->next;
              delete tmp;              // and old head is deleted;
         }
         else {                        // if more than one node in the list
              DLLNode<T> *pred, *tmp;
              for (pred = head, tmp = head->next; // and a non-head node
                   tmp != 0 && !(tmp->info == el);// is deleted;
                   pred = pred->next, tmp = tmp->next);
              if (tmp != 0) {
                   pred->next = tmp->next;
                   if (tmp == tail)
                      tail = pred;
                   delete tmp;
              }
         }
    }
}

template<class T>
bool DoublyLinkedList<T>::isInList(string el) const
{
    DLLNode<T> *tmp ;
    for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
    return tmp != 0;
}


#endif
