/*
 * Main.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Event.h"
#include "Customer.h"
#include "CustQueue.h"


int main(){
	Customer *_c1 = new Customer(1, 1);
	CustQueue *_cq = new CustQueue();
	_cq->addCust(_c1);
	Customer *_c2=new Customer(1,2);
	_cq->addCust(_c2);
	//should show c1
	std::cout<<_cq->popTop()->getId()<<std::endl;
	std::cout<<_cq->popTop()->getId()<<std::endl;
	delete _c1;
	delete _c2;
	delete _cq;
	return 0;
}



