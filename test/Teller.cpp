/*
 * Teller.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */

#include "Teller.h"
#include "Marshal.h"

Teller::Teller(int id){
	this->id=id;
	cQueue=new CustQueue();
	tRest=600;
	present = true;
}



