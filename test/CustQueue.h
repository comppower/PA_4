/*
 * CustQueue.h
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */
#include <list>
#include "Customer.h"

using ListC=std::list<Customer>;

#ifndef CUSTQUEUE_H_
#define CUSTQUEUE_H_
class CustQueue{
public:
	//these methods return the pointer of the
	//customer in the list (don't forget deletions)
	Customer *popTop();
	Customer *peekTop();
	int Length();
	void addCust(Customer *_c);
	//constructor
	CustQueue();
	~CustQueue();
private:
	ListC *_listC;
};

#endif /* CUSTQUEUE_H_ */
