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
	Marshal(int cNum, int tellerNum, int simTime, int avgServeTime);
	~Marshal();
	//gets the lines for the tellers set up
	static void initTellers();
	//finds a customer for the teller,
	//returns null if there are no more
	static Customer reqCustomer();
	//gets the sum of the wait times from
	//the tellers
	static int runSum();
private:
	static EventQueue eventQ;
	static float clock;
	//this is the single customer queue
	static CustQueue customerQ;
	//this is the list of tellers
	static ListTell listTell;
	//this is the list of serviced customers
	static ListCust listCust;
	static int cNum, tellerNum;
	static float avgServeTime, simTime;
};




#endif /* MARSHAL_H_ */
