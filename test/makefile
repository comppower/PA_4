CFLAGS=-g

all: Main docs

Main: Main.o Teller.o Event.o 
	g++ $(CFLAGS) -Wall Marshal.o Teller.o Customer.o Event.o Main.o -o Main

Main.o: Main.cpp Marshal.o
	g++ $(CFLAGS) -Wall -c Main.cpp

Marhsal.o: Teller.o Marshal.cpp Marshal.h
	g++ $(CFLAGS) -Wall -c Marshal.cpp
	
Teller.o: Customer.o Teller.cpp Teller.h  
	g++ $(CFLAGS) -Wall -c Teller.cpp

#CustQueue.o: CustQueue.cpp CustQueue.h Customer.o
	#g++ $(CFLAGS) -Wall -c CustQueue.cpp
	
Customer.o: Customer.cpp Customer.h
	g++ $(CFLAGS) -Wall -c Customer.cpp
	
Event.o: Event.cpp Event.h
	g++ $(CFLAGS) -Wall -c Event.cpp

docs: 
	doxygen
	
clean:
	rm -f *.o *.exe *.out Main
	rm -rf ./html ./latex
