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
	//gets the time the rest will be done
	int GetRestTime();
	int GetId();
	//constructors
	Teller(int id);
	Teller();
	~Teller();
private:
	//gets the time the service will be done
	int GetCompServeTime();
	CustQueue *_cQueue;
	//total rest time
	static const int tRest=10;
	bool available;
	int id;
};




#endif /* TELLER_H_ */
