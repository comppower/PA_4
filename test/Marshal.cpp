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
#include <math.h>



//sets up the marshaller varaibles
//these are just placeholders before init can be called
EventQueue *Marshal::_eventQ =new EventQueue();
bool Marshal::singleQ=true;
float Marshal::clock =0;
ListTell *Marshal::_listTell=new ListTell();
ListCust *Marshal::_customerQ = new ListCust();
ListCust *Marshal::_servedCust= new ListCust();
int Marshal::cNum=0;
int Marshal::tellerNum=0;
float Marshal::serveTime=0;
float Marshal::simTime=0;
int Marshal::cId=0;
//this Id will be
//the location in the list
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
	Marshal::tellerNum=tellerNum;
	serveTime=avgServeTime;
	Marshal::simTime=simTime;
	Marshal::InitTellers();
	for(int i=0; i<cNum; i++){
		float time= simTime*(rand()/float(RAND_MAX));
		//set to 0 so all customers come in at beginning
		Event *_e=new Event(time, EventType::enqCust, Marshal::cId++);
		Marshal::EnqEvent(_e);
	}
	if(singleQ){
		Marshal::ProcTellerReq();
	}
}
void Marshal::ProcTellerReq(){
	for (int i = 0; i < _listTell->size(); i++) {
		Event *_e=new Event(0,EventType::reqCust,(int) i);
		Marshal::EnqEvent(_e);
	}
}
void Marshal::InitTellers(){
	for(int i=0; i<tellerNum; i++){
		_listTell->push_back(new Teller(tId++));
	}
	for(int i=0; i<_listTell->size(); i++){
		std::cout<<_listTell->at(i)->GetId()<<std::endl;
	}
	printEQ();
}

ListTell *Marshal::GetSmallestQueue(){

	//finds the first available teller
	int startIndex = 0;
	ListTell *_opns = new ListTell();
	int minSize = _listTell->at(0)->CustQSize();
	for (int i = 0; i < _listTell->size(); i++) {
		if(_listTell->at(i)->IsAvailable())
		{
			if (_listTell->at(i)->CustQSize() < minSize) {
				_opns->clear();
				_opns->push_back(_listTell->at(i));
			} else if (_listTell->at(i)->CustQSize() == minSize) {
				_opns->push_back(_listTell->at(i));
			}
		}
	}
	return _opns;
}

ListTell *Marshal::GetFilledQueues(){

	//finds the first available teller
	int startIndex = 0;
	ListTell *_opns = new ListTell();
	for (int i = 0; i < _listTell->size(); i++) {
		if(_listTell->at(i)->IsAvailable())
		{
			if (_listTell->at(i)->CustQSize()>0) {
				_opns->push_back(_listTell->at(i));
			}
		}
	}
	return _opns;
}
void Marshal::RunSim() {

	while (!_eventQ->empty()) {
		Event e = _eventQ->top();
		EventType type = e.getType();
		clock = e.getTime();
		//Creates a switch statement for a type
		switch (type) {
		case enqCust:
			if (singleQ) {
				_customerQ->push_back(new Customer(Marshal::now(), cId++));
			} else {
				//the method that returns the list
				ListTell *_listOpns = GetSmallestQueue();
				//pick a random member from the list
				int targetIndex = rand() % _listOpns->size();
				_listOpns->at(targetIndex)->qCust(
						new Customer(Marshal::now(), cId++));
				//find the member and enqueue the customer and return it
				//to the list
				delete _listOpns;
			}
			break;

		case reqCust: {
			if (singleQ) {
				Customer *_c = new Customer(Marshal::now(), cId++);
				_listTell->at(e.getId())->qCust(_c);
			}
			//make sure to grab the 2nd person off of whatever queue and
			//make sure it gets removed from the queue
			else if (!singleQ) {
				ListTell *_opns = Marshal::GetFilledQueues();
				if (_opns->size() < 1) {
					Teller *_t = _opns->at(rand() % _listTell->size());
					_listTell->at(e.getId())->qCust(_t->PullFront());
				}
				delete _opns;
			}
			break;
		}

		case compRest: {
			_listTell->at(e.getId())->CompRest();
			break;
		}
		case compServe: {
			_listTell->at(e.getId())->CompService();
			break;
		}
		}			//switch
		printEQ();
		//advances the event queue
		_eventQ->pop();
	}//while
}

void Marshal::EnqEvent(Event *_e){
	_eventQ->push(*_e);
}

void Marshal::ReqCustomer(int id){
	/*if(singleQ){
		if(_customerQ->Length()>0){
			Teller *temp = new Teller();
			*temp = listTell.at(id);
			temp.qCust(_customerQ->popTop());
		}
	}*/
}


float Marshal::CalcSum(){
	float sum=0;

	for(int i=0; i<_servedCust->size(); i++){
		Customer *c= _servedCust->at(i);
		sum+=c->getOutTime();
		sum-=c->getInTime();
	}
	return sum;
}

void Marshal::StoreCust(Customer *_c){
	_servedCust->push_back(_c);
	std::cout<<"Cust served: "<<_servedCust->size()<<std::endl;
}

float Marshal::now(){
	return clock;
}

float Marshal::avgServeTime(){
	return serveTime;
}

void Marshal::printEQ(){
	EventQueue temp = *_eventQ;
	while (!temp.empty()) {
		Event e = temp.top();
		switch (e.getType()) {
		case EventType::enqCust:
			std::cout << "Event Type: EnqCust Id: " <<e.getId() <<" Time: "<<e.getTime()<< std::endl;
			break;
		case EventType::reqCust:
			std::cout << "Event Type: ReqCust Id: " <<e.getId()<<" Time: "<<e.getTime()<< std::endl;
			break;
		case EventType::compRest:
			std::cout << "Event Type: CompRest Id: " <<e.getId()<<" Time: "<<e.getTime()<< std::endl;
			break;
		case EventType::compServe:
			std::cout << "Event Type: CompServe Id: " <<e.getId()<<" Time: "<<e.getTime()<< std::endl;
			break;
			temp.pop();
		}
		temp.pop();
	}
	std::cout << "End of current event queue---" << std::endl<<std::endl;
}

float Marshal::getSimTime(){
	return simTime;
}

