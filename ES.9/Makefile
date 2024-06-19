# Compiler settings
CC = g++
CFLAGS = -Wall -O3 --std=c++11
LIBS := $(shell root-config --libs)
INCS := $(shell root-config --cflags)

# Rules for executables
esercizio9.exe: esercizio9.o random.o ingiro.o
	$(CC) esercizio9.o random.o ingiro.o -o $@ $(LIBS) $(INCS)


# Rules for object files
esercizio9.o: esercizio9.cpp ingiro.h
	$(CC) -c esercizio9.cpp -o $@ $(CFLAGS) $(INCS)


random.o: random.cpp random.h
	$(CC) -c random.cpp -o $@ $(CFLAGS) $(INCS)

ingiro.o: ingiro.cpp ingiro.h
	$(CC) -c ingiro.cpp -o $@ $(CFLAGS) $(INCS)

# Rule to build all
all: esercizio9.exe 

# Clean rule
clean:
	rm -f *.o esercizio9.exe seed.out

.PHONY: all clean
