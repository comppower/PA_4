#Written by Kent Libby and Corrin Courville

CFLAGS =-g

all: Main docs

Main: Main.o  Main.cpp
	g++ $(CFLAGS) -Wall Marshal.o Teller.o CustQueue.o Customer.o Event.o -o test
	
Marhsal.o: Marshal.cpp Marshal.h
	g++ $(CFLAGS) -Wall -c Marshal.cpp
	
Teller.o: Teller.cpp Teller.h CustQueue.o 
	g++ $(CFLAGS) -Wall -c Teller.cpp

CustQueue.o: CustQueue.cpp CustQueue.h Customer.o
	g++ $(CFLAGS) -Wall -c CustQueue.cpp
	
Customer.o: Customer.cpp Customer.h
	g++ $(CFLAGS) -Wall -c Customer.cpp
	
Event.o: Event.cpp Event.h
	g++ $(CFLAGS) -Wall -c Event.cpp

docs: 
	doxygen
	
clean:
	rm -f *.o *.exe *.out Main
	rm -f ./html ./latex

	