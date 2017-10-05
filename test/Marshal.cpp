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
ListTell Marshal::listTell;
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
	Marshal::tellerNum=tellerNum;
	serveTime=avgServeTime;
	Marshal::simTime=simTime;
	Marshal::listTell= List<Teller>();
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
	for (int i = 0; i < listTell.size(); i++) {
		Event *_e=new Event(0,EventType::reqCust,(int) i);
		Marshal::EnqEvent(_e);
	}
}
void Marshal::InitTellers(){
	for(int i=0; i<tellerNum; i++){
		/*Teller *t = new Teller();
		*t=Teller(tId++);*/
		listTell.push_back(new Teller(tId++));
	}
	for(int i=0; i<listTell.size(); i++){
		std::cout<<listTell.at(i).GetId()<<std::endl;
	}
	printEQ();
}

void Marshal::EnQCustFromIndex(int index) {
	bool found = false;
	Teller *t = new Teller();
	for (int i = 0; !found && i < listTell.size(); i++) {
		*t=listTell.at(i);
		if (t->GetId() == index) {
			found = true;
			listTell.erase(i);
			if(singleQ){
				if (_customerQ->Length() > 0) {
					t->qCust(_customerQ->popTop());
				}
			}
			else if(!singleQ){
				t->qCust(new Customer(Marshal::now(), cId++));
			}
			t->ReqService();
			listTell.push_back(t);
		}
	}
	delete t;
}
TempListTell *Marshal::GetSmallestQueue(){
	TempListTell *_custLineOpns = new TempListTell();
	try{
		//finds the first available teller
		int startIndex=0;
		Teller *t=new Teller();
		*t = listTell.at(startIndex);
		while(!t->IsAvailable()){
			startIndex++;
			*t=listTell.at(startIndex);
		}
		int minQueue=t->CustQSize();
		int count;
		for (int i = startIndex; i < listTell.size(); i++) {
			t=new Teller();
			*t = listTell.at(i);
			if (t->CustQSize() < minQueue&& t->IsAvailable()) {
				minQueue = t->CustQSize();
				_custLineOpns->clear();
				count = 0;
				_custLineOpns->push_back(t);
			} else if (t->CustQSize() == minQueue&& t->IsAvailable()) {
				_custLineOpns->push_back(t);
				count++;
			}
			else{
				delete t;
			}
		}

	}
	catch(const std::out_of_range& e){
		std::cout<<"The teller size is less than 0"<<std::endl;
	}
	return _custLineOpns;
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
				_customerQ->addCust(new Customer(Marshal::now(), cId++));
			} else if (!singleQ) {
				try {
					//the method that returns the list
					TempListTell *_listOpns=GetSmallestQueue();
					//pick a random member from the list
					int targetIndex = (int) lround(_listOpns->size() * (rand() / float(RAND_MAX)));
					for (int i = 0; i < targetIndex; i++) {
						_listOpns->pop_front();
					}
					//find the member and enqueue the customer and return it
					//to the list
					EnQCustFromIndex(_listOpns->front().GetId());

				} catch (const std::out_of_range& e) {
					std::cerr << "Out of range error " << e.what() << std::endl;
					std::cout << "Check teller list size enq" << std::endl;
				}
			}
			break;

		case reqCust: {
			if (singleQ) {
				EnQCustFromIndex(e.getId());
			}
			//make sure to grab the 2nd person off of whatever queue and
			//make sure it gets removed from the queue
			else if (!singleQ) {
				try {
					//this is the list of tellers with more than
					//2 people in their queue
					TempListTell *_listOpns = new TempListTell();
					//elements in the list
					int count = -1;
					//starting at 0 to ensure teller 0 is checked
					for (int i = 0; i < listTell.size(); i++) {
						Teller *t = new Teller();
						*t = listTell.at(i);
						if (t->CustQSize() > 1&& t->IsAvailable()) {
							_listOpns->push_back(t);
							count++;
						}
						else{
							delete t;
						}

					}
					//if the count is -1 don't add a customer and
					//just call reqService

					int pullID=-1;
					if (count > -1) {
						//pick a random member from the list
						int targetIndex = (int) roundl(count * (rand() / float(RAND_MAX)));
						for (int i = 0; i < targetIndex; i++) {
							_listOpns->pop_front();
						}
						//and get its ID
						pullID = _listOpns->front().GetId();
					}
					//find and pull the customer from the right teller
					bool pulledCust=false;
					Customer toMove = Customer(-1, -1);
					for (int i = 0; !pulledCust&&pullID>=0; i++) {
						Teller *t = new Teller();
						*t=listTell.at(i);
						if (t->GetId() == pullID) {
							pulledCust = true;
							listTell.erase(i);
							toMove=t->PullCust(1);
							listTell.push_back(t);
						}
						else {
							delete t;
						}
					}
					//find the teller to put the customer into
					bool putCust=false;
					for (int i = 0; !putCust; i++) {
						Teller *t = new Teller();
						*t=listTell.at(i);
						if (t->GetId() == e.getId()) {
							putCust = true;
							listTell.erase(i);
							if(pullID>=0){
								t->qCust(&toMove);
							}
							t->ReqService();
							listTell.push_back(t);
						}
						else{
							delete t;
						}
					}
					delete _listOpns;
				}
				catch (const std::out_of_range& e) {
					std::cerr << "Out of range error " << e.what() << std::endl;
					std::cout << "Check teller list size req" << std::endl;
				}
			}
			break;
		}
		case compRest:{
			bool found=false;
			for (int i = 0; !found && i < listTell.size(); i++) {
				Teller *t = new Teller();
				*t=listTell.at(i);
				if (t->GetId() == e.getId()) {
					found = true;
					listTell.erase(i);
					t->CompRest();
					listTell.push_back(t);
				}
				else{
					delete t;
				}
			}
			break;
		}
		case compServe:{
			bool found=false;
			for (int i = 0; !found && i < listTell.size(); i++) {
				Teller *t = new Teller();
				*t=listTell.at(i);
				if (t->GetId() == e.getId()) {
					found = true;
					listTell.erase(i);
					t->CompService();
					listTell.push_back(t);
				}
				else{
					delete t;
				}
			}
			break;
		}
		}//switch
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
	ListCust temp = *_servedCust;
	for(int i=0; i<temp.size(); i++){
		Customer c= _servedCust->front();
		sum+=c.getOutTime();
		sum-=c.getInTime();
		_servedCust->pop_front();
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

