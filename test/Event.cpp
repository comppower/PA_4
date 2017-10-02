/*
 * Event.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */
#include "Event.h"
#include<stdlib.h>
//sets every aspect of the id
Event::Event(float time, EventType type, int id){
	this->time=time;
	this->type=type;
	this->id=id;
}
//Creates the event without the id
Event::Event(float time, EventType type){
	this->time=time;
	this->type=type;
	this->id=-1;
}
Event::~Event(){

}
//This returns the time of the event
const int Event::getTime(){
	return time;
}
//This returns the Id of the people
int Event::getId(){
	return id;
}
//This flips the definition of the operator for the queue
bool operator<(const Event e1, const Event e2){
	return e1.getTime() >e2.getTime();
}
//returns the type
EventType Event::getType(){
	return this->type;
}





