#Written by Kent Libby and Corrin Courville

CFLAGS =-g

all: Main docs

Main: Main.o 

Marhsal.o: Marshal.cpp 
	
Teller.o: CustQueue.o 

CustQueue.o: CustQueue.cpp CustQueue.h Customer.o
	g++ $(CFLAGS) -Wall -c CustQueue.cpp
	
Customer.o: Customer.cpp Customer.h
	g++ $(CFLAGS) -Wall -c Customer.cpp
	
Event.o: Event.cpp Event.h
	g++ $(CFLAGS) -Wall -c Event.cpp