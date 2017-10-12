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
	_cQueue=new List<Customer>();
	available = true;
	totalDownTime=0;
}
/**
 * default constructor for vector list
 */
Teller::Teller(){
	this->id=-1;
	_cQueue=new List<Customer>();
	available=false;
	totalDownTime=0;
}
Teller::~Teller(){
	delete _cQueue;
}

void Teller::ReqService(){
	//see if exactly one person in the queue. If there's more than one, the subsequent
	//calls will be handled by the compService action
	if(_cQueue->size()==1){
		int outTime= Teller::GetCompServeTime()
		Event *_e = new Event(outTime, EventType::compServe, id);
		available=false;
		_cQueue->pop_front()->setOutTime(outTime);
		Marshal::EnqEvent(_e);
	}
	//otherwise ask the marshal for a customer
	else{
		//if there's still no customer then go on "break"
		if(_cQueue->size()==0){
			available=false;
			float restTime =Teller::GetRestTime();
			totalDownTime+=restTime;
			Event *_e = new Event(restTime, EventType::compRest, id);
			Marshal::EnqEvent(_e);
		}
		//otherwise complete service
		/*else{
			Event *_e = new Event(Teller::GetCompServeTime(), EventType::compServe, id);
			Marshal::EnqEvent(_e);
		}*/
	}
}

//could be a problem with pointers
void Teller::CompService(){
	//creates customer with placeholder values
	//ask the Marshal for a customer
	if(_cQueue->size()<1){
		available=true;
		Event *_e = new Event(Marshal::now(), EventType::reqCust, id);
		Marshal::EnqEvent(_e);
	}
	else{
		Event *_e = new Event(Teller::GetCompServeTime(), EventType::compServe, id);
		Marshal::EnqEvent(_e);
	}

}

void Teller::CompRest(){
	//this enqueues from reqCust because when the
	//teller rests there are no more customers in its queue so it
	//needs to attempt to get another one
	if(Marshal::now()<Marshal::getSimTime()){
		available=true;
		Event *_e = new Event(Marshal::now(), EventType::reqCust, id);
		Marshal::EnqEvent(_e);
	}
	//if the sim is over dont enqueue
	else{
		available=false;
	}

}
int Teller::CustQSize(){
	return _cQueue->size();
}
/**
 * @returns the time the rest is over
 */
float Teller::GetRestTime(){
	return Marshal::now()+tRest*(rand()/float(RAND_MAX));
}

float Teller::GetCompServeTime(){
	return Marshal::now()+2*Marshal::avgServeTime()*(rand()/float(RAND_MAX));
}

void Teller::qCust(Customer *_c){
	_cQueue->push_back(_c);
}

int Teller::GetId(){
	return id;
}

bool Teller::IsAvailable(){
	return available;
}
Customer *Teller::PullFront(){
	return _cQueue->pop_front();
}
