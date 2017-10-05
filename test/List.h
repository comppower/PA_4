/*
 * List.h
 *
 *  Created on: Oct 5, 2017
 *      Author: klibby
 */

#ifndef LIST_H_
#define LIST_H_

template <class T>
class Node{
public:
	Node(T val){
		this->val=val;
		this->_next=0;
	}
	void SetNext(T *_next){
		this->_next=val;
	}
	T Get(){
		return this->val;
	}
private:
	T val;
	Node *_next;
};

class List{

};


#endif /* LIST_H_ */
