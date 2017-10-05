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
	/**
	 * getInTime returns the arrival time of a customer
	 */
	const float getInTime(); //getter for the time in
	/**
	 * getOutTime returns the departure time for a customer
	 */
	const float getOutTime(); //getter for the time out
	/**
	 * setOutTime sets the elapsed time for the customer
	 * @param timeOut time the customer leaves the bank
	 */
	void setOutTime(float timeOut);
	/**
	 * getId returns the id number of the customer
	 */
	const int getId(); //getter for the Id number
	/**
	 * Customer constructor for Customer
	 * @param timeIn time customer enters bank
	 * @param id id number of the customer
	 */
	Customer(float timeIn, int id); //constructor
	~Customer();//destructor
private:
	//defined in customer.cpp
	int id;
	float timeIn;
	float timeOut;
};

#endif /* CUSTOMER_H_ */
