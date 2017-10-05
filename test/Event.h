/*c
 * Event.h
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */

#ifndef EVENT_H_
#define EVENT_H_

enum EventType {enqCust, reqCust, compRest, compServe};

class Event{
public:
	/**
	 * Event hold what type of event that it is
	 * teller holds it's own action classes to perform
	 * the service on the customer so data can be kept togther
	 * @param time time of clock
	 * @param type type of even
	 * @param id id number
	 */
	Event(float time, EventType type, int id); //constructor
	Event(float time, EventType type); //constructor
	~Event(); //destructor for an event
	/**
	 * getID returns the id of either the teller or customer
	 */
	int getId();  //getter function for id
	//bool operator<(Event e1, Event e2);
	/**
	 * getType returns the type of event that it is
	 * being either an even or a customer
	 */
	EventType getType(); //getter function for the type of event
	/**
	 * getTime returns the current time on the clock
	 */
	float getTime(); //getter function for the time
	/**
	 * operator overloads the operator so the built in
	 * priority queue can work
	 */
	friend bool operator < (Event const &, Event const &); //
private:
	//Defined in Event.cpp
	float time;
	int id;
	EventType type;
};




#endif /* EVENT_H_ */
