/*
 * Customer.h
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_
class Customer{
public:
	int getInTime();
	int getOutTime();
	void setOutTime(int tIn, int id);
	Customer(int inTime);
	~Customer();
	int id;
private:
	int timeIn;
	int timeOut;
};

#endif /* CUSTOMER_H_ */
