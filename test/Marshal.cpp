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
vectTell Marshal::listTell;
CustQueue *Marshal::_customerQ = new CustQueue();
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
	listTell.reserve(tellerNum);
	for(int i=0; i<cNum; i++){
		float time= simTime*(rand()/float(RAND_MAX));
		//set to 0 so all customers come in at beginning
		Event *_e=new Event(0, EventType::enqCust, Marshal::cId++);
		Marshal::EnqEvent(_e);
	}
	Marshal::InitTellers();
}

void Marshal::InitTellers(){
	if(singleQ){
		for(uint i=0; i<listTell.capacity(); i++){
			Teller t = Teller(tId++);
			listTell.push_back(t);
		}
	}
	for(uint i=0; i<listTell.size(); i++){
		std::cout<<listTell.at(i).GetId()<<std::endl;
	}
	printEQ();
}

void Marshal::RunSim() {
	while (!_eventQ->empty()) {
		Event e = _eventQ->top();
		EventType type = e.getType();
		clock = e.getTime();
		//advances the event queue
		_eventQ->pop();
		//Creates a switch statement for a type
		bool found = false;
		switch (type) {
		case enqCust:
			if (singleQ) {
				_customerQ->addCust(new Customer(Marshal::now(), cId++));
			}
			break;

		case reqCust:
			for (uint i = 0; !found || i < listTell.size(); i++) {
				Teller t = listTell.at(i);
				if (t.GetId() == e.getId()) {
					found = true;
					listTell.erase(listTell.begin() + i);
					if (singleQ) {
						if (_customerQ->Length() > 0) {
							t.qCust(_customerQ->popTop());
							listTell.push_back(t);
						}
					}
				}
			}
			break;

		case compRest:
			for (uint i = 0; !found||i < listTell.capacity(); i++) {
				Teller t = listTell.at(i);
				if (t.GetId() == e.getId()) {
					found =true;
					listTell.erase(listTell.begin() + i);
					t.CompRest();
				}
			}
			break;

		case compServe:
			for (uint i = 0;  !found||i < listTell.capacity(); i++) {
				Teller t = listTell.at(i);
				if (t.GetId() == e.getId()) {
					found =true;
					listTell.erase(listTell.begin() + i);
					t.CompService();
					listTell.push_back(t);
				}
			}
			break;
		}//switch
		//printEQ();
	}//while
}

void Marshal::EnqEvent(Event *_e){
	_eventQ->push(*_e);
}

void Marshal::ReqCustomer(int id){
	if(singleQ){
		if(_customerQ->Length()>0){
			Teller temp = listTell.at(id);
			temp.qCust(_customerQ->popTop());
		}
	}
}


int Marshal::CalcSum(){
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

void Marshal::printEQ(){
	EventQueue temp = *_eventQ;
	Event e = temp.top();
	temp.pop();
	while (!temp.empty()) {
		switch (e.getType()) {
		case EventType::enqCust:
			std::cout << "Event Type: EnqCust Id: " << e.getId() << std::endl;
			break;
		case EventType::reqCust:
			std::cout << "Event Type: ReqCust Id: " << e.getId() << std::endl;
			break;
		case EventType::compRest:
			std::cout << "Event Type: CompRest Id: " << e.getId() << std::endl;
			break;
		case EventType::compServe:
			std::cout << "Event Type: CompServe Id: " << e.getId() << std::endl;
			break;
			temp.pop();
		}
		e = temp.top();
		temp.pop();
	}
	std::cout << "End of current event queue---" << std::endl;
}

//prints the event queue
/*Event e=_eventQ->top();
while(!_eventQ->empty()){
	std::cout<<e.getTime()<<std::endl;
	_eventQ->pop();
	e=_eventQ->top();
}*/
