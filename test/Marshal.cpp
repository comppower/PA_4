/*
 * Marshal.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */

#include "Marshal.h"
#include <cstdlib>

/**
 * goes through and adds the customer events to the list
 * initializes the teller list. It also initializes the
 * breaks for the teller
 */
void Marshal::init(int cNum, int tellerNum, int simTime, int avgServeTime){
	cId=0; tId=0;
	for(int i=0; i<cNum; i++){
		float time= simTime*rand()/float(RAND_MAX);
		Event *_e=new Event(time, EventType::enqCust, Marshal::cId++);
		_eventQ->push(*_e);
	}

}


