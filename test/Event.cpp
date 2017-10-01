/*
 * Event.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */
#include "Event.h"

//sets every aspect of the id
Event::Event(int time, EventType type, int id){
	this->time=time;
	this->type=type;
	this->id=id;
}
//Creates the event without the id
Event::Event(int time, EventType type){
	this->time=time;
	this->type=type;
	this->id=-1;
}
//This returns the time of the event
int Event::getTime(){
	return time;
}
//This returns the Id of the people
int Event::getId(){
	return id;
}
//This flips the definition of the operator for the queue
bool Event::operator <(const Event *_e1, const Event *_e2){
	return _e1->time > _e2->time;
}
//returns the type
EventType Event::getType(){
	return this->type;
}





