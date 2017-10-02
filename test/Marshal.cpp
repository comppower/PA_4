/*
 * Marshal.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */

#include "Marshal.h"
#include "Teller.h"
#include <cstdlib>
#include <iostream>

//sets up the marshaller varaibles
//these are just placeholders before init can be called
EventQueue *Marshal::_eventQ =new EventQueue();
bool Marshal::singleQ=true;
float Marshal::clock =0;
CustQueue *Marshal::_customerQ = new CustQueue();
vectTell *Marshal::_listTell=new std::vector<Teller>(0);
ListCust *Marshal::_servedCust= new ListCust();
int Marshal::cNum=0;
int Marshal::tellerNum=0;
float Marshal::serveTime=0;
float Marshal::simTime=0;
int Marshal::cId=0;
int Marshal::tId=0;

//because this is a static class
//the constructor doesn't need to be called
//or do anything. This is done via init
Marshal::Marshal(){}

/**
 * goes through and adds the customer events to the list
 * initializes the teller list. It also initializes the
 * breaks for the teller
 */
void Marshal::init(int cNum, int tellerNum, int simTime, int avgServeTime){
	for(int i=0; i<cNum; i++){
		float time= simTime*(rand()/float(RAND_MAX));
		_listTell=new std::vector<Teller>(tellerNum);
		Event *_e=new Event(time, EventType::enqCust, Marshal::cId++);
		_eventQ->push(*_e);
	}
}

void Marshal::InitTellers(){
	if(singleQ){
		for(uint i=0; i<_listTell->size(); i++){
			Teller *_t = new Teller(tId++);
		}
	}
}

void Marshal::EnqEvent(Event *_e){
	_eventQ->push(*_e);
}

void Marshal::ReqCustomer(int id){
	if(singleQ){
		if(_customerQ->Length()>0){
			Teller temp = _listTell->at(id-1);
			temp.qCust(_customerQ->popTop());
		}
	}
}

int Marshal::RunSum(){
	return 0;
}

void Marshal::StoreCust(Customer *_c){
	_servedCust->push_front(*_c);
}

float Marshal::now(){
	return clock;
}

float Marshal::avgServeTime(){
	return serveTime;
}

//prints the event queue
/*Event e=_eventQ->top();
while(!_eventQ->empty()){
	std::cout<<e.getTime()<<std::endl;
	_eventQ->pop();
	e=_eventQ->top();
}*/
