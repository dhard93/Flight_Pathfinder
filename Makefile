CC=g++
CFLAGS=-g -v

## Create the executable Run
Run:Type.o FlightMap.o main.o
	$(CC) Type.o FlightMap.o main.o -o Run

Type.o:Type.cpp
	$(CC) $(CFLAGS) -c Type.cpp

FlightMap.o:FlightMap.cpp
	$(CC) $(CFLAGS) -c FlightMap.cpp

main.o:main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm *.o
