# Auteurs : Clement ROBIN & Lucas DESHAYES 

DOSSIER=sources
MAIN=$(DOSSIER)/parser.c
EXE=LRanalyzer
HEADERS=$(DOSSIER)/LRGrammar.h $(DOSSIER)/read_file.h $(DOSSIER)/outils.h $(DOSSIER)/arbre.h
PRECOMPILATION=$(DOSSIER)/LRGrammar.o $(DOSSIER)/read_file.o $(DOSSIER)/outils.o $(DOSSIER)/arbre.o

all: $(PRECOMPILATION)
	@ gcc -Wall $(MAIN) $(PRECOMPILATION) -o $(EXE)

%.o: %.c $(HEADERS)
	@ gcc -c -o $@ $<

clean:
	rm $(DOSSIER)/*.o
	rm $(EXE)