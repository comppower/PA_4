/*
 * Teller.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */

#include "Teller.h"
#include "Marshal.h"
#include <stdlib.h>
#include <cstdlib>
#include <iostream>

/**
 * This inits a teller and has it ask for a customer
 */
Teller::Teller(int id){
	this->id=id;
	_cQueue=new CustQueue();
	available = true;
	Event *_e = new Event(Marshal::now(), EventType::reqCust, id);
	Marshal::EnqEvent(_e);
}
/**
 * default constructor for vector list
 */
Teller::Teller(){
	this->id=-1;
	_cQueue=new CustQueue();
	available=false;
}
Teller::~Teller(){
	//delete _cQueue;
}

void Teller::ReqService(){
	//see if theres anyone else to serve
	if(_cQueue->Length()>0){
		Event *_e = new Event(Teller::GetCompServeTime(), EventType::compServe, id);
		Marshal::EnqEvent(_e);
	}
	//otherwise ask the marshal for a customer
	else{
		//this puts the customer into the queue
		//Marshal::ReqCustomer(id);
		//if there's still no customer then go on "break"
		if(_cQueue->Length()==0){
			available=false;
			Event *_e = new Event(Teller::GetRestTime(), EventType::compRest, id);
			Marshal::EnqEvent(_e);
		}
		else{
			Event *_e = new Event(Teller::GetCompServeTime(), EventType::compServe, id);
			Marshal::EnqEvent(_e);
		}
	}
}

void Teller::CompService(){
	//creates customer with placeholder values
	Customer *_c = new Customer(-1,-1);
	_c=_cQueue->popTop();
	_c->setOutTime(Marshal::now());
	Marshal::StoreCust(_c);
	//ask the Marshal for a customer
	Event *_e = new Event(Marshal::now(), EventType::reqCust, id);
	Marshal::EnqEvent(_e);
}

void Teller::CompRest(){
	Event *_e = new Event(Marshal::now(), EventType::reqCust, id);
	Marshal::EnqEvent(_e);
}
/**
 * @returns the time the rest is over
 */
int Teller::GetRestTime(){
	return Marshal::now()+((tRest*rand())/float(RAND_MAX));
}

int Teller::GetCompServeTime(){
	return Marshal::now()+((Marshal::avgServeTime()*rand())/float(RAND_MAX));
}

void Teller::qCust(Customer *_c){
	_cQueue->addCust(_c);
}

int Teller::GetId(){
	return id;
}
