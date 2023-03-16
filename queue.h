#include "linkedlist.h"

#pragma once

//front is equivalent is the head
//pops from the front
//pushes from the back
template<typename T>
class Queue : public LinkedList<T>{
public:
	void pop();
	void push(T);
	T front();
};

//removes the rear
template<typename T>
void Queue<T>::pop(){
	LinkedList<T>::pop_front();
}
//returns value of the front
template<typename T>
T Queue<T>::front(){
	return LinkedList<T>::head->value;
}

template<typename T>
void Queue<T>::push(T val){
	LinkedList<T>::push_back(val);
}
