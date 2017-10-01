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
	void reqService();
	void compService();
	//constructors
	Teller(int id);
private:
	CustQueue cQueue;
	//total rest time
	int tRest;
	bool present;
	int id;
};




#endif /* TELLER_H_ */
