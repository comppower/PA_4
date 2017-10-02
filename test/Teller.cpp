/*
 * Teller.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */

#include "Teller.h"
#include "Marshal.h"
#include<stdlib.h>
Teller::Teller(int id){
	this->id=id;
	_cQueue=new CustQueue();
	present = true;
}

Teller::~Teller(){
	delete _cQueue;
}


