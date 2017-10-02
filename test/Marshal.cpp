/*
 * Marshal.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */

#include "Marshal.h"
#include <cstdlib>
#include <iostream>

/**
 * goes through and adds the customer events to the list
 * initializes the teller list. It also initializes the
 * breaks for the teller
 */
EventQueue *Marshal::_eventQ =new EventQueue();
float Marshal::clock =0;
CustQueue *Marshal::_customerQ = new CustQueue();
ListTell *Marshal::_listTell=new ListTell();
ListCust *Marshal::_servedCust= new ListCust();
int Marshal::cNum=0;
int Marshal::tellerNum=0;
float Marshal::serveTime=0;
float Marshal::simTime=0;
int Marshal::cId=0;
int Marshal::tId=0;

Marshal::Marshal(){}
void Marshal::init(int cNum, int tellerNum, int simTime, int avgServeTime){
	for(int i=0; i<cNum; i++){
		float time= simTime*(rand()/float(RAND_MAX));
		Event *_e=new Event(time, EventType::enqCust, Marshal::cId++);
		_eventQ->push(*_e);
	}
	Event e=_eventQ->top();
	while(!_eventQ->empty()){
		std::cout<<e.getTime()<<std::endl;
		_eventQ->pop();
		e=_eventQ->top();
	}
}

void Marshal::InitTellers(){

}

void Marshal::EnqEvent(Event *_e){

}

void Marshal::ReqCustomer(int id){

}

int Marshal::RunSum(){
	return 0;
}

void Marshal::StoreCust(Customer *_c){

}

float Marshal::now(){
	return 0;
}

float Marshal::avgServeTime(){
	return 0;
}
