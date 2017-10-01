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
	const float getInTime();
	const float getOutTime();
	void setOutTime(float timeOut);
	const int getId();
	//constructor
	Customer(float timeIn, int id);
	~Customer();
private:
	int id;
	float timeIn;
	float timeOut;
};

#endif /* CUSTOMER_H_ */
