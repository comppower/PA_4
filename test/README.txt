Fixed makefile issue. Program still has trouble running

Summary of the program:
This program run a simulation of a certain amount of customers and tellers 
over a certain amount of time and average service time. The program takes in 
these values from the command line and generates a queue of events that reflect 
events that would happen in a bank: the arrival of a customer, the break of a bank teller, the servicing of a customer by a bank teller, and the waiting of a customer in a line for service. The program terminates when the time for the sim runs out of there aren’t any events left in the event queue. When the program terminates, it then calculates and outputs the total amount of time the simulation was running, the total amount of customers served, the number of tellers, type of queueing (one per teller or common), the average amount of time the customers spent in the bank and its standard deviation.       

How the program runs:
This program takes in a number of customers, a number of tellers, a 
simulation time and and an average service time. The simulation and 
service times are floats while the number of customers and the number 
of tellers are both integers. The program has a customer and a teller 
class that create customer and teller objects. A customer holds its time 
in, its time out and its id number. A teller holds its id number, its customer 
queue (if individual). Everything in the program is run through the marshal class. The marshal class keeps track of the clock, customers and where they are, the event queue, the tellers and whether they’re serving a customer, requesting a customer, or on a break. 

Limitations of the program:
One limitation of this program is that there always needs to be at 
least one teller at the bank. 

There is also a problem with the program accessing unrestricted memory. 
This comes from the fact the program erases and rewrites the tellers to 
update them which can cause problems

The program cannot output the data from the tests

Problems we encountered:
Choosing whether to use pointers or the actual values was a problem we encountered. Another problem we had was determining architecture and sharing information between classes. 


Due to the requirement discussed in class that we are not able to use the vector and
built in lists we attempted to create our own list class. However we ran into numerous 
segfaults late in the development and were unable to correct them. This caused us to have
to revert and still deal with the issues that were generated from the old implementation
because of this neither version was able to function correctly.