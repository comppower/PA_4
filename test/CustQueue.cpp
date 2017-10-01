/*
 * CustQueue.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */
#include "CustQueue.h"

CustQueue::CustQueue(){
	_listC=new ListC();
}

void CustQueue::addCust(Customer *_c){
	_listC->push_back(*_c);
}

const Customer CustQueue::peekTop(){
	return _listC->front();
}

const Customer CustQueue::popTop(){
	return _listC->pop_front();
}


