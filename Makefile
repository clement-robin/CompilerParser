# Auteurs : Clement ROBIN & Lucas DESHAYES 

CC=gcc
OPTIONS=-Wall
DOSSIER=sources
MAIN=$(DOSSIER)/parser.c
EXE=LRanalyzer
POINTH=$(DOSSIER)/LRGrammar.h $(DOSSIER)/read_file.h $(DOSSIER)/outils.h $(DOSSIER)/arbre.h
COMPILATION=$(DOSSIER)/LRGrammar.o $(DOSSIER)/read_file.o $(DOSSIER)/outils.o $(DOSSIER)/arbre.o

all: $(COMPILATION)
	@$(CC) $(OPTIONS) $(MAIN) $(COMPILATION) -o $(EXE)

%.o: %.c $(POINTH)
	@$(CC) -c -o $@ $<

clean:
	rm $(DOSSIER)/*.o
	rm $(EXE)