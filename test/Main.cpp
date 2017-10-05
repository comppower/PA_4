/*
 * Main.cpp
 *
 *  Created on: Oct 1, 2017
 *      Author: klibby
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include "Event.h"
#include "Customer.h"
#include "CustQueue.h"
#include "Marshal.h"
#include "List"


int main(){
	srand(time(NULL));
	Marshal::init(14, 3, 10, 3);
	Marshal::RunSim();
	std::cout<<"Serve Time "<<Marshal::CalcSum()<<std::endl;

}

//test for adding customers
/*Customer *_c1 = new Customer(1, 1);
CustQueue *_cq = new CustQueue();
_cq->addCust(_c1);
Customer *_c2=new Customer(1,2);
_cq->addCust(_c2);
//should show c1
std::cout<<_cq->popTop()->getId()<<std::endl;
std::cout<<_cq->popTop()->getId()<<std::endl;
delete _c1;
delete _c2;
delete _cq;*/

//for pulling from a list at a specified point
/*
 * 	while(custTest.Length()>0){
		Customer c = custTest.PullAt(0);
		std::cout<<c.getId()<<std::endl;
	}
	std::cout<<custTest.Length()<<std::endl;
 */

//test for custom list
/*Customer c =Customer(0,0);
Customer *c2= new Customer(1,1);
Customer *c3 = new Customer(2,2);
Customer *c4=new Customer(3,3);
Node<Customer> n= Node<Customer>(c2);
Node<Customer> n2=Node<Customer>(c3);
n.SetNext(&n2);
std::cout<<n.GetNext()->Get()->getId()<<std::endl;
List<Customer> lc = List<Customer>();
lc.push_back(*c2);
lc.push_back(*c3);
lc.push_back(*c4);
lc.erase(1);
std::cout<<lc.at(1).getId()<<std::endl;
return 0;*/
