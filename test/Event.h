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
	Event(float time, EventType type, int id);
	Event(float time, EventType type);
	~Event();
	int getId();
	//bool operator<(Event e1, Event e2);
	EventType getType();
	float time;
private:
	int id;
	EventType type;
};




#endif /* EVENT_H_ */
