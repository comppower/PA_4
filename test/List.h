/*
 * List.h
 *
 *  Created on: Oct 5, 2017
 *      Author: klibby
 */

#ifndef LIST_H_
#define LIST_H_
#include<iostream>
template <class T>
class Node{
public:
	Node(){
		this->_val=0;
		this->_next=0;
	}
	Node(T *_val){
		this->_val=_val;
		this->_next=0;
	}
	~Node(){
		delete _val;
	}
	void SetNext(Node *_next){
		this->_next= _next;
	}
	Node *GetNext(){
		return this->_next;
	}
	T *Get(){
		return this->_val;
	}
private:
	T *_val;
	Node *_next;
};

template <class T>
class List{
public:
	List(){
		this->_head=0;
		this->count=0;
	}
	void push_back(T val){
		//this bypasses the constructor for T
		//because it can't be accessed
		T *_temp = (T*) malloc(sizeof(T));
		//however it immediately sets it
		//to the val, which must be a valid
		//object
		*_temp=val;
		if(!_head){
			_head= new Node<T>(_temp);
			count++;
		}
		else{
			Node<T> *_curNode= new Node<T>;
			_curNode=_head;
			while(_curNode->GetNext()){
				_curNode=_curNode->GetNext();
			}
			_curNode->SetNext(new Node<T>(_temp));
			count++;
		}
	}
	T at(int index){
		if(index>=count){
			std::cout<<"out of bounds call"<<std::endl;
		}
		Node<T> *_curNode= new Node<T>;
		_curNode=_head;
		for(int i=0; i<index; i++){
			_curNode=_curNode->GetNext();
		}
		return *(_curNode->Get());
	}
	void erase(int index){
		if(index>=count){
			std::cout<<"out of bounds call"<<std::endl;
		}
		Node<T> *_curNode= new Node<T>;
		Node<T> *_temp= new Node<T>;
		_curNode=_head;
		//stops before it hits the actual
		//item
		for(int i=0; i<index-1; i++){
			_curNode=_curNode->GetNext();
		}
		_temp=_curNode->GetNext();
		_curNode->SetNext(_temp->GetNext());
		count--;
		delete _temp;
	}
	T pop_front(){
		Node<T> *_newHead= new Node<T>();
		Node<T> headVal=*_head;
		_newHead=_head->GetNext();
		delete _head;
		_head=_newHead;
		count--;
		return *(headVal.Get());
	}
	void clear(){
		run_clear(_head);
		delete _head;
		_head=0;
		count=0;
	}
private:
	Node<T> *_head;
	int count;
	void run_clear(Node<T> *_head){
		if(_head->GetNext()){
			run_clear(_head->GetNext());
			delete _head->GetNext();
			_head->SetNext(0);
		}
	}
};


#endif /* LIST_H_ */
