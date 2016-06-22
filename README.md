# second-programming-homework
This homework have 2 stages: the first one is related with the MESI cache coherence protocol simulator, the second one is about paralel programming

For MESI cache coherence protocol simulator

	1- To compile the source code and make the executable, go to ./cache_coherence directory and run 'make' from the terminal

		make
      
	2- To run the program, execute the following command from the terminal:

		zcat memory-trace-gcc.trace.gz  ./main 
      
	3- Wait for a few senconds, then the program will show the reslt for miss rate.

	NOTE: The "memory-trace-gcc.trace.gz" file isn't included in this repository, so you need to add it to the directory of your cloned repository.


For Eratostenes programms:

	To excecute the sequential version you have to use these commands through 
	the terminal:

	- To compile: g++ -o salidaSec eratostSec.cpp 

	- To execute: ./salidaSec




	To excecute the paralel version you have to use these commands through 
	the terminal:
	
	- To compile: mpicc -o salidaParalelo eratostParal.c -lmpi
	- To excecute: mpirun -np 4 salidaParalelo


	the number "4" in the last means the number of proccesses