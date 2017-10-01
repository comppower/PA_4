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
	const Customer popTop();
	const Customer peekTop();
	void addCust(Customer *_c);
	//constructor
	CustQueue();
	~CustQueue();
private:
	ListC *_listC;
};

#endif /* CUSTQUEUE_H_ */
