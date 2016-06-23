OBJ1 = eratostSec.cpp
OBJ2 = eratostParal.c
CC = g++
MIP = mpicc
MFLAG = -lmpi
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -pedantic
LFLAGS = -Wall $(DEBUG) -pedantic
TARGET1 = salidaSec
TARGET2 = salidaParalelo
$(TARGET1) : $(OBJ1) $(TARGET2)
	$(CC) $(OBJ1) -o $(TARGET1)
$(TARGET2) : $(OBJ2)
	$(MIP) -o $(TARGET2) $(OBJ2) $(MFLAG) -std=c99
clean:
	rm -f *.o *~ $(TARGET1) $(TARGET2) 
