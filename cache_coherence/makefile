OBJS = main.cpp cache_multilevel.o cache.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -pedantic
LFLAGS = -Wall $(DEBUG) -pedantic
TARGET = main
$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)
cache_multilivel.o : cache.o cache_multilivel.hh cache_multilivel.cpp
	$(CC) $(CFLAGS) cache_multilivel.cpp
cache.o : cache.hh cache.cpp
	$(CC) $(CFLAGS) cache.cpp
clean:
	rm -f *.o *~ $(TARGET)
