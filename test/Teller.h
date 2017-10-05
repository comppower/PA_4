/*
 * Teller.h
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */
#include "CustQueue.h"

#ifndef TELLER_H_
#define TELLER_H_

class Teller{
public:
	void ReqService();
	void CompService();
	void CompRest();
	void qCust(Customer *_c);
	int CustQSize();
	bool IsAvailable();
	Customer PullCust(int index);
	//gets the time the rest will be done
	float GetRestTime();
	int GetId();
	//constructors
	Teller(int id);
	Teller();
	~Teller();
private:
	//gets the time the service will be done
	float GetCompServeTime();
	CustQueue *_cQueue;
	//total rest time
	static const int tRest=5;
	bool available;
	float totalDownTime;
	int id;
};




#endif /* TELLER_H_ */
