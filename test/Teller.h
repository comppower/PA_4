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
	//gets the time the rest will be done
	int GetRestTime();
	//constructors
	Teller(int id);
	~Teller();
private:
	//gets the time the service will be done
	int GetCompServeTime();
	CustQueue *_cQueue;
	//total rest time
	const int tRest=10;
	bool available;
	int id;
};




#endif /* TELLER_H_ */
