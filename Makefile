CC=cc
CFLAGS= -Wall
EXE=compil

all: grammaire.o
	rm -f $(EXE)
	$(CC) $(CFLAGS) grammaire.o -o $(EXE)

exe: grammaire.o
	clear
	./$(EXE)

graph.o: grammaire.cpp grammaire.h
	$(CC) $(CFLAGS) -c graph.cpp

clean:
	rm -f *.o
	rm -f $(EXE)