/*
 * Event.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */
#include "Event.h"
#include<stdlib.h>
//TODO Create a custom event queue and get the makefile to switch between the two
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
//This returns the Id of the people
int Event::getId(){
	return id;
}
float Event::getTime(){
	return time;
}
//returns the type
EventType Event::getType(){
	return this->type;
}

bool operator <(Event const &e1, Event const &e2){
	 if(e1.time>e2.time){
		 return true;
	 }
	 else{
		 return false;
	 }
}



