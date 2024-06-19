# Nome del compilatore
CC = g++

# Opzioni di compilazione
CFLAGS = -Wall -O3 --std=c++11

# File di output
all: esercizio1.1.exe esercizio1.2.exe esercizio1.3.exe

# Regola per creare l'eseguibile 1.1
esercizio1.1.exe: esercizio1.1.o random.o function.o
	$(CC) random.o function.o esercizio1.1.o -o esercizio1.1.exe

# Regola per creare l'eseguibile 1.2
esercizio1.2.exe: esercizio1.2.o random.o function.o
	$(CC) random.o function.o esercizio1.2.o -o esercizio1.2.exe

# Regola per creare l'eseguibile 1.3
esercizio1.3.exe: esercizio1.3.o random.o function.o
	$(CC) random.o function.o esercizio1.3.o -o esercizio1.3.exe

# Regole per creare i file oggetto
esercizio1.1.o: esercizio1.1.cpp random.h function.h
	$(CC) -c esercizio1.1.cpp -o esercizio1.1.o $(CFLAGS)

esercizio1.2.o: esercizio1.2.cpp random.h function.h
	$(CC) -c esercizio1.2.cpp -o esercizio1.2.o $(CFLAGS)

esercizio1.3.o: esercizio1.3.cpp random.h function.h
	$(CC) -c esercizio1.3.cpp -o esercizio1.3.o $(CFLAGS)

random.o: random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

function.o: function.cpp function.h
	$(CC) -c function.cpp -o function.o $(CFLAGS)

# Regola per pulire i file generati
clean:
	rm -f *.o esercizio1.1.exe esercizio1.2.exe esercizio1.3.exe
