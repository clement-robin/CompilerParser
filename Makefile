# Author : Clement ROBIN & Lucas DESHAYES 

CC=gcc
OPTS=-Wall
FOLDER=sources
MAIN=parser.c
EXE=LRanalyzer
DEPS=$(FOLDER)/LRGrammar.h $(FOLDER)/read_file.h outils.h
PRECOMP=$(FOLDER)/LRGrammar.o $(FOLDER)/read_file.o outils.o

all: $(PRECOMP)
	@$(CC) $(OPT) $(MAIN) $(PRECOMP) -o $(EXE)
	@if [ -e $(EXE) ]; then echo 'Compilation réussi\nExecuter avec : ./$(EXE) + fichier SLR + mot'; fi

%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $<

clean:
	rm $(FOLDER)/*.o
	rm *.o
	rm $(EXE)