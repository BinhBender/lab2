#include <string>
#include <iostream>
#pragma once

//massive headache to do but it should work well enough
//A template structure that is a doubly linked node
template <typename T> 
struct Node{
public:
	T value;
	Node<T>* next = nullptr;
	Node<T>* previous = nullptr;

};

//The container for the nodes.
//In this program the Linked list is a parent class of
//queues and stacks.

//since queues and stacks derive from this class
//the implementation only needs to exist for this class
//and only the visibility needs to change for the queues and stacks
//you call this lazy, i call this being efficient
//also any bugs that happen can be fixed by fixing one file
//new features could also be done the same
template <typename T>
class LinkedList{
protected:
	Node<T>* head;
	Node<T>* tail;
	int size;

public:
	LinkedList<T>(){
		head = nullptr;
		tail = nullptr;
		size = 0;
	
	}
	~LinkedList(){
	//This makes n-1 "jumps" because
	//n jumps will cause you to jump to a nullptr
	//and you can't use ->previous with nullptr
	for(int i = 0; i < size-1; i++){
		head = head->next;
		delete head->previous;
	}
	delete head;                                      
	}
	
	int GetSize();
	void clear();
protected:
	void push_back(T);
	void push_front(T);
	
	void pop_back();
	void pop_front();
	
	
//getters
	Node<T>* GetHead();
	Node<T>* GetTail();
};
//this class will be a doubly linked list



template<typename T>
void LinkedList<T>::clear(){
	while(head != nullptr){
		pop_back();
	}
}
/*Desc: adds a new node with its data equaling val
 * at the end of the list
 * increasing the size and 
 * @param val: This is the input value 
 * 
 */
template <typename T>
void LinkedList<T>::push_back(T val){
	Node<T>* newNode = new Node<T>;
	newNode->value = val;
	//This is an edge case for if
	//its an empty array
	if(size == 0){
		head = tail = newNode;
		
	}else{
		
		//attaches the previous of the newNode to the tail
		//then the next of the current tail
		//then the tail becomes the newNode
		newNode->previous = tail;
		tail->next = newNode;
		tail = newNode;
	}
	//increase the size
	size++;
	
}
/*Desc: adds a new node with its data equaling val
 * at the front of the list
 * increasing the size and 
 * @param val: This is the input value 
 * 
 */
template <typename T>
void LinkedList<T>::push_front(T val){
	Node<T>* newNode = new Node<T>;
	newNode->value = val;
	if(size == 0){
		head = tail = newNode;
		
	}else{
		newNode->next = head;
		head->previous = newNode;
		head = newNode;
	}
	size++;
}
/*Desc: deletes a new node 
 * at the end of the list
 * decreasing the size and 
 * @param val: This is the input value 
 * 
 */
template <typename T>
void LinkedList<T>::pop_back(){
	//if the list is empty then nothing needs to be done
	if(size == 0) return;
	//if the list only contains 1 element
	if(size == 1){
		delete tail;
		head = tail = nullptr;
		size--;
		return;
	}
	tail = tail->previous;
	delete tail->next;
	tail->next = nullptr;
	size--;
}
/*Desc: deletes a new node 
 * at the front of the list
 * decreasing the size and deleting the old one
 * @param val: This is the input value 
 * 
 */
template <typename T>
void LinkedList<T>::pop_front(){
	//if the list is empty then nothing needs to be done
	if(size == 0) return;
	//if the list only contains 1 element
	if(size == 1){
		delete head;
		head = tail = nullptr;
		size--;
		return;
	}
	head = head->next;
	delete head->previous;
	head->previous = nullptr;
	size--;
	
}

//getters
template <typename T>
int LinkedList<T>::GetSize(){
	return size;
}
template <typename T>
Node<T>* LinkedList<T>::GetHead(){
	return head;
}
template <typename T>
Node<T>* LinkedList<T>::GetTail(){
	return tail;
}
