/*
 * CustQueue.h
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */
#include <list>
#include "Customer.h"

using ListC=std::list<Customer>;
using CustItr=ListC::iterator;

#ifndef CUSTQUEUE_H_
#define CUSTQUEUE_H_
class CustQueue{
public:
	//these methods return the pointer of the
	//customer in the list (don't forget deletions)
	/**
	 * *popTop gets customer stored without removing it
	 */
	Customer *popTop();
	/**
	 * *peekTop looks at the customer at the top
	 * of the queue and gets it stored without
	 * removing it
	 */
	Customer *peekTop();
	/**
	 * Length gets the length of the queue
	 */
	int Length(); //gets length of queue
	/**
	 * addCust adds a customer to the customer queue
	 * @param *_c a pointer to the customer to add to
	 * the customer queue
	 */
	void addCust(Customer *_c); //adds cust to list
	/**
	 *PullAt gets the customer from the designated location
	 *in the queue
	 *in @param index location of the cust to be pulled
	 */
	Customer PullAt(int index);
	/**
	 * CustQueue constructor to create a customer queue
	 */
	CustQueue(); 	//constructor
	~CustQueue(); //destructor
private:
	//defined in custQueue.cpp
	ListC *_listC;
};

#endif /* CUSTQUEUE_H_ */
