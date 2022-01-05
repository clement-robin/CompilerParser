# Auteurs : Clement ROBIN & Lucas DESHAYES 

CC=gcc
OPTIONS=-Wall
DOSSIER=sources
MAIN=parser.c
EXE=LRanalyzer
POINTH=$(DOSSIER)/LRGrammar.h $(DOSSIER)/read_file.h outils.h arbre.h
COMPILATION=$(DOSSIER)/LRGrammar.o $(DOSSIER)/read_file.o outils.o arbre.o

all: $(COMPILATION)
	@$(CC) $(OPTIONS) $(MAIN) $(COMPILATION) -o $(EXE)

%.o: %.c $(POINTH)
	@$(CC) -c -o $@ $<

clean:
	rm $(DOSSIER)/*.o
	rm *.o
	rm $(EXE)