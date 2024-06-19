# Compiler settings
CC = mpicxx
CFLAGS = -Wall -O3 --std=c++11

# Rules for executables
esercizio10.1.exe: esercizio10.1.o random.o ingiro.o
	$(CC) esercizio10.1.o random.o ingiro.o -o $@ $(LIBS) $(INCS)

esercizio10.2.exe: esercizio10.2.o random.o ingiro.o
	$(CC) esercizio10.2.o random.o ingiro.o -o $@ $(LIBS) $(INCS)

# Rules for object files
esercizio10.1.o: esercizio10.1.cpp
	$(CC) -c esercizio10.1.cpp -o $@ $(CFLAGS) $(INCS)

esercizio10.2.o: esercizio10.2.cpp
	$(CC) -c esercizio10.2.cpp -o $@ $(CFLAGS) $(INCS)

random.o: random.cpp random.h
	$(CC) -c random.cpp -o $@ $(CFLAGS) $(INCS)

ingiro.o: ingiro.cpp ingiro.h
	$(CC) -c ingiro.cpp -o $@ $(CFLAGS) $(INCS)

# Rule to build all
all: esercizio10.1.exe esercizio10.2.exe

# Clean rule
clean:
	rm -f *.o *.exe seed.out

.PHONY: all clean
