/*
 * Marshal.h
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */

#ifndef MARSHAL_H_
#define MARSHAL_H_
#include <queue>
#include "CustQueue.h"
#include "Teller.h"
#include "Event.h"

using EventQueue=std::priority_queue<Event>;
using ListCust=std::list<Customer>;
using ListTell=std::list<Teller>;

//Marshal is the C++ equivalent of a static class
//all of the methods are static because there will only
//ever be 1 instance required
class Marshal{
public:
	static void initTellers();
	static Customer reqCustomer();
	//gets the sum of the wait times from
	//the tellers
	static int runSum();
private:
	static EventQueue eventQ;
	static float clock;
	//this is the single customer queue
	static CustQueue customerQ;
	static ListTell listTell;
	//this is the list of serviced customers
	static ListCust listCust;
};




#endif /* MARSHAL_H_ */
