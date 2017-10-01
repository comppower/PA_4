/*
 * Customer.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */
#include "Customer.h"

Customer::Customer(float timeIn, int id){
	this->timeIn=timeIn;
	this->timeOut=-1;
	this->id=id;
}

const float Customer::getInTime(){
	return this->timeIn;
}

const float Customer::getOutTime(){
	return this->timeOut;
}
const int Customer::getId(){
	return id;
}
void Customer::setOutTime(float timeOut){
	this->timeOut=timeOut;
}


