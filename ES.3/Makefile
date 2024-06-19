CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio3.1.exe : esercizio3.1.o Random.o function.o
	$(CC) Random.o esercizio3.1.o function.o -o esercizio3.1.exe


esercizio3.1.o : esercizio3.1.cpp function.h
	$(CC) -c esercizio3.1.cpp -o esercizio3.1.o $(CFLAGS)



Random.o : Random.cpp Random.h
	$(CC) -c Random.cpp -o Random.o $(CFLAGS)

function.o : function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS)

clean :
	rm *.o esercizio3.1.exe seed.out
