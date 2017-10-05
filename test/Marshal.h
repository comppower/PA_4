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
using VectTell=std::vector<Teller>;
using TempListTell=std::list<Teller>;
//Marshal is the C++ equivalent of a static class
//all of the methods are static because there will only
//ever be 1 instance required
class Marshal{
public:
	/**
	 * init goes through and adds the customer events to the list
	 *initializes the teller list and the breaks for the tellers
	 *@param cNum customer number
	 *@param tellerNum teller number
	 *@param simTime simulation run time
	 *@param avgServiceTime average service time
	 */
	static void init(int cNum, int tellerNum, int simTime, int avgServeTime);
	~Marshal();
	/**
	 * InitTellers gets the lines for the tellers set up
	 */
	static void InitTellers();
	/**
	 * EnqEvent enqueues an event based on the
	 * time it occurs
	 */
	static void EnqEvent(Event *_e);
	/**
	 * ReqCustomer puts a customer in the
	 * teller's queue if one is available
	 * @param id id of the customer
	 */
	static void ReqCustomer(int id);
	/**
	 * RunSim runs the simulation
	 */
	static void RunSim();
	/**
	 * printEQ prints the event queue
	 */
	static void printEQ();
	/**
	 * CalcSum prints statistics of the
	 * simulation
	 */
	static void CalcStat();
	/**
	 * StoreCust puts the customer
	 * into the list of serviced customers
	 * @param *_c is a pointer to the customer
	 */
	static void StoreCust(Customer *_c);

	/**
	 * now returns the current time
	 */
	static float now();
	/**
	 * avgServiceTime returns the
	 * average service time
	 */
	static float avgServeTime();
	/**
	 * getSimTime returns the current
	 * simulation time
	 */
	static float getSimTime();
	static bool singleQ;
private:
	Marshal();
	/**
	 * EnQCustFromIndex enqueues the customer
	 * from the given index
	 * @param index customer index
	 */
	static void EnQCustFromIndex(int index);
	/**
	 * ProcTellerReq proctors a teller request
	 */
	static void ProcTellerReq();
	/**
	 * *GetSmallestQueue returns the smalles of
	 * the tellers' queues
	 */
	static TempListTell *GetSmallestQueue();
	static EventQueue *_eventQ;
	static float clock;
	//this is the single customer queue
	static CustQueue *_customerQ;
	//this is the list of tellers
	static VectTell listTell;
	//this is the list of serviced customers
	static ListCust *_servedCust;
	static int cNum, tellerNum;
	static float serveTime, simTime;
	static int cId, tId;
};




#endif /* MARSHAL_H_ */
