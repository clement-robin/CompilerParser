CC=gcc
OPTS=-Wall
FOLDER=sources
MAIN=main.c
EXE=LRanalyzer
DEPS=$(FOLDER)/LRGrammar.h $(FOLDER)/read_file.h
PRECOMP=$(FOLDER)/LRGrammar.o $(FOLDER)/read_file.o

all: $(PRECOMP)
	@$(CC) $(OPT) $(MAIN) $(PRECOMP) -o $(EXE)
	@if [ -e $(EXE) ]; then echo 'Compilation effectue\nlancement : ./$(EXE)'; fi

%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $<

clean:
	rm $(FOLDER)/*.o
	rm $(EXE)