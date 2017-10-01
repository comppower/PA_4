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
	Customer popTop();
	Customer peekTop();
	void addCust(Customer c);
private:
	ListC listC;
};

#endif /* CUSTQUEUE_H_ */
