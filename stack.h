#include "linkedlist.h"

#pragma once

template<typename T>
class Stack : public LinkedList<T>{
public:
	void push(T);
	void pop();
	T top();
};
template<typename T>
void Stack<T>::pop(){
	LinkedList<T>::pop_front();
}
//returns value of the front
template<typename T>
T Stack<T>::top(){
	return LinkedList<T>::head->value;
}
template<typename T>
void Stack<T>::push(T val){
	LinkedList<T>::push_front(val);
}
