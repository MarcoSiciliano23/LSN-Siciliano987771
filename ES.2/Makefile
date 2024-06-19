CC = g++
CFLAGS = -Wall -O3 --std=c++11

all: esercizio2.1.exe esercizio2.2.exe

esercizio2.1.exe: esercizio2.1.o random.o function.o
	$(CC) random.o esercizio2.1.o function.o -o esercizio2.1.exe

esercizio2.2.exe: esercizio2.2.o random.o function.o
	$(CC) random.o esercizio2.2.o function.o -o esercizio2.2.exe

esercizio2.1.o: esercizio2.1.cpp function.h
	$(CC) -c esercizio2.1.cpp -o esercizio2.1.o $(CFLAGS)

esercizio2.2.o: esercizio2.2.cpp function.h
	$(CC) -c esercizio2.2.cpp -o esercizio2.2.o $(CFLAGS)

random.o: random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

function.o: function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS)

clean:
	rm *.o esercizio2.1.exe esercizio2.2.exe seed.out
