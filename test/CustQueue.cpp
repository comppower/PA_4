/*
 * CustQueue.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */
#include "CustQueue.h"
#include <stdlib.h>
CustQueue::CustQueue(){
	_listC=new ListC();
}
CustQueue::~CustQueue(){
	_listC->clear();
	free(_listC);
}
void CustQueue::addCust(Customer *_c){
	_listC->push_back(*_c);
}
/**
 * This looks at the top of the customer queue
 * and gets the customer stored without removing it
 */
Customer *CustQueue::peekTop(){
	//this creates a placeholder customer
	Customer *_c=new Customer(-1,-1);
	*_c=_listC->front();
	return _c;
}
/**
 * This gets the customer stored and removes it
 */
Customer *CustQueue::popTop(){
	//this creates a placeholder customer
	Customer *_c=new Customer(-1,-1);
	*_c=_listC->front();
	_listC->pop_front();
	return _c;
}

int CustQueue::Length(){
	return _listC->size();
}


