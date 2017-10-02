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


typedef std::priority_queue<Event> EventQueue;
using ListCust=std::list<Customer>;
using ListTell=std::list<Teller>;

//Marshal is the C++ equivalent of a static class
//all of the methods are static because there will only
//ever be 1 instance required
class Marshal{
public:
	static void init(int cNum, int tellerNum, int simTime, int avgServeTime);
	~Marshal();
	//gets the lines for the tellers set up
	static void initTellers();
	//this enqueues an event based on the
	//time it occurs
	static void EnqEvent(Event *_e);
	//puts a customer in the teller's
	//queue if one is available
	static void ReqCustomer(int id);
	//gets the sum of the wait times from
	//the tellers
	static int RunSum();
	//puts the customer into the list of
	//serviced customers
	static void StoreCust(Customer *_c);
	//returns the current time
	static float now();
	//returns the average service time
	static float avgServeTime();

private:
	static EventQueue *_eventQ;
	static float clock;
	//this is the single customer queue
	static CustQueue *_customerQ;
	//this is the list of tellers
	static ListTell listTell;
	//this is the list of serviced customers
	static ListCust *_listCust;
	static int cNum, tellerNum;
	static float serveTime, simTime;
	static int cId, tId;
};




#endif /* MARSHAL_H_ */
