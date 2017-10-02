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
Teller::Teller(int id){
	this->id=id;
	_cQueue=new CustQueue();
	available = true;
}

Teller::~Teller(){
	delete _cQueue;
}

void Teller::ReqService(){
	//see if theres anyone else to serve
	if(_cQueue->Length()>0){
		Event *_e = new Event(Teller::GetCompServeTime(), EventType::compServe, id);
		Marshal::EnqEvent(_e);
		available=false;
	}
	//otherwise ask the marshal for a customer
	else{
		Marshal::ReqCustomer(id);
		//if there's still no customer then go on "break"
		if(_cQueue->Length()==0){
			available=false;
			Event *_e = new Event(Teller::GetRestTime(), EventType::compRest);
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
}

/**
 * @returns the time the rest is over
 */
int Teller::GetRestTime(){
	return Marshal::now()+(tRest*rand()/float(RAND_MAX));
}

int Teller::GetCompServeTime(){
	return Marshal::now()+(Marshal::avgServeTime()*rand()/float(RAND_MAX));
}

