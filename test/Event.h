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
	Event(int time, EventType type, int id);
	Event(int time, EventType type);
	~Event();
	int getTime();
	int getId();
	bool operator <(const Event *_e1);
	EventType getType();
private:
	int time;
	int id;
	EventType type;
};




#endif /* EVENT_H_ */
