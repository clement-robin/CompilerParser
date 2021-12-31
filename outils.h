/* Author : Clement ROBIN & Lucas DESHAYES */

#ifndef OUTILS
#define OUTILS

#include "sources/read_file.h"
#include "sources/LRGrammar.h"




/******* Fonctions d'affichage ******/

void affichage_debut(int tailleMot);
void affichage_ligne(char * val, char * flot, char * pile,int tailleMot);

/******* Fonctions de changement de chaines ******/

char * ajoutDebutDeChaine(char * chaine, char caractere);
char * ajoutFinDeChaine(char * chaine, char caractere);
char * encadrerChaine(char * chaine, char caractere);


#endif